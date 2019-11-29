/*********************************Segment Tree**************************************/
/*...........................Range Sum Query Online............................*/

/* Given an array of length N , and Query the sum in range left and right..Array can be update in a particular 
position in each query.. */

#include <bits/stdc++.h>
using namespace std ;

#define mxN 10000
int segtree[mxN * 4] ;

// Building segmentree in O(n)
void Build(int ar[] , int cur , int left , int  right) {
    if(left == right) {
        segtree[cur] = ar[left] ;
        return ;
    }
    int mid = ( left + right ) / 2 ;
    Build(ar , cur * 2 , left , mid ) ;
    Build(ar , cur * 2 + 1 , mid + 1 , right) ;
    segtree[cur] = segtree[cur * 2] +  segtree[cur * 2 + 1] ;
    return ;
}
// Updating in O(logN)
void Update(int cur , int left , int right , int pos , int val) {
    if(left == right) {
        segtree[cur] = val ;
        return ; 
    }
    int mid = (left + right) / 2 ;
    if(pos <= mid) 
        Update(cur * 2 , left , mid , pos , val) ;
    else
        Update(cur * 2 + 1 , mid + 1 , right , pos , val) ;
    segtree[cur] = segtree[cur * 2] + segtree[cur * 2 + 1] ;
    return ;
}
// Query the sum in O(logN)
int SumQuery(int cur , int left ,int right , int i ,int j) {
    if(i > right || j < left)
        return 0 ;
    if(left >= i && right <= j)
        return segtree[cur] ;
    int mid = (left + right) / 2 ;
    int q1 = SumQuery(cur * 2 , left , mid , i , j) ;
    int q2 = SumQuery(cur * 2 + 1 , mid + 1 , right , i , j) ;
    return q1 + q2 ;
}
int main() {
    int n , cin >> n ;
    int ar[n + 5] ;
    for(int i = 0 ; i < n ; i++) 
        cin >> ar[i] ;
    // root is 1 , and left 0 and right n - 1 as O base indexed..
    Build(ar , 1 , 0 , n - 1) ; // Building the segtree.. 
    int query  , cin >> query ;
    while(query--) {
        int x , cin >> x ;
        if(x == 1) {
            int left , right , cin >> left >> right ;
            // from 1 to n we are searching left to right segment or range sum..
            int ans = SumQuery(1 , 1 , n , left , right) ; // returning range sum..
            cout << ans << "\n" ;
        }
        else if(x == 2) {
            int ind , val , cin >> ind >> val ;
            ar[ind] = val ; // updating index value..
            Update(1 , 1 , n , ind , val) ; // Updating segtree in index and new value..
        }
    }
    return 0 ;
}
