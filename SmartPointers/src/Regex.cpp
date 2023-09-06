
#include <SmartPointers/Regex.h>

#include <regex>

namespace smartPointers
{
    bool validateEmail(const std::string& email)
{
    static const std::regex emailRegex(R"(^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$)");
    return std::regex_match(email, emailRegex);
}

std::string removeWhitespace(const std::string& text)
{
    static const std::regex whitespaceRegex(R"(\s+)");
    return std::regex_replace(text, whitespaceRegex, "");
}

std::string extractDomain(const std::string& email)
{
    static const std::regex domainRegex(R"(\@([\w\-]+\.+[\w\-]+))");
    std::smatch match;
    if (std::regex_search(email, match, domainRegex)) {
        return match[1].str();
    }
    return "";
}
}  // namespace smartPointers