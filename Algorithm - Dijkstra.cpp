
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
            if(wu + wv < dist[v]) { // path relaxation 
                dist[v] = wu + wv ;
                path[v] = u; // savinng Path here...
                pq.push({-dist[v],-v});
            }
        }
    }
}
// Shortest Path  Printing..
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
