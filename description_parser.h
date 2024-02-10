#ifndef DESCRIPTION_PARSER_H
#define DESCRIPTION_PARSER_H
#include <map>
#include <string>
#include <vector>
#include <fstream>

std::map<std::string, std::vector<std::string>> parse_file(std::ifstream &description_file);

#endif
