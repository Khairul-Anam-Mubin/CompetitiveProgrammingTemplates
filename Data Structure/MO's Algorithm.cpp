/*******************MO's ALgorithm***********************/
/*.............Range query..............*/

/* Given an array of length n and q querys of range l , r . Find the number of unique
elements in the given range */

#include <bits/stdc++.h>
using namespace std ;

#define FasterIO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define BLOCK 555

// Saving the querys..
struct query {
    int l ;
    int r ;
    int idx ;
} ;
query Q[200001] ; 
int ar[30001] , ans[200001] ;
int freq[1000001] ;
int cnt = 0 ;

bool Cmp(query a , query b) {
    if(a.l / BLOCK != b.l / BLOCK)
        return a.l / BLOCK < b.l / BLOCK ;
    return a.r < b.r ; 
}
void Add(int pos) {
    freq[ar[pos]]++ ;
    if(freq[ar[pos]] == 1)
        cnt++ ;
}
void Remove(int pos) {
    freq[ar[pos]]-- ;
    if(freq[ar[pos]] == 0)
        cnt-- ;
}
void MosAlgo(int q) {
    int ML = 0 , MR = -1 ;
    for(int i = 0 ; i < q ; i++) {
        int L = Q[i].l ;
        int R = Q[i].r ;
        while(ML > L) {
            ML-- ;
            Add(ML) ;
        }
        while(MR < R) {
            MR++ ;
            Add(MR) ;
        }
        while(ML < L) {
            Remove(ML) ;
            ML++ ;
        }
        while(MR > R) {
            Remove(MR) ;
            MR-- ;
        }
        ans[Q[i].idx] = cnt ;
    }
}
int main() {
    FasterIO
    int n , q ;
    cin >> n ;
    for(int i = 0 ; i < n ; i++)
        cin >> ar[i] ;
    cin >> q ;
    for(int i = 0 ; i < q ; i++) {
        cin >> Q[i].l >> Q[i].r ;
        Q[i].idx = i ;
        Q[i].l-- ;
        Q[i].r-- ;
    }
    sort(Q , Q + q , Cmp) ;
    MosAlgo(q) ;
    for(int i = 0 ; i < q ; i++) {
        cout << ans[i] << "\n" ;
    }
    return 0 ;
}
