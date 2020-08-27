int RodCuttDP(int price[] ,int size[] ,int n,int len) {
    int dp[n + 5][len + 5] ;
    for(int i = 0 ; i <= n ; i++) {
        for(int j = 0 ; j <= len ; j++ ) {
            if(i == 0 || j == 0)
                dp[i][j] = 0 ;
            else if(size[i - 1] <= j) 
                dp[i][j] = max(dp[i - 1][j] , price[i - 1] + dp[i][j - size[i - 1]]) ;
            else 
                dp[i][j] = dp[i - 1][j] ;
        }
     } 
     return dp[n][len] ;
}
int main() {
    int n ;
    scanf("%d",&n);
    int size[n + 5] ;
    int price[n + 5] ;
    for(int i = 0 ; i < n ; i++) {
        cin >> price[i] ;
        cin >> size[i] ;
    }
    int len ;
    cin >> len ;
    int ans = RodCuttDP(price,size,n ,len) ;
    cout << " " << ans << "\n" ;
    return 0 ;
}
/* 
intput : 
4
2 1
5 2
7 3
8 4
5
output :
12
*/
