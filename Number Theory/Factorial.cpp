/**************************Number of digits in N! in any base*****************************/
/* Given a nunmebr n , finds its digits in N! in base b.*/

#include <bits/stdc++.h>
using namespace std ;

#define eps 1e-9
#define mxN 1000000
double save[mxN + 10] ;

void precal() {
    for(int i = 1 ; i <= mxN ; i++)
        save[i] = log10(i) ;
    save[0] = 0 ;
    for(int i = 2 ; i <= mxN ; i++)
        save[i] += save[i - 1] ;
}
long long factorialdigitextended(long long num , long long base) {
    double x = save[num] / log10(base) ;
    long long res = x + 1 + eps ;
    return res ;
}
int main() {
    precal() ;
    int tc , test = 0 ;
    cin >> tc ;
    while(tc--) {
        long long num , base ;
        cin >> num >> base ;
        long long ans = factorialdigitextended(num , base) ;
        cout << "Case " << ++test << ": " << ans << "\n" ;
    }
    return 0 ;
}
