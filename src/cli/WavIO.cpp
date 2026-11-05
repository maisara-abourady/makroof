#include "cli/WavIO.h"

// dr_wav's include directory is SYSTEM (cmake/SpatialDependencies.cmake), which hides its warnings
// on GCC/Clang and with /external:W0 on MSVC; the pragma covers older MSVC behaviour as well.
#if defined(_MSC_VER)
#pragma warning(push, 0)
#endif
#define DR_WAV_IMPLEMENTATION
#include <dr_wav.h>
#if defined(_MSC_VER)
#pragma warning(pop)
#endif

#include <limits>
#include <memory>

namespace cli {

namespace {

struct WavCloser
{
    void operator()(drwav* wav) const noexcept
    {
        drwav_uninit(wav);
        delete wav;
    }
};
using WavHandle = std::unique_ptr<drwav, WavCloser>;

// dr_wav takes char paths; on Windows it treats them as UTF-8 only through the wide-char entry
// points, so use those there.
bool openRead(drwav& wav, const std::filesystem::path& path)
{
#if defined(_WIN32)
    return drwav_init_file_w(&wav, path.c_str(), nullptr) == DRWAV_TRUE;
#else
    return drwav_init_file(&wav, path.c_str(), nullptr) == DRWAV_TRUE;
#endif
}

bool openWrite(drwav& wav, const std::filesystem::path& path, const drwav_data_format& format)
{
#if defined(_WIN32)
    return drwav_init_file_write_w(&wav, path.c_str(), &format, nullptr) == DRWAV_TRUE;
#else
    return drwav_init_file_write(&wav, path.c_str(), &format, nullptr) == DRWAV_TRUE;
#endif
}

} // namespace

bool readWav(const std::filesystem::path& path, Audio& audio, std::string& error)
{
    auto* raw = new drwav{};
    if (!openRead(*raw, path))
    {
        delete raw;
        error = "cannot open or decode WAV file '" + path.string() + "'";
        return false;
    }
    WavHandle wav(raw);

    const std::uint32_t numChannels = wav->channels;
    const drwav_uint64 numFrames = wav->totalPCMFrameCount;
    if (numChannels == 0)
    {
        error = "WAV file '" + path.string() + "' has no channels";
        return false;
    }
    if (numFrames > std::numeric_limits<std::size_t>::max() / numChannels)
    {
        error = "WAV file '" + path.string() + "' is too large";
        return false;
    }

    std::vector<float> interleaved(static_cast<std::size_t>(numFrames) * numChannels);
    const drwav_uint64 read = drwav_read_pcm_frames_f32(wav.get(), numFrames, interleaved.data());
    if (read != numFrames)
    {
        error = "WAV file '" + path.string() + "' is truncated (read " + std::to_string(read) + " of "
                + std::to_string(numFrames) + " frames)";
        return false;
    }

    audio.sampleRate = wav->sampleRate;
    audio.channels.assign(numChannels, std::vector<float>(static_cast<std::size_t>(numFrames)));
    for (std::size_t frame = 0; frame < numFrames; ++frame)
        for (std::uint32_t c = 0; c < numChannels; ++c)
            audio.channels[c][frame] = interleaved[frame * numChannels + c];
    return true;
}

bool writeWavFloat32(const std::filesystem::path& path, const Audio& audio, std::string& error)
{
    if (audio.channels.empty())
    {
        error = "nothing to write to '" + path.string() + "' (no channels)";
        return false;
    }
    const std::size_t numChannels = audio.channels.size();
    const std::size_t numFrames = audio.numFrames();
    for (const auto& channel : audio.channels)
        if (channel.size() != numFrames)
        {
            error = "internal error: channels of different lengths";
            return false;
        }

    drwav_data_format format{};
    format.container = drwav_container_riff;
    format.format = DR_WAVE_FORMAT_IEEE_FLOAT;
    format.channels = static_cast<drwav_uint32>(numChannels);
    format.sampleRate = audio.sampleRate;
    format.bitsPerSample = 32;

    auto* raw = new drwav{};
    if (!openWrite(*raw, path, format))
    {
        delete raw;
        error = "cannot open '" + path.string() + "' for writing";
        return false;
    }
    WavHandle wav(raw);

    std::vector<float> interleaved(numFrames * numChannels);
    for (std::size_t frame = 0; frame < numFrames; ++frame)
        for (std::size_t c = 0; c < numChannels; ++c)
            interleaved[frame * numChannels + c] = audio.channels[c][frame];

    const drwav_uint64 written = drwav_write_pcm_frames(wav.get(), numFrames, interleaved.data());
    if (written != numFrames)
    {
        error = "failed writing '" + path.string() + "' (disk full?)";
        return false;
    }
    return true;
}

} // namespace cli
