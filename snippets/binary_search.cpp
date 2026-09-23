int binarySearch(vector<int> &arr, int target){
    int st = 0, en = arr.size() - 1;

    while (st <= en) {
        int m = st + (en - st) / 2;

        if (arr[m] == target) return m;
        else if (arr[m] < target) st = m + 1;
        else en = m - 1;
    }

    return -1;
} 