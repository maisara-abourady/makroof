#include "contract/Validate.h"

#include <nlohmann/json.hpp>

#include <array>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <string>

namespace contract {

namespace {

// For messages: %.15g when that reads back to the same double (so 0.005 prints as "0.005"),
// otherwise all 17 significant digits.
std::string formatNumber(double value)
{
    std::array<char, 32> buffer{};
    std::snprintf(buffer.data(), buffer.size(), "%.15g", value);
    if (std::strtod(buffer.data(), nullptr) != value)
        std::snprintf(buffer.data(), buffer.size(), "%.17g", value);
    return buffer.data();
}

std::string indexed(const std::string& path, std::size_t index)
{
    return path + "[" + std::to_string(index) + "]";
}

// NaN fails every comparison, so it is out of range too.
bool inRange(double value, double lo, double hi) noexcept
{
    return value >= lo && value <= hi;
}

class Validator
{
public:
    explicit Validator(std::vector<Issue>& issues)
        : issues_(issues)
    {}

    void add(IssueCode code, std::string path, std::string message)
    {
        issues_.push_back(Issue{code, std::move(path), std::move(message)});
    }

    void checkRange(double value, double lo, double hi, IssueCode code, const std::string& path,
                    std::string_view what, std::string_view unit = {})
    {
        if (!inRange(value, lo, hi))
        {
            add(code, path,
                std::string{what} + " must be in [" + formatNumber(lo) + ", " + formatNumber(hi) + "]"
                    + std::string{unit} + ", got " + formatNumber(value));
        }
    }

    void run(const SceneDescription& scene)
    {
        checkVersion(scene.contractVersion);
        const bool roomOk = checkRoom(scene.room);
        const bool listenerOk = roomOk
                                && checkClearance(scene.listener.position, scene.room.geometry.dimensions,
                                                  "listener.position",
                                                  IssueCode::E_LISTENER_SURFACE_CLEARANCE, "the listener");
        checkEmitters(scene, roomOk, listenerOk);
        checkRender(scene.render);
        checkExtensions(scene.extensionsJson);
    }

private:
    void checkVersion(ContractVersion version)
    {
        if (version.majorVersion != kContractVersionMajor)
        {
            add(IssueCode::E_VERSION_MAJOR, "contractVersion",
                "major version " + std::to_string(version.majorVersion)
                    + " is not supported (this build reads " + std::to_string(kContractVersionMajor) + ".x)");
        }
        else if (version.minorVersion > kContractVersionMinor)
        {
            add(IssueCode::W_VERSION_MINOR_NEWER, "contractVersion",
                "version " + toString(version) + " is newer than " + kContractVersion
                    + "; fields this build does not know are ignored");
        }
    }

    // Returns true when the room is usable for the geometric checks that follow.
    bool checkRoom(const Room& room)
    {
        bool ok = true;
        if (room.geometry.kind != GeometryKind::shoebox)
        {
            add(IssueCode::E_GEOMETRY_KIND, "room.geometry.kind", "only \"shoebox\" is supported in v1");
            ok = false;
        }
        const std::array<double, 3> dims{room.geometry.dimensions.x, room.geometry.dimensions.y,
                                         room.geometry.dimensions.z};
        for (std::size_t i = 0; i < dims.size(); ++i)
        {
            if (!inRange(dims[i], limits::kRoomDimensionMinM, limits::kRoomDimensionMaxM))
            {
                checkRange(dims[i], limits::kRoomDimensionMinM, limits::kRoomDimensionMaxM,
                           IssueCode::E_ROOM_DIMENSION_RANGE, indexed("room.geometry.dimensions", i),
                           "room dimension", " m");
                ok = false;
            }
        }
        for (const SurfaceId id : kAllSurfaces)
        {
            const SurfaceMaterial& material = room.surface(id);
            const std::string base = "room.surfaces." + std::string{surfaceName(id)};
            for (std::size_t band = 0; band < kNumOctaveBands; ++band)
            {
                checkRange(material.bandsAbsorption[band], limits::kAbsorptionMin, limits::kAbsorptionMax,
                           IssueCode::E_ABSORPTION_RANGE, indexed(base + ".absorption", band), "absorption");
            }
            checkRange(material.scattering, limits::kScatteringMin, limits::kScatteringMax,
                       IssueCode::E_SCATTERING_RANGE, base + ".scattering", "scattering");
        }
        return ok;
    }

    // AX6: inside the room and at least kSurfaceClearanceM from every surface. Returns false (after
    // reporting one issue) when the position violates it.
    bool checkClearance(const Vec3& position, const Vec3& dims, const std::string& path, IssueCode code,
                        std::string_view who)
    {
        const double c = limits::kSurfaceClearanceM - limits::kGeometryToleranceM;
        const std::array<double, 3> p{position.x, position.y, position.z};
        const std::array<double, 3> d{dims.x, dims.y, dims.z};
        const std::array<const char*, 3> axis{"x", "y", "z"};
        for (std::size_t i = 0; i < 3; ++i)
        {
            if (!(p[i] >= c && p[i] <= d[i] - c))
            {
                add(code, indexed(path, i),
                    std::string{who} + " must be inside the room at least 0.1 m from every surface: "
                        + axis[i] + " must be in [0.1, " + formatNumber(d[i] - limits::kSurfaceClearanceM)
                        + "] m, got " + formatNumber(p[i]));
                return false; // one issue per position
            }
        }
        return true;
    }

    // The distance to the listener is checked only when both positions are inside the room, so
    // one misplaced object gives one issue.
    void checkEmitters(const SceneDescription& scene, bool roomOk, bool listenerOk)
    {
        const auto& emitters = scene.emitters;
        // AX7: exactly two emitters, L and R, on channels 0 and 1. When the count is wrong the
        // id/channel set rules are not checked, so one mistake gives one issue.
        const bool countOk = emitters.size() == limits::kEmitterCount;
        if (!countOk)
        {
            add(IssueCode::E_EMITTER_COUNT, "emitters",
                "v1 needs exactly 2 emitters (L and R), got " + std::to_string(emitters.size()));
        }
        std::array<bool, 2> idSeen{false, false};
        std::array<bool, 2> channelSeen{false, false};
        for (std::size_t i = 0; i < emitters.size(); ++i)
        {
            const Emitter& e = emitters[i];
            const std::string base = indexed("emitters", i);
            if (e.id != "L" && e.id != "R")
            {
                add(IssueCode::E_EMITTER_ID, base + ".id", "id must be \"L\" or \"R\", got \"" + e.id + "\"");
            }
            else if (countOk)
            {
                bool& seen = idSeen[e.id == "L" ? 0 : 1];
                if (seen)
                    add(IssueCode::E_EMITTER_ID, base + ".id", "id \"" + e.id + "\" is used by two emitters");
                seen = true;
            }
            if (e.channel != 0 && e.channel != 1)
            {
                add(IssueCode::E_EMITTER_CHANNEL, base + ".channel",
                    "channel must be 0 or 1, got " + std::to_string(e.channel));
            }
            else if (countOk)
            {
                bool& seen = channelSeen[static_cast<std::size_t>(e.channel)];
                if (seen)
                    add(IssueCode::E_EMITTER_CHANNEL, base + ".channel",
                        "channel " + std::to_string(e.channel) + " is used by two emitters");
                seen = true;
            }
            checkRange(e.gainDb, limits::kGainDbMin, limits::kGainDbMax, IssueCode::E_GAIN_RANGE,
                       base + ".gainDb", "gainDb", " dB");
            if (!roomOk)
                continue;
            if (!checkClearance(e.position, scene.room.geometry.dimensions, base + ".position",
                                IssueCode::E_EMITTER_SURFACE_CLEARANCE, "an emitter")
                || !listenerOk)
                continue;
            const double dx = e.position.x - scene.listener.position.x;
            const double dy = e.position.y - scene.listener.position.y;
            const double dz = e.position.z - scene.listener.position.z;
            const double distance = std::sqrt(dx * dx + dy * dy + dz * dz);
            if (!(distance >= limits::kEmitterListenerMinDistanceM - limits::kGeometryToleranceM))
            {
                add(IssueCode::E_EMITTER_TOO_CLOSE_TO_LISTENER, base + ".position",
                    "an emitter must be at least 0.3 m from the listener, got " + formatNumber(distance)
                        + " m");
            }
        }
    }

    void checkRender(const RenderSettings& render)
    {
        if (render.outputMode != OutputMode::binaural && render.outputMode != OutputMode::stereoSpeakers)
            add(IssueCode::E_OUTPUT_MODE, "render.outputMode",
                "outputMode must be binaural or stereoSpeakers");
        if (render.hrtfId != kHrtfIdGenericV1)
        {
            add(IssueCode::E_HRTF_ID, "render.hrtfId",
                "v1 supports only hrtfId \"generic-v1\", got \"" + render.hrtfId + "\"");
        }
        if (render.maxReflectionOrder < limits::kMaxReflectionOrderMin
            || render.maxReflectionOrder > limits::kMaxReflectionOrderMax)
        {
            add(IssueCode::E_REFLECTION_ORDER_RANGE, "render.maxReflectionOrder",
                "maxReflectionOrder must be an integer in [0, 60], got "
                    + std::to_string(render.maxReflectionOrder));
        }
        // tailSeed: every std::uint32_t is valid.
    }

    void checkExtensions(const std::string& text)
    {
        const auto parsed = nlohmann::ordered_json::parse(text, nullptr, false);
        if (parsed.is_discarded() || !parsed.is_object())
            add(IssueCode::E_EXTENSIONS, "extensions", "extensions must be the text of a JSON object");
    }

    std::vector<Issue>& issues_;
};

} // namespace

ValidationResult validate(const SceneDescription& scene)
{
    ValidationResult result;
    Validator{result.issues}.run(scene);
    return result;
}

} // namespace contract
