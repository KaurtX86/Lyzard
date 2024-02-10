#include <map>
#include <string>
#include <vector>
#include <fstream>
#include "useful.cxx"


map< string,vector<string> > parse_file(ifstream &description_file){
    map< string, vector<string> > result;
    string line;
    
    while(getline(description_file, line)){
	vector<string> words = split(line, " ");
	
	for(int i; i < words.size(); i++){
	    if(words[i] == "macro"){
		
		vector<string> macro_params;
		for(int j = i + 1; j < words.size(); j++){
		    macro_params.push_back(words[j]);
		}
	    }
	}
    }
    return result;
}
