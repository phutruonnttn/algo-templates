class Solution {
    public:
        const int b = 29;
        const long long mod = 1e9 + 7, m2 = mod * mod;
    
        long long getHash(vector<long long>& hash, vector<long long>& base, int l, int r) {
            if (l == 0) {
                return hash[r] % mod;
            }
            return (hash[r] - hash[l - 1] * base[r - l + 1] + m2) % mod;
        }
    
        int strStr(string haystack, string needle) {
            int n = haystack.size(), m = needle.size();
    
            vector<long long> hash(n, 0);
            vector<long long> base(n, 0);
            hash[0] = haystack[0];
            base[0] = 1;
            for (int i = 1; i < n; i++) {
                hash[i] = (hash[i-1] * b + haystack[i]) % mod;
                base[i] = base[i - 1] * b % mod;
            }
    
            long long needleHash = needle[0];
            for (int i = 1; i < m; i++) {
                needleHash = (needleHash * b + (int)needle[i]) % mod;
            }
    
            for (int i = 0; i < n - m + 1; i++) {
                if (needleHash == getHash(hash, base, i, i + m - 1)) {
                    return i;
                }
            }
    
            return -1;
        }
    };