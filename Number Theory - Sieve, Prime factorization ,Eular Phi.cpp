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
// returning sum of divisors of N
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

void FactorialFactorisation(ll n) {
    dp[1] = 0 ;
    for(int i = 2 ; i <= mx - 9 ; i++) {
        dp[i] = dp[i - 1] ;
        ll x = i ;
        for(ll j = 0 ; j < prime.size() && prime[j] * prime[j] <= x ; j++) {
            if(x % prime[j] == 0) {
                while(x % prime[j] == 0) {
                    x /= prime[j] ;
                    dp[i]++ ;
                }
            }
        }
        if(x != 1)
            dp[i]++ ;
    }
}
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
