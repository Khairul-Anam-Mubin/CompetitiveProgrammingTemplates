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

// mxN have to define before...
const int mxN = 30;
struct DSU {
    vector <int> parent;
    vector <int> siz;
    DSU(int mxN) {
        mxN <<= 1;
        parent.resize(mxN + 1);
        siz.resize(mxN + 1);
    }
    void Makeset(int n) {
        for (int i = 0 ; i <= n ; i++) {
            parent[i] = n + i;
            parent[n + i] = n + i;
            siz[n + i] = 1;
        }
    }
    int Find(int u) {
        if (parent[u] == u) return u ;
        return parent[u] = Find(parent[u]) ;
    }
    void Union(int u , int v) {
        u = Find(u);
        v = Find(v);
        if (u != v) {
            if (siz[u] < siz[v]) swap(u , v);
            parent[v] = u;
            siz[u] += siz[v];
        }
    }
    bool SameSet(int u , int v) {
        return (Find(u) == Find(v)) ;
    }
    void MoveUtoSetV(int u , int v) {
        if (SameSet(u , v)) return;
        int x = Find(u);
        int y = Find(v);
        siz[x]--;
        siz[y]++;
        parent[u] = y;
    }
    int Size(int u) {
        return siz[Find(u)];
    }
} dsu(mxN);

struct MST {
    vector <pair<int, pair<int , int>>> edges;
    vector <pair<int, pair<int , int>>> mstedges;
    int nodes , mstcost;
    void ProcessKruskal() {
        sort(edges.begin() , edges.end());
        int cnt = 0 ;
        for (auto it : edges) {
            int u = it.second.first;
            int v = it.second.second;
            int w = it.first;
            if (!dsu.SameSet(u , v)) {
                dsu.Union(u , v);
                mstedges.push_back(make_pair(w , make_pair(u , v)));
                cnt++ , mstcost += w;
            }
            if (cnt + 1 == nodes)
                break ;
        }
    }
    void Init(int n , const vector<pair<int , pair<int , int>>> &_edges) {
        edges = _edges;
        nodes = n;
        mstcost = 0;
        dsu.Makeset(nodes);
    }
    void Init(int n) {
        nodes = n;
        mstcost = 0;
        dsu.Makeset(nodes);
        edges.clear();
    }
    void AddEdge(int u, int v, int w) {
        edges.push_back(make_pair(w , make_pair(u , v)));
    }
    void ShowEdgeList() {
        for (auto it : edges) {
            cout << it.second.first << " -> " << it.second.first << " " ;
            cout << it.first << "\n";
        }
    }
    void ShowMSTEdgeList() {
        for (auto it : mstedges) { 
            cout << it.second.first << " -> " << it.second.second << " ";
            cout << it.first << "\n";
        }    
    }
};
