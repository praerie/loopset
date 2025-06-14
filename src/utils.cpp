#include "utils.hpp"
#include <iostream>
#include <cctype>
#include <algorithm>

/**
 * @brief Removes leading and trailing whitespace from a string.
 * 
 * @param str The input string to trim.
 * @return A new string with no leading or trailing whitespace.
 */
std::string trim(const std::string& str) {
    auto start = str.begin();
    while (start != str.end() && std::isspace(*start)) start++;

    auto end = str.end();
    do {
        end--;
    } while (std::distance(start, end) > 0 && std::isspace(*end));

    return std::string(start, end + 1);
}

/**
 * @brief Prompts the user for input and trims leading/trailing whitespace.
 * 
 * If the input is empty (after trimming), the function treats it as a cancellation
 * and returns an empty string.
 * 
 * @param prompt The message displayed to the user.
 * @return A trimmed input string, or an empty string if the input is blank.
 */
std::string getValidatedInput(const std::string& prompt) {
    std::string input;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        input = trim(input);

        if (input.empty()) {
            std::cout << "Cancelled.\n";
            return "";
        }

        return input;
    }
}

/**
 * @brief Converts a string to lowercase.
 * 
 * Transforms all characters in the input string to their lowercase equivalents.
 * 
 * @param str The original string.
 * @return A new string with all characters in lowercase.
 */
std::string toLower(const std::string& str) {
    std::string lower = str;
    std::transform(lower.begin(), lower.end(), lower.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return lower;
}
