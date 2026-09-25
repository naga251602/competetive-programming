#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <optional>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <sstream>


using namespace std;
using vi = vector<int>;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

template <class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;
template <class T> using max_heap = priority_queue<T, vector<T>>;

constexpr ll INF = numeric_limits<ll>::max() / 4;
constexpr int MOD = 1'000'000'007;

template <class T> bool chmin(T& a, const T& b) {
    if (b < a) { a = b; return true; }
    return false;
}
template <class T> bool chmax(T& a, const T& b) {
    if (a < b) { a = b; return true; }
    return false;
}

// debugging different types
template <class T>
void print_debug(const T& x) {
    cerr << x;
}

template <class A, class B>
void print_debug(const pair<A, B>& p) {
    cerr << "(";
    print_debug(p.first);
    cerr << ", ";
    print_debug(p.second);
    cerr << ")";
}

template <class T>
void print_debug(const vector<T>& v) {
    cerr << "[";
    for (int i = 0; i < (int)v.size(); i++) {
        if (i) cerr << ", ";
        print_debug(v[i]);
    }
    cerr << "]";
}

template <class T>
void print_debug(const set<T>& s) {
    cerr << "{";
    bool first = true;
    for (auto& x : s) {
        if (!first) cerr << ", ";
        first = false;
        print_debug(x);
    }
    cerr << "}";
}

template <class T>
void print_debug(const unordered_set<T>& s) {
    cerr << "{";
    bool first = true;
    for (auto& x : s) {
        if (!first) cerr << ", ";
        first = false;
        print_debug(x);
    }
    cerr << "}";
}

template <class K, class V>
void print_debug(const map<K, V>& mp) {
    cerr << "{";
    bool first = true;
    for (auto& [k, v] : mp) {
        if (!first) cerr << ", ";
        first = false;
        print_debug(k);
        cerr << ": ";
        print_debug(v);
    }
    cerr << "}";
}

template <class K, class V>
void print_debug(const unordered_map<K, V>& mp) {
    cerr << "{";
    bool first = true;
    for (auto& [k, v] : mp) {
        if (!first) cerr << ", ";
        first = false;
        print_debug(k);
        cerr << ": ";
        print_debug(v);
    }
    cerr << "}";
}

template <class... Ts>
void debug_values(const char* names, const Ts&... values) {
    cerr << "[" << names << "] = ";
    ((print_debug(values), cerr << " "), ...);
    cerr << "\n";
}

#define dbg(...) debug_values(#__VA_ARGS__, __VA_ARGS__)

struct MyHash {
    template <typename T>
    size_t operator()(const vector<T> &vec) {
        string h;

        for (size_t i = 0; i < vec.size(); i ++) {
            h += to_string(vec[i]);
            if (i!= vec.size() - 1) h += "#";
        }

        return hash<string>{}(h);
    }
};

vector<vector<long long>> sol;
void permute (vector<long long> &vec, vector<bool> &used, vector<long long> res){
    if (res.size() == vec.size()) {
        sol.push_back(res);
        return;
    }

    for (int i = 0; i < vec.size(); i ++) {
        if (used[i]) continue;

        used[i] = true;
        res.push_back(vec[i]);
        
        permute(vec, used, res);

        res.pop_back();
        used[i] = false;
    }
}
void solve(int tc) {
    int n1, n2;
    cin >> n1 >> n2;

    string s1, s2;
    cin >> s1 >> s2;

    int op = 0;

    while (s1.length() < s2.length()) {
        s1 += s1;
        op++;
    }

    if (s1.find(s2) != string::npos) {
        cout << op << '\n';
        return;
    }

    s1 += s1;
    op++;

    if (s1.find(s2) != string::npos)
        cout << op << '\n';
    else
        cout << -1 << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tests = 1;
    cin >> tests;
    for (int tc = 0; tc < tests; ++tc) solve(tc);
    return 0;
}
