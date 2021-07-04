#include <bits/stdc++.h>
using namespace std;

/******************************** Number Theory (Prime and Prime Factorisation) *****************************/
/*
    1. Always set mxN
    2. Always Call once Sieve() from main function
    3. if nod or sod needed, call once SieveOfDivisors() from main
    4. if Eulers phi needed, call once SieveOfEulersPhi() from main
    5. now after initialization/build calls that you need, you can use IsPrime(n) , Nod(n), Sod(n), Phi(n)
*/
const long long mxN = 1e7;      // maximum value to precomputation, the most preferable mxN <= 1e7
bool isp[mxN + 1];              // marking primes <= mxN. if isp[i] = 0, then i is prime, else it's composite 
long long prime[mxN + 1];       // storing all primes <= mxN
long long tot_primes = 0;       // total number of primes generating through sieve
long long nod[mxN + 1];         // store nod <= mxN
long long sod[mxN + 1];         // store sod <= mxN
long long phi[mxN + 1];         // store phi <= mxN
long long pf_list[100];         // it can be proven that total number of prime factors always will be less then 100 
long long tot_pf = 0;           // total number of prime factors of a number

// Build Complexity : O(NloglogN) (Much faster Sieve)
void Sieve() {
    for (int i = 0; i <= mxN; i++) isp[i] = 0;            
    for (int i = 4; i <= mxN; i += 2) isp[i] = 1;         
    isp[0] = isp[1] = 1;                                  
    for (long long i = 3; i * i <= mxN; i += 2) {               
        if (isp[i] == 0) {                                
            for (long long j = i * i; j <= mxN; j += i + i) {   
                isp[j] = 1;                               
            }
        }
    }
    prime[tot_primes++] = 2;                               
    for (int i = 3; i <= mxN; i += 2) {
        if (isp[i] == 0) prime[tot_primes++] = i;
    }
}
// if n <= mxN, always query in O(1)
// else per query O(sqrtN)
// return 0 if prime, else return 1
bool IsPrime(long long n) {
    if (n <= mxN) return isp[n];
    if (n % 2 == 0) return 1;
    for (int i = 0; i < tot_primes; i++) {
        long long x = prime[i];
        if (x * x > n) return 0;
        if (n % x == 0) return 1;
    }
    return 0;
}
// if n <= mxN, works O(logN) per query
// if n >= mxN, most often works with O(logN) per query but sometimes goes O(sqrtN) in very rare.
// pf_list stores the prime factors and tot_pf is the number of prime factors of n
// example: n = 12 , the pf_list contains 2 , 2 , 3 and tot_pf = 3
void PrimeFactorization(long long n) {
    tot_pf = 0;
    for (int i = 0; i < tot_primes; i++) {
        long long x = prime[i];
        if (x * x > n) break;
        if (n <= mxN && isp[n] == 0) break;
        while (n % x == 0) {
            n /= x;
            pf_list[tot_pf++] = x;
        }
    }
    if (n != 1) pf_list[tot_pf++] = n;
}
// Build Complexity : O(NlogN)
void SieveOfDivisors() {
    for (int i = 0; i <= mxN; i++) {
        nod[i] = 0;
        sod[i] = 0;
    }
    for (int i = 1; i <= mxN; i++) {
        for (int j = i; j <= mxN; j += i) {
            nod[j] += 1;
            sod[j] += i;
        }
    }
}
// if n <= 1e7, always works with O(1) per query
// if n >= 1e7, most often works with O(logN) per query but sometimes goes O(sqrtN) in very rare.
int Nod(int n) {
    if (n <= mxN) return nod[n];
    int ans = 1;
    for (int i = 0; i < tot_primes; i++) {
        if (n <= mxN && isp[n] == 0) break;
        int x = prime[i];
        if (x * x > n) break; 
        if (n % x == 0) {
            int cnt = 1;
            while (n % x == 0) {
                n /= x;
                cnt += 1;
            }
            ans *= cnt;
        }
    }
    if (n != 1) ans *= 2;
    return ans;
}
// if n <= 1e7, always works with O(1) per query
// if n >= 1e7, most often works with O(logN) per query but sometimes goes O(sqrtN) in very rare.
long long Sod(long long n) {
    if (n <= mxN) return sod[n];
    long long ans = 1;
    for (int i = 0; i < tot_primes; i++) {
        if (n <= mxN && isp[n] == 0) break;
        long long x = prime[i];
        if (x * x > n) break;
        if (n % x == 0) {
            long long tmpsum = 1, p = 1;
            while (n % x == 0) {
                n /= x;
                p *= x;
                tmpsum += p;
            }
            ans *= tmpsum;
        }
    }
    if (n != 1) ans *= (n + 1LL);
    return ans;
}
// Build Complexity : O(NlogN)
void SieveOfEulersPhi() {
    for (int i = 0; i <= mxN; i++) phi[i] = 0;
    phi[1] = 1;
    for (int i = 2; i <= mxN; i++) {
        if (phi[i] == 0) {
            phi[i] = i - 1;
            for (int j = i + i; j <= mxN; j += i) {
                if (phi[j] == 0) phi[j] = j;
                phi[j] -= phi[j] / i;
            } 
        }
    }
}
// if n <= 1e7, always works with O(1) per query
// if n >= 1e7, most often works with O(logN) per query but sometimes goes O(sqrtN) in very rare.
long long Phi(long long n) {
    if (n <= mxN) return phi[n];
    long long coprime = n;
    for (int i = 0; i < tot_primes; i++) {
        if (n <= mxN && isp[n] == 0) break;
        long long x = prime[i];
        if (x * x > n) break;
        if (n % x == 0) {
            while (n % x == 0) n /= x;
            coprime -= coprime / x;
        }
    }
    if (n != 1) coprime -= coprime / n;
    return coprime;
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    Sieve();
    long long n; cin >> n;
    cout << IsPrime(n) << "\n";
    return 0;
}

// SubLinearSieve
// o(n) complexity
const int N = 10000000;
int lp[N+1];
vector<int> pr;

void LinearSieve() {
    for (int i=2; i<=N; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            pr.push_back (i);
        }
        for (int j = 0 ; j < (int)pr.size() && pr[j] <= lp[i] && i * pr[j] <= N ; ++j)
            lp[i * pr[j]] = pr[j];
    }
}


// Sum of Number of divisors in range 1 to N .
// Complexity O(sqrt(N))
int SNOD( int n ) {
    int res = 0;
    int u = sqrt(n);
    for ( int i = 1; i <= u; i++ ) {
        res += ( n / i ) - i; //Step 1
    }
    res *= 2; //Step 2
    res += u; //Step 3
    return res;
}

// sum of coprimes of n
int sumofcoprimesN(int n){
    int x = phi(n);
    int ans = (x * n) / 2 ;
    return ans;
}

// GCD Sum Function – g(n)
     //Given a positive integer N, find the value of g(N), where
     // g(n) = gcd(1,n) + gcd(2,n) + gcd(3,n) +⋯+ gcd(n,n) =  i=1 to n ∑ gcd(i,n)
ll GcdSum(ll x) {
    ll sq = sqrt(x) ;
    ll ans = 1LL ; 
    for(ll i = 0 ; i < prime.size() && prime[i] <= sq ; i++) {
        if(x % prime[i] == 0) {
            ll p = 0LL ;
            while(x % prime[i] == 0) {
                x /= prime[i] ;
                p++ ;
            }
            sq = sqrt(x) ;
            ans *= (((p + 1LL) * Pow(prime[i] , p)) - (p * Pow(prime[i] , p - 1LL))) ; 
        }
    }
    if(x != 1) {
        ans *= ((2 * x) - 1) ; 
    }
    return ans ;
}

// Linear Diophantine Equation
// Given the value of integers A,B and C find a pair of integers (x,y) such that it satisfies the equation Ax+By=C.
bool linearDiophantine ( int A, int B, int C, int *x, int *y ) {
    int g = gcd ( A, B );
    if ( C % g != 0 ) return false;  //No Solution
 
    int a = A / g, b = B / g, c = C / g;
    ext_gcd( a, b, x, y );  //Solve ax + by = 1
 
    if ( g < 0 ) {  //Make Sure gcd(a,b) = 1
        a *= -1; b *= -1; c *= -1;
    }
 
    *x *= c; *y *= c;  //ax + by = c
    return true;  //Solution Exists
} 
int main () {
    int x, y, A = 2, B = 3, C = 5;
    bool res = linearDiophantine ( A, B, C, &x, &y );
 
    if ( res == false ) printf ( "No Solution\n" );
    else {
        printf ( "One Possible Solution (%d %d)\n", x, y );
 
        int g = gcd ( A, B );
 
        int k = 1; //Use different value of k to get different solutions
        printf ( "Another Possible Solution (%d %d)\n", x + k * ( B / g ), y - k * ( A / g ) );
    }
 
 return 0;
}

// leading numbers ..
int main() {
    int tc ;
    scanf("%d",&tc) ;
    while(tc--) {
        ll n , k ;
        scanf("%lld%lld",&n,&k) ;
        ll lead , trail ;
        trail = BigMod(n , k , 1000LL) ;
        
        // leading zeros..
        double x = log10(n) * k ;
        double t = x - (int) x ;
        double p = pow(10 , t) ;
        lead = p * 100 ;
        
        printf("%03lld...%03lld\n",lead , trail) ;
    }
    return 0 ;
}
// Number of digits in a given number N..
int numberDigit ( int n ) {
    int Answer = log10(n) + 1 + eps; // This is right.
    return Answer;
}
// Number of digits in N! in decimal base..
int factorialDigit ( int n ) {
    double x = 0;
    for ( int i = 1; i <= n; i++ ) {
        x += log10 ( i );
    }
    int res = x + 1 + eps;
    return res;
}
// Number of digits in N! in any base..
int factorialDigitExtended ( int n, int base ) {
    double x = 0;
    for ( int i = 1; i <= n; i++ ) {
        x += log10 ( i ) / log10(base); // Base Conversion
    }
    int res = x + 1 + eps;
    return res;
}

// factorial prime factorization...
void factFactorize ( int n ) {
    for ( int i = 0; i < prime.size() && prime[i] <= n; i++ ) {
        int x = n;
        int freq = 0;
 
        while ( x / prime[i] ) {
            freq += x / prime[i];
            x = x / prime[i];
        }
        printf ( "%d^%d\n", prime[i], freq );
    }
}
// n! mod p 
// complexity PlogpN
int factmod(int n, int p) {
    int res = 1;
    while (n > 1) {
        res = (res * ((n/p) % 2 ?  p-1 : 1)) % p;
        for (int i = 2; i <= n%p; ++i)
            res = (res * i) % p;
        n /= p;
    }
    return res % p;
}


// Find the first K digits of N!
int leadingDigitFact ( int n, int k ) {
    double fact = 0;
 
    // Find log(N!)
    for ( int i = 1; i <= n; i++ ) {
        fact += log10 ( i );
    }
 
    // Find the value of q
    double q = fact - floor ( fact+eps );
 
    double B = pow ( 10, q );
 
    // Shift decimal point k-1 \times
    for ( int i = 0; i < k - 1; i++ ) {
        B *= 10;
    }
 
    // Don't forget to floor it
    return floor(B+eps);
}

// Chinese remainder theorem...
// Given two sequences of numbers A=[a1,a2,…,an] and M=[m1,m2,…,mn], 
//find the smallest solution to the following linear congruence equations if it exists:
    x ≡ a1(mod m1)
    x ≡ a2(mod m2)
    …
    x ≡ an(mod mn)
        
/** Works for non-coprime moduli.
 Returns {-1,-1} if solution does not exist or input is invalid.
 Otherwise, returns {x,L}, where x is the solution unique to mod L
*/
pair<int, int> chinese_remainder_theorem( vector<int> A, vector<int> M ) {
    if(A.size() != M.size()) return {-1,-1}; /** Invalid input*/
 
    int n = A.size();
 
    int a1 = A[0];
    int m1 = M[0];
    /** Initially x = a_0 (mod m_0)*/
 
    /** Merge the solution with remaining equations */
    for ( int i = 1; i < n; i++ ) {
        int a2 = A[i];
        int m2 = M[i];
 
        int g = __gcd(m1, m2);
        if ( a1 % g != a2 % g ) return {-1,-1}; /** No solution exists*/
 
        /** Merge the two equations*/
        int p, q;
        ext_gcd(m1/g, m2/g, &p, &q);
 
        int mod = m1 / g * m2; /** LCM of m1 and m2*/
 
        /** We need to be careful about overflow, but I did not bother about overflow here to keep the code simple.*/
        int x = (a1*(m2/g)*q + a2*(m1/g)*p) % mod;
 
        /** Merged equation*/
        a1 = x;
        if (a1 < 0) a1 += mod; /** Result is not suppose to be negative*/
        m1 = mod;
    }
    return {a1, m1};
}


// Number Theory
// Segmented Sieve 
// This is for Finding prime Numbers Upto 10^13 in a range 

#define mx 100000
bool isp[mx+10]; // prime numbers are marked indexed base here
vector <ll> prime; // all prime numbers stored in vector

// doing sieve upto mx and storing them..
void sieve()
{
    isp[1] = true;
    for(ll i = 4 ; i <= mx ; i += 2)
        isp[i] = true;
    for(ll i = 3 ; i*i <= mx ; i += 2)
        if(isp[i] == false)
            for(ll j = i*i ; j <= mx ; j +=(i+i))
                isp[j] = true;
    prime.pb(2);
    for(ll i = 3 ; i <= mx ; i += 2)
        if(isp[i] == false)
            prime.pb(i);
}

//returns the vectors where the prime genereted between a,b
//if isp2[j-a] == false then 'j' is prime where 'a' is the lower bound of the given range
vector<bool> segmented(ll a , ll b)
{
    ll psize = prime.size();

    ll siz = b + a - 1;
    vector <bool>isp2(siz+1,0);
    ll sq = (ll)sqrt(b) + 1;
    if(a == 1)
        a++;
    for(ll i = 0 ; i < psize && prime[i] <= sq ; i++){
        ll p = prime[i];
        ll j = p*p;
        if(j < a)
            j = ((a + p - 1)/p) * p;
        for( ; j <= b ; j += p )
            isp2[j-a] = true;
    }
    return isp2;
}

// The above code returns Fn and Fn+1 as a pair..
//where Fn and Fn+1 is nth and nth + 1 fibonacci number respectively
pair<int, int> fib (int n) {
    if (n == 0)
        return {0, 1};

    auto p = fib(n >> 1);
    int c = p.first * (2 * p.second - p.first);
    int d = p.first * p.first + p.second * p.second;
    if (n & 1)
        return {d, c + d};
    else
        return {c, d};
}
