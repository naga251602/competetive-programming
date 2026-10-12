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

template <class... Args>
void print_debug(const tuple<Args...>& t) {
    cerr << "(";
    apply([](const auto&... x) {
        bool first = true;
        ((cerr << (exchange(first, false) ? "" : ", "),
          print_debug(x)), ...);
    }, t);
    cerr << ")";
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

template <class... Ts>
void debug_values(const char* names, const Ts&... values) {
    cerr << "[debug] [" << names << "] = ";
    bool first = true;
    ((cerr << (exchange(first, false) ? "" : " "), print_debug(values)), ...);
    cerr << "\n";
}

#ifdef LOCAL
#define dbg(...) debug_values(#__VA_ARGS__, __VA_ARGS__)
#else
#define dbg(...) ((void)0)
#endif

template <class T>
T minv(const vector<T>& v) {
    return *min_element(v.begin(), v.end());
}

template <class T>
T maxv(const vector<T>& v) {
    return *max_element(v.begin(), v.end());
}

void rev(vector<int> &vec, int st, int en) {
    while (st < en) {
        swap(vec[st ++], vec[en --]);
    }
}

int sumOfSquares(int n) {
    int s = 0;

    while (n > 0) {
        int d = (n%10);
        s += (d * d);
        n /= 10;
    }

    return s;
}

void solve(int t) {
    vector<int> vec{3, -6, 1};

    cout << '\n';
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tests = 1;
    cin >> tests;
    for (int tc = 0; tc < tests; ++tc) solve(tc);
    return 0;
}
