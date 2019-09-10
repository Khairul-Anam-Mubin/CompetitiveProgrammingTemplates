#include <bits/stdc++.h>

#define pb       push_back
#define Sqr(n)   (n*n)
#define Sort(v)  sort(v.begin(),v.end())
#define Mxe(v)   *max_element(v.begin(),v.end())
#define Mne(v)   *min_element(v.begin(),v.end())
#define Fill0(a) memset(a,0,sizeof(a))
#define precision(a) cout << fixed << setprecision(a)
#define Fin      freopen("input.txt","r",stdin)
#define Fout     freopen("output.txt","w",stdout)

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
const double pi = acos(-1.0);

// Templates........
template <typename T> T Abs(T a) {
    if(a < 0) return -a;
    else return a;
}
template <typename T> T Pow(T B,T P){
    if(P == 0) return 1;
    if(P & 1) return B*Pow(B,P-1);
    else return Sqr(Pow(B,P/2));
}
template <typename T> T isperfectsq(T x){
    T n = sqrt(x);
    return ((n * n == x)?1:0);
}
template <typename T> T BigMod (T b,T p,T m){
    if (p == 0) return 1;
    if (p%2 == 0){
        T s = BigMod(b,p/2,m);
        return ((s%m)*(s%m))%m;
    }
    return ((b%m)*(BigMod(b,p-1,m)%m))%m;
}
template <typename T> T ModInv (T b,T m) {
    return BigMod(b,m-2,m);
}
template <typename T> T gcd(T a,T b){
    if(a < 0)return gcd(-a,b);
    if(b < 0)return gcd(a,-b);
    return (b == 0)?a:gcd(b,a%b);
}
template <typename T> T lcm(T a,T b) {
    if(a < 0)return lcm(-a,b);
    if(b < 0)return lcm(a,-b);
    return a*(b/gcd(a,b));
}
template <typename T> T exgcd(T a,T b,T &x,T &y) {
    if(a < 0){
        T d = exgcd(-a,b,x,y);
        x =- x;
        return d;
    }
    if(b < 0){
        T d = exgcd(a,-b,x,y);
        y =- y;
        return d;
    }
    if(b == 0){
        x = 1;
        y = 0;
        return a;
    }
    else{
        T d = exgcd(b,a%b,x,y);
        T t = x;
        x = y;
        y = t - (a/b) * y;
        return d;
    }
}
//Take a vector and a value and it insert sorted optimally..
template < typename T >
typename std::vector<T>::iterator insert_sorted (std :: vector<T> & vec, T const& item) {
    return vec.insert (std::upper_bound( vec.begin(), vec.end(), item ), item);
}

//Functions....
char uplowch(char ch){
    if(ch >= 'A' &&  ch <= 'Z') ch += 32;
    return ch;
}
char lowupch(char ch){
    if(ch >= 'a' &&  ch <= 'z') ch -= 32;
    return ch;
}
bool isalpha(char ch){
    if((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) return true;
    return false;
}
int strtoint(string str){
    stringstream ss(str);
    int x = 0;
    ss >> x ;
    return x ;
}
string intostr(int x){
    stringstream ss;
    ss << x;
    string str = ss.str();
    return str;
}
vector<string> linetostr(string str){
    string s;
    vector <string> v ;
    istringstream is(str);
    while(is >> s)v.pb(s);
    return v;
}

#define MOD 1e9+7 
#define INF 2147483647
#define IINF 9223372036854775807
#define WHITE 0 
#define GRAY 1
#define BLACK 2

//int dx[] = {0,0,-1,1,-1,-1,1,1,0};
//int dy[] = {1,-1,0,0,-1,1,-1,1,0};

// A structure containing the edge node and the weight.
struct node{
    ll x , cost ;
    // constructor : when declaring a node also can initialize..
    node(ll _x , ll _cost) {
        x = _x ;
        cost = _cost ;
    }
    // operator overloading..
    bool operator < (const node& p) const {
        return cost > p.cost ;
    }
};

//Code starts from here......

int main()
{
    //file input and output Fin , Fout ;


    return 0;
}
// g++ -std=c++11 Codework.cpp && ./a.out
