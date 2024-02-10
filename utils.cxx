#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> split(string a, string delimiter) {
	
    vector<string> b; // Результат
    size_t pos = 0;
    string token;
    
    while ((pos = a.find(delimiter)) != string::npos) { // Пока есть запятые мы добавляем
        token = a.substr(0, pos);
        b.push_back(token);
        a.erase(0, pos + delimiter.length()); // Удаляем до запятой
    }
    
    b.push_back(a);
    
    return b;
}