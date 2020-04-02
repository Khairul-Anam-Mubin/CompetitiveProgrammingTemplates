/*********** Big Prime and Factorisation***************/
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
/*
支持更高的快速幂操作
expower.mod_pow(a,b,mod);
*/ 
struct Expower {
    ull Mod_mul(ull a, ull b, ull M) {
        ll ret = a * b - M * ull(ld(a) * ld(b) / ld(M));
        return ret + M * (ret < 0) - M * (ret >= (ll)M);
    }
    ull Mod_pow(ull b, ull e, ull mod) {
        ull ans = 1;
        for ( ; e ; b = Mod_mul( b, b, mod), e /= 2)
            if (e & 1) ans = Mod_mul(ans, b, mod);
        return ans % mod;
    }
} Expower;
struct BigPrime {    
    /*
    Miller-Rubin素数判别
    is_prime(n);    
    */
    bool IsPrime(ull n) { 
        if (n < 2 || n % 6 % 4 != 1) 
            return n - 2 < 2;
        ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
        ull s = __builtin_ctzll(n - 1), d = n >> s;
        for (auto a : A) {
            ull p = Expower.Mod_pow(a, d, n), i = s;
            while (p != 1 && p != n - 1 && a % n && i--)
                p = Expower.Mod_mul(p, p, n);
            if (p != n - 1 && i != s) 
                return 0;
        }
        return 1;
    }
    /*
    素因数分解
    ret=factorization(n);
    */
    ull Pollard(ull n) {
        auto f = [n](ull x) { 
            return ( Expower.Mod_mul(x, x, n) + 1) % n;
        };
        if (!( n & 1)) 
            return 2;
        for (ull i = 2 ; ; i++) {
            ull x = i, y = f(x), p;
            while ((p = __gcd( n + y - x , n)) == 1)
                x = f(x) , y = f(f(y));
            if (p != n) return p;
        }
    }
    vector <ull> Factorization(ull n){
        if (n == 1) return {};
        if (IsPrime(n)) return {n};
        ull x = Pollard(n);
        auto l = Factorization(x), r = Factorization(n/x);
        l.insert(l.end(), begin(r), end(r));
        return l;
    }
};
int main() {
    FasterIO
    BigPrime ob;
    int tc; cin >> tc;
    while (tc--) {
        ull n ; cin >> n;
        if (ob.IsPrime(n)) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    return 0 ;
}
