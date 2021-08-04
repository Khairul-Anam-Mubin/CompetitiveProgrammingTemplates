/***********************Wavelet Tree**************************/
#include <bits/stdc++.h>
using namespace std;
// 1 based index...
const int N = 3e5, M = N;
const int MAX = 1e6; 
int a[N];
struct wavelet_tree {
    int lo, hi;
    wavelet_tree *l, *r;
    vector <int> b;
    vector <int> c; // c holds the prefix sum of elements
    //nos are in range [x,y]
    //array indices are [from, to)
    wavelet_tree(int *from, int *to, int x, int y) {
        lo = x, hi = y;
        if( from >= to) return;
        if( hi == lo ) {
            b.reserve(to - from + 1);
            b.push_back(0);
            c.reserve(to - from + 1);
            c.push_back(0);
            for(auto it = from; it != to; it++) {
                b.push_back(b.back() + 1);
                c.push_back(c.back() + *it);
            }
            return ;
        }
        int mid = (lo + hi) / 2;
        auto f = [mid](int x) {
            return x <= mid;
        };
        b.reserve(to - from + 1);
        b.push_back(0);
        c.reserve(to - from + 1);
        c.push_back(0);
        for(auto it = from; it != to; it++) {
            b.push_back(b.back() + f(*it));
            c.push_back(c.back() + *it);
        }
        //stable_partition the lamda function
        auto pivot = stable_partition(from, to, f);
        l = new wavelet_tree(from, pivot, lo, mid);
        r = new wavelet_tree(pivot, to, mid + 1, hi);
    }
    // swap a[i] with a[i+1]  , if a[i]!=a[i+1] call swapadjacent(i)
    void swapadjacent(int i) {
        if(lo == hi) return ;
        b[i] = b[i - 1] + b[i + 1] - b[i];
        c[i] = c[i - 1] + c[i + 1] - c[i];
        if( b[i + 1] - b[i] == b[i] - b[i - 1]) {
            if(b[i] - b[i - 1]) 
                return this->l->swapadjacent(b[i]);
            else
                return this->r->swapadjacent(i - b[i]);
        }
        return ;
    }
    //kth smallest element in [l, r]
    int kth(int l, int r, int k) {
        if(l > r) return 0;
        if(lo == hi) return lo;
        int inLeft = b[r] - b[l - 1];
        int lb = b[l - 1]; //amt of nos in first (l-1) nos that go in left
        int rb = b[r]; //amt of nos in first (r) nos that go in left
        if(k <= inLeft) return this->l->kth(lb + 1, rb, k);
        return this->r->kth(l - lb, r - rb, k - inLeft);
    }
    //count of nos in [l, r] Less than or equal to k
    int LTE(int l, int r, int k) {
        if(l > r || k < lo) return 0;
        if(hi <= k) return r - l + 1;
        int lb = b[l-1], rb = b[r];
        return this->l->LTE(lb + 1, rb, k) + this->r->LTE(l - lb, r - rb, k);
    }
    //count of nos in [l, r] equal to k
    int count(int l, int r, int k) {
        if(l > r || k < lo || k > hi) return 0;
        if(lo == hi) return r - l + 1;
        int lb = b[l - 1], rb = b[r], mid = (lo + hi) / 2;
        if(k <= mid) return this->l->count(lb + 1, rb, k);
        return this->r->count(l - lb, r - rb, k);
    }
    //sum of nos in [l ,r] less than or equal to k
    int sumk(int l, int r, int k) {
        if(l > r || k < lo) return 0;
        if(hi <= k) return c[r] - c[l-1];
        int lb = b[l - 1], rb = b[r];
        return this->l->sumk(lb + 1, rb, k) + this->r->sumk(l - lb, r - rb, k);
    }
    ~wavelet_tree() {
        delete l;
        delete r;
    }
};
int main() {
    int n ; cin >> n;
    for(int i = 1 ; i <= n ; i++) {
        cin >> a[i] ;
    }
    // wavelet_tree T(array start address, array end address, min element, max element) ;
    wavelet_tree T(a + 1, a + n + 1 , 1, MAX) ;
    int q ; cin >> q ;
    while(q--) {
        int x ; cin >> x;
        int k , l , r ;
        if(x == 0) {
            //kth smallest element in range [l , r]
            cin >> l >> r >> k;
            cout << "Kth smallest: ";
            cout << T.kth(l, r, k) << endl;
        }
        if(x == 1) {
            //Number of Elements less than or equal to K in range [l , r]
            cin >> l >> r >> k;
            cout << "LTE: ";
            cout << T.LTE(l, r, k) << endl;
        }
        if(x == 2) {
            //count occurence of K in [l, r]
            cin >> l >> r >> k;
            cout << "Occurence of K: ";
            cout << T.count(l, r, k) << endl;
        }
        if(x == 3) {
            //sum of elements less than or equal to K in [l, r]
            cin >> l >> r >> k;
            cout << "Sum: ";
            cout << T.sumk(l, r, k) << endl;
        }
        if(x == 4) {
            int pos ; cin >> pos ;
            if(a[pos] != a[pos + 1])
                T.swapadjacent(pos) ;
        }
    }
    return 0;
}
/*................MKTHNUM..............*/
int main() {
    FasterIO
    int n , m ;
    cin >> n >> m ;
    int ar[n + 1] ; 
    map<int ,int> mp , rev_mp ;
    for(int i = 1 ; i <= n ; i++) {
        cin >> ar[i] ;
        mp[ar[i]] = 1 ;
    }
    int k = 1 ;
    for(auto &it : mp) {
        rev_mp[k] = it.first ;
        it.second = k++ ;
    }
    for(int i = 1 ; i <= n ; i++) {
        ar[i] = mp[ar[i]] ;
    }
    wavelet_tree T(ar + 1 , ar + n + 1 , 1 , k) ;
    while(m--) {
        int l , r , k ;
        cin >> l >> r >> k ;
        cout << rev_mp[T.kth(l , r ,k)] << "\n" ;
    }
    return 0 ;  
}