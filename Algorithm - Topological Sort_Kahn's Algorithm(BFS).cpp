// Algorithm 
// Topological sorting (BFS) 
// Kahn's Algorithm 
map <string , int> mp ; // simply mapping
map <int , string> ans ; // simply mapping
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
		vec.pb(ans[u]) ; // this must be in the sorted list..  
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
			G[u].pb(v) ;
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
