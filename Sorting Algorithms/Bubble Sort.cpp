#include <bits/stdc++.h>
using namespace std ;

void BubbleSort(int ar[] , int n) {
    for(int i = 0 ; i < n  ; i++) {
        for(int j = 0 ; j < n - 1; j++) {
            if(ar[j] > ar[j + 1]) {
                int temp = ar[j] ;
                ar[j] = ar[j + 1] ;
                ar[j + 1] = temp ;
            }
        }
    }
}
int main() {
	cout << "Enter the Size of Array : " ;
	int  n  ;
	cin >> n ;
	cout << "Enter the array elements : " ;
	int ar[n + 5] ;
	for(int i = 0 ; i < n ; i++ ) {
		cin >> ar[i] ;
	}
	BubbleSort(ar , n) ;
	cout << "\nSorted List In ascecnding order : " ;
	for(int i  = 0  ; i  < n ; i++) {
		cout <<  ar[i] << " " ;
	}
	cout << "\n" ;
	return 0 ;
}
