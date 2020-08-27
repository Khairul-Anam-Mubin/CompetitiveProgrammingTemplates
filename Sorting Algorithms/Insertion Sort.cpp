#include <bibts/stdc++.h>
using namespace std ;

void InsertionSort(int ar[] , int n) {
	for(int i = 1 ; i < n ; i++) {
		int value = ar[i] ;
		int hole = i ;
		while(hole > 0 && ar[hole - 1 ] > value) {
			ar[hole] = ar[hole - 1] ;
			hole-- ;
		}
		ar[hole] = value ;
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
	InsertionSort(ar , n) ;
	cout << "\nSorted List In ascecnding order : " ;
	for(int i  = 0  ; i  < n ; i++) {
		cout <<  ar[i] << " " ;
	}
	cout << "\n" ;
	return 0 ;
}
