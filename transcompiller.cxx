#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <sys/stat.h>
#include "description_parser.cxx"
#include "utils.cxx"


#define VERSION "0.1.0"
#define PROGRAM_NAME "lyzard"

using namespace std;

// Variables
string path = "";
// This variable stores all settings from input file that setted with &setup
map<string, string> settings_from_setup;
map<vector<string>, string> structures_from_description_file;


// Functions
int check_argv(int argc, char** argv){
    for(int i; i < argc; i++){
	if(argv[i] == "-v" or argv[i] == "--version")
	    cout << "Lyzard interpeter " << VERSION << endl;

	else{
	    if((argv[i][0] == '-') or ((argv[i][0] == '-') and (argv[i][1] == '-'))){
		cout << PROGRAM_NAME << ": " << "invalid option " << i << endl;
		return 2;
	    }
	}
    }
    return 0;
}



int main(int argc, char* argv[]){
    int return_status = check_argv(argc, argv);
    
    if(return_status == 2)
	return 2;
    
    // Creating a file <base name of input file>.py
    // for writing converted code in it
    string output_filename = split(path, "/")[0];
    output_filename = split(output_filename, ".")[0];
    output_filename = output_filename + ".py";

    // Opening output and input files
    ofstream output_file(output_filename);
    ofstream lyzard_py("lyzard.py");

    ifstream description_file;
    ifstream input_file(path);
    
    if(not input_file.good())
	cout << PROGRAM_NAME << ":" << " cannot access '" << path << "'" << " no such file or directory" << endl;
    
    vector<string> output_file_contents;
    vector<string> input_file_lines;
    string line = "";
    string buffer_line;
    string converted_macro;

    /* Main code analyze and convertation
       after line is readed, line will be analyzed
       if there any lyzard specific structures
       it will convert separately any of those
       and put in new file called lyzard.py

       When overloading a operator or creating a new,
       function will be created in format:
       def operator<the operator> (args):

       all those functions will be writen in lyzard.py file, so
       do not overwrite it!!!
       
    */
    while(getline(input_file, line)){
	for(auto i: line){
	    buffer_line += i;

	    // Checking if buffer_line contains one of structures, described in ~/.config/lyzard/language.json
	    
	}
    }
    
    return 0;
}
