#include <bits/stdc++.h>
using namespace std ;

int partion(int ar[] , int start , int end) {
    int pivot = ar[end] ; // considering end is the pivot
    int partionindx = start ; // set partionindx start initially
    for(int i = start ; i < end ; i++) {
        if(ar[i] <= pivot) {
            swap(ar[i] , ar[partionindx]) ; // swapping if element is lesser than pivot
            partionindx++ ;
        }
    }
    swap(ar[partionindx] , ar[end]) ; //swap pivot with partion element indx
    return partionindx ;
}
void SORT(int ar[] ,int start , int end) {
    if( start < end ) {
        int partionindx = partion(ar , start ,end) ;
        SORT(ar , start , partionindx - 1) ;
        SORT(ar , partionindx + 1 , end) ;
    }
}
void QuickSort(int ar[] ,int n) {
    SORT(ar , 0 , n - 1) ;
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
	QuickSort(ar , n) ;
	cout << "\nSorted List In ascecnding order : " ;
	for(int i  = 0  ; i  < n ; i++) {
		cout <<  ar[i] << " " ;
	}
	cout << "\n" ;
	return 0 ;
}
