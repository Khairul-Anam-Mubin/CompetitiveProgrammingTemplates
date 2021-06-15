struct StronglyConnectedComponent {
    vector <vector <int>> g , gr;
    vector <bool> vis;
    vector <int> order, sccid;
    int nodes , edges , scc = 0;
 
    void Init(int _nodes) {
        nodes = _nodes;
        edges = 0;
        scc = 0;
        g.clear();
        gr.clear();
        g.assign(nodes + 1 , {});
        gr.assign(nodes + 1, {});
        order.clear();
        vis.assign(nodes + 1, 0);
        sccid.resize(nodes + 1);
    } 
    void AddEdge(int u , int v) {
        if (u == -1 || v == -1) return;
        g[u].push_back(v);
        gr[v].push_back(u);
        edges++;
    }
    void Init() {
        for (int i = 0; i <= nodes; i++) vis[i] = 0;
    }
    void Dfs1(int u) {
        if (vis[u]) return;
        vis[u] = 1;
        for (int v : g[u]) Dfs1(v);
        order.push_back(u);
    }
    void TopSort() {
        Init();
        for (int i = 0; i < nodes; i++) { 
            if (!vis[i]) Dfs1(i);
        }
        reverse(order.begin() , order.end());
    }
    void Dfs2(int u, int id) {
        if (vis[u]) return;
        vis[u] = 1;
        sccid[u] = id;
        for (int v : gr[u]) Dfs2(v , id);
    }
    void KosarajuSCC() {
        TopSort();
        Init();
        for (int i : order) {
            if (!vis[i]) {
                Dfs2(i , scc);
                scc++;
            }
        }
    }
    int GetAns() {
        vector <int> here(nodes + 1);
        for (int i = 0; i < scc; i++ ) {
            here[i] = 1;
        }
        for (int i = 0; i < nodes; i++) {
            for (int j : g[i]) {
                if (sccid[i] != sccid[j])
                    here[sccid[j]] = 0;
            }
        }
        int ans = 0;
        for (int i = 0; i < scc; i++) ans += here[i];
        return ans;
    }
};
/*********************************Strongly Connected Component(Kosaraju_dfs)**************************************/

/*...........................Finding strongly connected component............................*/
/* Given a graph , Find if there is one or more connected component. print 1 for 1 or 0 for more.. */
// complexity : O(V + E) 

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
