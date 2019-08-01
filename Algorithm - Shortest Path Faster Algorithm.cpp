// Algorithm
// Shortest Path Faster Algorithm by chinese programmers
// Bellman ford's varient 
// Uva 558 - Wormholes

vector < pair <int , int> > G[1010] ; // Graph..
int cost[1010] ; // containing shortest path costs..
int vis[1010] ;

// The chinese algorithm..
void ShortestPathFasterAlgorithm(int nodes) {
	for(int i = 0 ; i < 1010 ; i++) {
		cost[i] = INF ;
		vis[i] = 0 ;
	}
	cost[0] = 0 ; // setting the source cost as 0
	queue <int> q ;
	q.push(0) ; 
	while(!q.empty()) {
		int u = q.front() ;
		q.pop() ;
		vis[u] = 1 ;
		for(int i = 0 ; i < G[u].size() ; i++) {
			int v = G[u][i].first ;
			int wv = G[u][i].second ;
			if(cost[u] + wv < cost[v]) {
				cost[v] = cost[u] + wv ;
				if(!vis[v]) {
					q.push(v) ;
					vis[v] = 1 ;
				}
			}
		}
	}
}
// If there exist a negative weight cycle returning true 
bool NegativeCycle(int nodes) {
	for(int u = 0 ; u < nodes ; u++) {
		for(int i = 0 ; i < G[u].size() ; i++) {
			int v = G[u][i].first ;
			int wv = G[u][i].second ;
			if(cost[v] > cost[u] + wv) 
				return 1 ;
		}
	}
	return 0 ;
}
int main() {
	int tc ;
	cin >> tc ;
	while(tc--) {
		int nodes, edges ;
		cin >> nodes >> edges ;
		for(int i = 0 ; i < edges ; i++) {
			int u , v , w ;
			cin >> u >> v >> w ;
			G[u].pb(MP(v , w)) ;
		}
		ShortestPathFasterAlgorithm(nodes) ;
		bool ans = NegativeCycle(nodes) ;
		if(ans) 
			cout << "possible\n" ;
		else
			cout << "not possible\n" ;
		for(int i = 0 ; i <= nodes + 1 ; i++)
			G[i].clear() ;
	}
	return 0 ;
}
