// problem link https://cses.fi/problemset/task/1084/
void solve() {
    int n, m, k;

    cin >> n >> m >> k;
    vector<int> a(n), s(m);

    for (int i = 0; i < n; i ++) cin >> a[i];
    for (int i = 0; i < m; i ++) cin >> s[i];

    sort(a.begin(), a.end());
    sort(s.begin(), s.end());

    int count = 0;

    int i = 0, j = 0;

    while (i < n && j < m) {
        if (a[i] - k <= s[j] && s[j] <= a[i] + k) {
            count ++; 
            i ++;
            j ++;
        } else if (a[i] - k > s[j]) {
            if (j == m-1) break;
            j ++;
        } else {
            if (i == n-1) break;
            i ++;
        }
    }

    cout << count;
}