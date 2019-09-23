// Binary search on finding floating answer..

int p , q , r , s , t , u ;
// Calculating part..
double check(double mid) {
    return p * exp(-mid) + q * sin(mid) + r * cos(mid) + s * tan(mid) + t * mid * mid + u ;
}
// double binary search
double search() {
    double low = 0.0, high = 1.0 ;
    int round = 50 ; 
    double ans ;
    while(round--) {
        double mid = (low + high) / 2.0 ;
        ans = check(mid) ;
        if(Abs(ans) < 1e-12) // double checking..
            return mid ;
        if(ans > 0)
            low = mid ;
        else
            high = mid ;
    } 
    return -1 ;
}
int main() {
    while(scanf("%d%d%d%d%d%d",&p,&q,&r,&s,&t,&u) == 6) {
        double ans = search() ;
        if(ans == -1) {
            printf("No solution\n") ;
        } else {
            printf("%0.4lf\n",ans) ;
        }
    }
    return 0 ;
}
