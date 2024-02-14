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
const char CONFIG_PATH[] = ".config/lyzard";
// Variables
string path = "";
map<string, vector<string>> structures_from_description_file;

// Functions
int check_argv(int argc, char** argv) {
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-v") == 0 or strcmp(argv[i], "--version") == 0) {
            cout << "Lyzard interpeter " << VERSION << endl;
	    return 1;
	}
        else {
            if (argv[i][0] == '-' or argv[i][0] == '-' and argv[i][1] == '-') {
                cout << PROGRAM_NAME << ": " << "invalid option " << i << endl;
                return 2;
            }
        }
    }
    return 0;
}



int main(int argc, char* argv[]) {
    int return_status = check_argv(argc, argv);
    
    if (return_status == 2)
        return 2;
    if (return_status == 1)
	return 0;
    
    // Creating a file <base name of input file>.py
    // for writing converted code in it
    string output_filename = split(path, "/")[0];
    output_filename = split(output_filename, ".")[0];
    output_filename = output_filename + ".py";

    // Opening files
    ofstream output_file(output_filename);
    ofstream lyzard_py("lyzard.py");

    ifstream description_file("~/");
    ifstream input_file(path);

    structures_from_description_file = parse_file(description_file);
    
    if (not input_file.good()) {
        cout << PROGRAM_NAME << ":" << " cannot access '" << path << "'" << " no such file or directory" << endl;
        return 2;
    }
    
    vector<string> output_file_contents;
    vector<string> input_file_lines;
    string line = "";
    string buffer_line;
    string converted_macro;


    /*
        Main code analyze and convertation.

        After line is readed, line will be analyzed
        if there any Lyzard specific structures
        it will convert separately any of those
        and put in new file called lyzard.py.

        When overloading an operator or creating new,
        function will be created in format:
        def lyzard_operator_COUNTER (args):

        All those functions will be writen in lyzard.py file, so
        DO NOT overwrite it!!!
    */
    while (getline(input_file, line)) {
        for (char i : line) {
            buffer_line += i;

            // Checking if buffer_line contains one of structures, described in ~/.config/lyzard/language.des
	    
        }
    }
    
    return 0;
}
