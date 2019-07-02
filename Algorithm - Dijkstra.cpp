// Dijkstra Algorithm implementation
//solution with : 10986 - Sending email

#include <bits/stdc++.h>
using namespace std ;
typedef long long ll ;
// A structure containing the edge node and the weight.
struct node{
    ll x , cost ;
    // constructor : when declaring a node also can initialize..
    node(ll _x , ll _cost) {
        x = _x ;
        cost = _cost ;
    }
    // operator overloading..
    bool operator < (const node& p) const {
        return cost > p.cost ;
    }
};
vector <node> G[20010] ;
ll dist[20010] ;
//clearing vector everytime and initialize with a large value in dist array
void Fill(ll nodes) {
    for(ll i = 0 ; i <= nodes + 1 ; i++){
        G[i].clear();
        dist[i] = 1e18 ;
    }
}
ll dijkstra(ll from , ll to , ll nodes) {
    priority_queue <node> pq ;
    dist[from] = 0 ; // current node is at 0 distance
    pq.push(node(from , 0)) ; // starting node and weight..
    while(!pq.empty()) {
        node temp = pq.top() ;
        ll u = pq.top().x ;
        ll wu = pq.top().cost ;
        pq.pop() ;
        if(u == to) // returning the minimum distance
            return dist[to] ;
        if(dist[u] < wu) // if current distance is bigger continuing
            continue ;
        for(ll i = 0 ; i < G[u].size() ; i++) {
            ll v = G[u][i].x ;
            ll wv = G[u][i].cost ;
            if(wu + wv < dist[v]) { //path relaxation..
                dist[v] = wu + wv ;
                pq.push(node(v,dist[v]));
            }
        }
    }
    return -1 ; //if no connection on from to to then returning -1..
}
int main() {
    int tc ,t = 0 ;
    scanf("%d",&tc) ;
    while(tc--) {
        ll nodes , edge ,from , to ;
        scanf("%lld%lld%lld%lld",&nodes,&edge,&from,&to) ;
        Fill(nodes) ;
        for(int i = 0 ; i < edge ; i++) {
            ll u , v , w ;
            scanf("%lld%lld%lld",&u,&v,&w) ;
            G[u].push_back(node( v , w)) ;
            G[v].push_back(node( u , w)) ;
        }
        ll ans = dijkstra(from , to , nodes) ;
        if(ans == -1)
            printf("Case #%d: unreachable\n",++t) ;
        else
            printf("Case #%d: %lld\n",++t , ans) ;
    }
    return 0;
}



// same as before just path printing included here..
// Problem name : C. Dijkstra?
// site : Codeforces

struct node{
    ll y , w;
};
vector <node> G[100001];
vector <ll> dist ;
ll path[100001] ;
bool flag = 0;
void dijkstra(ll source , ll destination , ll nodes){
    dist.resize(nodes + 1 , 1e18);
    dist[source] = 0;
    priority_queue <pair <ll,ll> > pq;
    pq.push({0,-source});
    while(!pq.empty()) {
        ll u = -pq.top().second;
        ll wu = -pq.top().first;
        pq.pop();
        if(u == destination){
            flag = 1;
            return ;
        }
        if(wu > dist[u])
            continue;
        for(int i = 0 ; i < G[u].size() ; i++) {
            node temp = G[u][i];
            ll v = temp.y ;
            ll wv = temp.w ;
            if(wu + wv < dist[v]) {
                dist[v] = wu + wv ;
                path[v] = u;
                pq.push({-dist[v],-v});
            }
        }
    }
}
void pathprint(ll from , ll to){
    ll temp = to ;
    vector <ll> v ;
    while(flag) {
        v.pb(temp) ;
        if(temp == from)
            break;
        temp = path[temp];
    }
    for(ll i = v.size() - 1 ; i >= 0 && flag ; i--){
        cout << v[i] << " ";
    }
    if(!flag)
        printf("-1");
    printf("\n");
}
int main() {
    int n , m  ;
    cin >> n >> m ;
    for(int i = 0 ; i < m ; i++) {
        ll a , b , w ;
        cin >> a >> b >> w ;
        node temp ;
        temp.y = b ;
        temp.w = w ;
        G[a].pb(temp);
        temp.y = a;
        G[b].pb(temp);
    }
    dijkstra(1 , n , n + 1);
    pathprint(1 , n) ;
    return 0;
}
