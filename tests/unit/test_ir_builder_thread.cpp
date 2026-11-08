// Phase 07 scope 3: the IR builder thread under AX33 (a minimum spacing of 20 ms between build starts)
// with an injected clock (decider D6): an isolated request starts at once; requests 5 ms apart start
// >= 20 ms apart; the final state is built (no lost wake-up, FR-3D-10).
#include "PipelineTestUtil.h"

#include "plugin/core/IrBuilderThread.h"

#include <catch2/catch_test_macros.hpp>

#include <atomic>
#include <mutex>
#include <vector>

// Exact comparisons are intended (the injected clock's times).
#if defined(__clang__) || defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif

namespace {

struct Harness
{
    pipeline_test::ManualClock clock;
    std::atomic<std::uint64_t> gen{0};
    std::atomic<std::uint64_t> handled{0};
    std::mutex m;
    std::vector<double> starts;
    std::vector<std::uint64_t> builtGens;
    plugin::IrBuilderThread builder{clock, [this] { return gen.load() != handled.load(); },
                                    [this] {
                                        const auto g = gen.load(); // read before the "snapshot"
                                        {
                                            std::lock_guard<std::mutex> lock(m);
                                            starts.push_back(clock.now());
                                            builtGens.push_back(g);
                                        }
                                        handled.store(g);
                                    }};

    // Lets the builder react to the current clock and work, then waits until it rests: either all work
    // is handled, or it waits for its AX33 slot.
    void settle()
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        REQUIRE(pipeline_test::waitFor([this] { return builder.idleOrWaiting(); }));
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
};

} // namespace

TEST_CASE("AX33: an isolated request starts at once; 5 ms requests start >= 20 ms apart; the final "
          "state is built",
          "[pipeline][ax33]")
{
    Harness h;
    h.builder.restart();

    // An isolated request at 0 ms.
    h.clock.set(0.0);
    h.gen.fetch_add(1);
    REQUIRE(pipeline_test::waitFor([&] { return h.handled.load() == h.gen.load(); }));
    {
        std::lock_guard<std::mutex> lock(h.m);
        REQUIRE(h.starts.size() == 1);
        REQUIRE(h.starts[0] == 0.0);
    }

    // Requests every 5 ms from 5 ms to 100 ms.
    for (int k = 1; k <= 20; ++k)
    {
        h.clock.set(0.005 * k);
        h.gen.fetch_add(1);
        h.settle();
    }
    // Let time run on until everything is built.
    for (int k = 21; k <= 40; ++k)
    {
        h.clock.set(0.005 * k);
        h.settle();
    }
    REQUIRE(pipeline_test::waitFor([&] { return h.handled.load() == h.gen.load(); }));
    {
        std::lock_guard<std::mutex> lock(h.m);
        INFO("builds: " << h.starts.size());
        REQUIRE(h.starts.size() >= 5);
        for (std::size_t i = 1; i < h.starts.size(); ++i)
        {
            INFO("start " << i << " at " << h.starts[i] << " s, previous " << h.starts[i - 1] << " s");
            REQUIRE(h.starts[i] - h.starts[i - 1] >= 0.020 - 1e-12);
        }
        REQUIRE(h.builtGens.back() == h.gen.load()); // the final state was built
    }

    // An isolated request long after the last build starts at once.
    h.clock.set(1.0);
    h.settle();
    const auto before = [&] {
        std::lock_guard<std::mutex> lock(h.m);
        return h.starts.size();
    }();
    h.gen.fetch_add(1);
    REQUIRE(pipeline_test::waitFor([&] { return h.handled.load() == h.gen.load(); }));
    std::lock_guard<std::mutex> lock(h.m);
    REQUIRE(h.starts.size() == before + 1);
    REQUIRE(h.starts.back() == 1.0);
}

TEST_CASE("IR builder: quiesce waits for a running build and stops new ones; restart resumes",
          "[pipeline][builder]")
{
    Harness h;
    h.builder.restart();
    h.gen.fetch_add(1);
    REQUIRE(pipeline_test::waitFor([&] { return h.handled.load() == h.gen.load(); }));
    h.builder.quiesce();
    REQUIRE_FALSE(h.builder.accepting());
    REQUIRE_FALSE(h.builder.busy());
    h.clock.set(1.0);
    h.gen.fetch_add(1);
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    REQUIRE(h.handled.load() != h.gen.load()); // quiesced: nothing built
    h.builder.restart();
    REQUIRE(pipeline_test::waitFor([&] { return h.handled.load() == h.gen.load(); }));
}
