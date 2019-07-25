// Uva : 11631 - Dark roads
// Kruskal Algorithm
// Finding Minimum Spanning Tree

#include <bits/stdc++.h>
using namespace std ;

set < pair <int ,pair <int , int > > > st ;
set < pair <int ,pair <int , int > > > :: iterator it ;
#define mx 200010
int dsu[mx] ;
void makeset(int nodes) {
	for(int i = 0 ; i <= nodes + 1 ; i++) 
		dsu[i] = i ;
}
int Find(int x) {
	if(x == dsu[x]) 
		return x ;
	return dsu[x] = Find(dsu[x]) ;
}
void Union(int x ,int y) {
	x = Find(x) ;
	y = Find(y) ;
	if( x != y) 
		dsu[x] = y ;
}
bool sameset(int u, int v) {
	if(Find(u) == Find(v)) 
		return 1 ;
	return 0 ; 
}
int KruskalAlgo(int nodes) {
	makeset(nodes) ;
	int cost = 0 ;
	int cnt = 0 ;
	for(it = st.begin() ; it != st.end() ; it++) {
		int u = (*it).second.first ;
		int v = (*it).second.second ;
		int w = (*it).first ;
		if(!sameset(u , v)) {
			cost += w ;
			Union(u  ,v) ;
			cnt++ ;
		}
		if(cnt == nodes - 1)
			break;
	}
	return cost ;
}

int main() {
	int nodes , edges ;
	while(cin >> nodes >> edges && nodes && edges) {
		int tot = 0 ; 
		for(int i = 0 ; i < edges ; i++) {
			int u , v , w ;
			cin >> u >> v >> w ;
			st.insert(MP(w ,MP(u , v))) ;
			tot += w ;
		}
		int ans = tot - KruskalAlgo(nodes) ; 
		cout << ans << "\n" ;
		st.clear() ;
	}
	return 0 ;
}
// Note : For the 2nd minimum spanning tree we fisrt have to find 1st  MST and a vis array to mark the edges which are used in making  
// these MST the we simply ignore each time igonre 1 edge and try to make spanning tree and rest the minimum of them is the answer..
// MST is also used as Minimax , maximin , forest , sub graph
