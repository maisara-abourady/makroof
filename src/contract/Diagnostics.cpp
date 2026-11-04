#include "contract/Diagnostics.h"

#include <algorithm>

namespace contract {

std::string_view codeName(IssueCode code) noexcept
{
    switch (code)
    {
#define SPATIAL_CONTRACT_NAME_CASE(name, number, meaning)                                                    \
    case IssueCode::name:                                                                                    \
        return #name;
        SPATIAL_CONTRACT_ISSUE_CODES(SPATIAL_CONTRACT_NAME_CASE)
#undef SPATIAL_CONTRACT_NAME_CASE
    }
    return {};
}

std::string_view codeMeaning(IssueCode code) noexcept
{
    switch (code)
    {
#define SPATIAL_CONTRACT_MEANING_CASE(name, number, meaning)                                                 \
    case IssueCode::name:                                                                                    \
        return meaning;
        SPATIAL_CONTRACT_ISSUE_CODES(SPATIAL_CONTRACT_MEANING_CASE)
#undef SPATIAL_CONTRACT_MEANING_CASE
    }
    return {};
}

const std::vector<IssueCode>& allIssueCodes()
{
    static const std::vector<IssueCode> codes{
#define SPATIAL_CONTRACT_LIST_ENTRY(name, number, meaning) IssueCode::name,
        SPATIAL_CONTRACT_ISSUE_CODES(SPATIAL_CONTRACT_LIST_ENTRY)
#undef SPATIAL_CONTRACT_LIST_ENTRY
    };
    return codes;
}

std::optional<IssueCode> codeFromName(std::string_view name) noexcept
{
#define SPATIAL_CONTRACT_FROM_NAME(codeId, number, meaning)                                                  \
    if (name == #codeId)                                                                                     \
        return IssueCode::codeId;
    SPATIAL_CONTRACT_ISSUE_CODES(SPATIAL_CONTRACT_FROM_NAME)
#undef SPATIAL_CONTRACT_FROM_NAME
    return std::nullopt;
}

Severity severityOf(IssueCode code) noexcept
{
    return codeName(code).starts_with("W_") ? Severity::warning : Severity::error;
}

bool hasErrors(const std::vector<Issue>& issues) noexcept
{
    return std::any_of(issues.begin(), issues.end(),
                       [](const Issue& issue) { return issue.severity() == Severity::error; });
}

std::string toString(const Issue& issue)
{
    std::string text{codeName(issue.code)};
    text += " at ";
    text += issue.path.empty() ? std::string{"(root)"} : issue.path;
    text += ": ";
    text += issue.message;
    return text;
}

} // namespace contract
