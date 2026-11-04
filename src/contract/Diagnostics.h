#pragma once

// Issues reported by the contract reader (Json.h, Parse.h) and the validator (Validate.h).
// Codes are a stable API: tests, fixtures (tests/scenes/invalid/<CODE>.json) and later the UI refer
// to them by name. Append new codes at the end with the next number; never rename or renumber one.
// Codes starting with W_ are warnings, all others are errors.
#include "contract/SceneDescription.h"

#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace contract {

// X(name, number, one-line meaning). The list is the single source for the enum and codeName().
#define SPATIAL_CONTRACT_ISSUE_CODES(X)                                                                      \
    X(E_INTERNAL, 0, "unexpected internal failure (e.g. out of memory); never caused by the document")       \
    X(E_JSON_SYNTAX, 1, "the text is not valid JSON")                                                        \
    X(E_TYPE, 2, "a value has the wrong JSON type")                                                          \
    X(E_MISSING_FIELD, 3, "a required field is missing")                                                     \
    X(E_UNKNOWN_FIELD, 4, "a field is not part of the contract at this minor version")                       \
    X(E_ARRAY_LENGTH, 5, "an array has the wrong number of elements")                                        \
    X(E_VERSION_FORMAT, 6, "contractVersion is not \"MAJOR.MINOR\"")                                         \
    X(E_VERSION_MAJOR, 7, "contractVersion has a major version this build cannot read")                      \
    X(W_VERSION_MINOR_NEWER, 8, "contractVersion is a newer minor version; unknown fields were ignored")     \
    X(E_UNITS, 9, "units is not \"meters\"")                                                                 \
    X(E_GEOMETRY_KIND, 10, "room.geometry.kind is not a supported kind")                                     \
    X(E_ROOM_DIMENSION_RANGE, 11, "a room dimension is outside [1.5, 100] m")                                \
    X(E_ABSORPTION_RANGE, 12, "an absorption coefficient is outside [0.01, 1.0]")                            \
    X(E_SCATTERING_RANGE, 13, "a scattering coefficient is outside [0, 1]")                                  \
    X(E_LISTENER_SURFACE_CLEARANCE, 14, "the listener is not inside the room 0.1 m clear of every surface")  \
    X(E_EMITTER_COUNT, 15, "there are not exactly two emitters")                                             \
    X(E_EMITTER_ID, 16, "an emitter id is not \"L\" or \"R\", or is used twice")                             \
    X(E_EMITTER_CHANNEL, 17, "an emitter channel is not 0 or 1, or is used twice")                           \
    X(E_GAIN_RANGE, 18, "an emitter gainDb is outside [-60, +12]")                                           \
    X(E_EMITTER_SURFACE_CLEARANCE, 19, "an emitter is not inside the room 0.1 m clear of every surface")     \
    X(E_EMITTER_TOO_CLOSE_TO_LISTENER, 20, "an emitter is less than 0.3 m from the listener")                \
    X(E_OUTPUT_MODE, 21, "render.outputMode is not \"binaural\" or \"stereoSpeakers\"")                      \
    X(E_HRTF_ID, 22, "render.hrtfId is not a supported HRTF")                                                \
    X(E_REFLECTION_ORDER_RANGE, 23, "render.maxReflectionOrder is outside [0, 60]")                          \
    X(E_TAIL_SEED_RANGE, 24, "render.tailSeed is not an unsigned 32-bit integer")                            \
    X(E_EXTENSIONS, 25,                                                                                      \
      "SceneDescription::extensionsJson is not the text of a JSON object (in-memory scenes)")

enum class IssueCode
{
#define SPATIAL_CONTRACT_ENUM_ENTRY(name, number, meaning) name = number,
    SPATIAL_CONTRACT_ISSUE_CODES(SPATIAL_CONTRACT_ENUM_ENTRY)
#undef SPATIAL_CONTRACT_ENUM_ENTRY
};

enum class Severity
{
    warning,
    error
};

// The code's name, e.g. "E_ABSORPTION_RANGE". Empty for a value outside the enum.
std::string_view codeName(IssueCode code) noexcept;
// One-line meaning of the code (the third column above).
std::string_view codeMeaning(IssueCode code) noexcept;
// Inverse of codeName().
std::optional<IssueCode> codeFromName(std::string_view name) noexcept;
// Every code, in numeric order.
const std::vector<IssueCode>& allIssueCodes();

Severity severityOf(IssueCode code) noexcept;

struct Issue
{
    IssueCode code = IssueCode::E_INTERNAL;
    // JSON path of the offending value, e.g. "room.surfaces.floor.absorption[3]". Empty for the
    // document root.
    std::string path;
    // Human-readable explanation, e.g. "absorption must be in [0.01, 1.0], got 1.2".
    std::string message;

    Severity severity() const noexcept { return severityOf(code); }

    friend bool operator==(const Issue&, const Issue&) = default;
};

bool hasErrors(const std::vector<Issue>& issues) noexcept;

// "E_ABSORPTION_RANGE at room.surfaces.floor.absorption[3]: absorption must be ..."
std::string toString(const Issue& issue);

} // namespace contract
