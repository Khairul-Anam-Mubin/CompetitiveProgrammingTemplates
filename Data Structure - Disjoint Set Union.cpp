//Data Structure - Disjoint Set Union
//Educational Codeforces Round 65 (Rated for Div. 2)
//Problem C. News Distribution

#include <bits/stdc++.h>

using namespace std;

int dsu[1000000]; // disjoint set array
int tot[1000000];
//Make set operation for initialize. Firstly there are N sets indicating this.
void makeset(int n){
    for(int i = 0 ; i <= n ; i++)
        dsu[i] = i;
}
//This Function finds parent and mark all child as same parent
int Find(int child){
    if(dsu[child] == child)
        return child;
    return dsu[child] = Find(dsu[child]);
}
//Simply Unions two set
void Union(int x,int y){
    x = Find(x);
    y = Find(y);
    dsu[x] = y;
}
int main() {
    int n , m ;
    cin >> n >> m;
    makeset(n);
    while(m--) {
        int k ; cin >> k ;
        if(!k) continue;
        int first ; cin >> first;
        for(int i = 1 ; i < k ; i++){
            int add; cin >> add;
            Union(first,add);
        }
    }
    //Finding Total number of elements in a particular set.
    for(int i = 1 ; i <= n ; i++)
        tot[Find(i)]++;
    for(int i = 1 ; i <= n  ; i++)
        cout << tot[Find(i)] << " ";
    cout << "\n";

    return 0;
}
