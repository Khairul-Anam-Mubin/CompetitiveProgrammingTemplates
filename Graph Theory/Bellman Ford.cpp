/***************************Bellman Ford******************/
/*.................Shortest path Negative cost graph..............*/

// Uva 558 - Wormholes
// negative weight graph
// Can find negative weight cycle with it

#include <bits/stdc++.h>
using namespace std ;

#define INF 1e9
vector < pair <int , int> > G[1010] ; 
int cost[1010] ; // containing shortest path costs..

// on adjacency list..
void BellmanFord(int nodes) {
    for(int i = 0 ; i < 1010 ; i++)
        cost[i] = INF ;
    cost[0] = 0 ;
    for(int i = 0 ; i < nodes - 1 ; i++) {
        for(int u = 0 ; u < nodes ; u++) {
            for(int k = 0 ; k < G[u].size() ; k++) {
                int v = G[u][k].first ;
                int wv = G[u][k].second ;
                cost[v] = min(cost[v] , cost[u] + wv) ;
            }
        }
    }
}
// If there exist a negative weight cycle returning true 
bool NegativeCycle(int nodes) {
    for(int u = 0 ; u < nodes ; u++) {
        for(int i = 0 ; i < G[u].size() ; i++) {
            int v = G[u][i].first ;
            int wv = G[u][i].second ;
            if(cost[v] > cost[u] + wv) 
                return 1 ;
        }
    }
    return 0 ;
}
int main() {
    int tc ;
    cin >> tc ;
    while(tc--) {
        int nodes, edges ;
        cin >> nodes >> edges ;
        for(int i = 0 ; i < edges ; i++) {
            int u , v , w ;
            cin >> u >> v >> w ;
            G[u].push_back(make_pair(v , w)) ;
        }
        BellmanFord(nodes) ;
        bool ans = NegativeCycle(nodes) ;
        if(ans) 
            cout << "possible\n" ;
        else
            cout << "not possible\n" ;
        for(int i = 0 ; i <= nodes + 1 ; i++)
            G[i].clear() ;
    }
    return 0 ;
}
/*.................shortest path negative cost................*/

#include <bits/stdc++.h>
using namespace std ;
 
#define mxN 200
#define INF 1e9
struct node {
    long long u , v , w ;
    node(long long _u , long long _v , long long _w) {
        u = _u ;
        v = _v ;
        w = _w ;
    }
};
long long val[mxN + 10] ;
long long cost[mxN + 10] ;
vector <node> g ;
// Edgelist version..
void bellmanford(int nodes , int edges) {
    for(int i = 0 ; i <= nodes + 1 ; i++)
        cost[i] = INF ;
    cost[1] = 0 ;
    for(int i = 1 ; i <= nodes - 1 ; i++) {
        for(int j = 0 ; j < edges ; j++) {
            long long u = g[j].u ;
            long long v = g[j].v ;
            long long w = g[j].w ;
            if(cost[u] != INF && cost[u] + w < cost[v])
                cost[v] = cost[u] + w ;
        }
    }
}
int main() {
    int tc ,test = 0 ;
    cin >> tc ;
    while(tc--) {
        int nodes ;
        cin >> nodes ;
        for(int i = 1 ; i <= nodes ; i++)
            cin >> val[i] ;
        int edges ;
        cin >> edges ;
        for(int i = 0 ; i < edges ; i++) {
            long long u , v , w ;
            cin >> u >> v ;
            w = (val[v] - val[u]) * (val[v] - val[u]) * (val[v] - val[u]) ;
            g.push_back(node(u , v , w)) ;
        }
        bellmanford(nodes , edges) ;
        int q ;
        cin >> q ;
        cout << "Case " << ++test << ":\n" ;
        while(q--) {
            int x ;
            cin >> x ;
            if(cost[x] < 3 || cost[x] == INF)
                cout << "?\n" ;
            else
                cout << cost[x] << "\n" ;
        }  
        g.clear() ;
    } 
    return 0 ;
}
