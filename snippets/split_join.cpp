vector<string> split(const string &s, const string &delim) {
    vector<string> arr;

    string input = "";
    int d = delim.size();
    
    for (int i = 0; i < s.length(); i ++) {
        string k = s.substr(i, d);
        if (k == delim){ 
            if (input.length() > 0) arr.push_back(input);
            i += d - 1;
            input.clear();
        }
        else input += s[i];
    }
    
    if (!input.empty()) {
        arr.push_back(input);
    }

    return arr;
}

// join
template <typename A>
string join(const vector<A> &arr, const string &delim) {
    stringstream res;
    int pos = 0;
    for (auto val: arr) {
        res << val;
        if (pos != arr.size()-1) res << delim;
        pos ++;
    }

    return res.str();
}