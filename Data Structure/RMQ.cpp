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
        for (int k = 0; k < levels; k++) {
            sptab[k].resize(n - (1 << k) + 1);
        }
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
