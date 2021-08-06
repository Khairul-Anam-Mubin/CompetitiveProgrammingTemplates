#include <bits/stdc++.h>
using namespace std;

template<typename T, bool maximum_mode = false>
struct RMQ {
    int n = 0;
    vector<vector<T>> sptab;
    static int Largest_Bit(int x) {
        return 31 - __builtin_clz(x);
    }
    static T Better(T a, T b) {
        return maximum_mode? max(a , b): min(a, b);
    }
    void Build(const vector<T> &values) {
        n = int(values.size());
        int levels = Largest_Bit(n) + 1;
        sptab.resize(levels);
        for (int k = 0; k < levels; k++) sptab[k].resize(n - (1 << k) + 1);
        if (n > 0) sptab[0] = values;
        for (int k = 1; k < levels; k++) {
            for (int i = 0; i <= n - (1 << k); i++) {
                sptab[k][i] = Better(sptab[k - 1][i], sptab[k - 1][i + (1 << (k - 1))]);
            }
        }
    }
    int query_value(int a, int b) const {  // Complexity : O(1)
        assert(0 <= a && a < b && b <= n);
        int level = Largest_Bit(b - a);
        return Better(sptab[level][a], sptab[level][b - (1 << level)]);
    }
};
RMQ<int>rmq;
// Complexity O(N * LogN) [radix_sort used]
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
    void BuildSuffixArray() {
        vector <pair<char,int>> a(n);
        for (int i = 0; i < n; i++) a[i] = {s[i] , i};
        sort(a.begin() , a.end());
        for (int i = 0; i < n; i++) sar[i] = a[i].second;
        rank[sar[0]] = 0;
        for (int i = 1; i < n; i++) {
            rank[sar[i]] = rank[sar[i - 1]];
            if (a[i].first != a[i - 1].first) rank[sar[i]]++;
        }
        for (int k = 0; (1 << k) < n; k++) {
            vector <pair<pair<int , int>, int>> a(n);
            for (int i = 0; i < n; i++) a[i] = {{rank[i] , rank[(i + (1 << k)) % n]} , i};
            Radix_Sort(a);
            for (int i = 0; i < n; i++) sar[i] = a[i].second;
            rank[sar[0]] = 0;
            for (int i = 1; i < n; i++) {
                rank[sar[i]] = rank[sar[i - 1]];
                if (a[i].first != a[i - 1].first) rank[sar[i]]++;
            }
        }
    }
    void Radix_Sort(vector <pair<pair<int , int>, int>> &a) {
        vector <int> cnt(n, 0) , pos(n);
        vector <pair<pair<int , int> , int>> a_new(n);
        for (auto it: a) cnt[it.first.second]++;
        pos[0] = 0;
        for (int i = 1; i < n; i++) pos[i] = pos[i - 1] + cnt[i - 1];
        for (auto it : a) {
            int i = it.first.second;
            a_new[pos[i]] = it;
            pos[i]++;
        }
        a.swap(a_new);
        cnt.assign(n , 0);
        for (auto it: a) cnt[it.first.first]++;
        pos[0] = 0;
        for (int i = 1; i < n; i++) pos[i] = pos[i - 1] + cnt[i - 1];
        for (auto it : a) {
            int i = it.first.first;
            a_new[pos[i]] = it;
            pos[i]++;
        }
        a.swap(a_new);
    }
    // algorithm of Kasai, Arimura, Arikawa, Lee and Park.
    // Complexity O(n)
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
    int get_lcp_from_ranks(int a, int b) const {
        if (a == b) return n - sar[a];
        if (a > b) swap(a, b);
        return rmq.query_value(a + 1, b + 1);
    }
    int get_lcp(int a, int b) const {
        if (a >= n || b >= n) return 0;
        if (a == b) return n - a;
        return get_lcp_from_ranks(rank[a], rank[b]);
    }
    // Compares the substrings starting at `a` and `b` up to `length` in O(1).
    int compare(int a, int b, int length = -1) const {
        if (length < 0) length = n;
        if (a == b) return 0;
        int common = get_lcp(a, b);
        if (common >= length) return 0;
        if (a + common >= n || b + common >= n) {
            return a + common >= n ? -1 : 1;
        }
        return s[a + common] < s[b + common] ? -1 : (s[a + common] == s[b + common] ? 0 : 1);
    }
    void ShowSuffixArray() {
        cout << "Rank LCP    SA    Suffixes\n";
        for (int i = 0; i < n; i++) {
            cout << rank[i] << "    " << lcp[i] << "     " << sar[i] << "     " << s.substr(sar[i] , n - sar[i]) << "\n";
        }
    }
    // Extends Templates(Queries)...
    // Binary search Complexity O(logN)
    long long NumOfUniqueSubStr() {
        long long sum = 0;
        for (int i = 0; i < lcp.size(); i++) sum += lcp[i];
        
        long long sz = ((n - 1) * n) / 2;
        return sz - sum;
    }
    bool IsSubstr(string &t) {  
        if ((int)t.size() > (int)s.size()) return false;
        int low = Lower_Bound(t);
        if (s.substr(sar[low] , min(int(t.size()) , n)) == t) return true;
        return false;
    }
    int Lower_Bound(string &t) {
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
    int Upper_Bound(string &t) {
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
    int SubstrOccurences(string &t) {
        int low = Lower_Bound(t) , up = Upper_Bound(t);
        if (low == up || s.substr(sar[low] , min(int(t.size()) , n)) != t) return 0;
        return (up - low);
    }
    string LCS(string &a, string &b) {
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
};