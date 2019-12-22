108 Maximum Sum
#include <bits/stdc++.h>
using namespace std ;

int main() {
    int n ;
    int dp[101][101] ;
    while(cin >> n) {
        for(int i = 0 ; i < n ; i++) {
            for(int j = 0 ; j < n ; j++) {
                cin >> dp[i][j] ;
                if(i > 0) {
                    dp[i][j] += dp[i - 1][j] ;
                }
                if(j > 0) {
                    dp[i][j] += dp[i][j - 1] ;
                }
                if(i > 0 && j > 0) {
                    dp[i][j] -= dp[i - 1][j - 1] ;
                }
            }
        }
        int maxsub = -1e7 ;
        for(int i = 0 ; i < n ; i++) {
            for(int j = 0 ; j < n ; j++) {
                for(int k = i ; k < n ; k++) {
                    for(int l = j ; l < n ; l++) {
                        int subrect = dp[k][l] ;
                        if(i > 0) {
                            subrect -= dp[i - 1][l] ;
                        }
                        if(j > 0) {
                            subrect -= dp[k][j - 1] ;
                        }
                        if( i > 0 && j > 0) {
                            subrect += dp[i - 1][j - 1] ;
                        }
                        maxsub = max(maxsub , subrect) ;
                    }
                }
            }
        }
        cout << maxsub << "\n" ;
    }

    return 0 ;
}
