/**********************Factorial Factorization************************/
/*.Given a number n , find all its factorial factorisations.*/

#include <bits/stdc++.h>
using namespace std ;

#define mxN 100

bool isp[mxN + 10] ;
vector <int> prime ;
vector <pair <int , int>> fac[mxN + 10] ;

void sieve(){
    isp[1] = 1 ;
    for(int i = 4 ; i <= mxN ; i += 2)
        isp[i] = true;
    for(int i = 3 ; i * i <= mxN ; i += 2)
        if(!isp[i])
            for(int j = i * i ; j <= mxN ; j +=(i + i))
                isp[j] = true;
    prime.push_back(2);
    for(int i = 3 ; i <= mxN ; i += 2)
        if(!isp[i])
            prime.push_back(i);
}
void facFactorize(int n , vector <pair<int , int>> &v) {
    for(int i = 0 ; i < prime.size() && prime[i] <= n ; i++) {
        int x = n ;
        int freq = 0 ;
        while(x / prime[i]) {
            freq += x / prime[i] ;
            x /= prime[i] ;
        }
        v.push_back(make_pair(prime[i] , freq)) ;
    }
}
void precal() {
    for(int i = 2 ; i <= mxN ; i++) {
        facFactorize(i , fac[i]) ;
    }
}
int main() {
    sieve() ;
    precal() ;
    int tc , test = 0 ;
    cin >> tc ;
    while(tc--) {
        int n ;
        cin >> n ;
        cout << "Case " << ++test << ": " ;
        cout << n << " = " ;
        for(int i = 0 ; i < fac[n].size() ; i++) {
            if(i + 1 == fac[n].size()) {
                cout << fac[n][i].first << " (" << fac[n][i].second << ")\n" ;
            } else {
                cout << fac[n][i].first << " (" << fac[n][i].second << ") * " ;
            }
        }
    }
    return 0 ;
}
