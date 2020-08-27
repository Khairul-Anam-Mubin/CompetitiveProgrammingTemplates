#include <bits/stdc++.h>
using namespace std ;

void SelectionSort(int ar[] , int n) {
    for(int i = 0 ; i < n ; i++) {
        int minIndx = i ;
        for(int j = i + 1 ; j < n ; j++) {
            if(ar[minIndx] > ar[j]) {
                minIndx = j ;
            }
        }
        int temp = ar[i] ;
        ar[i] = ar[minIndx] ;
        ar[minIndx] = temp ;
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
	SelectionSort(ar , n) ;
	cout << "\nSorted List In ascecnding order : " ;
	for(int i  = 0  ; i  < n ; i++) {
		cout <<  ar[i] << " " ;
	}
	cout << "\n" ;
	return 0 ;
}
