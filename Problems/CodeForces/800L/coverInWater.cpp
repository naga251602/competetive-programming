// link -> https://codeforces.com/problemset/problem/1900/A
void solve() {
    int n;
    cin >> n;

    string s;
    cin >> s;

    vector<int> c;
    int l = 0, count = 0, i, v = 0, mx = 0;

    while (l < s.length() && s[l] != '.') l ++;
    
    if (l != s.length()) v = 1;

    for (i = l+1; i < s.length(); i++) {
        if (s[i] == '.') {
            v ++;
            mx = max(mx, v);
            continue;
        }
        else {
            c.push_back(v);
            l = i;
            v = 0;
        }
    }

    if(v!=0) c.push_back(v);
    int sum = accumulate(c.begin(), c.end(), 0);

    cout << ((mx > 2)? 2:sum) << "\n";
}