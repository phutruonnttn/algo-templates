class Solution {
    public:
        int strStr(string haystack, string needle) {
            // Rabin-Karp algorithm
            int n = haystack.size(), m = needle.size();
    
            if (n < m) {
                return -1;
            }
    
            // Step 1: Choose K = 2
            // Step 2: Create mod[x] = (2 ^ x) % q;  
            int q = 1e9 + 7;  
            long mod[n];
            mod[0] = 1;
    
            for (int i = 1; i < n; i++) {
                mod[i] = (2 * mod[i-1]) % q;
            }
    
            // Step 3: Calculate the hash value of string needle
            int needleHash = 0;
            for (int i = 0; i < m; i++) { 
                needleHash = (needleHash * 2 + needle[i]) % q;
            }
    
            // Step 4: Calculate the hash value of first m characters in string haystack 
            int haystackHash = 0;
            for (int i = 0; i < m; i++) {
                haystackHash = (haystackHash * 2 + haystack[i]) % q;
            }
    
            // Update the hash value (rolling hash)
            for (int i = 0; i < n - m; i++) {
                if (haystackHash == needleHash) {
                    if (haystack.substr(i, m) == needle) { // O(M)
                        return i;
                    }
                }
    
                haystackHash = (2 * (haystackHash - haystack[i] * mod[m - 1]) + haystack[i + m]) % q;
                if (haystackHash < 0) {
                    haystackHash += q;
                }
            }
    
            if (haystackHash == needleHash) {
                if (haystack.substr(n - m, m) == needle) {
                    return n - m;
                }
            }
    
            return -1;
        }
    };