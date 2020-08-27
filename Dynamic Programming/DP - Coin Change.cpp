#include <bits/stdc++.h>
using namespace std ;

//varient 1
int possible[10001];
int main()
{
    // File input and outputs :      
    //Fin ; Fout ;
    //given  five coins with weight.. find if possible to make with them n . 
    int coin[10];
    //assingings coins..
    coin[1] = 2;
    coin[2] = 5;
    coin[3] = 10;
    coin[4] = 25;
    coin[5] = 50;
    //The 0 can made..
    possible[0] = 1;
    for(int i = 1 ; i <= 10000 ; i++){
        for(int j = 1; j <= 5 ; j++){
            if(i >= coin[j]){
                possible[i] = possible[i - coin[j]];
                if(possible[i])
                    break;
            }
        }
    }
    int n;
    while(cin >> n)
    {
        if(possible[n] == 1)
            cout << "yes\n";
        else 
            cout << "no\n";
    }
    return 0;
}

//varient 2
//Code starts from here......

int main()
{
    // File input and outputs :      
    //Fin ; Fout ;
    //given  five coins with weight.. how many possible way to make with them n . 
    int coin[10];
    coin[1] = 1;
    coin[2] = 5;
    coin[3] = 10;
    coin[4] = 25;
    coin[5] = 50;
    ll way[10000];
    way[0] = 1;
    for(int i = 1; i <= 8000 ; i++){
        for(int j = 1; j <= 5 ; j++){
            if(i >= coin[j])
                way[i] += way[i-coin[j]];
        }
    }
    int n;
    while(cin >> n){
        cout << way[n] << "\n";
    }
    return 0;
}
//varient 3
//Code starts from here......

ll dp[10][8010];

int main()
{
    // File input and outputs :      
    //Fin ; Fout ;

    ll coin[10];

    //given  five coins with weight.. how many different possible way to make with them n . 

    coin[1] = 1;
    coin[2] = 5;
    coin[3] = 10;
    coin[4] = 25;
    coin[5] = 50;

    dp[0][0] = 1;
    dp[1][0] = 1;
    dp[2][0] = 1;
    dp[3][0] = 1;
    dp[4][0] = 1;
    dp[5][0] = 1;

    for(int i = 1 ; i <= 5 ; i++){
        for(int j = 1 ; j <= 8000; j++){
            if(j >= coin[i])
                dp[i][j] = dp[i-1][j] + dp[i][j - coin[i]];
            else
                dp[i][j] = dp[i-1][j];
        }
    }
    ll n ;
    while(cin >> n) {
       cout << dp[5][n] << "\n";
    }

    return 0;
}
