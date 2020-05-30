// 1348 - Aladdin and the Return Journey

/**************************HeavyLightDecomposition***********************/
/*  1.  All nodes are number from 0 to n - 1  */ 
/*  2.  Assign the graph by Init(graph) or simply Init(total nodes) and 
        call AddEdge(u , v) for all the edges */
/*  3.  Must be Take the node value from input directly or use the 
        TakeNodeVal(nodeval) to assigning the node value */
/*  4.  Call Build() to construct hld and segment tree */
/*  5.  simply use the path query by query(u , v) and update(pos , val) */

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
    }
    void Init(const vector <vector<int>> &_g) {
        Init(_g.size());
        g = _g;
    }
    void AddEdge(int u , int v) {
        g[u].push_back(v) ;
        g[v].push_back(u) ;
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
    }
    void Update(int p , int val) {
        T.Update(1 , 0 , N - 1, node_serial[p] , -node_val[p]);
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
