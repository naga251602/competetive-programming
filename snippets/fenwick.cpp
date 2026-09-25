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