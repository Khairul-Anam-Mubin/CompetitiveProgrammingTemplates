/**************************Least Common Multiple***************************/
/*.........................LCM SUM...........................*/

/* Given n, calculate the sum LCM(1,n)+LCM(2,n)+…+LCM(n,n), where LCM(i,n) denotes the Least Common Multiple of the integers i and n.*/

#include <bits/stdc++.h>
 
#define FOR(i,x,y) for(vlong i = (x) ; i <= (y) ; ++i)
 
using namespace std;
typedef long long vlong;
 
vlong res[1000010];
vlong phi[1000010];
 
void precal( int n ) {
    // Calculate phi from 1 to n using sieve
    FOR(i,1,n) phi[i] = i;
    FOR(i,2,n) {
        if ( phi[i] == i ) {
        for ( int j = i; j <= n; j += i ) {
            phi[j] /= i;
            phi[j] *= i - 1;
        }
    }
 }
 
 // Calculate partial result using sieve
 // For each divisor d of n, add phi(d)*d to result array
 FOR(i,1,n){
    for ( int j = i; j <= n; j += i ) {
        res[j] += ( i * phi[i] );
    }
 }
}
 
int main () {
    precal( 1000000 );
 
    int kase;
    scanf ( "%d", &kase );
 
    while ( kase-- ) {
        vlong n;
        scanf ( "%lld", &n );
 
        // We already have partial result in res[n]
        vlong ans = res[n] + 1;
        ans *= n;
        ans /= 2;
 
        printf ( "%lld\n", ans );
    }
 
    return 0;
}
