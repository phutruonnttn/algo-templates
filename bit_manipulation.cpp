// Number_of_set_bits (number of bit 1)
int: __builtin_popcount(x);
long long: __builtin_popcountll(x);

// LSB – rightmost 1
int x = 40;          // 101000
int lowest = x & -x; // 1000 = 8

int pos = __builtin_ctz(x); // ctz = Count Trailing Zeros

long long: __builtin_ctzll(x);

// MSB – leftmost 1
int pos = 31 - __builtin_clz(x); // clz: Count Leading Zeros
int highest = 1 << (31 - __builtin_clz(x));

long long: __builtin_clzll(x);
