// 0 - 1 knapsack with printing the included weight printing..
int knapsack01(int profit[] ,int weight[] , int items ,int capacity) {
    int dp[items][capacity] ;
    for(int i = 0 ; i <= items ; i++) {
        for(int w = 0 ; w <= capacity ; w++) {
            if(i == 0 || w == 0)
                dp[i][w] = 0 ;
            else if(weight[i - 1] <= w) 
                dp[i][w] = max(profit[i - 1] + dp[i - 1][w - weight[i - 1]] , dp[i - 1][w]) ;
            else
                dp[i][w] = dp[i - 1][w] ;
        }
    }
    cout << "\nitems included : \n" ;
    int res = dp[items][capacity] ;
    int w = capacity ;
    for (int i = items ; i > 0 && res > 0; i--) { 
          
        // either the result comes from the top 
        // (K[i-1][w]) or from (val[i-1] + K[i-1] 
        // [w-wt[i-1]]) as in Knapsack table. If 
        // it comes from the latter one/ it means  
        // the item is included. 
        if (res == dp[i - 1][w])  
            continue;         
        else { 
  
            // This item is included. 
            printf("%d ", weight[i - 1]); 
              
            // Since this weight is included its  
            // value is deducted 
            res = res - profit[i - 1]; 
            w = w - weight[i - 1]; 
        } 
    } 
    cout << "\n" ;
    return dp[items][capacity] ;
}
int main() {
    int items , capacity ;
    while(cin >> items >> capacity) {
        int profit[items + 5] ;
        int weight[items + 5] ;
        for(int i = 0 ; i < items ; i++) {
            cin >> profit[i] >> weight[i] ;
        }
        int ans = knapsack01(profit , weight ,items , capacity) ;
        cout << ans  << "\n" ;
    }
    return 0 ;
}
