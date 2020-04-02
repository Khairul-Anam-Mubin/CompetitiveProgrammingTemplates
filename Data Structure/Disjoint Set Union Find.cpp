/*************************Disjoint Set Union Find**************************/

struct DSU {
    vector <int> parent;
    vector <int> siz;
    DSU(int mxN) {
        mxN <<= 1;
        parent.resize(mxN + 1);
        siz.resize(mxN + 1);
    }
    void Makeset(int n) {
        for (int i = 1 ; i <= n ; i++) {
            parent[i] = n + i;
            parent[n + i] = n + i;
            siz[n + i] = 1;
        }
    }
    int Find(int u) {
        if (parent[u] == u) return u ;
        return parent[u] = Find(parent[u]) ;
    }
    void Union(int u , int v) {
        u = Find(u);
        v = Find(v);
        if (u != v) {
            if (siz[u] < siz[v]) swap(u , v);
            parent[v] = u;
            siz[u] += siz[v];
        }
    }
    bool SameSet(int u , int v) {
        return (Find(u) == Find(v)) ;
    }
    void MoveUtoSetV(int u , int v) {
        if (SameSet(u , v)) return;
        int x = Find(u);
        int y = Find(v);
        siz[x]--;
        siz[y]++;
        parent[u] = y;
    }
    int Size(int u) {
        return siz[Find(u)];
    }
};
int main() {
    FasterIO
    DSU dsu(1000001);
    int n , m;
    cin >> n >> m;
    dsu.Makeset(n);
    for (int i = 1; i <= m; i++) {
        int k; cin >> k;
        if (!k) continue;
        int u; cin >> u;
        for (int j = 1; j < k; j++) {
            int v; cin >> v;
            dsu.Union(u , v);
        }
    }
    for (int i = 1; i <= n; i++)
        cout << dsu.Size(i) << " ";
    return 0 ;
}
