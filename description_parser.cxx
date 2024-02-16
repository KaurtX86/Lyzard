#include <sstream>
#include <iostream>

#include "description_parser.h"
#include "utils.h"

using namespace std;


void process_block(const pair<StructureType, string>& name, string block, map<pair<StructureType, string>, vector<string>>& to) {
    switch (name.first) {
        case StructureType::MACRO:
            to[name] = {block};
            break;
    }
}


vector<string> parse_description_file(ifstream &description_file, map<pair<StructureType, string>, vector<string>>& to) {
    string line;
    int line_counter = 0;
    vector<string> errors;

    bool block_next = false;
    bool block_opened = false;
    bool block_first_line = false;
    pair<StructureType, string> block_name;
    stringstream value;
    
    while (getline(description_file, line)) {
        line_counter++;
        if (line.size() > 0)
            if (line[0] == '#')
                continue;

        if (block_next) {
            if (line == "$") {
                block_next = false;
                block_opened = true;
                block_first_line = true;
                value.clear();
                continue;
            }
            else {
                create_error(errors, line_counter, "Block - expected $ on next line as block begin.");
                block_next = false;
                continue;
            }
        }

        if (block_opened) {
            if (line == "$") {
                block_opened = false;
                process_block(block_name, value.str(), to);
                continue;
            }
            if (not block_first_line)
                value << endl;
            value << line;
            block_first_line = false;
            continue;
        }

        line = strip_chars(line, ' ');
        line = strip_chars(line, '\t');
        if (line.empty())
            continue;

        vector<string> words = split(line, " ");
        //string buffer = "";
        //bool code_block = false;

        if (words[0] == "macro") {
            vector<string> macro_parts = split(line, "=");
            if (macro_parts.size() > 2) {
                create_error(errors, line_counter, "Macro definition - expected 1 equal sign.");
                continue;
            }
            vector<string> definition_parts = split(strip_chars(macro_parts[0]), " ");
            if (definition_parts.size() != 2) {
                create_error(errors, line_counter, "Macro definition - expected 1 name.");
                continue;
            }
            pair<StructureType, string> name = {StructureType::MACRO, definition_parts[1]};
            if (macro_parts.size() == 1) {
                block_name = name;
                block_next = true;
            }
            else {
                if (macro_parts[1].empty()) {
                    create_error(errors, line_counter, "Macro definition - expected value.");
                    continue;
                }
                process_block(name, strip_chars(macro_parts[1]), to);
            }
        }
        /*else if (words[0] == "structure") {
            vector<string> structure_params;
            // map<string, string> structure_params;
            vector<string> name = {};
        }*/
        else {
            create_error(errors, line_counter, "Unexpected '" + line + "'. Expected definition.");
        }

    }

    if (block_opened)
        create_error(errors, line_counter, "Block - expected closing '$'.");

    return errors;
}


void create_error(vector<string>& errors, int line, string error) {
    stringstream ss;
    ss << "[Error] At line " << line << ": ";
    ss << error;
    errors.push_back(ss.str());
}
