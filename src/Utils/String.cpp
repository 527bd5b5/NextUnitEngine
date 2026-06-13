#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Utils/String.hpp"

namespace util
{
    void printDebugLine(const std::string& text)
    {
        std::cout << "[DEBUG] " + text << std::endl;
    }

    void printDebugLine(const int i)
    {
        printDebugLine(std::to_string(i));
    }

    void printDebugLine(const double d)
    {
        printDebugLine(std::to_string(d));
    }

    void printErrorLine(const std::string& text, int code)
    {
        std::cerr << "\x1b[1;31m" << "[ERROR] " + text << "\x1b[m" << std::endl;

        std::exit(code);
    }

    std::vector<std::string>
    splitString(const std::string& text, const char separator)
    {
        std::stringstream ss(text);
        std::string item;
        std::vector<std::string> items;

        if (text.empty())
            return items;

        while (std::getline(ss, item, separator))
            items.push_back(item);

        return items;
    }

    std::string trimSpace(const std::string& text)
    {
        if (text.empty())
            return text;

        size_t start = text.find_first_not_of(" \t");
        size_t end = text.find_last_not_of(" \t");

        return text.substr(start, end - start + 1);
    }

    void trimSpace(std::vector<std::string>& items)
    {
        for (std::string& item : items)
            item = trimSpace(item);
    }
}
