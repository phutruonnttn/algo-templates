// Prime sieve
vector<int> primes;
vector<bool> isPrime;

void buildSieve() {
    isPrime.assign(maxN + 1, true);
    if (maxN >= 0) isPrime[0] = false;
    if (maxN >= 1) isPrime[1] = false;

    primes.clear();
    for (int i = 2; i <= maxN; ++i) {
        if (!isPrime[i]) continue;
        primes.push_back(i);

        if (1LL * i * i > maxN) continue;
        for (int j = i * i; j <= maxN; j += i) {
            isPrime[j] = false;
        }
    }
}

//-----------------------------------------------
class Solution {
    public:
        const int maxN = 100000;
        vector<int> spf;   // smallest prime factor
    
        void buildSPF() {
            spf.assign(maxN + 1, 0);
            for (int i = 2; i <= maxN; ++i) spf[i] = i;
    
            for (int i = 2; i * i <= maxN; ++i) {
                if (spf[i] != i) continue; // not prime
                for (int j = i * i; j <= maxN; j += i) {
                    if (spf[j] == j) spf[j] = i;
                }
            }
        }
    
        int sumFourDivisors(vector<int>& nums) {
            buildSPF();
            int ans = 0;
    
            for (int n : nums) {
                if (n < 2) continue;
    
                // factorize n using SPF
                int x = n, p1 = 0, e1 = 0, p2 = 0, e2 = 0;
                bool check = true;
    
                while (x > 1) {
                    int p = spf[x];
                    int e = 0;
                    while (x % p == 0) { 
                        x /= p; 
                        ++e; 
                    }
    
                    if (p1 == 0) { 
                        p1 = p; 
                        e1 = e; 
                    } else if (p2 == 0) { 
                        p2 = p; 
                        e2 = e; 
                    } else { // > 2 distinct prime factors
                        check = false; 
                        break; 
                    } 
    
                    if (e > 3) { // exponent too big for 4 divisors
                        check = false; 
                        break; 
                    } 
                }
                if (!check) continue;
    
                // case: p^3
                if (p2 == 0 && e1 == 3) {
                    ans += 1 + p1 + p1 * p1 + p1 * p1 * p1; // 1 + p + p^2 + p^3
                    continue;
                }
    
                // case: p*q
                if (p2 != 0 && e1 == 1 && e2 == 1) {
                    ans += 1 + n + p1 + p2; // 1 + p + q + pq
                }
            }
    
            return ans;
        }
    };