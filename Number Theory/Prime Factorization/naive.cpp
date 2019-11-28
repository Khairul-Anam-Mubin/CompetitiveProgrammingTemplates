#include <bits/stdc++.h>

using namespace std ;

// Complexity O(sqrt(N))
// it will work in upto 10^14

void PrimeFactorisation(long long x) {
    vector <long long> pf ;
    for(long long i = 2 ; i * i <= x ; i++) {
        if(x % i == 0) {
            while(x % i == 0) {
                x /= i ;
                pf.push_back(i) ;
            }
        }
    }
    if(x != 1)
        pf.push_back(x) ;

    // printing the prime factors..
    for(long long i = 0 ;  i < pf.size() ; i++) {
        cout << pf[i] << " " ;
    }
}
int main() { 
    long long n ;
    while(cin >> n) {
        PrimeFactorisation(n) ; // getting the prime factors of n..
        cout << "\n" ;
    }
    return 0 ;
}
