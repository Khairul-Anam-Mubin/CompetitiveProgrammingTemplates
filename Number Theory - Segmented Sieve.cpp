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
