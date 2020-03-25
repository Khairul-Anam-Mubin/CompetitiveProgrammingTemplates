/**********************LCA Sparse Table************************/
/*Given a tree , and q query , in each query two node u , v are given , 
find the LCA of u , v or find the max - min wight through their path */

#include <bits/stdc++.h>
using namespace std ;

const int mxN = 100010 ;
const int INF9 = 1000000000 ;
const int po = 20 ; //log(mxN)  
vector < pair <int , int>  > g[mxN] ;
int level[mxN] , weight[mxN] , parent[mxN] ;
int SpTab[mxN][po] ;
int MX[mxN][po] ;   // max edge weight
int MN[mxN][po];    // min edge weight
int root ;          // tree root
int N ;             // Graph size
void Reset() {
    for(int i = 0 ; i < N ; i++) {
        for(int j = 0 ; (1 << j) < N ; j++) {
            SpTab[i][j] = -1 ;
            MX[i][j] = -INF9 ;
            MN[i][j] = INF9 ;
        }
        g[i].clear() ;
    }
}
pair<int , int> Query(int u , int v) {
    int mn = INF9 , mx = -INF9 ;
    if(level[u] < level[v]) 
        swap(u , v) ;
    int log ;
    for(log = 1 ; (1 << log) <= level[u] ; log++); 
    log-- ;
    for(int i = log ; i >= 0 ; i--) {
        if(level[u] - (1 << i) >= level[v]) {
            mn = min(mn , MN[u][i]) ;
            mx = max(mx , MX[u][i]) ;
            u = SpTab[u][i] ;
        }
    }
    if(u == v) {    // if the root is equal v
        // return u ;
        return make_pair(mn , mx) ;
    }
    for(int i = log ; i >= 0 ; i--) {
        if(SpTab[u][i] != -1 && SpTab[u][i] != SpTab[v][i]) {
            mn = min(mn , min(MN[u][i] , MN[v][i])) ;
            mx = max(mx , max(MX[u][i] , MX[v][i])) ;
            u = SpTab[u][i] ;
            v = SpTab[v][i] ;
        }
    }
    mn = min(mn , min(MN[u][0] , MN[v][0])) ;
    mx = max(mx , max(MX[u][0] , MX[v][0])) ;
    //return parent[u] ; 
    return make_pair(mn , mx) ;
}
void Dfs(int u , int par = -1) {
    if(par == -1) {                 // if tree is root  
        level[u] = weight[u] = 0 ;  // zero level and no weight
        parent[u] = -1 ;            // no parent for root
    }
    for(int j = 0 ; j < g[u].size(); j++) {
        int v = g[u][j].first ;
        int w = g[u][j].second ;
        if(v != par) {              
            parent[v] = u ;
            weight[v] = w ;
            level[v] = level[u] + 1 ;
            Dfs(v , u) ;
        }
    }
}    
void SparseTable() {
    Dfs(root) ;
    for(int i = 0 ; i < N ; i++) {
        SpTab[i][0] = parent[i] ;
        MX[i][0] = MN[i][0] = weight[i] ;
    }
    for(int j = 1 ; (1 << j) < N ; j++) {
        for(int i = 0 ; i < N ; i++) {
            if(SpTab[i][j - 1] != -1) {
                SpTab[i][j] = SpTab[SpTab[i][j - 1]][j - 1] ;
                MX[i][j] = max(MX[i][j - 1] , MX[SpTab[i][j - 1]][j - 1]) ;
                MN[i][j] = min(MN[i][j - 1] , MN[SpTab[i][j - 1]][j - 1]) ;
            }
        }
    }   
}
void Solve() {
    int n ; 
    scanf("%d",&n) ;
    Reset() ;
    N = n ;
    root = 0 ;
    for(int i = 1 ; i <= n - 1 ; i++) {
        int u , v , w ;
        scanf("%d%d%d",&u,&v,&w) ;
        u-- , v-- ;
        g[u].push_back(make_pair(v , w)) ;
        g[v].push_back(make_pair(u , w)) ;
    }
    SparseTable() ;
    int q ; 
    scanf("%d",&q) ;
    while(q--) {
        int u , v ;
        scanf("%d%d",&u,&v) ;
        u-- , v-- ;
        pair<int,int> ans = Query(u , v) ;
        printf("%d %d\n", ans.first , ans.second);
    }
}
int main() {
    int tc , test = 0 ;
    scanf("%d",&tc) ;
    while(tc--) {
        printf("Case %d:\n", ++test);
        Solve() ;
    }
    return 0 ;
}
