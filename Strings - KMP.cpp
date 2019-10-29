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

// Freq counting....
// 1255 - Substring Frequency
// Light OJ
#include <bits/stdc++.h>

using namespace std ;

char pattern[1000001] , text[1000001] ;
int pfix[1000001] ;
void BuildPrefixArray() {
    int len = strlen(pattern) ;
    pfix[0] = 0 ;
    for(int i = 1 , j = 0 ; i < len ; ) {
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
}
int KMP() {
    BuildPrefixArray() ;
    int len1 = strlen(text) ;
    int len2 = strlen(pattern) ;
    int cnt = 0 ;
    for(int i = 0 , j = 0 ; i < len1 && j < len2 ; ) {
        if(text[i] == pattern[j]) {
            i++ ;
            j++ ;
        }
        else {
            if(j == 0) 
                i++ ;
            else
                j = pfix[j - 1] ;
        }
        if(j == len2) {
            cnt++ ;
            j = pfix[j - 1] ;
        }
    }
    return cnt ;
}
int main() {
    int tc , test = 0 ;
    scanf("%d" ,&tc) ;
    while(tc--) {
        scanf("%s%s" ,text , pattern) ;
        int ans = KMP() ;
        printf("Case %d: %d\n" ,++test , ans) ; 
    }
    return 0 ;
}
