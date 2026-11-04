#include "contract/Json.h"

#include <nlohmann/json.hpp>

#include <cmath>
#include <cstdint>
#include <exception>
#include <initializer_list>
#include <limits>
#include <utility>

namespace contract {

namespace {

// ordered_json keeps keys in insertion order: the writer emits specification order and
// "extensions" round-trips with its original key order.
using Json = nlohmann::ordered_json;

std::string child(const std::string& parent, std::string_view key)
{
    return parent.empty() ? std::string{key} : parent + "." + std::string{key};
}

std::string indexed(const std::string& parent, std::size_t index)
{
    return parent + "[" + std::to_string(index) + "]";
}

std::string typeOf(const Json& value)
{
    return value.type_name();
}

// Reads the JSON tree into a SceneDescription, recording every structural problem it finds. Each
// read function returns std::nullopt (or false) after reporting, and reading carries on with the
// next field so a document with several mistakes reports all of them.
class Reader
{
public:
    explicit Reader(std::vector<Issue>& issues)
        : issues_(issues)
    {}

    std::optional<SceneDescription> readScene(const Json& root)
    {
        if (!root.is_object())
        {
            error(IssueCode::E_TYPE, "", "a scene must be a JSON object, got " + typeOf(root));
            return std::nullopt;
        }
        if (!readVersion(root))
            return std::nullopt;

        checkKeys(root, "",
                  {"contractVersion", "units", "room", "listener", "emitters", "render", "extensions"});

        SceneDescription scene;
        scene.contractVersion = kCurrentContractVersion;

        if (const Json* units = field(root, "", "units"))
        {
            if (const auto text = string(*units, "units"); text && *text != "meters")
                error(IssueCode::E_UNITS, "units", "units must be \"meters\", got \"" + *text + "\"");
        }
        if (const Json* room = field(root, "", "room"))
            readRoom(*room, "room", scene.room);
        if (const Json* listener = field(root, "", "listener"))
            readListener(*listener, "listener", scene.listener);
        if (const Json* emitters = field(root, "", "emitters"))
            readEmitters(*emitters, "emitters", scene.emitters);
        if (const Json* render = field(root, "", "render"))
            readRender(*render, "render", scene.render);
        if (const Json* extensions = field(root, "", "extensions"))
        {
            if (extensions->is_object())
                scene.extensionsJson = extensions->dump(-1, ' ', false, Json::error_handler_t::strict);
            else
                error(IssueCode::E_TYPE, "extensions",
                      "extensions must be an object, got " + typeOf(*extensions));
        }

        if (failed_)
            return std::nullopt;
        return scene;
    }

private:
    void error(IssueCode code, std::string path, std::string message)
    {
        issues_.push_back(Issue{code, std::move(path), std::move(message)});
        if (severityOf(code) == Severity::error)
            failed_ = true;
    }

    // contractVersion is read first: it decides how the rest of the document is read.
    bool readVersion(const Json& root)
    {
        const Json* value = field(root, "", "contractVersion");
        if (value == nullptr)
            return false;
        const auto text = string(*value, "contractVersion");
        if (!text)
            return false;
        const auto version = parseContractVersion(*text);
        if (!version)
        {
            error(IssueCode::E_VERSION_FORMAT, "contractVersion",
                  "contractVersion must be \"MAJOR.MINOR\" (e.g. \"1.0\"), got \"" + *text + "\"");
            return false;
        }
        if (version->majorVersion != kContractVersionMajor)
        {
            error(IssueCode::E_VERSION_MAJOR, "contractVersion",
                  "major version " + std::to_string(version->majorVersion)
                      + " is not supported (this build reads " + std::to_string(kContractVersionMajor)
                      + ".x)");
            return false;
        }
        if (version->minorVersion > kContractVersionMinor)
        {
            ignoreUnknownFields_ = true;
            error(IssueCode::W_VERSION_MINOR_NEWER, "contractVersion",
                  "version " + *text + " is newer than " + kContractVersion
                      + "; fields this build does not know were ignored");
        }
        return true;
    }

    // Requires an object; reports unknown keys unless the document is a newer minor version.
    bool object(const Json& value, const std::string& path, std::initializer_list<std::string_view> known)
    {
        if (!value.is_object())
        {
            error(IssueCode::E_TYPE, path, "expected an object, got " + typeOf(value));
            return false;
        }
        checkKeys(value, path, known);
        return true;
    }

    void checkKeys(const Json& value, const std::string& path, std::initializer_list<std::string_view> known)
    {
        if (ignoreUnknownFields_)
            return;
        for (auto it = value.begin(); it != value.end(); ++it)
        {
            bool isKnown = false;
            for (const std::string_view key : known)
                isKnown = isKnown || it.key() == key;
            if (!isKnown)
            {
                error(IssueCode::E_UNKNOWN_FIELD, child(path, it.key()),
                      "unknown field \"" + it.key() + "\" (check the spelling; contract " + kContractVersion
                          + ")");
            }
        }
    }

    const Json* field(const Json& object, const std::string& path, std::string_view key)
    {
        const auto it = object.find(std::string{key});
        if (it == object.end())
        {
            error(IssueCode::E_MISSING_FIELD, child(path, key), "required field is missing");
            return nullptr;
        }
        return &*it;
    }

    std::optional<std::string> string(const Json& value, const std::string& path)
    {
        if (!value.is_string())
        {
            error(IssueCode::E_TYPE, path, "expected a string, got " + typeOf(value));
            return std::nullopt;
        }
        return value.get<std::string>();
    }

    std::optional<double> number(const Json& value, const std::string& path)
    {
        if (!value.is_number())
        {
            error(IssueCode::E_TYPE, path, "expected a number, got " + typeOf(value));
            return std::nullopt;
        }
        return value.get<double>();
    }

    // An integer in [lo, hi]. A float with no fractional part (e.g. 20.0) counts as an integer, as in
    // JSON Schema. Values outside [lo, hi] are reported with rangeCode.
    std::optional<std::int64_t> integer(const Json& value, const std::string& path, std::int64_t lo,
                                        std::int64_t hi, IssueCode rangeCode)
    {
        const auto outOfRange = [&](const std::string& got) {
            error(rangeCode, path,
                  "expected an integer in [" + std::to_string(lo) + ", " + std::to_string(hi) + "], got "
                      + got);
            return std::nullopt;
        };
        if (value.is_number_unsigned())
        {
            const auto v = value.get<std::uint64_t>();
            if (v > static_cast<std::uint64_t>(hi))
                return outOfRange(std::to_string(v));
            return static_cast<std::int64_t>(v);
        }
        if (value.is_number_integer())
        {
            const auto v = value.get<std::int64_t>();
            if (v < lo || v > hi)
                return outOfRange(std::to_string(v));
            return v;
        }
        if (value.is_number_float())
        {
            const double v = value.get<double>();
            if (!std::isfinite(v) || std::trunc(v) != v)
            {
                error(IssueCode::E_TYPE, path, "expected an integer, got " + value.dump());
                return std::nullopt;
            }
            if (v < static_cast<double>(lo) || v > static_cast<double>(hi))
                return outOfRange(value.dump());
            return static_cast<std::int64_t>(v);
        }
        error(IssueCode::E_TYPE, path, "expected an integer, got " + typeOf(value));
        return std::nullopt;
    }

    // A fixed-length array of numbers.
    template <std::size_t N>
    std::optional<std::array<double, N>> numbers(const Json& value, const std::string& path)
    {
        if (!value.is_array())
        {
            error(IssueCode::E_TYPE, path,
                  "expected an array of " + std::to_string(N) + " numbers, got " + typeOf(value));
            return std::nullopt;
        }
        if (value.size() != N)
        {
            error(IssueCode::E_ARRAY_LENGTH, path,
                  "expected exactly " + std::to_string(N) + " values, got " + std::to_string(value.size()));
            return std::nullopt;
        }
        std::array<double, N> out{};
        bool ok = true;
        for (std::size_t i = 0; i < N; ++i)
        {
            if (const auto v = number(value[i], indexed(path, i)))
                out[i] = *v;
            else
                ok = false;
        }
        if (!ok)
            return std::nullopt;
        return out;
    }

    std::optional<Vec3> vec3(const Json& value, const std::string& path)
    {
        const auto v = numbers<3>(value, path);
        if (!v)
            return std::nullopt;
        return Vec3{(*v)[0], (*v)[1], (*v)[2]};
    }

    void readRoom(const Json& value, const std::string& path, Room& room)
    {
        if (!object(value, path, {"geometry", "surfaces"}))
            return;
        if (const Json* geometry = field(value, path, "geometry"))
        {
            const std::string gpath = child(path, "geometry");
            if (object(*geometry, gpath, {"kind", "dimensions"}))
            {
                if (const Json* kind = field(*geometry, gpath, "kind"))
                {
                    if (const auto text = string(*kind, child(gpath, "kind")); text && *text != "shoebox")
                    {
                        error(IssueCode::E_GEOMETRY_KIND, child(gpath, "kind"),
                              "v1 supports only geometry kind \"shoebox\", got \"" + *text + "\"");
                    }
                }
                if (const Json* dims = field(*geometry, gpath, "dimensions"))
                {
                    if (const auto v = vec3(*dims, child(gpath, "dimensions")))
                        room.geometry.dimensions = *v;
                }
            }
        }
        if (const Json* surfaces = field(value, path, "surfaces"))
        {
            const std::string spath = child(path, "surfaces");
            if (object(*surfaces, spath, {"xMin", "xMax", "yMin", "yMax", "floor", "ceiling"}))
            {
                for (const SurfaceId id : kAllSurfaces)
                {
                    if (const Json* surface = field(*surfaces, spath, surfaceName(id)))
                        readSurface(*surface, child(spath, surfaceName(id)), room.surface(id));
                }
            }
        }
    }

    void readSurface(const Json& value, const std::string& path, SurfaceMaterial& material)
    {
        if (!object(value, path, {"absorption", "scattering"}))
            return;
        if (const Json* absorption = field(value, path, "absorption"))
        {
            if (const auto v = numbers<kNumOctaveBands>(*absorption, child(path, "absorption")))
                material.bandsAbsorption = *v;
        }
        if (const Json* scattering = field(value, path, "scattering"))
        {
            if (const auto v = number(*scattering, child(path, "scattering")))
                material.scattering = *v;
        }
    }

    void readListener(const Json& value, const std::string& path, Listener& listener)
    {
        if (!object(value, path, {"position"}))
            return;
        if (const Json* position = field(value, path, "position"))
        {
            if (const auto v = vec3(*position, child(path, "position")))
                listener.position = *v;
        }
    }

    void readEmitters(const Json& value, const std::string& path, std::vector<Emitter>& emitters)
    {
        if (!value.is_array())
        {
            error(IssueCode::E_TYPE, path, "expected an array of emitters, got " + typeOf(value));
            return;
        }
        for (std::size_t i = 0; i < value.size(); ++i)
        {
            const std::string epath = indexed(path, i);
            const Json& item = value[i];
            Emitter emitter;
            if (object(item, epath, {"id", "channel", "position", "gainDb"}))
            {
                if (const Json* id = field(item, epath, "id"))
                {
                    if (const auto v = string(*id, child(epath, "id")))
                        emitter.id = *v;
                }
                if (const Json* channel = field(item, epath, "channel"))
                {
                    // Range here is only "fits in int"; validate() checks 0/1 and uniqueness.
                    if (const auto v = integer(*channel, child(epath, "channel"),
                                               std::numeric_limits<int>::min(),
                                               std::numeric_limits<int>::max(), IssueCode::E_EMITTER_CHANNEL))
                        emitter.channel = static_cast<int>(*v);
                }
                if (const Json* position = field(item, epath, "position"))
                {
                    if (const auto v = vec3(*position, child(epath, "position")))
                        emitter.position = *v;
                }
                if (const Json* gain = field(item, epath, "gainDb"))
                {
                    if (const auto v = number(*gain, child(epath, "gainDb")))
                        emitter.gainDb = *v;
                }
            }
            emitters.push_back(std::move(emitter));
        }
    }

    void readRender(const Json& value, const std::string& path, RenderSettings& render)
    {
        if (!object(value, path, {"outputMode", "hrtfId", "maxReflectionOrder", "tailSeed"}))
            return;
        if (const Json* mode = field(value, path, "outputMode"))
        {
            if (const auto text = string(*mode, child(path, "outputMode")))
            {
                if (*text == outputModeName(OutputMode::binaural))
                    render.outputMode = OutputMode::binaural;
                else if (*text == outputModeName(OutputMode::stereoSpeakers))
                    render.outputMode = OutputMode::stereoSpeakers;
                else
                    error(IssueCode::E_OUTPUT_MODE, child(path, "outputMode"),
                          "outputMode must be \"binaural\" or \"stereoSpeakers\", got \"" + *text + "\"");
            }
        }
        if (const Json* hrtf = field(value, path, "hrtfId"))
        {
            if (const auto text = string(*hrtf, child(path, "hrtfId")))
                render.hrtfId = *text;
        }
        if (const Json* order = field(value, path, "maxReflectionOrder"))
        {
            // Range here is only "fits in int"; validate() checks [0, 60].
            if (const auto v = integer(*order, child(path, "maxReflectionOrder"),
                                       std::numeric_limits<int>::min(), std::numeric_limits<int>::max(),
                                       IssueCode::E_REFLECTION_ORDER_RANGE))
                render.maxReflectionOrder = static_cast<int>(*v);
        }
        if (const Json* seed = field(value, path, "tailSeed"))
        {
            if (const auto v = integer(*seed, child(path, "tailSeed"), 0,
                                       std::numeric_limits<std::uint32_t>::max(),
                                       IssueCode::E_TAIL_SEED_RANGE))
                render.tailSeed = static_cast<std::uint32_t>(*v);
        }
    }

    std::vector<Issue>& issues_;
    bool ignoreUnknownFields_ = false;
    bool failed_ = false;
};

Json vec3Json(const Vec3& v)
{
    return Json::array({v.x, v.y, v.z});
}

} // namespace

std::string toJson(const SceneDescription& scene)
{
    Json surfaces = Json::object();
    for (const SurfaceId id : kAllSurfaces)
    {
        const SurfaceMaterial& material = scene.room.surface(id);
        Json absorption = Json::array();
        for (const double a : material.bandsAbsorption)
            absorption.push_back(a);
        Json surface = Json::object();
        surface["absorption"] = std::move(absorption);
        surface["scattering"] = material.scattering;
        surfaces[std::string{surfaceName(id)}] = std::move(surface);
    }

    Json geometry = Json::object();
    geometry["kind"] = "shoebox";
    geometry["dimensions"] = vec3Json(scene.room.geometry.dimensions);

    Json room = Json::object();
    room["geometry"] = std::move(geometry);
    room["surfaces"] = std::move(surfaces);

    Json listener = Json::object();
    listener["position"] = vec3Json(scene.listener.position);

    Json emitters = Json::array();
    for (const Emitter& e : scene.emitters)
    {
        Json emitter = Json::object();
        emitter["id"] = e.id;
        emitter["channel"] = e.channel;
        emitter["position"] = vec3Json(e.position);
        emitter["gainDb"] = e.gainDb;
        emitters.push_back(std::move(emitter));
    }

    Json render = Json::object();
    render["outputMode"] = std::string{outputModeName(scene.render.outputMode)};
    render["hrtfId"] = scene.render.hrtfId;
    render["maxReflectionOrder"] = scene.render.maxReflectionOrder;
    render["tailSeed"] = scene.render.tailSeed;

    // An in-memory scene with invalid extension text is written with an empty object; validate()
    // reports it as E_EXTENSIONS.
    Json extensions = Json::parse(scene.extensionsJson, nullptr, false);
    if (extensions.is_discarded() || !extensions.is_object())
        extensions = Json::object();

    Json root = Json::object();
    root["contractVersion"] = toString(scene.contractVersion);
    root["units"] = "meters";
    root["room"] = std::move(room);
    root["listener"] = std::move(listener);
    root["emitters"] = std::move(emitters);
    root["render"] = std::move(render);
    root["extensions"] = std::move(extensions);

    // replace: invalid UTF-8 in an in-memory string must not throw out of the writer.
    return root.dump(2, ' ', false, Json::error_handler_t::replace) + "\n";
}

ParseResult fromJson(std::string_view json) noexcept
{
    ParseResult result;
    try
    {
        Json root;
        try
        {
            root = Json::parse(json.begin(), json.end());
        }
        catch (const Json::exception& e) // parse_error, or out_of_range for a number that overflows a double
        {
            result.issues.push_back(Issue{IssueCode::E_JSON_SYNTAX, "", e.what()});
            return result;
        }
        Reader reader{result.issues};
        result.scene = reader.readScene(root);
        return result;
    }
    catch (const std::exception& e)
    {
        try
        {
            result.scene.reset();
            result.issues.push_back(
                Issue{IssueCode::E_INTERNAL, "", std::string{"internal error: "} + e.what()});
        }
        catch (...)
        {}
        return result;
    }
    catch (...)
    {
        result.scene.reset();
        return result;
    }
}

} // namespace contract
