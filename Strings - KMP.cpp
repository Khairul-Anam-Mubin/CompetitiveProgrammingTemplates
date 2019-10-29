// Complexity O(n + m)

#include <bits/stdc++.h>

using namespace std ;

// Building Prefix array
vector <int> BuildPrefixArray(string pattern) {
    vector <int> pfix(pattern.length()) ;
    pfix[0] = 0 ;
    for(int i = 1 ,j = 0 ; i < pattern.length() ; ) {
        if(pattern[i] == pattern[j]) {
            pfix[i] = j + 1 ;
            i++ ;
            j++ ;
        }
        else {
            if(j == 0) {
                pfix[i] = 0 ;
                i++ ;
            }
            else {
                j = pfix[j - 1] ;
            }
        }
    }
    return pfix ;
}
int Kmp(string text , string pattern) {
    vector <int> pfix = BuildPrefixArray(pattern) ;
    int cnt = 0 ;
    for(int i = 0 , j = 0 ; i < (int)text.length() && j < (int)pattern.length() ; ) {
        if(text[i] == pattern[j]) {
            i++ ;
            j++ ;
        }
        else {
            if(j == 0) {
                i++ ;
            }
            else {
                j = pfix[j - 1] ;
            }
        }
        if(j == (int)pattern.length()) {
            cnt++ ; // Number of occurances..
            j = pfix[j - 1] ;
        }
    }
    return cnt ;
}
int main() {
    string text , pattern ;
    cin >> pattern ;
    cin >> text ;
    cout << Kmp(text , pattern) << "\n" ; ;
    return 0 ;
}
