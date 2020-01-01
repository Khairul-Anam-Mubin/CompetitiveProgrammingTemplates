/**********************************Eulers Phi********************************/
/*.............................Genereationg co-primes..........................*/

/* Given a range of a , b <= 5*10^6 and have to find sum of all phi(i) * phi(i) in range a to b.*/

#include <bits/stdc++.h>
using namespace std ;

#define mxN 5000000
unsigned long long phi[mxN + 10] ;

void PreCalPhi() {
    // generating....
    phi[0] = 0 ;
    phi[1] = 1 ;
    for(int i = 2 ; i <= mxN ; i++) {
        if(phi[i] == 0) {
            phi[i] = i - 1 ;             
            for(int j = i + i ; j <= mxN ; j += i) {
                if(phi[j] == 0)
                    phi[j] = j ;
                phi[j] -= (phi[j] / i) ;
            }
        }
    }
    for(int i = 1 ; i <= mxN ; i++)
        phi[i] = (phi[i] * phi[i]) ;
    // Cumulative sum for range sum query...
    for(int i = 1 ; i <= mxN ; i++)
        phi[i] += phi[i - 1] ;
}
int main() {
    PreCalPhi() ;
    int tc , test = 0 ;
    cin >> tc ;
    while(tc--) {
        int a , b ;
        cin >> a >> b ;
        if(a > b)
            swap(a , b) ;
        cout << "Case " << ++test << ": " ;
        cout << phi[b] - phi[a - 1] << "\n" ;
    }
    return 0 ;
}
