// Algorithm
// Prim's Algorithm
//Minimum  Spanning tree
// Problem Uva : 11631 - Dark roads

#include <bits/stdc++.h>
using namespace std ;
// this is the pair..
struct node{
    int x ;
    int cost ;
    node(int _x , int _cost ) {
        x = _x ;
        cost = _cost;
    }
    bool operator < ( const node& p) const {
        return cost > p.cost ;
    }
};
#define mx 200010
vector <node> G[mx] ;
bool taken[mx] ;
priority_queue <node> pq ;

// clearing the vector and assigning 0's at taken
void clear(int nodes) {
    for(int i = 0 ; i <= nodes ; i++) {
        G[i].clear() ;
        taken[i] = 0 ;
    }
}

// taking the all adjacent nodes and procecssing...
void PrimsProcess(int u) {
    taken[u] = 1 ;
    for(int i = 0 ; i < G[u].size() ; i++) {
        int v = G[u][i].x ;
        int wv = G[u][i].cost ;
        if(!taken[v]) {
            pq.push(node(v , wv)) ;
        }
    }
}
int main() {
    //Fin ;
    int nodes , edges ;
    while(cin >> nodes >> edges) {
        if(nodes == 0 && edges == 0)
            break ;
        int tot = 0 ;
        // making the graph
        for(int i = 0  ; i < edges ; i++) {
            int u , v , w ;
            cin >> u >> v >> w ;
            G[u].pb(node(v , w)) ;
            G[v].pb(node(u , w)) ;
            tot += w ; // counting the total before finding minimum spanning tree
        }
        //cout << tot << "\n" ;
        
        // Prim's algorithm starts...
        PrimsProcess(0) ;
        int mincost = 0 ;
        while(!pq.empty()) {
            int u = pq.top().x ;
            int wu = pq.top().cost ;
            pq.pop() ;
            if(!taken[u]) {
                mincost += wu ;
                PrimsProcess(u) ;
            }
        }
        cout << tot - mincost << "\n" ;
        clear(nodes) ;
    }
    return 0 ;
}
