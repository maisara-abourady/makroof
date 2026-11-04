#pragma once

// JSON I/O for SceneDescription v1 (spec: docs/contract/README.md, schema:
// docs/contract/scene-v1.schema.json). nlohmann/json stays an implementation detail of this
// library; callers see strings only.
#include "contract/Diagnostics.h"
#include "contract/SceneDescription.h"

#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace contract {

struct ParseResult
{
    // Set when the document was read without errors. parseScene() also requires validate() to pass.
    std::optional<SceneDescription> scene;
    std::vector<Issue> issues; // errors and warnings

    bool ok() const noexcept { return scene.has_value() && !hasErrors(issues); }
};

// Serializes a scene: 2-space indented JSON, keys in specification order, a trailing newline.
// Doubles are written with the shortest text that reads back to the same double (round-trip
// precision, equivalent to %.17g), so toJson(parse(toJson(s))) == toJson(s) byte for byte.
// Writes the value as is; it does not validate. Throws only std::bad_alloc.
std::string toJson(const SceneDescription& scene);

// Reads a document: JSON syntax, the version rules, types, required/unknown fields and array
// lengths. It does not run the semantic checks of validate(); use parseScene() for both.
//
// Version rules: same major as this build is required (E_VERSION_MAJOR otherwise). A newer minor
// loads, ignores unknown fields and adds W_VERSION_MINOR_NEWER. At a known minor version an
// unknown field is an error (E_UNKNOWN_FIELD), which catches typos. Never throws.
ParseResult fromJson(std::string_view json) noexcept;

} // namespace contract
