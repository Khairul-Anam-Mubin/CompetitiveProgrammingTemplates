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

Here we discuss two problems at once. 
    Given a string s of length n. 
    In the first variation of the problem we want to count the number of appearances of each prefix s[0…i] in the same string. 
    In the second variation of the problem another string t is given and we want to count the number of appearances of each prefix s[0…i] in t.

vector<int> ans(n + 1);
for (int i = 0; i < n; i++)
    ans[pi[i]]++;
for (int i = n-1; i > 0; i--)
    ans[pi[i-1]] += ans[i];
for (int i = 0; i <= n; i++)
    ans[i]++;
