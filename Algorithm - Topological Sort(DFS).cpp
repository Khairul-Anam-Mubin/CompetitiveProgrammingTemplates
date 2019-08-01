// Algorithm
// Topological Sort
// Uva 10305 - Ordering Tasks

#define mxN 110
vector <int> G[mxN] ; // Graph adjacency list
vector <int> vec ; // containing the topological sort elements
int vis[mxN] ; // visited array
void dfs(int u) {
	vis[u] = 1 ;
	for(int i = 0 ; i < G[u].size() ; i++) {
		int v = G[u][i] ;
		if(!vis[v])
			dfs(v) ;
	}
	vec.pb(u) ;
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
			G[u].pb(v) ;
		}
		topsort(nodes);
		for(int i = 0 ; i < vec.size() - 1 ; i++)
			cout << vec[i] << " " ;
		cout << vec[vec.size() - 1 ] << "\n" ;
	}
	return  0 ;
}
