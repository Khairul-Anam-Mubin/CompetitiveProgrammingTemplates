/*******************String Hashing*********************/
// Double Hashing
// 1. Modular Exponentian Needed
// 2. Init must be call and set the maximum length of the string
// 3. If sub string hash required then Compute hash have to call
// 4. If prefix and suffix hash required ComputePreAndSufHash have to call

struct ModularExponentiation {
    template <typename T> T Pow(T b, T p) {
        T res = 1;
        while (p > 0) {
            if (p % 2 == 1) res = res * b;
            b = b * b;
            p /= 2;
        }
        return res;
    }
    template <typename T> T Mod(T a, T m) { 
        return (((a % m) + m) % m);
    }
    template <typename T> T BigMod(T b, T p, T m) {
        T res = 1;
        if (b > m) b %= m;
        while (p) {
            if (p % 2 == 1) res = res * b % m;
            b = b * b % m;
            p /= 2;
        }
        return res;
    }
    template <typename T> T ModInv(T b,T m) {
        return BigMod(b , m - 2 , m);
    }
};
struct DoubleHashing {
    long long base[2] = {1949313259, 1997293877};
    long long mod[2] = {2091573227, 2117566807};
    vector <long long> pow[2] , inv[2];
    vector <long long> prehash[2] , sufhash[2];
    int maxN , flag = 0 , len;
    void Init(int n) {
        maxN = n + 2;
        for (int i = 0; i < 2; i++) {
            pow[i].resize(maxN);
            inv[i].resize(maxN);
        }
        Generate();
    }
    void Generate() {
        ModularExponentiation Ex;
        for (int j = 0; j < 2; j++) {
            pow[j][0] = 1;
            inv[j][0] = 1;
            long long minv = Ex.ModInv(base[j] ,mod[j]);
            for (int i = 1; i < maxN; i++) {
                pow[j][i] = pow[j][i - 1] * base[j] % mod[j];
                inv[j][i] = inv[j][i - 1] * minv % mod[j];
            }
        }
    }
    long long GetHash(string &s) {
        long long hash_val[2] = {0 , 0};
        int n = s.size();
        for (int j = 0; j < 2; j++) {
            for (int i = 0; i < n; i++) {
                hash_val[j] = (hash_val[j] + s[i] * pow[j][i]) % mod[j];
            }
        }
        return (hash_val[0] << 32LL) | hash_val[1];
    }
    void ComputeHash(string &s) {
        flag = 1;
        len = s.size();
        for (int j = 0; j < 2; j++) prehash[j].resize(maxN);
        for (int j = 0; j < 2; j++) prehash[j][0] = 0;
        for (int j = 0; j < 2; j++) {
            for (int i = 0; i < len; i++) {
                prehash[j][i + 1] = (prehash[j][i] + pow[j][i] * s[i]) % mod[j];
            }
        }
    }
    long long GetSubstrHash(int l , int r) {
        if (!flag) { cout << "ComputeHash\n"; return -1;}
        long long hash_val[2];
        for (int j = 0; j < 2; j++) 
            hash_val[j] = (prehash[j][r + 1] - prehash[j][l]) * inv[j][l] % mod[j];
        for (int j = 0; j < 2; j++) if (hash_val[j] < 0) hash_val[j] += mod[j];   
        return (hash_val[0] << 32) | hash_val[1]; 
    }
    void ComputePreAndSufHash(string &s) {
        flag = 1;
        len = s.size();
        for (int j = 0; j < 2; j++) { 
            prehash[j].resize(maxN);
            sufhash[j].resize(maxN);
        }
        for (int j = 0; j < 2; j++) prehash[j][0] = sufhash[j][0] = 0;
        for (int j = 0; j < 2; j++) {
            for (int i = 0; i < len; i++) {
                prehash[j][i + 1] = (prehash[j][i] + pow[j][i] * s[i]) % mod[j];
                sufhash[j][i + 1] = (sufhash[j][i] + pow[j][len - i + 1] * s[i]) % mod[j];
            }
        }
    }
    long long GetPrefixHash(int l , int r) {
        return GetSubstrHash(l , r);
    }
    long long GetSuffixHash(int l , int r) {
        if (!flag) { cout << "ComputePreAndSufHash\n"; return -1;}
        long long hash_val[2];
        for (int j = 0; j < 2; j++) 
            hash_val[j] = (sufhash[j][r + 1] - sufhash[j][l]) * inv[j][len - r + 1] % mod[j];
        for (int j = 0; j < 2; j++) if (hash_val[j] < 0) hash_val[j] += mod[j];   
        return (hash_val[0] << 32) | hash_val[1];  
    } 
    bool IsPallindrome(int l , int r) {
        return (GetPrefixHash(l , r) == GetSuffixHash(l , r));
    }
    vector <int> RabinKarp(string &txt , string &ptrn) {
        ComputeHash(txt);
        long long ptrn_hash = GetHash(ptrn);
        vector <int> occurences;
        int txtlen = txt.size();
        int ptrnlen = ptrn.size();
        for (int i = 0; i < txtlen - ptrnlen + 1; i++) {
            long long cur_hash = GetSubstrHash(i , ((i + ptrnlen) - 1));
            // pattern match...
            if (cur_hash == ptrn_hash) 
                occurences.emplace_back(i + 1);
        }
        return occurences;
    }
} ;
