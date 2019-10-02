//DP - Longest Pallindromic Subsequence
//11151 - Longest Palindrome
// complexity O(n^2)

int dp[1001][1001] ;
int main() {
    //Fin , Fout ;
    //Fast ;
    int tc ;
    cin >> tc ;
    getchar() ;
    while(tc--) {
        string str ;
        getline(cin , str) ;
        int len = str.size() ;
        // longest pallindromic subsequence...
        Fill0(dp) ;
        for(int i = 0 ; i <= len ; i++)
            dp[i][i] = 1 ;
        for(int cur = 2 ; cur <= len ; cur++) {
            for(int i = 0 ; i < len - cur + 1 ; i++) {
                int j = i + cur - 1 ;
                if(cur == 2 && str[i] == str[j] )  {
                    dp[i][j] = 2 ;
                }
                else if(str[i] == str[j]) {
                    dp[i][j] = dp[i + 1][j - 1] + 2 ;
                }
                else
                    dp[i][j] = max(dp[i + 1][j] , dp[i][j - 1]) ;
            }
        }
        int ans = dp[0][len - 1] ;
        
        cout << ans << "\n" ;
    }

    return 0 ;
}
