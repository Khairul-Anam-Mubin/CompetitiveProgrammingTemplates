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
int sumofcoprimesN(int n){
    int x = phi(n);
    int ans = (x * n) / 2 ;
    return ans;
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
****//

// leading zero..
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
