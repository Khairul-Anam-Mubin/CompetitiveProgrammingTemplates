// 1348 - Aladdin and the Return Journey

const int mxN = 30000;
vector <int> pos;

struct SegmentTree {
    vector <long long> seg;
    vector <long long> lazy;
    vector <long long> ar;
    void Init(int N) {
        seg.assign(N << 2, 0);
        lazy.assign(N << 2 , 0);
    }
    void Init(vector <long long> &s) {
        Init(s.size() + 1);
        ar = s;
    }
    void PushDown(int cur , int left , int right) {
        seg[cur] += (right - left + 1) * lazy[cur];
        if (left != right) {        
            lazy[cur << 1] += lazy[cur];  
            lazy[cur << 1 | 1] += lazy[cur];
        }
        lazy[cur] = 0;   
        return;
    }
    void Build(int cur , int left , int right) {
        lazy[cur] = 0;
        if (left == right) {
            seg[cur] = ar[left];
            return;
        }
        int mid = (left + right) >> 1;
        Build(cur << 1 , left , mid);
        Build(cur << 1 | 1 , mid + 1 , right);
        seg[cur] = seg[cur << 1] + seg[cur << 1 | 1];
        return;
    }
    void Update(int cur , int left , int right , int pos , long long val) {
        Update(cur , left , right , pos , pos , val);
        return;
    }
    void Update(int cur , int left , int right , int l , int r , long long val) {
        if (lazy[cur] != 0) PushDown(cur , left , right);         
        if (l > right || r < left) return;
        if (left >= l && right <= r) {
            lazy[cur] = val;
            PushDown(cur , left , right);
            return ;
        }
        int mid = (left + right) >> 1;
        Update(cur << 1 , left , mid , l , r , val);
        Update(cur << 1 | 1 , mid + 1 , right , l , r , val);
        seg[cur] = seg[cur << 1] + seg[cur << 1 | 1];
        return ;
    }
    long long Query(int cur , int left , int right , int l , int r) {
        if (l > right || r < left) return 0;
        if (lazy[cur] != 0) PushDown(cur , left , right);
        if (left >= l && right <= r) return seg[cur];
        int mid = (left + right) >> 1;
        long long p1 = Query(cur << 1 , left , mid , l , r);
        long long p2 = Query(cur << 1 | 1 , mid + 1 , right , l , r);
        return (p1 + p2) ;
    }
} T;

struct PathQuery {
    vector <vector <int> > g ; // graph
    vector <long long> segarr; // segment tree array on the flat tree
    // HLD and LCA staffs
    int chain_no, indx;
    int N , root = 0 , po ;
    vector <vector <int> > sptab ; 
    vector <int> depth , parent , sub;
    vector <int> chain_head , chain_ind;
    vector <int> node_serial , serial_node;
    void Init(int n) {
        N = n;
        po = log2((N + 1)) + 1 ;
        g.assign(N + 1 , {}) ;
        sptab.assign(N + 1 , {}) ;
        depth.resize(N + 1) ;
        parent.resize(N + 1) ;
        sub.resize(N + 1);
        chain_head.assign(N + 1 , -1);
        chain_ind.resize(N + 1);
        node_serial.resize(N + 1);
        serial_node.resize(N + 1);
        segarr.resize(N + 1);
    }
    void Init(const vector <vector<int>> &_g) {
        Init(_g.size() + 1);
        g = _g;
    }
    void AddEdge(int u , int v) {
        g[u].push_back(v) ;
        g[v].push_back(u) ;
    }
    void ShowGraph() {
        for(int i = 0 ; i < N ; i++) {
            cout << i << " : " ;
            for(int j = 0 ; j < g[i].size() ; j++) {
                cout << g[i][j] << " " ;
            }
            cout << "\n" ;
        }
    }
    void Dfs(int u, int par = -1) {
        sub[u] = 1;
        if (par == -1) {
            depth[u] = 0;
            parent[u] = -1;
        }
        for (int v : g[u]) {
            if (v != par) {
                parent[v] = u;
                depth[v] = depth[u] + 1;
                Dfs(v , u);
                sub[u] += sub[v];
            }
        }
    }
    void SparceTable() {
        for(int i = 0 ; i < N ; i++) {
            sptab[i][0] = parent[i] ;
        }
        for(int j = 1 ; (1 << j) < N ; j++) {
            for(int i = 0 ; i < N ; i++) {
                if(sptab[i][j - 1] != -1) {
                    sptab[i][j] = sptab[sptab[i][j - 1]][j - 1] ;
                }
            }
        }
    }
    void Build() {
        for (int i = 0 ; i <= N ; i++) {
            for (int j = 0 ; j <= po ; j++) {
                sptab[i].push_back(-1);
            }
        }
        Dfs(root);
        SparceTable();
        // here heavy light call and other DS used..
        chain_no = 0, indx = 0;
        HeavyLightDecompose(0 , 0);
        T.Init(segarr);
        T.Build(1 , 0 , N - 1);
    }
    void HeavyLightDecompose(int u , int par) {
        if (chain_head[chain_no] == -1) chain_head[chain_no] = u;
        chain_ind[u] = chain_no; 
        node_serial[u] = indx;
        serial_node[indx] = u;
        segarr[indx] = pos[u]; // tree flatting..
        indx++;
        int heavychild = -1 , heavysize = 0;
        for (int v : g[u]) {
            if (v != par) {
                if (sub[v] > heavysize) {
                    heavysize = sub[v];
                    heavychild = v;
                }
            }
        }
        if (heavychild != -1) 
            HeavyLightDecompose(heavychild , u);
        for (int v : g[u]) {
            if (v != par && v != heavychild) {
                chain_no++;
                HeavyLightDecompose(v , u);
            }
        }
    }
    // These are HLD queries using other DS like segment tree.
    void HldUpdate(int p , int val) {
        T.Update(1 , 0 , N - 1, node_serial[p] , val);
    }
    long long HldQuery(int u, int v) {
        long long ans = 0;
        while (chain_ind[u] != chain_ind[v]) { // Query on different heavy and light chain..
            ans += T.Query(1 , 0 , N - 1, node_serial[chain_head[chain_ind[u]]] , node_serial[u]);
            u = sptab[chain_head[chain_ind[u]]][0];
        }
        // Query on same chain..
        ans += T.Query(1 , 0 , N - 1, node_serial[v] , node_serial[u]); 
        return ans;
    }
    int Lca(int u , int v) {
        if (depth[u] < depth[v]) swap(u , v) ;
        int log ;
        for (log = 1 ; (1 << log) <= depth[u] ; log++); log--;
        for (int i = log ; i >= 0 ; i--) {
            if (depth[u] - (1 << i) >= depth[v]) {
                u = sptab[u][i];
            }
        }
        if (u == v) return u;
        for (int i = log ; i >= 0 ; i--) {
            if (sptab[u][i] != -1 && sptab[u][i] != sptab[v][i]) {
                u = sptab[u][i];
                v = sptab[v][i];
            } 
        }
        return parent[u];
    }
    int Getdist(int u , int v) {
        return depth[u] + depth[v] - (2 * (depth[Lca(u , v)])) ;
    }
    bool IsAnsector(int u , int v) {
        int cur = Lca(u , v) ;
        if(cur == u) return 1 ;
        return 0 ;
    }
} HLD;
long long Query(int u , int v) {
    long long lca = HLD.Lca(u , v);
    long long ans = HLD.HldQuery(u  , lca);
    ans += HLD.HldQuery(v , lca);
    ans -= pos[lca];
    return ans;
}
void Update(int p , int val) {
    HLD.HldUpdate(p , -pos[p]);
    HLD.HldUpdate(p , val);
    pos[p] = val;
}   
int main() {
    Faster
    Test {
        int n; cin >> n;
        for (int i = 0; i < n; i++) {
            ll x; cin >> x;
            pos.PB(x);
        }
        HLD.Init(n);
        for (int i = 0; i < n - 1; i++) {
            int u , v; cin >> u >> v;
            HLD.AddEdge(u , v);
        }
        HLD.Build();
        int q; cin >> q;
        cout << "Case " << tc << ":\n";
        while (q--) {
            int x; cin >> x;
            if (x == 0) {
                int u , v; cin >> u >> v;
                cout << Query(u , v) << "\n";
            } else if (x == 1) {
                int node , val;
                cin >> node >> val;
                Update(node , val);
            }
        }
        pos.clear();
    }
    return 0;
}
