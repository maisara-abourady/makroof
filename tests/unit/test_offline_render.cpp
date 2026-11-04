// sim::renderOffline, the reference renderer: stub bit-identity, and both convolution methods
// against a naive textbook convolution written out here.
#include "ContractFixtures.h"
#include "contract/Parse.h"
#include "sim/Engine.h"
#include "sim/OfflineRender.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <cmath>
#include <cstring>
#include <limits>
#include <random>
#include <stdexcept>

namespace {

sim::MultiChannel randomStereo(std::size_t frames, std::uint32_t seed)
{
    std::mt19937 rng(seed);
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
    sim::MultiChannel audio(2, std::vector<float>(frames));
    for (auto& channel : audio)
        for (auto& v : channel)
            v = dist(rng);
    return audio;
}

bool bitIdentical(const std::vector<float>& a, const std::vector<float>& b)
{
    return a.size() == b.size() && std::memcmp(a.data(), b.data(), a.size() * sizeof(float)) == 0;
}

// y[n] = sum_k h[k] x[n-k], written the textbook way (no skipping, ascending k), in long double.
std::vector<long double> naiveConvolve(const std::vector<float>& x, const std::vector<float>& h)
{
    std::vector<long double> y(x.size() + h.size() - 1, 0.0L);
    for (std::size_t n = 0; n < y.size(); ++n)
        for (std::size_t k = 0; k < h.size(); ++k)
            if (n >= k && n - k < x.size())
                y[n] += static_cast<long double>(h[k]) * static_cast<long double>(x[n - k]);
    return y;
}

// Largest |a - b| relative to the peak of |b|, in dB.
double errorDb(const std::vector<double>& a, const std::vector<long double>& b)
{
    REQUIRE(a.size() == b.size());
    long double peak = 0.0L, err = 0.0L;
    for (std::size_t i = 0; i < a.size(); ++i)
    {
        peak = std::max(peak, std::fabs(b[i]));
        err = std::max(err, std::fabs(static_cast<long double>(a[i]) - b[i]));
    }
    if (!(err > 0.0L))
        return -std::numeric_limits<double>::infinity();
    return 20.0 * std::log10(static_cast<double>(err / peak));
}

} // namespace

TEST_CASE("stub render of random stereo input is bit-identical to the input", "[sim][render]")
{
    const auto parsed = contract::parseScene(
        contract_fixtures::read(contract_fixtures::scenesDir() / "valid" / "medium_room.json"));
    REQUIRE(parsed.ok());
    const sim::RoomIR ir = sim::buildRoomIR(*parsed.scene, {48000.0, sim::BuildOptions::Kind::Binaural});

    auto input = randomStereo(48000 * 2 + 17, 20261104u);
    // Special values must survive too: signed zero, subnormals, extremes, and non-finite values.
    input[0][0] = -0.0f;
    input[1][1] = std::numeric_limits<float>::denorm_min();
    input[0][2] = -std::numeric_limits<float>::max();
    input[1][3] = std::numeric_limits<float>::infinity();
    input[0][4] = std::numeric_limits<float>::quiet_NaN();

    const auto method = GENERATE(sim::ConvolutionMethod::Auto, sim::ConvolutionMethod::Direct);
    const sim::MultiChannel output = sim::renderOffline(ir, input, method);
    REQUIRE(output.size() == 2);
    CHECK(bitIdentical(output[0], input[0]));
    CHECK(bitIdentical(output[1], input[1]));
}

TEST_CASE("direct and FFT convolution match a naive convolution", "[sim][render]")
{
    std::mt19937 rng(7);
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
    const std::size_t xLength = GENERATE(1u, 2u, 37u, 1000u, 4801u);
    const std::size_t hLength = GENERATE(1u, 3u, 64u, 513u, 2048u);

    std::vector<float> x(xLength), h(hLength);
    for (auto& v : x)
        v = dist(rng);
    for (auto& v : h)
        v = dist(rng);
    const auto reference = naiveConvolve(x, h);

    // Both sum in double (the products of two floats are exact in double), so the error is double
    // rounding: around -300 dB for Direct, a little more for the FFT (grows with log2 N). The bounds
    // (1e-12 and 1e-10 of the peak) are still far below what a float32 output can show (~-150 dB).
    // On MSVC long double is double, so the reference has double rounding error too.
    CHECK(errorDb(sim::convolve(x, h, sim::ConvolutionMethod::Direct), reference) < -240.0);
    CHECK(errorDb(sim::convolve(x, h, sim::ConvolutionMethod::Fft), reference) < -200.0);
}

TEST_CASE("renderOffline mixes the emitter x output matrix", "[sim][render]")
{
    sim::RoomIR ir;
    ir.sampleRate = 48000.0;
    ir.numEmitters = 2;
    ir.numOutputs = 2;
    // e0->o0: delay 2, e0->o1: gain 0.5, e1->o0: -1 at 1, e1->o1: 0.25 at 0 and 3.
    ir.taps = {{0, 0, 1, 0}, {0.5f, 0, 0, 0}, {0, -1, 0, 0}, {0.25f, 0, 0, 0.25f}};
    const sim::MultiChannel input = {{1.0f, 2.0f}, {4.0f, 8.0f}};

    const auto method = GENERATE(sim::ConvolutionMethod::Direct, sim::ConvolutionMethod::Fft);
    const auto out = sim::renderOffline(ir, input, method);
    REQUIRE(out.size() == 2);
    REQUIRE(out[0].size() == 5);
    const std::vector<float> expect0{0.0f, -4.0f, 1.0f - 8.0f, 2.0f, 0.0f};
    const std::vector<float> expect1{0.5f + 1.0f, 1.0f + 2.0f, 0.0f, 1.0f, 2.0f};
    for (std::size_t n = 0; n < 5; ++n)
    {
        CHECK(std::fabs(out[0][n] - expect0[n]) < 1e-6f);
        CHECK(std::fabs(out[1][n] - expect1[n]) < 1e-6f);
    }
}

TEST_CASE("renderOffline is deterministic", "[sim][render]")
{
    sim::RoomIR ir;
    ir.numEmitters = 2;
    ir.numOutputs = 2;
    const auto taps = randomStereo(3000, 99);
    ir.taps = {taps[0], taps[1], taps[1], taps[0]};
    const auto input = randomStereo(30000, 5);
    const auto a = sim::renderOffline(ir, input);
    const auto b = sim::renderOffline(ir, input);
    CHECK(bitIdentical(a[0], b[0]));
    CHECK(bitIdentical(a[1], b[1]));
}

TEST_CASE("renderOffline rejects mismatched inputs", "[sim][render]")
{
    sim::RoomIR ir;
    ir.numEmitters = 2;
    ir.numOutputs = 2;
    ir.taps = {{1.0f}, {0.0f}, {0.0f}, {1.0f}};
    CHECK_THROWS_AS(sim::renderOffline(ir, sim::MultiChannel{{1.0f}}), std::invalid_argument);
    CHECK_THROWS_AS(sim::renderOffline(ir, sim::MultiChannel{{1.0f}, {1.0f, 2.0f}}), std::invalid_argument);
    ir.taps[3] = {1.0f, 0.0f};
    CHECK_THROWS_AS(sim::renderOffline(ir, sim::MultiChannel{{1.0f}, {1.0f}}), std::invalid_argument);
    // Empty input: empty output channels.
    ir.taps[3] = {1.0f};
    const auto out = sim::renderOffline(ir, sim::MultiChannel{{}, {}});
    REQUIRE(out.size() == 2);
    CHECK(out[0].empty());
}

TEST_CASE("Auto picks direct for sparse or small work and FFT for long dense IRs", "[sim][render]")
{
    CHECK(sim::chooseMethod(48000 * 600, 1, 1) == sim::ConvolutionMethod::Direct);
    CHECK(sim::chooseMethod(48000 * 600, 500000, 64) == sim::ConvolutionMethod::Direct);
    CHECK(sim::chooseMethod(1000, 2000, 2000) == sim::ConvolutionMethod::Direct);
    CHECK(sim::chooseMethod(48000 * 10, 48000 * 3, 48000 * 3) == sim::ConvolutionMethod::Fft);
}
