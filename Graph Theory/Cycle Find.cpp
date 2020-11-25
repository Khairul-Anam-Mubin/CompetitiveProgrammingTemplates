/*********************************Cycle Find**************************************/

struct CycleFind {
    vector <pair <int , int>> edges;
    vector <vector <int>> g;
    vector <int> par;
    vector <int> col;
    vector <int> mark;
    vector <vector <int>> cycles; 
    int NumOfCycles = 0;
    int N ;
    void Init(int n) {
        if (NumOfCycles) {
            for (int i = 0; i <= NumOfCycles; i++) cycles[i].clear();
        }
        N = n;
        NumOfCycles = 0;
        par.resize(n + 2);
        col.assign(n + 2 , 0);
        mark.assign(n + 2 , 0);
        edges.clear();
        g.resize(n + 2);
        for (int i = 0; i <= n; i++)g[i].clear();
    } 
    void TakeEdges(vector <pair <int , int>> ve) {
        edges = ve;
        for (int i = 0; i < edges.size(); i++) {
            int u = edges[i].first;
            int v = edges[i].second;
            g[u].emplace_back(v);
            g[v].emplace_back(u);
        }
    }
    void Dfs(int u , int p) {
        if (col[u] == 2) return; 
        if (col[u] == 1) { // Backtracking through parents and marking the cycles
            NumOfCycles++;
            int cur = p;
            mark[cur] = NumOfCycles;
            while (cur != u) {
                cur = par[cur];
                mark[cur] = NumOfCycles;
            }
            return;
        }
        col[u] = 1; // Partially visited
        par[u] = p; 
        for (int v : g[u]) {
            if (v == p) continue;
            Dfs(v , u);
        }
        col[u] = 2; // completely visited
    }
    void Cycle() {
        Dfs(1 , 0);
        cycles.resize(NumOfCycles + 1);
        for (int i = 0; i <= N; i++) {
            if (mark[i]) {
                cycles[mark[i]].emplace_back(i);
            }
        }
        //Print_Cycles();
    }
    void Print_Cycles(  ) {
        for (int i = 1; i <= NumOfCycles; i++) {
            cout << i << " : ";
            for (int j = 0; j < cycles[i].size(); j++) {
                cout << cycles[i][j] << " ";
            }
            cout << "\n";
        }
    }
} cf;

/*...........................Cycle Find in Directed Graph............................*/
/*  given a directed graph consisting of n vertices and m edges ,is it possible to make this graph 
acyclic by removing at most one edge from it ? */

#include <bits/stdc++.h>
using namespace std ;

vector <int> g[510] ;
int color[510] , cycle = 0 ;
void makeset(int n) {
    for(int i = 0 ; i <= n ; i++)
        color[i] = 0 ;
}
void dfs(int u) {
    color[u] = 2 ;
    for(int v : g[u]) {
        if(color[v] == 2) { 
            cycle++ ; // counting cycles...
        } else if(color[v] == 0) {
            dfs(v) ;
        }
    }
    color[u] = 1 ;
}
int main() {
    int n , m ;
    cin >> n >> m ;
    for(int i = 0 ; i < m ; i++) {
        int u , v ;
        cin >> u >> v ;
        g[u].push_back(v) ;
    }
    makeset(n) ;
    bool flag = 0 ;
    for(int i = 1 ; i <= n ; i++) {
        cycle = 0 ;
        makeset(n) ;
        dfs(i) ;
        for(int j = 1 ; j <= n && cycle <= 1 ; j++) {
            if(!color[j])
                dfs(j) ;
        }
        if(cycle <= 1) {
            flag = 1 ;
            break ;
        }
    }
    if(flag) {
        cout << "YES\n" ;
    } else {
        cout << "NO\n" ;
    }
    return 0 ;
}
