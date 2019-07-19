// CodeForces C. Basketball Exercise
// Dp with maximum sum problem of two array

#include <bits/stdc++.h>
using namespace std ;
ll n  ; 
ll ar[2][100010] ;
ll dp[2][100010] ; // This is the part of memoization / dp..Not using this causes TLE.. 

// In each recurance I am just going forward and changing the row along with the max current sum. 
ll dfs(ll pos , ll mark) { 
	if( pos >= n) // if I am in the last index simply returning..
		return 0 ;

if(dp[mark][pos])
		return dp[mark][pos] ; // returning the previous calculated sum..

// Here i am taking the array elements and further going forward. and changing the row.
	// and other is not to take the array elements and not to change row just go forward
	// Over all maximum saving and returning..
	return dp[mark][pos] = max (ar[mark][pos] + dfs(pos + 1 , !mark) , dfs(pos + 1 , mark))  ; 
}
int main() {
	cin >> n ;
	for(int i = 0 ; i < 2 ; i++) {
		for(int j = 0 ; j < n ; j++) {
			cin >> ar[i][j] ;
		}
	}
	Fill0(dp) ;
	ll ans = max(dfs(0 , 0) , dfs(0 , 1)) ; // going with row 0 then 1 from pos 0. which returning us the maximum that's the answer.
	cout << ans << "\n";
	return 0 ;
}
