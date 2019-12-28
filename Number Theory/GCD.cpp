/*******************************Greatest common divisor************************/
/*............................GCD SUM...................................*/
/* Given N , find all possible pair gcd(i,j) sum upto n, where i != j */

#include <bits/stdc++.h>
using namespace std ;

int prime[ (2*maxl) + 2];
ll ans[maxl + 3], phi[maxl + 2]; //declaring the arrays of prime and phi

void EulersPhiSeive() //we'll find phi and primes till n
{
    memset(ans, 0, sizeof ans);

    for(int i = 1; i <= maxl; i++) phi[i] = i, prime[i] = 0; //initializing the members of phi

    phi[1] = 0;   //initializing the first element
    prime[1] = 1; //initializing the first element

    for(int i = 2; i <= maxl; i++)
    {
        if(!prime[i])   //if the number is prime
        {
            for(int j = i;j <= maxl; j += i)
            {
                prime[j+i] = 1;   //all the numbers that are divisible by i are not prime
                phi[j] = (phi[j] / i) * (i-1);    //for the phi of a number n, we divide n with a prime number p such that n is divisible by p
                                            // and multiply it by (p-1), so we get the phi
            }
        }
    }

    for(ll i = 1; i <= maxl; i++){
        for(ll j = i + i; j <= maxl; j += i){
            ans[j] += ( phi[j / i] * i );
        }
    }
    for(int i = 1; i <= maxl; i++) ans[i] += ans[i - 1];

}
int main()
{
    EulersPhiSeive();
    int n;
    while(scanf("%d",&n) == 1 && n){
        printf("%lld\n",ans[n]);
    }

    return 0;
}
