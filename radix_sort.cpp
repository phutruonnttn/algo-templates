void radixSort(vector<int>& a) {
    int base = 256; // 2^8
    int passed = 4; // 2^8^4 = 2^32 ~ 4 * 10^9 > 10^9
    int n = a.size();
    vector<int> tmp(n);
    vector<int> cnt(base);

    for (int pass = 0; pass < passed; ++pass){
        cnt.assign(base, 0);
        int shift = pass * 8; // follow base

        for (int i = 0; i < n; ++i) {
            ++cnt[(a[i] >> shift) & (base - 1)];
        }

        for (int i = 1; i < base; ++i) {
            cnt[i] += cnt[i - 1];
        }

        for (int i = n - 1; i >= 0; --i) {
            tmp[--cnt[(a[i] >> shift) & (base - 1)]] = a[i];
        }

        a.swap(tmp);
    }
}
