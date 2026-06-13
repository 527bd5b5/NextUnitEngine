#pragma once

#include <string>
#include <vector>

namespace util
{
    void printDebugLine(const std::string& text);
    void printDebugLine(int i);
    void printDebugLine(double d);
    void printErrorLine(const std::string& text, int code);
    std::vector<std::string>
    splitString(const std::string& text, const char separator);
    std::string trimSpace(const std::string& text);
    void trimSpace(std::vector<std::string>& items);
}
