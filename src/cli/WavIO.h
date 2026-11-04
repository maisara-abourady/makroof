#pragma once

// WAV file I/O for render_cli (dr_wav, no JUCE). Reading converts any PCM or float WAV to float32
// samples; writing always produces IEEE float32 WAV, so a float32 input survives a read/write
// cycle bit for bit.
#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>

namespace cli {

struct Audio
{
    std::uint32_t sampleRate = 48000;
    std::vector<std::vector<float>> channels; // one vector per channel, equal lengths

    std::size_t numFrames() const noexcept { return channels.empty() ? 0 : channels.front().size(); }
};

// Returns false and sets `error` when the file can't be opened or decoded.
bool readWav(const std::filesystem::path& path, Audio& audio, std::string& error);

// Writes float32 WAV. Returns false and sets `error` on failure. Channels must have equal lengths
// and there must be at least one.
bool writeWavFloat32(const std::filesystem::path& path, const Audio& audio, std::string& error);

} // namespace cli
