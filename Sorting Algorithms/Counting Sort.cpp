#include <bits/stdc++.h>
using namespace std ;

#define mx 200000
void CountingSort(int ar[] , int n) {
    int count[mx + 5] ;
    int temp[n + 5] ;
    int maximum_element = 0 ;
    for(int i = 0 ; i <= mx ; i++)
        count[i] = 0 ;
    for(int i = 0 ; i < n ; i++) {
        count[ar[i]]++ ;
        maximum_element = max(maximum_element , ar[i]) ;
    }
    for(int i = 1 ; i <= maximum_element ; i++)
        count[i] += count[i - 1] ;
    for(int i = n - 1 ; i >= 0 ; i--) {
        temp[count[ar[i]]] = ar[i] ;
        count[ar[i]]-- ;
    }
    for(int i = 0, j = 1 ; i < n ; i++ , j++)
        ar[i] = temp[j] ;
}
int main() {
    //Fin ;
	cout << "Enter the Size of Array : " ;
	int  n  ;
	cin >> n ;
	cout << "Enter the array elements : " ;
	int ar[n + 5] ;
	for(int i = 0 ; i < n ; i++ ) {
		cin >> ar[i] ;
	}
	CountingSort(ar , n) ;
	cout << "\nSorted List In ascecnding order : " ;
	for(int i  = 0  ; i  < n ; i++) {
		cout <<  ar[i] << " " ;
	}
	cout << "\n" ;
	return 0 ;
}
