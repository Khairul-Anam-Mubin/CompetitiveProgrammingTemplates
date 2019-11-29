/*********************************Segment Tree**************************************/

/*...........................Range Sum Query(Update Single)............................*/
/* Given an array of length N , and Query the sum in range left , right..Array can be update in a particular 
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
        segtree[cur] = val ; // updating the cur node by new value..
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
int SumQuery(int cur , int left ,int right , int l ,int r) {
    if(l > right || r < left)
        return 0 ;
    if(left >= l && right <= r)
        return segtree[cur] ;
    int mid = (left + right) / 2 ;
    int q1 = SumQuery(cur * 2 , left , mid , l , r) ;
    int q2 = SumQuery(cur * 2 + 1 , mid + 1 , right , l , r) ;
    return q1 + q2 ;
}
int main() {
    int n ; cin >> n ;
    int ar[n + 5] ;
    for(int i = 0 ; i < n ; i++) 
        cin >> ar[i] ;
    // root is 1 , and left 0 and right n - 1 as O base indexed..
    Build(ar , 1 , 0 , n - 1) ; // Building the segtree.. 
    int query ; cin >> query ;
    while(query--) {
        int x ; cin >> x ;
        if(x == 1) {
            int left , right ; cin >> left >> right ;
            // from 1 to n we are searching left to right segment or range sum..
            int ans = SumQuery(1 , 1 , n , left , right) ; // returning range sum..
            cout << ans << "\n" ;
        }
        else if(x == 2) {
            int ind , val ; cin >> ind >> val ;
            ar[ind] = val ; // updating index value..
            Update(1 , 1 , n , ind , val) ; // Updating segtree in index and new value..
        }
    }
    return 0 ;
}

/*...........................Range Max-Min Query(Update Single)............................*/

/* Given an array of length N , and Query the Min or Max in range left to right..Array can be update in a particular 
position in each query.. */

#include <bits/stdc++.h>
using namespace std ;

#define INF 1e9 
#define mxN 100000 
int ar[mxN + 5] ;
int segtree[mxN * 4] ;

void Build(int ar[] , int cur ,int left , int right) {
    if(left == right) {
        segtree[cur] = ar[left] ;
        return ;
    }
    int mid = ( left + right ) / 2 ;
    Build(ar , cur * 2 , left , mid) ;
    Build(ar , cur * 2 + 1 , mid + 1 , right) ;
    segtree[cur] = min(segtree[cur * 2] , segtree[cur * 2 + 1]) ; // taking the min from childs and storing in parent..
    // If max query we just have to change the min to max..
    return ;
}
void Update(int cur ,int left , int right ,int pos , int val) {
    if(left == right) {
        segtree[cur] = val ; // updating here the cur node by new value..
        return ;
    }
    int mid = (left + right) / 2 ;
    if(pos <= mid) 
        Update(cur * 2 , left , mid , pos , val) ;
    else 
        Update(cur * 2 + 1 , mid + 1 , right , pos , val) ;
    segtree[cur] = min(segtree[cur * 2] , segtree[cur * 2 + 1]) ; // taking the min from childs and storing in parent..
    // If max query we just have to change the min to max..
    return ;
}
int MinQuery(int cur ,int left ,int right ,int l , int r) {
    if(l > right || r < left)
        return INF ; // if out of bound returning INF , if max query return -INF..
    if(left >= l && right <= r)
        return segtree[cur] ;
    int mid = (left + right) / 2 ;
    int q1 = MinQuery(cur * 2 , left , mid , l , r) ;
    int q2 = MinQuery(cur * 2 + 1 , mid + 1 ,right , l , r) ;
    return min(q1 , q2) ; // If max query use max instead of min..
}
int main() {
    int n ; cin >> n ;
    for(int i = 0 ; i < n ; i++) 
        cin >> ar[i] ;
    Build(ar , 1 , 0 , n - 1) ; // Building segtree..
    int query ; cin >> query ;
    while(query--) {
        int x ; cin >> x ;
        if(x == 1) {
            int left , right ;
            cin >> left >> right ;
            int ans = MinQuery(1 , 1 , n , left , right) ; // query for range..
            cout << ans << "\n" ;
        }
        else if(x == 2) {
            int ind , val ; cin >> ind >> val ;
            ar[ind] = val ; // updating the ar ind with new value..
            Update(1 , 1 , n , ind , val) ; // Updating..
        }
    }
    return 0 ;
}
