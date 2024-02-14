#include "description_parser.h"
#include "utils.h"

using namespace std;

map<pair<string, string>, vector<string>> parse_file(ifstream &description_file) {
    map<pair<string, string>, vector<string>> result;
    string line;
    int line_counter = 0;
    vector<string> errors;
    
    while (getline(description_file, line)) {
        line_counter++;

        vector<string> words = split(line, " ");
        string buffer = "";
        bool code_block = false;

        for (int i = 0; i < words.size(); i++) {
            if (words[i] == "macro" and i == 0) {
                pair<string, string> name = {words[i + 1], "macro"};
            }
            if (words[i] == "structure") {
                vector<string> structure_params;
                // map<string, string> structure_params;
                vector<string> name = {};
            }
        }
    }
    return result;
}
