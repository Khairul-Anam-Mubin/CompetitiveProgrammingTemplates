/***********************Lowest Common Ancestor***********************/
/* 1.   All nodes are number 0 to n - 1 */
/* 2.   simply Init(total nodes) and call AddEdge(u , v) for all the edges */
/* 3.   Call Build() to run dfs and build the sparse table */

struct LowestCommonAncestor {
    int N , root = 0, po;
    
    vector <vector <int> > g;
    vector <vector <int> > sptab; 
    vector <int> depth;
    vector <int> parent;
    
    void Init(int _n) {
        N = _n; 
        po = log2((N)) + 1;
        g.assign(N, {});
        depth.resize(N);
        parent.resize(N);
        sptab.assign(N, {});
    }
    void AddEdge(int u , int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    void Dfs(int u , int par = -1) {
        if(par == -1) {
            depth[u] = 0;
            parent[u] = -1;
        }
        for(int v : g[u]) {
            if (v == par) continue;
            parent[v] = u;
            depth[v] = depth[u] + 1;
            Dfs(v , u);
        }
    } 
    void SparceTable() {
        for(int i = 0 ; i < N ; i++) sptab[i][0] = parent[i];
        for(int j = 1 ; (1 << j) < N ; j++) {
            for(int i = 0 ; i < N ; i++) {
                if(sptab[i][j - 1] != -1) {
                    sptab[i][j] = sptab[sptab[i][j - 1]][j - 1];
                }
            }
        }
    }
    void Build() {
        for(int i = 0 ; i < N ; i++) {
            for(int j = 0 ; j <= po ; j++) {
                sptab[i].push_back(-1);
            }
        }
        Dfs(root);
        SparceTable();
    }
    int Lca(int u , int v) {
        if(depth[u] < depth[v]) swap(u , v);
        int log;
        for(log = 1 ; (1 << log) <= depth[u] ; log++); log--;
        for(int i = log ; i >= 0 ; i--) {
            if(depth[u] - (1 << i) >= depth[v]) {
                u = sptab[u][i];
            }
        }
        if(u == v) return u;
        for(int i = log ; i >= 0 ; i--) {
            if(sptab[u][i] != -1 && sptab[u][i] != sptab[v][i]) {
                u = sptab[u][i];
                v = sptab[v][i];
            } 
        }
        return parent[u];
    }
    int KthAncestor(int u, int k) {
        int log;
        for(log = 1 ; (1 << log) <= depth[u] ; log++); log--;
        for(int i = log ; i >= 0 ; i--) {
            if(k - (1 << i) >= 0) {
                u = sptab[u][i];
                k -= (1 << i);
            }
        }
        return u;
    }
    int Getdist(int u , int v) {
        return (depth[u] + depth[v] - (2 * (depth[Lca(u , v)]))) ;
    }
    bool IsAnsector(int u , int v) {
        int cur = Lca(u , v);
        if(cur == u) return 1;
        return 0;
    }
} lca;
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
pair<int , int> LCA(int u , int v) {
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
        pair<int,int> ans = LCA(u , v) ;
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
