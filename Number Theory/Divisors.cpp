/*************************************Divisors********************************/
// Complexity : O(sqrt(n))

#include <bits/stdc++.h>
using namespace std ;

vector <long long> vec ;
void divisors(long long n) {
    vec.clear() ;
    for(long long i = 1 ; i * i <= n ; i++) {
        if(n % i == 0) {
            vec.push_back(i) ;
            if(i * i != n)
                vec.push_back(n / i) ;
        }
    } 
}
