// Phase-07c-1 condition 11 (A11): the host-trace instrument (src/plugin/core/HostTrace.h). The ring is
// bounded, lock-free and allocation-free on push (the real-time path), safe with several producer threads
// (TSan: the [pipeline] tag runs in the tsan job), drops and counts when full, and the drain thread writes
// one line per record off the producers' threads. The plugin's own processBlock with the trace compiled in is
// checked by "[plugin][alloc]" in the host-trace CI job (SPATIAL_HOST_TRACE=ON).
#include "AllocationTracker.h"
#include "plugin/core/HostTrace.h"

#include <catch2/catch_test_macros.hpp>

#include <atomic>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <string>
#include <thread>
#include <vector>

using namespace plugin::trace;

static_assert(std::atomic<std::size_t>::is_always_lock_free, "the trace ring's counters must be lock-free");

TEST_CASE("Host trace: the ring pushes and pops in order and drops when full", "[pipeline][host-trace]")
{
    Ring ring(8);
    Record r;
    for (int i = 0; i < 8; ++i)
    {
        r.argument = i;
        REQUIRE(ring.push(r));
    }
    REQUIRE_FALSE(ring.push(r)); // full: dropped, never blocks
    REQUIRE(ring.dropped() == 1);
    for (int i = 0; i < 8; ++i)
    {
        Record out;
        REQUIRE(ring.pop(out));
        REQUIRE(out.argument == i);
    }
    Record out;
    REQUIRE_FALSE(ring.pop(out));
    REQUIRE_THROWS(Ring(6)); // not a power of two
}

TEST_CASE("Host trace: a push and a timed scope allocate nothing (the real-time path)",
          "[pipeline][host-trace]")
{
    const auto path = (std::filesystem::temp_directory_path() / "spatial_host_trace_alloc.txt").string();
    {
        Logger logger(path, 1024);
        std::size_t allocs = 0, frees = 0;
        {
            test_support::ScopedTracking tracking;
            for (int i = 0; i < 100; ++i)
            {
                const Scope scope(&logger, Entry::ProcessBlock, false, Transport::Playing, 256);
                Record r;
                r.entry = Entry::Reset;
                logger.push(r);
            }
            const Scope none(nullptr, Entry::ProcessBlock, false, Transport::Unknown, 0); // trace off: no-op
            allocs = tracking.allocations();
            frees = tracking.deallocations();
        }
        if (test_support::trackerActive())
        {
            REQUIRE(allocs == 0);
            REQUIRE(frees == 0);
        }
    }
    std::filesystem::remove(path);
}

TEST_CASE("Host trace: several producer threads and the drain thread (TSan); every record is written once",
          "[pipeline][host-trace]")
{
    const auto path = (std::filesystem::temp_directory_path() / "spatial_host_trace_mp.txt").string();
    constexpr int kThreads = 4;
    constexpr int kPerThread = 2000;
    std::uint64_t dropped = 0;
    {
        Logger logger(path, 1u << 14);
        std::vector<std::thread> producers;
        for (int t = 0; t < kThreads; ++t)
            producers.emplace_back([&, t] {
                for (int i = 0; i < kPerThread; ++i)
                {
                    const Scope scope(&logger, t == 0 ? Entry::ProcessBlock : Entry::SetState, t == 1,
                                      Transport::Unknown, i, t);
                }
            });
        for (auto& p : producers)
            p.join();
        // The destructor drains what is left.
        dropped = logger.dropped();
    }
    std::ifstream in(path);
    std::string line;
    std::uint64_t lines = 0;
    bool sawDroppedLine = false;
    while (std::getline(in, line))
    {
        if (line.rfind("# dropped", 0) == 0)
            sawDroppedLine = true;
        else if (!line.empty() && line[0] != '#')
            ++lines;
    }
    REQUIRE(sawDroppedLine);
    in.close(); // Windows refuses to remove a file that is still open
    REQUIRE(lines + dropped == static_cast<std::uint64_t>(kThreads * kPerThread));
    std::filesystem::remove(path);
}
