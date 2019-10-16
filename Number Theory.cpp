// Number Theory 
// Sieve of eratosthenes(Generating Prime), Prime Factorization
// Eular Totient(Phi) / Number of co-prime of a Numebr 
// Sum of all co-primes of a number 

#define mx 50000
bool isp[mx+10];
vector <int> prime;

//sieve function for pre-calculate the primes..
void sieve(){
    for(int i = 4 ; i <= mx ; i += 2)
        isp[i] = true;
    for(int i = 3 ; i*i <= mx ; i += 2)
        if(!isp[i])
            for(int j = i*i ; j <= mx ; j +=(i+i))
                isp[j] = true;
    prime.pb(2);
    for(int i = 3 ; i <= mx ; i += 2)
        if(!isp[i])
            prime.pb(i);
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

// returning sum of divisors of N
// complexity of optimized prime factorization..
int SOD( int n ) {
    int res = 1;
    int sqrtn = sqrt ( n );
    for ( int i = 0; i < prime.size() && prime[i] <= sqrtn; i++ ) {
        if ( n % prime[i] == 0 ) {
            int tempSum = 1; // Contains value of (p^0+p^1+...p^a)
            int p = 1;
            while ( n % prime[i] == 0 ) {
                n /= prime[i];
                p *= prime[i];
                tempSum += p;
            }
            sqrtn = sqrt ( n );
            res *= tempSum;
        }
    }
    if ( n != 1 ) {
        res *= ( n + 1 ); // Need to multiply (p^0+p^1)
    }
    return res;
}

// returning number of divisors of N
// Complexity of oprimized prime factorization
int NOD ( int n ) {
    int sqrtn = sqrt ( n );
    int res = 1;
    for ( int i = 0; i < prime.size() && prime[i] <= sqrtn; i++ ) {
        if ( n % prime[i] == 0 ) {
            int p = 0; // Counter for power of prime
            while ( n % prime[i] == 0 ) {
                n /= prime[i];
                p++;
            }
            sqrtn = sqrt ( n );
            p++; // Increase it by one at end
            res *= p; // Multiply with answer
        }
    }
    if ( n != 1 ) {
        res *= 2; // Remaining prime has power p^1. So multiply with 2/
    }
    return res;
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

// Pre calculation sieve method..
// complexity of sieve..
#define mx 50000
int phi[mx + 10] ;
void PreCalPhi() {
    phi[1] = 1 ;
    for(int i = 2 ; i <= mx ; i++) {
        if(phi[i] == 0) {
            phi[i] = i - 1 ;
            for(int j = i + i ; j <= mx ; j += i) {
                if(phi[j] == 0) 
                    phi[j] = j ;
                phi[j] = phi[j] - (phi[j] / i) ;
            }
        }
    }
}

// returns the number of co-prime of a number
int phi(int n){
    //Assigning n is as it's co-prime
    int coprime = n ;
    int sz = prime.size();
    
    //This is the prime factorization part
    for(int  i = 0 ; i < sz && Sqr(prime[i]) <= n ; i++){
        if(n % prime[i] == 0){
            while(n % prime[i] == 0)
                n /= prime[i];
            coprime -= (coprime / prime[i]);
        }
    }
    if( n > 1)
        coprime -= (coprime / n);
    return coprime;
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
