/**************************HeavyLightDecomposition***********************/
/*  1.  All nodes are number from 0 to n - 1  */ 
/*  2.  Assign the graph by Init(graph) or simply Init(total nodes) and 
        call AddEdge(u , v) for all the edges */
/*  3.  Must be Take the node value from input directly or use the 
        TakeNodeVal(nodeval) to assigning the node value */
/*  4.  Call Build() to construct hld and segment tree */
/*  5.  simply use the path query by query(u , v) and update(pos , val) 
/*
/*  6. use optimized segment tree sometimes it cz TLE
/**********************Segment tree**************************************/
/*
    1. constructor
    2. init
    3. build
    4. take careod INF9 and INF18
*/
#define INF9         2147483647
#define INF18        9223372036854775806
template <typename T> struct SegmentTree {
    vector <T> seg;
    vector <T> lazy;
    vector <T> ar;
    int type , up;
    SegmentTree() {
        type = 0;
        up = 0;
    }
    SegmentTree(int tp , int u) {
        type = tp;
        up = u;
    }
    void Init(int N) {
        seg.assign(N << 2, 0);
        lazy.assign(N << 2 , 0);
    }
    void Init(vector <T> &s) {
        Init(s.size() + 1);
        ar = s;
    }
    void PushDown(int cur , int left , int right) {
        if (type == 0) {
            if (up == 1) seg[cur] += (right - left + 1) * lazy[cur];
            else seg[cur] = (right - left + 1) * lazy[cur];
        } else {
            if (up == 1) seg[cur] += lazy[cur];
            else seg[cur] = lazy[cur];
        }
        if (left != right) {
            if (up == 1) {        
                lazy[cur << 1] += lazy[cur];  
                lazy[cur << 1 | 1] += lazy[cur];
            } else {
                lazy[cur << 1] = lazy[cur];  
                lazy[cur << 1 | 1] = lazy[cur];
            }
        }
        lazy[cur] = 0;
    }
    T Merge(T x , T y) {
        if (type == 0) return x + y;
        if (type == 1) return max(x , y);
        if (type == 2) return min(x , y);
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
        seg[cur] = Merge(seg[cur << 1] , seg[cur << 1 | 1]);
    }
    void Update(int cur , int left , int right , int pos , T val) {
        Update(cur , left , right , pos , pos , val);
    }
    void Update(int cur , int left , int right , int l , int r , T val) {
        if (lazy[cur] != 0) PushDown(cur , left , right);         
        if (l > right || r < left) return;
        if (left >= l && right <= r) {
            if (up == 0) lazy[cur] = val;
            else lazy[cur] += val;
            PushDown(cur , left , right);
            return ;
        }
        int mid = (left + right) >> 1;
        Update(cur << 1 , left , mid , l , r , val);
        Update(cur << 1 | 1 , mid + 1 , right , l , r , val);
        seg[cur] = Merge(seg[cur << 1] , seg[cur << 1 | 1]);
    }
    T Query(int cur , int left , int right , int l , int r) {
        if (l > right || r < left) {
            if (type == 0) return 0;
            if (type == 1) return -INF18;
            if (type == 2) return INF18;
        }
        if (lazy[cur] != 0) PushDown(cur , left , right);
        if (left >= l && right <= r) return seg[cur];
        int mid = (left + right) >> 1;
        T p1 = Query(cur << 1 , left , mid , l , r);
        T p2 = Query(cur << 1 | 1 , mid + 1 , right , l , r);
        return Merge(p1 , p2);
    }
};
//for sum = 0, max = 1, min = 2, for assignment update send 0 or 1 for increment.
SegmentTree <long long> T(0 , 0);
struct HeavyLightDecompose {
    vector <vector <int> > g ; // graph
    vector <long long> node_val;
    int N , root = 0;
    vector <int> depth , parent , sub;
    // HLD staffs
    int chain_no, indx;
    vector <int> chain_head , chain_ind;
    vector <int> node_serial , serial_node;
    vector <long long> segarr; // tree on linear format
    void Init(int n) {
        N = n;
        g.assign(N , {});
        node_val.clear();
        segarr.resize(N);
        depth.resize(N);
        parent.resize(N);
        sub.resize(N);
        chain_head.assign(N, -1);
        chain_ind.resize(N);
        node_serial.resize(N);
        serial_node.resize(N);
        return;
    }
    void Init(const vector <vector<int>> &_g) {
        Init(_g.size());
        g = _g;
        return;
    }
    void AddEdge(int u , int v) {
        g[u].push_back(v) ;
        g[v].push_back(u) ;
        return;
    }
    void TakeNodeVal(const vector <long long> &_node_val) {
        node_val = _node_val;
    }
    void Build() {
        Dfs(root);
        chain_no = 0, indx = 0;
        HLD(0);
        T.Init(segarr);
        T.Build(1 , 0 , N - 1);
    }
    void Dfs(int u, int par = -1) {
        sub[u] = 1;
        if (par == -1) {
            depth[u] = 0;
            parent[u] = -1;
        }
        for (int v : g[u]) {
            if (v == par) continue;
            parent[v] = u;
            depth[v] = depth[u] + 1;
            Dfs(v , u);
            sub[u] += sub[v];
            
        }
        return;
    }
    void HLD(int u , int par = -1) {
        if (chain_head[chain_no] == -1) chain_head[chain_no] = u;
        chain_ind[u] = chain_no;
        node_serial[u] = indx;
        serial_node[indx] = u;
        segarr[indx] = node_val[u]; // tree flatting..
        indx++;
        int heavychild = -1 , heavysize = 0;
        for (int v : g[u]) {
            if (v == par) continue;
            if (sub[v] > heavysize) {
                heavysize = sub[v];
                heavychild = v;
            }
        }
        if (heavychild != -1) HLD(heavychild , u);
        for (int v : g[u]) {
            if (v != par && v != heavychild) {
                chain_no++;
                HLD(v , u);
            }
        }
        return;
    }
    void Update(int p , int val) {
        T.Update(1 , 0 , N - 1, node_serial[p] , val);
        node_val[p] = val;
    }
    long long Query(int u , int v) {
        long long ans = 0;
        for ( ; chain_ind[u] != chain_ind[v] ; v = parent[chain_head[chain_ind[v]]]) {
            if (depth[chain_head[chain_ind[u]]] > depth[chain_head[chain_ind[v]]])
                swap( u , v );
            ans += T.Query(1 , 0 , N - 1 , node_serial[chain_head[chain_ind[v]]] , node_serial[v]);
        }
        if (depth[u] > depth[v])
            swap(u , v);
        ans += T.Query(1 , 0 , N - 1 , node_serial[u] , node_serial[v]);
        return ans;
    }
} hd;