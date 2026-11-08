#pragma once

// Helpers for the Phase 07 pipeline tests: an injectable builder clock (AX33), waiting with a real-time
// limit, scene fixtures, and the analytic crossfade reference of the switch-rule nulls (D7: the Phase 06
// technique, out(t) = (1 - g) (x*A)(t - P) + g (x*B)(t - P) for equal gain, cos/sin for equal power).
#include "ContractFixtures.h"
#include "ConvTestUtil.h"

#include "contract/Json.h"
#include "plugin/core/IrBuilderThread.h"
#include "plugin/core/ScenePipeline.h"
#include "sim/OfflineRender.h"

#include <catch2/catch_test_macros.hpp>

#include <atomic>
#include <chrono>
#include <cmath>
#include <condition_variable>
#include <functional>
#include <limits>
#include <mutex>
#include <numbers>
#include <thread>
#include <vector>

namespace pipeline_test {

// A clock that only moves when the test moves it. waitUntil() polls (in real time) for the stop
// condition or the deadline, so a test that advances the time or bumps the work wakes the builder.
class ManualClock final : public plugin::BuilderClock
{
public:
    double now() override { return t_.load(); }
    void waitUntil(std::unique_lock<std::mutex>& lock, std::condition_variable& cv, double deadline,
                   const std::function<bool()>& stop) override
    {
        while (!stop() && t_.load() < deadline)
            cv.wait_for(lock, std::chrono::microseconds(200));
    }
    void set(double t) { t_.store(t); }

private:
    std::atomic<double> t_{0.0};
};

// Polls pred() every millisecond for up to `limit`; returns its last value.
inline bool waitFor(const std::function<bool()>& pred,
                    std::chrono::milliseconds limit = std::chrono::seconds(60))
{
    const auto end = std::chrono::steady_clock::now() + limit;
    while (!pred())
    {
        if (std::chrono::steady_clock::now() > end)
            return pred();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    return true;
}

inline contract::SceneDescription loadScene(const char* name)
{
    auto parsed = contract::fromJson(
        contract_fixtures::read(contract_fixtures::scenesDir() / "valid" / name));
    REQUIRE(parsed.ok());
    return *parsed.scene;
}

// Feeds a pipeline and records its input and output (both channels) from the last prepare()/reset().
struct Recorder
{
    explicit Recorder(plugin::ScenePipeline& p)
        : pipeline(p)
    {}

    plugin::ScenePipeline& pipeline;
    std::vector<float> in[2];
    std::vector<float> out[2];
    std::uint64_t seed = 1;

    void clear()
    {
        for (int c = 0; c < 2; ++c)
        {
            in[c].clear();
            out[c].clear();
        }
    }

    // Processes n samples of seeded noise in blocks of `block`.
    void run(std::size_t n, int block = 256)
    {
        std::vector<float> a = conv_test::noise(n, seed++, 0.2);
        std::vector<float> b = conv_test::noise(n, seed++, 0.2);
        std::size_t pos = 0;
        while (pos < n)
        {
            const int len = static_cast<int>(std::min<std::size_t>(static_cast<std::size_t>(block), n - pos));
            std::vector<float> o0(a.begin() + static_cast<std::ptrdiff_t>(pos),
                                  a.begin() + static_cast<std::ptrdiff_t>(pos) + len);
            std::vector<float> o1(b.begin() + static_cast<std::ptrdiff_t>(pos),
                                  b.begin() + static_cast<std::ptrdiff_t>(pos) + len);
            in[0].insert(in[0].end(), o0.begin(), o0.end());
            in[1].insert(in[1].end(), o1.begin(), o1.end());
            const float* const ip[2] = {o0.data(), o1.data()};
            float* const op[2] = {o0.data(), o1.data()};
            pipeline.process(ip, op, len);
            out[0].insert(out[0].end(), o0.begin(), o0.end());
            out[1].insert(out[1].end(), o1.begin(), o1.end());
            pos += static_cast<std::size_t>(len);
        }
    }

    std::size_t samples() const { return in[0].size(); }
};

inline bool sameIr(const sim::RoomIR& a, const sim::RoomIR& b)
{
    return a.numEmitters == b.numEmitters && a.numOutputs == b.numOutputs && a.taps == b.taps
           && !(a.sampleRate < b.sampleRate) && !(b.sampleRate < a.sampleRate);
}

// One state of the switch-rule chain: the IR that became current with a fade starting at s0 (-1 for the
// IR installed at once), under `law`.
struct Segment
{
    sim::RoomIR ir;
    std::int64_t s0 = -1;
    sim::conv::CrossfadeLaw law = sim::conv::CrossfadeLaw::EqualGain;
};

// The analytic output of the chain on output channel `channel` and its residual in dB against `y`
// (10 log10 of the residual energy over the reference energy, from the first segment's start).
inline double chainResidualDb(const std::vector<float> (&x)[2], const std::vector<float>& y,
                              const std::vector<Segment>& chain, int channel, int partitionSize,
                              int fadeLength)
{
    const std::size_t n = y.size();
    // Full convolutions of the whole input with each IR, delayed by P.
    std::vector<std::vector<double>> conv(chain.size());
    for (std::size_t k = 0; k < chain.size(); ++k)
    {
        const auto& ir = chain[k].ir;
        std::vector<double> acc(n, 0.0);
        for (int e = 0; e < 2; ++e)
        {
            const auto c = sim::convolve(x[e], ir.ir(e, channel), sim::ConvolutionMethod::Auto);
            for (std::size_t t = static_cast<std::size_t>(partitionSize); t < n; ++t)
            {
                const std::size_t src = t - static_cast<std::size_t>(partitionSize);
                if (src < c.size())
                    acc[t] += c[src];
            }
        }
        conv[k] = std::move(acc);
    }
    double err = 0.0, ref = 0.0;
    for (std::size_t t = 0; t < n; ++t)
    {
        // The latest segment whose fade has started by t.
        std::size_t k = 0;
        for (std::size_t j = 1; j < chain.size(); ++j)
            if (static_cast<std::int64_t>(t) >= chain[j].s0)
                k = j;
        double r = conv[k][t];
        if (k > 0 && static_cast<std::int64_t>(t) < chain[k].s0 + fadeLength)
        {
            const double g = static_cast<double>(static_cast<std::int64_t>(t) - chain[k].s0) / fadeLength;
            double gin = g, gout = 1.0 - g;
            if (chain[k].law == sim::conv::CrossfadeLaw::EqualPower)
            {
                gin = std::sin(g * std::numbers::pi / 2.0);
                gout = std::cos(g * std::numbers::pi / 2.0);
            }
            r = gout * conv[k - 1][t] + gin * conv[k][t];
        }
        const double d = static_cast<double>(y[t]) - r;
        err += d * d;
        ref += r * r;
    }
    if (!(err > 0.0))
        return -std::numeric_limits<double>::infinity();
    return 10.0 * std::log10(err / ref);
}

} // namespace pipeline_test
