#include <bits/stdc++.h>
using namespace std ;

#define mxN 1000000

bool isp[mxN + 10];
vector <int> prime; // all the primes <= mxN
vector <pair <int , int>> ff; // storing factorial factorization as p^q pair(p , q) 

void Sieve() { 
    isp[0] = isp[1] = 1 ;
    for (int i = 4 ; i <= mxN ; i += 2)
        isp[i] = 1;
    for (int i = 3 ; i * i <= mxN ; i += 2) {
        if (isp[i] == 0) {
            for (int j = i * i ; j <= mxN ; j +=(i + i)) {
                isp[j] = 1;
            }
        }
    }
    prime.push_back(2);
    for (int i = 3 ; i <= mxN ; i += 2) {
        if (isp[i] == 0) {
            prime.push_back(i);
        }
    }
}
void FactFactorize(int n) {
    for (int i = 0 ; i < prime.size() && prime[i] <= n ; i++) {
        int x = n;
        int freq = 0;
        int tmp = prime[i];
        while (x / tmp) {
            freq += x / tmp ;
            tmp *= prime[i] ;
        }
        ff.push_back(make_pair(prime[i] , freq)) ;
    }
}
int main() {
    Sieve();
    int n ; cin >> n;
    FactFactorize(n);
    for (int i = 0; i < ff.size(); i++) {
        cout << ff[i].first << "^" << ff[i].second << "\n";
    }
    return 0;
}