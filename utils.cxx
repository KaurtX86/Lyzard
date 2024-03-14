#include "utils.h"

using namespace std;

vector<string> split(string a, const string& delimiter) {
    vector<string> b;
    size_t pos = 0;
    string token;
    
    while ((pos = a.find(delimiter)) != string::npos) {
        token = a.substr(0, pos);
        b.push_back(token);
        a.erase(0, pos + delimiter.length());
    }
    token = "";
    
    b.push_back(a);
    
    return b;
}


string strip_chars(const string& what, char to_strip, bool strip_right, bool strip_left) {
    int start_idx = 0, end_idx = what.size();
    if (strip_left) {
        start_idx = -1;
        for (int i = 0; i < what.size(); i++) {
            if (what[i] != to_strip) {
                start_idx = i;
                break;
            }
        }
    }
    if (strip_right) {
        end_idx = -1;
        for (int i = what.size() - 1; i >= 0; i--) {
            if (what[i] != to_strip) {
                end_idx = i;
                break;
            }
        }
    }
    if (strip_left and start_idx == -1)
        return string();
    if (strip_right and end_idx == -1)
        return string();
    return what.substr(start_idx, end_idx - start_idx + 1);
}
