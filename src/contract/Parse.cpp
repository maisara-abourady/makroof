#include "contract/Parse.h"

#include "contract/Validate.h"

#include <exception>
#include <string>
#include <utility>

namespace contract {

ParseResult parseScene(std::string_view json) noexcept
{
    try
    {
        ParseResult result = fromJson(json);
        if (!result.scene)
            return result;
        ValidationResult validation = validate(*result.scene);
        for (Issue& issue : validation.issues)
            result.issues.push_back(std::move(issue));
        if (hasErrors(result.issues))
            result.scene.reset();
        return result;
    }
    catch (const std::exception& e)
    {
        ParseResult failed;
        try
        {
            failed.issues.push_back(
                Issue{IssueCode::E_INTERNAL, "", std::string{"internal error: "} + e.what()});
        }
        catch (...)
        {}
        return failed;
    }
    catch (...)
    {
        return ParseResult{};
    }
}

} // namespace contract
