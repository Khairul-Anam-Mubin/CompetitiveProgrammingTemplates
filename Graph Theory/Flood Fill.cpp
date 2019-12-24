/*********************************Flood Fill**************************************/

/*...........................Finding connected Components............................*/
// Uva : Oil deposits
#include <bits/stdc++.h>
using namespace std;
int n , m ;
char grid[110][110];
int visited[110][110]; // visited array
// Direction array
int row[] = {0,0,-1,1,-1,-1,1,1};
int col[] = {1,-1,0,0,-1,1,-1,1};
// initializing all grid as unvisited
void filll() {
    for(int i  = 0 ; i <= n+1 ; i++){
        for(int j = 0 ; j <= m+1 ; j++){
            visited[i][j] = 0;
        }
    }
}
// starting dfs
void dfs(int x, int y) {
    visited[x][y] = 1;
    int xx , yy ;
    for(int i = 0 ; i < 8 ; i++){
        xx = x + row[i]; 
        yy = y + col[i];
        // boundary checking and if unvisited then agian go with dfs
        if((grid[xx][yy] == '@') && (xx >= 1) && (yy >= 1) && (xx <= n) && (yy <= m) && (visited[xx][yy] == 0)){
            dfs(xx,yy);
        }
    }
}
int main() {
    while(cin >> n >> m) {
        if(n==0 && m==0)break;
        filll();
        for(int i = 1 ; i <= n ; i++)
            for(int j = 1 ; j <= m ; j++)
                cin >> grid[i][j];
        int cnt = 0;
        for(int i = 1 ; i <= n ; i++){
            for(int j = 1 ; j <= m; j++){
                if(grid[i][j] == '@' && visited[i][j] == 0 ){
                    cnt++; // these are the connected components
                    dfs(i,j);
                }
            }
        }
        cout << cnt << "\n";
    }
    return 0;
}
