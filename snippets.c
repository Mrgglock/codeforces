// qsort asc function
int asc(const void *pa, const void *pb) { return *(int *)pa - *(int *)pb; }
int desc(const void *pa, const void *pb) { return *(int *)pb - *(int *)pa; }
int ascPair(const void *pa, const void *pb) { 
    int *a = (int *)pa;
    int *b = (int *)pb;
    if (a[0] == b[0]) return a[1] - b[1];
    else return a[0] - b[0];
}
int ascPairSecond(const void *pa, const void *pb) { 
    int *a = (int *)pa;
    int *b = (int *)pb;
    if (a[1] == b[1]) return a[0] - b[0];
    else return a[1] - b[1];
}

// ceil(a / b) ! HAS TO BE WELL DEFINED ! b > 0, a >= 0
static inline int ceilDivide(int a, int b) { return a / b + (a % b != 0); }

// abs(a) returns the magnitude of a
static inline int abs(int a) { return (a < 0) ? a * -1 : a; }

// BINARY SEARCH an array, start and end indices included, for a number.
#include <stdbool.h>
bool contains(int *array, int start, int end, int num) {
    if (start == end) return array[start] == num;
    if (end - start == 1) return (array[start] == num || array[end] == num);
    int mid = start + (end - start) / 2;
    if (array[mid] == num) return true;
    if (num < array[mid]) return contains(array, start, mid - 1, num);
    return contains(array, mid + 1, end, num);
}

// BINARY SEARCH an array, start and end indices included, for the smallest number that is greater than or equal to num.
// returns the iterator (index) of the element if it exists, -1 if not
int containsMinMoreOrEqual(int *array, int start, int end, int num) {
    if (start == end) {
        if (array[start] >= num) return start;
        else return -1;
    }
    int mid = start + (end - start) / 2;
    if (mid < num) return containsMinMoreOrEqual(array, mid + 1, end, num);
    return containsMinMoreOrEqual(array, start, mid, num);
}

// nCr % mod function
// Using Fermat's Little theorem: a^(p-2) = a^(-1) (mod p)

#define _1e9plus7 1000000007

// Calculate base ^ pow % mod
long long modPower(long long base, int pow, int mod)
{
    long long res = 1;
    base %= mod;
    // constantly decompose base ^ pow = (base ^ 2) ^ (pow / 2)
    while (pow > 0) {
        // make sure if it is odd, then base ^ pow = base ^ (pow - 1) * base
        if (pow % 2 == 1) res = res * base % mod;
        pow /= 2;
        base = (base * base) % mod;
    }
    return res;
}

// a ^ (p - 2) = a ^ (-1) (mod p)
long long modInverse(long long n, int mod) {
    return modPower(n, mod - 2, mod);
}

// nCr = n! / r! / (n - r)!
// nCr = n! * inv(r!) * inv((n - r)!)
long long nCrModP(unsigned long long n, int r, int mod) {
    // Base cases
    if (n < r) return 0;
    if (r == 0) return 1;

    // Build factorial array
    long long fac[n + 1];
    fac[0] = 1;
    for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod; 
    return fac[n] * modInverse(fac[r], mod) % mod
           * modInverse(fac[n - r], mod) % mod;
}



// PRIME SIEVING: FILL PRIMES; PRIME FACTORISATION.

#include <stdbool.h>
#define sieve_size 50000 // sqrt(10^9) - an int. guarantees that all prime factors up to that will be generated
// increase the sieve_size to 10^9 to process `long long`s.
bool isPrime[sieve_size]; // isPrime[n] returns true if n is a prime; false if not.
int prime[sieve_size]; // array of prime numbers - 5133 in the first 49999 numbers.
int numberOfPrimes; // = 5133 in the first 49999 numbers.

// Call this function to init prime sieving.
void fill_primes(int n) {
    for (int i = 0; i < n; ++i) isPrime[i] = true;
    isPrime[0] = false;
    isPrime[1] = false;
    // Prime sieving - https://cp-algorithms.com/algebra/sieve-of-eratosthenes.html
    for (int i = 2; i < n; ++i) {
        if (!isPrime[i]) continue;
        if ((long long) i * i >= n) break;
        for (int j = i * i; j < n; j += i) isPrime[j] = false;
    }
    // Fill `primes` array.
    int j = 0;
    for (int i = 0; i < n; ++i) {
        if (isPrime[i]) {
            prime[j] = i;
            ++j;
        }
    }
    // store length of primes array
    numberOfPrimes = j;
}

// Count the number of prime factors an int has.
int numberOfPrimeFactors(int a) {
    int count = 0;
    // Go through every prime factor, up to (and including) sqrt(a).
    for (int i = 0; prime[i] * prime[i] <= a; ++i) {
        while (a % prime[i] == 0) {
            ++count;
            a /= prime[i];
        }
    }
    // If a is still not 1, this number itself is a prime (as we have already went through every factor up to (and including) sqrt(a)).
    if (a > 1) ++count;
    return count;
}

