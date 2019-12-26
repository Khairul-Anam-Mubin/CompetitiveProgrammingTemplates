/**********************Minimum Spanning Tree************************/

/*...................................... Note..............................*/ 
/* For the 2nd minimum spanning tree we first have to find 1st  MST and a vis array to mark the edges which are used in making  
the first MST , then we simply ignore each time 1 edge and try to make spanning tree and rest the minimum of them is the answer..
MST is also used as Minimax , maximin , forest , sub graph */

/*......................Prim's Algorithm........................*/
/* Given a graph with n nodes and m edges , Find the minimum spanning tree .*/
// Problem Uva : 11631 - Dark roads

#include <bits/stdc++.h>
using namespace std ;

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
    int nodes , edges ;
    while(cin >> nodes >> edges) {
        if(nodes == 0 && edges == 0)
            break ;
        int tot = 0 ;
        for(int i = 0  ; i < edges ; i++) {
            int u , v , w ;
            cin >> u >> v >> w ;
            G[u].push_back(node(v , w)) ;
            G[v].push_back(node(u , w)) ;
            tot += w ; // counting the total before finding minimum spanning tree
        }
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
/*....................Kruskal Algrithm.................*/
/* Given a graph with n nodes and m edges , find the minimum spanning tree.*/
// Uva : 11631 - Dark roads

#include <bits/stdc++.h>
using namespace std ;

vector <pair <int , pair <int, int> > > g ;

#define mx 200010
int dsu[mx] ;

void makeset(int nodes) {
    for(int i = 0 ; i <= nodes + 1 ; i++) 
        dsu[i] = i ;
}
int Find(int x) {
    if(x == dsu[x]) 
        return x ;
    return dsu[x] = Find(dsu[x]) ;
}
void Union(int x ,int y) {
    x = Find(x) ;
    y = Find(y) ;
    if( x != y) 
        dsu[x] = y ;
}
bool sameset(int u, int v) {
    return (Find(u) == Find(v)) ; 
}
int KruskalAlgo(int nodes) {
    makeset(nodes) ;
    int cost = 0 ;
    int cnt = 0 ;
    sort(g.begin() , g.end()) ;
    for(auto it : g) {
        int u = it.second.first ;
        int v = it.second.second ;
        int w = it.first ;
        if(!sameset(u , v)) {
            cost += w ;
            Union(u  ,v) ;
            cnt++ ;
        }
        if(cnt == nodes - 1)
            break;
    }
    return cost ;
}
int main() {
    int nodes , edges ;
    while(cin >> nodes >> edges && nodes && edges) {
        int tot = 0 ; 
        for(int i = 0 ; i < edges ; i++) {
            int u , v , w ;
            cin >> u >> v >> w ;
            g.push_back(make_pair(w ,make_pair(u , v))) ;
            tot += w ;
        }
        int ans = tot - KruskalAlgo(nodes) ; 
        cout << ans << "\n" ;
        g.clear() ;
    }
    return 0 ;
}
