// https://codeforces.com/problemset/problem/1901/A

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> arr;
    int x;
    
    arr.push_back(0);
    
    for (int i = 0; i < n;i ++) {   
        cin >> x;
        arr.push_back(x);
    }
    int mx = 1;
 
    for(int i = 1; i < arr.size(); i ++) {
        mx = max(mx, arr[i] - arr[i-1]);
    }
    mx = max(mx, 2 * (k - arr[arr.size() - 1]));
    cout << mx << "\n";
}