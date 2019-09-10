#include <bits/stdc++.h>
using namespace std;

typedef long long ll ;
struct str {
    ll r_g;
    ll r_b;
    ll r_w;
    ll g_b;
    ll g_w;
    ll b_w;
    ll pos;
};
vector<str>friends;

bool compare1(str x, str y) {
    //cout<<"S  "<<x.pos<<"  "<<y.pos<<endl;
    if(x.r_g == y.r_g) {
        if(x.r_b == y.r_b) {
            if(x.r_w == y.r_w) {
                if(x.g_b == y.g_b) {
                    if(x.g_w == y.g_w) {
                        if(x.b_w == y.b_w) {
                            x.pos>y.pos;
                        }
                        return x.b_w>y.b_w;
                    }
                    return x.g_w>y.g_w;
                }
                return x.g_b>y.g_b;
            }
            return x.r_w>y.r_w;
        }
        return x.r_b>y.r_b;
    }
    return x.r_g>y.r_g;
}
int main() {
    //freopen("1st_input.txt","r",stdin);
   int t,cas=1;
    scanf("%d",&t);
    while(t--) {
        ll p=0LL;
        int n;
        scanf("%d",&n);
        for(int i=0; i<n; i++) {
            ll r,g,b,w;
            scanf("%lld %lld %lld %lld",&r,&g,&b,&w);
            friends.push_back({r+g,r+b,r+w,g+b,g+w,b+w,p++});
        }
        sort(friends.begin(),friends.end(),compare1);
        printf("Case %d\n",cas++);
        for(int i=0; i<n; i++) {
            printf("%lld\n",friends[i].pos+1LL);
        }
        friends.clear();
    }
    return 0;
}
