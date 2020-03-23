/**********Square root Decomposition**************/

// Complexity O(sqrt(N))
#include <bits/stdc++.h>
using namespace std ;

#define mxN 100000
int ar[mxN + 10] ;
int seg[mxN + 10] ;
int segment_size ;
void Build(int n) {
    int cur_seg = -1 ;
    segment_size = sqrt(n) ;
    for(int i = 0 ; i < n ; i++) {
        if(i % segment_size == 0) 
            cur_seg++ ;
        seg[cur_seg] += ar[i] ;
    }
}
void Update(int pos , int val) {
    int seg_no = pos / segment_size ;
    seg[seg_no] -= ar[pos] ;
    seg[seg_no] += val ;
    ar[pos] = val ;
}
int Query(int l , int r) {
    int sum = 0 ;
    while(l < r && l % segment_size != 0) 
        sum += ar[l++] ;
    while(l + segment_size <= r) {
        sum += seg[l / segment_size] ;
        l += segment_size ;
    }
    while(l <= r) 
        sum += ar[l++] ;
    return sum ;
}
int main() {
    int n ; cin >> n ;
    for(int i = 0 ; i < n ; i++) 
        cin >> ar[i] ;
    Build(n) ;
    int q ; cin >> q ;
    while(q-- ) {
        int x ; cin >> x ;
        if(x == 1) {
            int l , r ;
            cin >> l >> r ;
            int ans = Query(l , r) ;
            cout << ans << "\n" ;
        } else {
            int pos , val ;
            cin >> pos >> val ;
            Update(pos , val) ;
        }
    }
    return 0 ;
}
