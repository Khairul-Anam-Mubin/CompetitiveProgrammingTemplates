/************************All Pair Shortest Path*********************/
/*........................ Floyd Warshal...................*/
/* all pair shortest path and path printing.......*/
// Complexity : O(V^3)

#include <bits/stdc++.h>
using namespace std ;

#define INF 1e18
#define mxN 1000

long long dp[mxN + 10][mxN + 10] ;
int path[mxN + 10][mxN + 10] ;

void printPath(int i, int j) {
    if(i != j) 
        printPath(i , path[i][j]);
    printf(" %d", j);
}
void FloyedWarshall(int nodes) {
    for(int i = 0 ; i <= nodes ; i++) {
        for(int j = 0 ; j <= nodes ; j++) {
            dp[i][j] = INF ;
            path[i][j] = i ;
            if(i == j)
                dp[i][j] = 0 ;
        }
    }
    for(int k = 1 ; k <= nodes ; k++) {
        for(int i = 1 ; i <= nodes ; i++) {
            for(int j = 1 ; j <= nodes ; j++) {
                if (dp[i][k] < INF && dp[k][j] < INF) {
                    dp[i][j] = min(dp[i][j] , dp[i][k] + dp[k][j]) ;
                    path[i][j] = path[k][j] ;
                }
            }
        }
    }
}

