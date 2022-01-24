#include <bits/stdc++.h>
using namespace std;

/************************Manacher's Algorithm*****************************/
/*
    Algorithm:
    1. Finds all sub-palindromes in O(N)
    
    Applications:
    1. Finds Longest Palindromes O(N)
*/
/*
    Guide:

    1. string is 0 based indexed of length n.
    2. the manacher will make a string of length 2 * n + 1. 
        ex: "abba" will be "#a#b#b#a#".
    3. Odd length palindromes: 
        for all i = 0 to i < n
            i is a center and stored maxlen palindrome in 2i + 1 th index in P.
    4. Even length palindromes: 
        there are n - 1 centered positions. 
        for all i = 0 to i < n - 1
            max length palindrome centered at i found in 2i + 2 th index in P.
*/
vector<int> Manacher_Odd_Length(string T) {
    int n = T.size();
    vector <int> P(n);
    int C = 0, R = -1, rad; 
    for (int i = 0; i < n; ++i) {
        if (i <= R) {
            rad = min(P[2 * C - i], R - i); 
        } else {
            rad = 0; 
        }
        // Try to extend
        while (i + rad < n && i - rad >= 0 && T[i - rad] == T[i + rad]) {
            rad++; 
        }
        P[i] = rad;
        if (i + rad - 1 > R) {
            C = i; 
            R = i + rad - 1; 
        }
    }
    for (int i = 0; i < (int)P.size(); i ++) {
        P[i]--;
    }
    return P;
}
vector <int> Manacher(const string &s) {
    string t;
    for(auto c: s) {
        t += string("#") + c;
    }
    return Manacher_Odd_Length(t + "#");
}
string LongestPalindrome(const string &s) {
    vector <int> P = Manacher(s);
    int mxlen = 0, startpos = -1;
    for (int i = 0; i < (int)s.size(); i++) {
        if (mxlen < P[2 * i + 1]) {
            mxlen = P[2 * i + 1];
            startpos = i - P[2 * i + 1] / 2;
        }
    }
    for (int i = 0; i < (int)s.size() - 1; i++) {
        if (mxlen < P[2 * i + 2]) {
            mxlen = P[2 * i + 2];
            startpos = i - P[2 * i + 2] / 2 + 1;
        }
    }
    return s.substr(startpos, mxlen);
}
int main() {
    cin.tie(0);
    cout.tie(0);

    string s; cin >> s;
    cout << LongestPalindrome(s) << "\n";
    return 0;
}