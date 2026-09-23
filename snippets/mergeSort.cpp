void merge(vector<int> &arr, int low, int mid, int high) {
    int p = mid - low + 1;
    int q = high - mid;

    vector<int> left(p, 0), right(q, 0);

    for(int i = 0; i < p; i++) {
        left[i] = arr[i + low];
    }

    for (int j = 0; j < q; j ++) {
        right[j] = arr[j + mid + 1];
    }

    int i = 0, j = 0, k = low;

    while (i < p && j < q){
        if (left[i] <= right[j]) {
            arr[k ++] = left[i ++];
        } else { 
            arr[k ++] = right[j ++];
        }
    }

    while (i < p) {
        arr[k ++] = left[i ++];
    }

    while (j < q) {
        arr[k ++] = right[j ++];
    }
}

void mergeSort(vector<int> &arr, int low, int high) {
    if (low >= high) return;
    int mid = low + (high - low) / 2;

    mergeSort(arr, low, mid);
    mergeSort(arr, mid+1, high);
    merge(arr, low, mid, high);
}