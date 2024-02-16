#ifndef DESCRIPTION_PARSER_H
#define DESCRIPTION_PARSER_H
#include <map>
#include <string>
#include <vector>
#include <fstream>

enum StructureType {
    MACRO = 0,
};

void process_block(const std::pair<StructureType, std::string>& name, std::string block, std::map<std::pair<StructureType, std::string>, std::vector<std::string>>& to);
std::vector<std::string> parse_description_file(std::ifstream &description_file, std::map<std::pair<StructureType, std::string>, std::vector<std::string>>&);
void create_error(std::vector<std::string>& errors, int line, std::string error);

#endif
