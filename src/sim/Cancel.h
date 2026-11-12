#pragma once

// Cancellation of a room-IR build (AX39 D6; phase-07c-1 condition 10). A build is cancelled by the
// caller setting an atomic flag it passed in (BuildOptions::cancel); the build checks it at its cancel
// points and throws BuildCancelled, producing nothing. The cancel points (condition 10): image-source
// planning (per emitter), the diffuse solve (between blocks), tail::BandNoiseGenerator (between the
// band-pair transforms and every kCancelCheckSamples samples of its sample loops), the IR assembly
// (every kCancelCheckSamples samples) and the IR-set build (per partition). They also bound every
// quiesce (restore, prepare, release, the destructor) by the time to the next cancel point.
#include <atomic>
#include <cstddef>
#include <stdexcept>

namespace sim {

// Thrown by a build when its cancel flag was set: the caller asked for the build to stop; nothing was
// produced and the caller's state is untouched.
struct BuildCancelled : std::runtime_error
{
    BuildCancelled()
        : std::runtime_error("room IR build cancelled")
    {}
};

// Sample loops check the flag every 2^16 samples (condition 10): ~0.7 ms of a 96 kHz IR, a few hundred
// microseconds of work at most, against one relaxed load per check.
inline constexpr std::size_t kCancelCheckSamples = std::size_t{1} << 16;

// One cancel point. `cancel` may be nullptr (never cancelled).
inline void throwIfCancelled(const std::atomic<bool>* cancel)
{
    if (cancel != nullptr && cancel->load(std::memory_order_acquire))
        throw BuildCancelled();
}

} // namespace sim
