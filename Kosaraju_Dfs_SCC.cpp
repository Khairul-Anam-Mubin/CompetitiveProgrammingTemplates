#include <bits/stdc++.h>
using namespace std ;

#define mxN 2000
vector <int> G[mxN + 10] , GR[mxN + 10] ;
vector <int> order , component ;
bool vis[mxN + 10] ;

void graph_clear(int nodes) {
    for(int i = 0 ; i <= nodes + 1 ; i++) {
        G[i].clear() ;
        GR[i].clear() ;
    }
}
void init(int nodes) {
    for(int i = 0 ; i <= nodes ; i++)
        vis[i] = 0 ;
}
void dfs1(int u) {
    vis[u] = 1 ;
    for(int v : G[u]) {
        if(!vis[v])
            dfs1(v) ;
    }
    order.push_back(u) ;
}
void reverse_edges(int nodes , int edges) {
    for(int i = 1 ; i <= nodes ; i++) {
        for(int j : G[i]) {
            GR[j].push_back(i) ;
        }
    }
}
void dfs2(int u) {
    vis[u] = 1 ;
    component.push_back(u) ;
    for(int v : GR[u]) {
        if(!vis[v])
            dfs2(v) ;
    }
}
void KosarajuSCC(int nodes ,int edges) {
    init(nodes) ; 
    for(int i = 1 ; i <= nodes ; i++) {
        if(!vis[i])
            dfs1(i) ;
    }
    reverse_edges(nodes , edges) ;
    init(nodes) ;
    int cnt = 0 ;
    for(int i = order.size() - 1 ; i >= 0 ; i--) {
        int v = order[i] ;
        if(!vis[v]) {
            dfs2(v) ;
            cnt++ ; // Component containg here all the nodes which are in a SCC..
            component.clear() ;
        }
    }
    if(cnt == 1)
        cout << "1\n" ;
    else
        cout << "0\n" ;
}
int main() {
    int nodes , edges ;
    while(cin >> nodes >> edges) {
        if(nodes == edges && nodes == 0)
            break ;
        for(int i = 0 ; i < edges ; i++) {
            int u , v , w ;
            cin >> u >> v >> w ;
            if(w == 1) {
                G[u].push_back(v) ;
            } else {
                G[u].push_back(v) ;
                G[v].push_back(u) ;
            }
        }
        KosarajuSCC(nodes ,  edges) ;
        graph_clear(nodes) ; 
    }
    return 0 ;
}
