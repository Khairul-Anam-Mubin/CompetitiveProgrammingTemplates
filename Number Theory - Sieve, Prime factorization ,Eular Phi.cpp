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
