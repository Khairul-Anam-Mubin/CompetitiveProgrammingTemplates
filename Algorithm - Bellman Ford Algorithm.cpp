// The algorithm..
void BellmanFord(int nodes) {
	for(int i = 0 ; i < 1010 ; i++)
		cost[i] = INF ;
	cost[0] = 0 ;
		for(int u = 0 ; u < nodes ; u++) {
			for(int k = 0 ; k < G[u].size() ; k++) {
				int v = G[u][k].first ;
				int wv = G[u][k].second ;
				cost[v] = min(cost[v] , cost[u] + wv) ;
			}
		}
}

// Algorithm
// Bellman Ford Algorithm
// Uva 558 - Wormholes
// negative weight graph
// Can find negative weight cycle with it

vector < pair <int , int> > G[1010] ; // Graph..
int cost[1010] ; // containing shortest path costs..

// The algorithm..
void BellmanFord(int nodes) {
	for(int i = 0 ; i < 1010 ; i++)
		cost[i] = INF ;
	cost[0] = 0 ;
	for(int i = 0 ; i < nodes - 1 ; i++) {
		for(int u = 0 ; u < nodes ; u++) {
			for(int k = 0 ; k < G[u].size() ; k++) {
				int v = G[u][k].first ;
				int wv = G[u][k].second ;
				cost[v] = min(cost[v] , cost[u] + wv) ;
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
		BellmanFord(nodes) ;
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
