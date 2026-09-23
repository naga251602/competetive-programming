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

ll mod_pow(ll base, ll exponent, int mod = MOD) {
    assert(mod > 0 && exponent >= 0);
    base = (base % mod + mod) % mod;
    ll answer = 1 % mod;
    while (exponent) {
        if (exponent & 1) answer = answer * base % mod;
        base = base * base % mod;
        exponent >>= 1;
    }
    return answer;
}

struct DSU {
    vector<int> parent, size;
    explicit DSU(int n) : parent(n), size(n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        while (x != parent[x]) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (size[a] < size[b]) swap(a, b);
        parent[b] = a;
        size[a] += size[b];
        return true;
    }
};

template <class T = ll> struct Fenwick {
    int n;
    vector<T> tree;
    explicit Fenwick(int count) : n(count), tree(count + 1, T{}) {}
    void add(int index, T delta) {
        assert(0 <= index && index < n);
        for (++index; index <= n; index += index & -index) tree[index] += delta;
    }
    T prefix_sum(int r) const {
        assert(0 <= r && r <= n);
        T result{};
        for (; r > 0; r -= r & -r) result += tree[r];
        return result;
    }
    T range_sum(int l, int r) const {
        assert(0 <= l && l <= r && r <= n);
        return prefix_sum(r) - prefix_sum(l);
    }
};

#ifdef LOCAL
template <class... Ts> void debug_values(const char* names, const Ts&... values) {
    cerr << "[" << names << "]:";
    ((cerr << ' ' << values), ...);
    cerr << '\n';
}
#define dbg(...) debug_values(#__VA_ARGS__, __VA_ARGS__)
#else
#define dbg(...) ((void)0)
#endif
#define pb push_back

void solve() {
    // code here
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tests = 1;
    // cin >> tests;
    for (int tc = 0; tc < tests; ++tc) solve();
    return 0;
}
