/**************************Topological Sort********************/

/*..................Straight Forward TopSort_Kosaraju(DFS).................*/

// Algorithm
// Topological Sort
// Uva 10305 - Ordering Tasks

#define mxN 110
vector <int> G[mxN] ; 
vector <int> vec ; // containing the topological sort elements
int vis[mxN] ;
void dfs(int u) {
    vis[u] = 1 ;
    for(int i = 0 ; i < G[u].size() ; i++) {
        int v = G[u][i] ;
        if(!vis[v])
            dfs(v) ;
    }
    vec.push_back(u) ;
}
void topsort(int nodes) {
    for(int i = 0 ; i <= nodes ; i++)
        vis[i] = 0 ;
    for(int i = 1 ; i <= nodes ; i++) 
        if(!vis[i]) 
            dfs(i) ;
    reverse(vec.begin() , vec.end()) ; // reversing the list to simply find the topological order
}
int main() {
    int nodes , edges ;
    while(cin >> nodes >> edges) {
        if(nodes == 0 && edges == 0)
            break;
        for(int i = 0 ; i < edges ; i++) {
            int u , v ;
            cin >> u >> v ;
            G[u].push_back(v) ;
        }
        topsort(nodes);
        for(int i = 0 ; i < vec.size() - 1 ; i++)
            cout << vec[i] << " " ;
        cout << vec[vec.size() - 1 ] << "\n" ;
    }
    return  0 ;
}
// parenting the orders...
int parent[100010] ;
    int pos = 0 ;
    for(int i = 0 ; i < vec.size() ; i++) {
        int x = vec[i] ;
        parent[x] = pos ;
        pos = x ;
    }
    for(int i = 1 ; i <= n ; i++) {
        cout << parent[i] << "\n" ;
    }

/*...........................Topological Sort order dfs............................*/
/*  the minimum number of dominos that must be knocked over by hand in order for all the dominos to fall.
if u and v are connected dominos then if u falls also v will fall. */

#include <bits/stdc++.h>
using namespace std ;

#define mxN 100000
vector <int> G[mxN + 10] ;
vector <int> order ;
bool vis[mxN + 10] ;

void Graph_clear(int n) {
    for(int i = 0 ; i <= n ; i++)
        G[i].clear() ;
    order.clear() ;
} 
void init(int n) {
    for(int i = 0 ; i <= n + 1 ; i++)
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
void dfs(int u) {
    vis[u] = 1 ;
    for(int v : G[u]) {
        if(!vis[v])
            dfs(v) ;
    }
}
int main() {
    int tc ;
    cin >> tc ;
    while(tc--) {
        int n , m ;
        cin >> n >> m ;
        for(int i = 0 ; i < m ; i++) {
            int u , v ;
            cin >> u >> v ;
            G[u].push_back(v) ;
        }
        init(n) ;
        for(int i = 1 ; i <= n ; i++) {
            if(!vis[i])
                dfs1(i) ;
        }
        reverse(order.begin() ,  order.end()) ;
        int ans = 0 ;
        init(n) ;
        for(int i = 0 ; i < order.size() ; i++) {
            int v = order[i] ;
            if(!vis[v]) {
                dfs(v) ;
                ans++ ;
            }
        }
        cout << ans << "\n" ;
        Graph_clear(n) ;
    }
    return 0 ;
}

/*......................Topological Sort_Kahn's Algorithm(BFS/Priority Queue)...................*/
/* straight Forward..*/

// Algorithm 
// Topological sorting (BFS) 
// Kahn's Algorithm 

#include <bits/stdc++.h>
using namespace std ;

map <string , int> mp ; 
map <int , string> ans ; 
vector <string> vec ; // topsort order list
vector <int> G[110] ; // graph
int indegree[110] ; // counting indegree

// this is kahn's algorithm , Topologicol sorting bfs algorithm 
void  KahnsAlgo(int nodes) {
    priority_queue <int> pq ;
    for(int i = 1 ; i <= nodes ; i++) {
        if(indegree[i] == 0)
            pq.push(-i) ;
    }
    while(!pq.empty()) {
        int u = -pq.top() ;
        pq.pop() ;
        vec.push_back(ans[u]) ; // this must be in the sorted list..  
        for(int i = 0 ; i < G[u].size() ; i++) {
            int v = G[u][i] ;
            indegree[v]-- ;
            if(indegree[v] == 0)
                pq.push(-v) ;
        }
    }
}
int main() {
    int tc , t = 0 ; 
    while(cin >> tc) {
        for(int i = 0 ; i <= 105 ; i++)
            indegree[i] = 0 ;
        for(int i = 1 ; i <= tc ; i++){
            string str ;
            cin >> str ;
            mp[str] = i ;
            ans[i] = str ;
        }
        int n ; 
        cin >> n ;
        for(int i = 1 ; i <= n ; i++) {
            string s1 , s2 ;
            cin >> s1 >> s2 ;
            int u , v ;
            u = mp[s1] ;
            v = mp[s2] ;
            G[u].push_back(v) ;
            indegree[v]++ ;
        }
        printf("Case #%d: Dilbert should drink beverages in this order:", ++t);
        KahnsAlgo(tc) ;
        for(int i = 0 ; i < vec.size() ; i++)
            cout << " " << vec[i] ;
        cout << ".\n\n" ; 
        for(int i = 0 ; i < 110 ; i++)
            G[i].clear() ;
        mp.clear() ;
        vec.clear() ;
    }
    return 0 ;
}
