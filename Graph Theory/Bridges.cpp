/***********************Bridges************************/
/*.....................critical links......................*/
/* Given the graph , finds the all critical links..*/
#include <bits/stdc++.h>
using namespace std ;

#define mxN 10000000

vector <int> G[mxN + 5] ;
vector < pair<int , int> > bridges ;
bool vis[mxN + 5] ;
int tin[mxN + 5] ; 
int low[mxN + 5] ;   
int timer ;

void graph_clear(int n) {
    for (int i = 0; i < n ; ++i) {
        G[i].clear() ;
    }
    bridges.clear() ;
}
void is_bridge(int u , int v) {
    int x = min(u , v) ;
    int y = max(u , v) ;
    bridges.push_back(make_pair(x , y)) ;
}
void dfs(int u , int p = -1 ) {
    vis[u] = 1 ;
    tin[u] = low[u] = timer++ ;
    for(int v : G[u]) {
        if(v == p)
            continue ;
        if(vis[v]) {
            low[u] = min(low[u] , tin[v]) ;
        } else {
            dfs(v , u) ;
            low[u] = min(low[u] , low[v]) ;
            if(low[v] > tin[u]) {
                is_bridge(u , v) ;
            }
        }
    }
}
void find_bridges(int nodes) {
    timer = 0 ;
    for(int i = 0 ; i <= nodes ; i++) {
        vis[i] = 0 ;
        tin[i] = low[i] = -1 ;
    }
    for(int i = 0 ; i < nodes ; i++) {
        if(!vis[i])
            dfs(i) ;
    }
    sort(bridges.begin() , bridges.end()) ;
    cout << bridges.size() << " critical links\n" ;
    if(bridges.size() == 0)
        return ;
    for(auto it : bridges) {
        cout << it.first << " - " << it.second << "\n" ;
    }
    cout << "\n" ;
}
int main() {
    int n ;
    while(cin >> n) {
        for(int i = 0 ; i < n ; i++) {
            int u ; cin >> u ;
            char ch ;
            cin >> ch ;
            int x ; cin >> x ;
            cin >> ch ;
            for(int j = 0 ; j < x ; j++) {
                int v ; cin >> v ;
                G[u].push_back(v) ;
            }
        }
        find_bridges(n) ;
        graph_clear(n) ;
    }
    return 0 ;
}
/*
intput :
8
0 (1) 1
1 (3) 2 0 3
2 (2) 1 3
3 (3) 1 2 4
4 (1) 3
7 (1) 6
6 (1) 7
5 (0)
output : 
3 critical links
0 - 1
3 - 4
6 - 7
*/
