#ifndef UTILS_H
#define UTILS_H
#include <string>
#include <vector>

std::vector<std::string> split(std::string a, const std::string& delimiter);
std::string strip_chars(const std::string& what, char to_strip = ' ', bool strip_right = true, bool strip_left = true);

#endif
