/*********************************Segment Tree**************************************/

/*...........................Range Sum Query(Update Single)............................*/
/* Given an array of length N , and Query the sum in range left , right..Array can be update in a particular 
position in each query.. */

#include <bits/stdc++.h>
using namespace std ;

/* 1 base index*/

#define mxN 100000
long long ar[mxN + 5] ;
long long segtree[mxN * 4] ;

// Building segmentree in O(n)
void Build(int cur, int left, int right) {
    if (left == right) {
        segtree[cur] = ar[left] ;
        return ;
    }
    int mid = (left + right) / 2 ;
    Build(cur * 2 , left , mid) ;
    Build(cur * 2 + 1 , mid + 1, right) ;
    segtree[cur] = segtree[cur * 2] + segtree[cur * 2 + 1] ;
    return ;
}
// Query the sum in O(logN)
long long Query(int cur, int left, int right, int l, int r) {
    if (l > right || r < left)
        return 0 ; 
    if (left >= l && right <= r)
        return segtree[cur] ;
    int mid = (left + right) / 2 ;
    long long p1 = Query(cur * 2, left, mid, l, r) ;
    long long p2 = Query(cur * 2 + 1 , mid + 1, right, l, r) ;
    return p1 + p2 ;
}
// Updating in O(logN)
void Update(int cur, int left, int right, int pos , long long newvalue) {
    if (pos > right || pos < left)
        return ; 
    if (left >= pos && right <= pos) { 
        segtree[cur] = newvalue ;
        return;
    }
    int mid = (left + right) / 2 ;
    Update(cur * 2 , left, mid, pos, newvalue) ;
    Update(cur * 2 + 1 , mid + 1, right , pos , newvalue) ;
    segtree[cur] = segtree[cur * 2] + segtree[cur * 2 + 1] ;
    return ;
}
int main() {
    int n ; cin >> n ;
    for(int i = 1 ; i <= n ; i++) 
        cin >> ar[i] ;
    // root is 1 , and left 1 and right n as 1 base indexed..
    Build(1 , 1 , n ) ; // Building the segtree.. 
    int query ; cin >> query ;
    while(query--) {
        int x ; cin >> x ;
        if(x == 1) {
            int l , r ; cin >> l >> r ;
            int ans = Query(1 , 1 , n , l , r) ; // returning range sum..
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

/* 1 base index*/

#define mxN 100000
#define INF 1e9
long long ar[mxN + 5] ;
long long segtree[mxN * 4] ;

// Building segmentree in O(n)
void Build(int cur, int left, int right) {
    if (left == right) {
        segtree[cur] = ar[left] ;
        return ;
    }
    int mid = (left + right) / 2 ;
    Build(cur * 2 , left , mid) ;
    Build(cur * 2 + 1 , mid + 1, right) ;
    segtree[cur] = min(segtree[cur * 2] , segtree[cur * 2 + 1]) ; // taking the min from childs and storing in parent..
    // If max query we just have to change the min to max..
    return ;
}
// Query the max / min in O(logN)
long long Query(int cur, int left, int right, int l, int r) {
    if (l > right || r < left)
        return INF ;          // if out of bound returning INF , if max query return -INF..
    if (left >= l && right <= r)
        return segtree[cur] ;
    int mid = (left + right) / 2 ;
    long long p1 = Query(cur * 2, left, mid, l, r) ;
    long long p2 = Query(cur * 2 + 1 , mid + 1, right, l, r) ;
    return min( p1 , p2 ) ; // If max query use max instead of min..
}
// Updating in O(logN)
void Update(int cur, int left, int right, int pos , long long newvalue) {
    if (pos > right || pos < left)
        return ; 
    if (left >= pos && right <= pos) { 
        segtree[cur] = newvalue ;
        return;
    }
    int mid = (left + right) / 2 ;
    Update(cur * 2 , left, mid, pos, newvalue) ;
    Update(cur * 2 + 1 , mid + 1, right , pos , newvalue) ;
    segtree[cur] = min(segtree[cur * 2] , segtree[cur * 2 + 1]) ; // taking the min from childs and storing in parent..
    // If max query we just have to change the min to max..    
    return ;
}
int main() {
    int n ; cin >> n ;
    for(int i = 1 ; i <= n ; i++) 
        cin >> ar[i] ;
    // root is 1 , and left 1 and right n as 1 base indexed..
    Build(1 , 1 , n ) ; // Building the segtree.. 
    int query ; cin >> query ;
    while(query--) {
        int x ; cin >> x ;
        if(x == 1) {
            int l , r ; cin >> l >> r ;
            int ans = Query(1 , 1 , n , l , r) ; // returning range min..
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
/*.............................Range query Most Frequent values(non-update).....................*/
/* Given an array of length n and q query, in each l , r you have to tell the most frquecy.. 

/* 1 based index */
// Uva : 11235

#include <bits/stdc++.h>
using namespace std ;

#define INF 1e9
#define mxN 100000
int ar[mxN + 10] ;
int dp[mxN + 10] ;
vector <pair <int , int> > segtree(mxN * 4) ;  

pair <int , int> getmax(pair <int , int> &a , pair <int ,int> &b) {
    if(a.first > b.first)
        return a ;
    else if(a.first < b.first) 
        return b ;
    if(a.second >= b.second)
        return a ;
    else
        return b ;
}
void Build(int cur , int left , int right) {
    if(left == right) {
        segtree[cur] = make_pair(dp[left] , left);
        return ;
    }
    int mid = (left + right) / 2 ;
    Build(cur * 2 , left , mid) ;
    Build(cur * 2 + 1 , mid + 1 , right) ;
    segtree[cur] = getmax(segtree[cur * 2] , segtree[cur * 2 + 1]) ;
    return ;
}
pair <int , int> Query(int cur , int left , int right ,int l , int r) {
    if(l > right || r < left)
        return make_pair(-INF , 0) ;
    if(left >= l && right <= r) 
        return segtree[cur] ;
    int mid = (left + right) / 2 ;
    pair <int , int> p1 = Query(cur * 2 , left , mid , l , r) ;
    pair <int , int> p2 = Query(cur * 2 + 1 , mid + 1 , right , l , r) ;
    return getmax(p1 , p2) ;
}
int main() {
    int n , q ;
    while(scanf("%d",&n) == 1 && n != 0) {
        int q ;
        scanf("%d",&q) ;
        dp[0] = 0 ;
        for(int i = 1 ; i <= n ; i++) {
            scanf("%d",&ar[i]) ;
            dp[i] = 1 ;
        }
        for(int i = 2 ; i <= n ; i++) {
            while(i <= n && ar[i] == ar[i - 1]) {
                dp[i] = dp[i - 1] + 1 ;
                i++ ;
            }
        }
        Build(1 , 1 , n) ;
        while(q--) {
            int l , r ;
            scanf("%d%d",&l , &r) ;

            pair <int , int> ok = Query(1 , 1 , n , l , r) ;
            int ans = ok.first ;
            
            if(ar[ok.second] == ar[l - 1]) {
                ans = ok.second - (l - 1) ; 
                if(ok.second < r) {
                    ok = Query(1 , 1 , n , ok.second + 1 , r) ;
                    ans = max(ans , ok.first) ;
                }
            }
            printf("%d\n", ans) ;
        }
    }
    return 0 ;
}

/*********************Segmentree Lazy Propagation**********************/

/*.......................Range Update............................*/
/* Given n elements and q queries , in each query update all value 
in range l , r to val and return range sum in l , r */

/* 1 based index */

#include <bits/stdc++.h>
using namespace std ;

#define mxN 100000

long long ar[mxN + 10] ;
long long segtree[mxN * 4] ;
long long lazy[mxN * 4] ;
// simply building tree
void Build(int cur , int left , int right) {
    if(left == right) {
        segtree[cur] = ar[left] ;
        return ;
    }
    int mid = (left + right) / 2 ;
    Build(cur * 2 , left , mid) ;
    Build(cur * 2 + 1 , mid + 1 , right) ;
    segtree[cur] = segtree[cur * 2] + segtree[cur * 2 + 1] ;
    return ;
}
// Lazy update
void Update(int cur , int left , int right , int l , int r , long long val) {
    if(lazy[cur] != 0) {              // if lazy value is non zero then update
        segtree[cur] += (right - left + 1) * lazy[cur] ;
        if(left != right) {         // if this is not child
            lazy[cur * 2] += lazy[cur] ;  // propagating its childs
            lazy[cur * 2 + 1] += lazy[cur] ;
        }
        lazy[cur] = 0 ;           // cur node eluminate so reset 0
    }
    if (l > right || r < left)
        return ;
    if (left >= l && right <= r) {
        segtree[cur] += (right - left + 1) * val ;
        if(left != right) {
            lazy[cur * 2] += val ;
            lazy[cur * 2 + 1] += val ;
        }
        return ;
    }
    int mid = (left + right) / 2 ;
    Update(cur * 2 , left , mid , l , r , val) ;
    Update(cur * 2 + 1 , mid + 1 , right , l , r , val) ;
    segtree[cur] = segtree[cur * 2] + segtree[cur * 2 + 1] ;
    return ;
}
long long Query(int cur , int left , int right , int l , int r) {
    if(l > right || r < left)
        return 0 ;
    if(lazy[cur] != 0) {
        segtree[cur] += (right - left + 1) * lazy[cur] ;
        if(left != right) {
            lazy[cur * 2] += lazy[cur] ;
            lazy[cur * 2 + 1] += lazy[cur] ;
        }
        lazy[cur] = 0 ;
    }
    if (left >= l && right <= r)
        return segtree[cur] ;
    int mid = (left + right) / 2 ;
    long long p1 = Query(cur * 2 , left , mid , l , r) ;
    long long p2 = Query(cur * 2 + 1 , mid + 1 , right , l , r) ;
    return (p1 + p2) ;
}
int main() {
    int tc ;
    scanf("%d",&tc) ;
    while(tc--) {
        long long n , q ;
        scanf("%lld%lld",&n,&q) ;
        for(int i = 1 ; i <= n ; i++) {
            scanf("%lld",&ar[i]) ;
        }
        for(int i = 0 ; i < 4 * mxN ; i++) {
            lazy[i] = 0 ;
            segtree[i] = 0 ;
        }
        Build(1 , 1 , n) ;
        while(q--) {
            int how ;
            scanf("%d",&how) ;
            if(how == 0) {
                long long l , r , val ;
                scanf("%lld%lld%lld",&l,&r,&val) ;
                if(l > r)
                    swap(l , r) ;
                Update(1 , 1 , n , l , r , val) ;
            } else if(how == 1) {
                long long l ,  r ;
                scanf("%lld%lld",&l,&r) ;
                if(l > r)
                    swap(l , r) ;
                long long ans = Query(1 , 1 , n , l , r) ;
                printf("%lld\n",ans) ;
            }
        }
    }
    return 0 ;
}
