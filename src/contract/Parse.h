#pragma once

// The one entry point for loading a scene: fromJson() (syntax, version, structure) followed by
// validate() (ranges, counts, geometry). Never throws out of the library.
#include "contract/Json.h"

#include <string_view>

namespace contract {

// result.ok() is true when the scene can be rendered; result.scene is set only then. Warnings
// (e.g. W_VERSION_MINOR_NEWER) do not stop a scene from loading.
ParseResult parseScene(std::string_view json) noexcept;

} // namespace contract
