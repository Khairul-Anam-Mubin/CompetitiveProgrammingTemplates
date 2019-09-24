// Floyed Warshall Algorithm
// All pair shortest path
// The ALgorithm..
for(int k = 1 ; k <= 100 ; k++) {
            for(int i = 1 ; i <= 100 ; i++) {
                for(int j = 1 ; j <= 100 ; j++) {
                    dp[i][j] = min(dp[i][j] , dp[i][k] + dp[k][j]) ;
                }
            }
        }

// Uva : 821 - Page Hopping
// Floyed Warshall
// DP
// all pair shortest path

int main() {
    int u , v , tc = 0 ;
    while(scanf("%d%d",&u,&v) == 2) {
        if(u == 0 && v == 0)
            break ;
        int dp[110][110] ;
        for(int i = 0 ; i < 110 ; i++)
            for(int j = 0 ; j < 110 ; j++)
                dp[i][j] = MOD ;
        dp[u][v] = 1 ;
        while(scanf("%d%d",&u,&v) == 2) {
            if(u == 0 && v == 0)
                break ;
            dp[u][v] = 1 ;
        }
        for(int k = 1 ; k <= 100 ; k++) {
            for(int i = 1 ; i <= 100 ; i++) {
                for(int j = 1 ; j <= 100 ; j++) {
                    dp[i][j] = min(dp[i][j] , dp[i][k] + dp[k][j]) ;
                }
            }
        }
        double sum = 0 , cnt = 0 ;
        for(int i = 1 ; i <= 100 ; i++) {
            for(int j = 1 ; j <= 100 ; j++) {
                if(i != j && dp[i][j] != MOD) {
                    sum += dp[i][j] ;
                    cnt++ ;
                }
            }
        }
        printf("Case %d: average length between pages = %0.3lf clicks\n",++tc ,sum / cnt) ;
    } 
    return 0 ;
}
