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
            cycle++ ;
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
