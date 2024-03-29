#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <cstring>

#include "description_parser.h"
#include "utils.h"

using namespace std;

// Constants
const char VERSION[] = "0.1.0";
const char PROGRAM_NAME[] = "Lyzard";

// Variables
string script_path = "";
string description_file_path = string(getenv("HOME")) + "/.config/lyzard/language.des";

// Variables specific for built in structures
int operator_counter = 0;

// Parameters from argv
bool run_after_complete = false;

// Interesting things
map<pair<StructureType, string>, vector<string>> structures_from_description_file;
map<pair<string, string>, string> operators_data;

// Functions
int check_argv(int argc, char** argv) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-v") == 0 or strcmp(argv[i], "--version") == 0) {
            cout << "Lyzard interpeter " << VERSION << endl;
            return 1;
        }
        else if (strcmp(argv[i], "-r") == 0 or strcmp(argv[i], "--run") == 0) {
            run_after_complete = true;
        }
        else {
            if (argv[i][0] == '-') {
                cout << PROGRAM_NAME << ": " << "invalid option " << argv[i]  << endl;
                return 127;
            }
            script_path = argv[i];
        }
    }
    return 0;
}

string parse_string_macros(string str) {
    string buffer_str = "";

    for (unsigned int i = 0; i < str.size(); i++) {
        buffer_str += str[i];
        for (unsigned int j = 0; j < structures_from_description_file.size(); j++) {

        }
    }
    return "";
}

// Returns converted string, error message or nothing
string parse_string(string str) {
    string converted_string = "def lyzard-operator";
    string buffer_line = "";
    string spaces = "";
    for (unsigned int i = 0; i < str.size(); i++){
        if (str[i] == ' ' or str[i] == '\t') {
            spaces += str[i];
            continue;
        }

        buffer_line += str[i];

        if (str[i] == '#') {
            break;
        }
        
        for (unsigned int j = 0; j < structures_from_description_file.size(); j++) {
            // Built in structures
            if (buffer_line == "operator") {
                // bool parsing_operator = true;
                string operator_word = "";
                string operator_args = "";

                for (unsigned int x = i + 1; x < str.size(); x++) {
                    if (str[x] == ' ' or str[x] == '\t') {
                        continue;
                    }
                    
                    while (str[x] != ' ') {
                        operator_word += str[x];
                    }

                    while (str[x] != ' ' or str[x] != ':') {
                        operator_args += str[x];
                    }

                    if (operator_word == "") {
                        return "invalid operator";
                    }

                    if (operator_args == "") {
                        return "invalid arguments";
                    }

                }
                operator_args = parse_string_macros(operator_args);
                converted_string = "def lyzard-operator-" + to_string(operator_counter) + " " + operator_args + ":";
                operator_counter++;
            }
        }
    }
    
    return converted_string;
}

int main(int argc, char* argv[]) {
    int return_status = check_argv(argc, argv);

    if (return_status == 1)
        return 0;
    if (return_status)
        return return_status;

    ifstream description_file(description_file_path);
    ifstream input_file(script_path);

    if (not description_file.good()) {
        cout << PROGRAM_NAME << ":" << " cannot access '" << description_file_path << "'" << " no such file or directory" << endl;
        return 2;
    }
    
    cout << "[DESCRIPTION FILE PARSE OUTPUT]" << endl;
    vector<string> parse_errors = parse_description_file(description_file, structures_from_description_file);
    if (parse_errors.size() > 0) {
        for (const string& i : parse_errors)
            cerr << i << endl;
        return 5;
    }

    for (const pair<pair<StructureType, string>, vector<string>> &i : structures_from_description_file) {
        cout << "Type: " << i.first.first << ", Name: " << i.first.second << ", Data: ";
        for (const string &j : i.second)
            cout << j << ' ';
        cout << endl;
    }

    if (not input_file.good() or script_path == "") {
        cout << PROGRAM_NAME << ":" << " cannot access '" << script_path << "'" << " no such file or directory" << endl;
        return 2;
    }

    string output_filename = split(script_path, "/")[0];
    output_filename = split(output_filename, ".")[0];
    output_filename = output_filename + ".py";

    // Creating a file <base name of input file>.py
    // for writing converted code in it

    // Opening files
    ofstream output_file(output_filename);
    ofstream lyzard_py("lyzard.py");

    vector<string> output_file_lines = {"from lyzard import *"};
    vector<string> input_file_lines;
    string line = "";
    string buffer_line = "";
    string converted_macro = "";
    int line_counter = 0;

    /*
      Main code analyze and convertation.

      After line is readed, line will be analyzed
      if there any Lyzard specific structures
      it will convert separately any of those
      and put in new file called lyzard.py

      When overloading an operator or creating new,
      function will be created in format:
      def lyzard_operator_COUNTER (args):

      All those functions will be writen in lyzard.py file, so
      DO NOT overwrite it!!!
    */
    cout << "[SCRIPT PARSE/TRANSCOMPILATION OUTPUT]" << endl;
    
    while (getline(input_file, line)) {
        line_counter++;
        vector<string> words = split(line, " ");

        for (unsigned int i = 0; i < line.size(); i++) {
            buffer_line += line[i];

            // Checking if buffer_line contains one of structures, described in description file or stupidly built in
            for (unsigned int j = 0; j < structures_from_description_file.size(); j++) {
                if (buffer_line == "operator") {
                    // bool parsing_operator = true;
                    string operator_word = "";
                    string args = "";
                    for (unsigned int x = i + 1; x < line.size(); x++) {
                        if (line[x] == ' ' or line[x] == '\t') {
                            continue;
                        }
                        buffer_line += line[x];
                        
                    }
                    
                    if (operator_word == "") {
                        cerr << line_counter << "| " << "[Error] in [" << script_path << "] " << "invalid operator" << endl;
                        continue;
                    }
                    operator_counter++;
                }
            }
        }
    }
    
    if (run_after_complete)
        system(("python3 " + output_filename).c_str());

    return 0;
}
