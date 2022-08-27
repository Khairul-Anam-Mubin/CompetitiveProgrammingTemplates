template<typename T, bool maximum_mode = false>
struct RangeMinQuery {
    int n = 0;
    vector<vector<T>> sptab;
    static int LargestBit(int x) {
        return 31 - __builtin_clz(x);
    }
    static T Better(T a, T b) {
        return maximum_mode? max(a , b): min(a, b);
    }
    // O(NlogN)
    void Build(const vector<T> &values) {
        n = int(values.size());
        int levels = LargestBit(n) + 1;
        sptab.resize(levels);
        for (int k = 0; k < levels; k++) sptab[k].resize(n - (1 << k) + 1);
        if (n > 0) sptab[0] = values;
        for (int k = 1; k < levels; k++) {
            for (int i = 0; i <= n - (1 << k); i++) {
                sptab[k][i] = Better(sptab[k - 1][i], sptab[k - 1][i + (1 << (k - 1))]);
            }
        }
    }
    // O(1)
    int Query(int a, int b) const {  
        assert(0 <= a && a < b && b <= n);
        int level = LargestBit(b - a);
        return Better(sptab[level][a], sptab[level][b - (1 << level)]);
    }
};
RangeMinQuery<int>rmq;
// Complexity O(N * LogN)
struct SuffixArray{
    string s;
    int n;
    vector <int> sar , lcp, rank; // suffix array, lcp , rank
    SuffixArray() {}
    SuffixArray(string _s) {
        Init(_s);
    }
    void Init(string _s) {
        s = _s;
        s += "$";
        n = s.size();
        sar.resize(n);
        rank.resize(n);
        lcp.resize(n);
        BuildSuffixArray();
        BuildLCPArray();
        rmq.Build(lcp);
    }
    // O(NLogN)
    void BuildSuffixArray() {
        vector <int> cnt(256, 0), pos(256);
        for (int i = 0; i < n; i++) cnt[s[i]]++;
        pos[0] = 0;
        for (int i = 1; i < 256; i++) pos[i] = pos[i - 1] + cnt[i - 1];
        for (int i = 0; i < n; i++) {
            sar[pos[s[i]]] = i;
            pos[s[i]]++;
        }
        rank[sar[0]] = 0;
        for (int i = 1; i < n; i++) {
            rank[sar[i]] = rank[sar[i - 1]];
            if (s[sar[i]] != s[sar[i - 1]]) rank[sar[i]]++;
        }
        pos.resize(n);
        for (int k = 0; (1 << k) < n; k++) {
            for (int i = 0; i < n; i++) sar[i] = (sar[i] - (1 << k) + n) % n;
            cnt.assign(n, 0);
            for (int x : rank) cnt[x]++;
            pos[0] = 0;
            for (int i = 1; i < n; i++) pos[i] = pos[i - 1] + cnt[i - 1];
            vector <int> sar_new(n);
            for (int x : sar) {
                int i = rank[x];
                sar_new[pos[i]] = x;
                pos[i]++;
            }
            sar = sar_new;
            vector <int> rank_new(n);
            rank_new[sar[0]] = 0;
            for (int i = 1; i < n; i++) {
                rank_new[sar[i]] = rank_new[sar[i - 1]];
                pair <int, int> prev = {rank[sar[i - 1]], rank[(sar[i - 1] + (1 << k)) % n]};
                pair <int, int> cur = {rank[sar[i]] , rank[(sar[i] + (1 << k)) % n]};
                if (prev != cur) rank_new[sar[i]]++;
            }
            rank = rank_new;
        }
    }
    // algorithm of Kasai, Arimura, Arikawa, Lee and Park.
    // Complexity O(n)
    // Longest Common prefix of adjacent suffixes
    void BuildLCPArray() {
        int k = 0;
        for (int i = 0; i < n - 1; i++) {
            int pi = rank[i];
            int j = sar[pi - 1];
            while (s[i + k] == s[j + k]) k++;
            lcp[pi] = k;
            k = max(k - 1, 0);
        }
    }
    // O(1)
    int GetLcpFromRanks(int a, int b) const {
        if (a == b) return n - sar[a];
        if (a > b) swap(a, b);
        return rmq.Query(a + 1, b + 1);
    }
    // O(1)
    int GetLcp(int a, int b) const {
        if (a >= n || b >= n) return 0;
        if (a == b) return n - a;
        return GetLcpFromRanks(rank[a], rank[b]);
    }
    // Compares the substrings starting at `a` and `b` up to `length`
    // O(1)
    int Compare(int a, int b, int length = -1) const {
        if (length < 0) length = n;
        if (a == b) return 0;
        int common = GetLcp(a, b);
        if (common >= length) return 0;
        if (a + common >= n || b + common >= n) {
            return a + common >= n ? -1 : 1;
        }
        return s[a + common] < s[b + common] ? -1 : (s[a + common] == s[b + common] ? 0 : 1);
    }
    // O(N)
    long long NumOfUniqueSubStr() {
        long long sum = 0;
        for (int i = 1; i < lcp.size(); i++) sum += lcp[i];
        long long sz = n - 1; // actual size of string
        long long totalSubStrings = (sz * (sz + 1)) / 2LL;
        return totalSubStrings - sum;
    }
    // O(|t|*LogN)
    bool IsSubstr(string &t) {  
        int tlen = t.size();
        if (tlen > n) return false;
        int low = LowerBound(t);
        if (low < n && n - sar[low] >= tlen && s.compare(sar[low] , tlen, t) == 0) return true;
        return false;
    }
    // O(|t|*LogN)
    int LowerBound(string &t) {
        int low = 0 ,high = n ,tlen = t.size();
        while (low < high) {
            int mid = (low + high) >> 1;
            if (s.compare(sar[mid], tlen, t) < 0)
                low = mid + 1;
            else
                high = mid;
        }
        return low;
    }
    // O(|t|*LogN)
    int UpperBound(string &t) {
        int low = 0 ,high = n ,tlen = t.size();
        while (low < high) {
            int mid = (low + high) >> 1;
            if (s.compare(sar[mid], tlen, t) <= 0)
                low = mid + 1;
            else
                high = mid;
        }
        return low;
    }
    // O(|t|*LogN)
    int SubstrOccurences(string &t) {
        int tlen = t.size();
        int low = LowerBound(t) , up = UpperBound(t);
        if (low == up || s.compare(sar[low] , tlen , t) != 0) return 0;
        return (up - low);
    }
    // Longest common substring of two string
    // O(NLogN)
    string LongestCommonSubstring(string &a, string &b) {
        int alen = a.size();
        Init(a + "&" + b);
        int tot = sar.size();
        bool color[tot];
        for (int i = 0; i < tot; i++) {
            if (sar[i] < alen) color[i] = 1;
            else color[i] = 0;
        }
        int mx = -1 , mxid = -1;
        for (int i = 1; i < tot; i++) {
            if (color[i] != color[i - 1] && mx < lcp[i]) {
                mx = lcp[i];
                mxid = sar[i];
            }
        }
        if (mxid != -1) return s.substr(mxid , mx);
        return "";
    }
    void ShowSuffixArray() {
        cout << "Rank LCP    SA    Suffixes\n";
        for (int i = 0; i < n; i++) {
            cout << rank[i] << "    " << lcp[i] << "     " << sar[i] << "     " << s.substr(sar[i] , n - sar[i]) << "\n";
        }
    }
};
