int mod = 1e9 + 7;

class Solution {
public:
    class Matrix22 {
        public: 
            long long a, b, c, d;

            Matrix22 (int a, int b, int c, int d) {
                this->a = a;
                this->b = b;
                this->c = c;
                this->d = d;
            }

            Matrix22* multiplied(Matrix22 *other) {
                long long newA = a * other->a % mod + b * other->c % mod;
                long long newB = a * other->b % mod + b * other->d % mod;
                long long newC = c * other->a % mod + d * other->c % mod;
                long long newD = c * other->b % mod + d * other->d % mod;
                return new Matrix22(newA, newB, newC, newD);
            }

            Matrix22* pow(int n) {
                if (n == 1) {
                    return this;
                }

                Matrix22* hafl = pow(n / 2);
                if (n % 2) {
                    return multiplied(hafl->multiplied(hafl));
                } else {
                    return hafl->multiplied(hafl);
                }
            }
    };

    int countHousePlacements(int n) {
        Matrix22 *A = new Matrix22(1, 1, 1, 0);
        Matrix22 *M = A->pow(n + 1);

        return (M->a * M->a) % mod;
    }
};