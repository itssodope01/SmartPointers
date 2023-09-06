#include <iostream>
#include <memory>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

namespace smartPointers
{
bool validateEmail(const std::string& email);
std::string removeWhitespace(const std::string& text);
std::string extractDomain(const std::string& email);
}  // namespace smartPointers
