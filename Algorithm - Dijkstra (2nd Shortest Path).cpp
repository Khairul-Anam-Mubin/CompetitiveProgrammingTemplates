// Dijkstra - 2nd shortest path..
// Light oj 1099 - Not the Best

#include <bits/stdc++.h>
uisng namespace std ;

vector <pair<int , int > > G[5010] ;
int dis1[5010] , dis2[5010] ;
void clean(int nodes) {
    for(int i = 0 ; i <= nodes ; i++) {
        G[i].clear() ;
        dis1[i] = INF ;
        dis2[i] = INF ;
    }
}
void dijkstra() {
    priority_queue <pair <int , int> > pq ;
    dis1[1] = 0 ;
    pq.push(MP(0 , 1)) ;
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
                pq.push(MP(-dis1[v] , v)) ;
                pq.push(MP(-(dis1[v] + wv) , u)) ; // as considering back edge..
            }
            else if(wv + wu != dis1[v] && wu + wv < dis2[v]) {
                dis2[v] = wu + wv ;
                pq.push(MP(-dis2[v], v)) ;
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
        clean(nodes) ;
        for(int i = 0 ; i < edges ; i++) {
            int u , v , w ;
            scanf("%d%d%d",&u , &v, &w) ;
            G[u].pb(MP(w , v)) ;
            G[v].pb(MP(w , u)) ;
        }
        dijkstra() ;
        printf("Case %d: %d\n",++t , dis2[nodes] );
    }
    return 0 ;
}
