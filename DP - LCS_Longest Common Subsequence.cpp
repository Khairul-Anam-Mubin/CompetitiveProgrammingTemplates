// Uva : 10192 - Vacation

#include <bits/stdc++.h>
using namespace std ;

int LCS(string a , string b) {
    int dp[300][300] ;
    int alen = a.size() , blen = b.size() ;
    for(int i = 0 ; i <= alen ; i++) {
        for(int j = 0 ; j <= blen ; j++) {
            if(i == 0 || j == 0) // base case..
                dp[i][j] = 0 ;
            else if(a[i - 1] == b[j - 1]) 
                dp[i][j] =  1 + dp[i - 1][j - 1] ; // if match digonally value + 1
            else
                dp[i][j] = max(dp[i - 1][j] , dp[i][j - 1]) ; // if not taking max(previous row,previos column)
        }
    }
    return dp[alen][blen] ; // returning LCS 
}
int main() {
    //Fin , Fout ;
    string a , b ;
    int tc = 0 ;
    while(getline(cin ,a) && a[0] != '#') {
        getline(cin , b) ;
        int ans = LCS(a , b) ;
        cout << "Case #" << ++tc << ": you can visit at most "<< ans << " cities.\n" ;    
    }
    return 0 ;
}
