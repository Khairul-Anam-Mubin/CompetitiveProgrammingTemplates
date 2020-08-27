#include <bits/stdc++.h>
using namespace std ;

// Heapifying the elements
void heapify(int ar[] , int n , int i) {
    int largest = i ;
    int left = 2 * i + 1 ;
    int right = 2 * i + 2 ;
    if( left < n && ar[left] > ar[largest])
        largest = left ;
    if( right < n && ar[right] > ar[largest])
        largest = right ;
    if(i != largest) {
        swap(ar[i] , ar[largest]) ;
        heapify(ar , n , largest) ;
    }
}
void HeapSort(int ar[] , int  n) {
    // Building max heap
    for(int i = n / 2 - 1 ; i >= 0 ; i--)
        heapify(ar , n , i) ;
    // Deleting root node and again make max heap and rest of the  deleted node goes the sorted part
    for(int i = n - 1 ; i >= 0 ; i--) {
        swap(ar[0] , ar[i]) ;
        heapify(ar , i , 0) ;
    }
}
int main() {
    Fin ;
	cout << "Enter the Size of Array : " ;
	int  n  ;
	cin >> n ;
	cout << "Enter the array elements : " ;
	int ar[n + 5] ;
	for(int i = 0 ; i < n ; i++ ) {
		cin >> ar[i] ;
	}
	HeapSort(ar , n) ;
	cout << "\nSorted List In ascecnding order : " ;
	for(int i  = 0  ; i  < n ; i++) {
		cout <<  ar[i] << " " ;
	}
	cout << "\n" ;
	return 0 ;
}
