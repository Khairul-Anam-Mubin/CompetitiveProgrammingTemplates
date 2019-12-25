/********************************Dijkstra*************************/
/*...........Shortest Path on weighted graph and path printing........*/
/* Given a graph of n nodes and m edges , print the shortest path from 1 to n */

// Problem name : C. Dijkstra?
// site : Codeforces

#include <bits/stdc++.h>
using namespace std ;
 
#define mxN 100000
#define INF 1e18
 
vector <pair <long long , int> > G[mxN + 10] ;
long long cost[mxN + 10] ;
int path[mxN + 10] ;
//path printing... 
void pathprint(int u) {
    if(path[u] == u) { 
        cout << u << " " ;
        return ;
    }
    pathprint(path[u]) ;
    cout << u << " " ;
}
bool dijkstra(int start , int destination , int nodes) {
    for(int i = 0 ; i <= nodes ; i++) {
        cost[i] = INF ;
        path[i] = i ;
    }
    // pq weight contains first...
    priority_queue <pair <long long , int > > pq ;
    cost[start] = 0 ;
    path[start] = start ;
    pq.push(make_pair(0 , start)) ;
    while(!pq.empty()) {
        int u = pq.top().second ;
        long long wu = -pq.top().first ;
        pq.pop() ;
        if(u == destination && cost[destination] != INF) 
            return 1 ;
        if(cost[u] < wu)
            continue ;
        for(auto it : G[u]) {
            int v = it.second ;
            long long wv = it.first ;
            if(cost[v] > wu + wv) { 
                cost[v] = wu + wv ;
                path[v] = u ;        // taking u as parent of v
                pq.push(make_pair(-cost[v] , v)) ;
            }
        }
    }
    return 0 ;
}
int main() {
    int n , m ;
    cin >> n >> m ;
    for(int i = 0 ; i < m ; i++) {
        int u , v ;
        long long w ;
        cin >> u >> v >> w ;
        // weight contains first..
        G[u].push_back(make_pair(w , v)) ;
        G[v].push_back(make_pair(w , u)) ;
    }
    bool flag = dijkstra(1 , n , n) ;
    if(flag)
        pathprint(n) ;
    else
        cout << "-1\n" ;
    return 0 ;
}

/*..............Dijkstra - 2nd shortest path...........*/

// Light oj 1099 - Not the Best
#include <bits/stdc++.h>
using namespace std ;

#define mxN 5000
#define INF 1e18

vector <pair<int , int > > G[mxN + 10] ;
long long dis1[mxN + 10] , dis2[mxN + 10] ;

void graph_clear(int nodes) {
    for(int i = 0 ; i <= nodes ; i++) {
        G[i].clear() ;
    }
}
void dijkstra(int start , int destination , int nodes) {
    for(int i = 0 ; i <= nodes ; i++)
        dis1[i] = dis2[i] = INF ;

    priority_queue <pair <int , int> > pq ;
    dis1[1] = 0 ;
    pq.push(make_pair(0 , 1)) ;
    
    while(!pq.empty()) {
        int u = pq.top().second ;
        int wu = -pq.top().first ;
        pq.pop() ;
        for(int i = 0 ; i < G[u].size() ; i++) {
            int v = G[u][i].second ;
            int wv = G[u][i].first ;
            if(wv + wu < dis1[v]) {
                dis2[v] = dis1[v] ; // if current weight is less then previous then the previous could be our 2nd shortest dis
                dis1[v] = wv + wu ;
                pq.push(make_pair(-dis1[v] , v)) ;
                pq.push(make_pair(-(dis1[v] + wv) , u)) ; // as considering back edge..
            }
            else if(wv + wu != dis1[v] && wu + wv < dis2[v]) {
                dis2[v] = wu + wv ;
                pq.push(make_pair(-dis2[v], v)) ;
            }
        }
    }
}
int main() {
    int tc ,t = 0 ;
    scanf("%d",&tc );
    while(tc--) {
        int nodes , edges ;
        scanf("%d%d",&nodes ,&edges );
        for(int i = 0 ; i < edges ; i++) {
            int u , v , w ;
            scanf("%d%d%d",&u , &v, &w) ;
            G[u].push_back(make_pair(w , v)) ;
            G[v].push_back(make_pair(w , u)) ;
        }
        int start = 1 , destination = nodes ;
        dijkstra(start , destination , nodes) ;
        printf("Case %d: %d\n",++t , dis2[destination] );
        graph_clear(nodes) ;
    }
    return 0 ;
}
