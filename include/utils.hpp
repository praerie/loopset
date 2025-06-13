#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <algorithm>
#include <cctype>

std::string trim(const std::string& str);
std::string getValidatedInput(const std::string& prompt);
std::string toLower(const std::string& str);

#endif
