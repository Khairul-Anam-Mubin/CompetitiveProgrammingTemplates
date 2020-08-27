#include <bits/stdc++.h>
using namespace std ;

void merge(int ar[] , int left ,int mid , int right) {
    int leftsize = mid - left + 1 ;
    int rightsize = right - mid ;
    int Larr[leftsize + 1] ;
    int Rarr[rightsize + 1] ;
    int i , j , k ;
    for(i = 0 ; i < leftsize ; i++)
        Larr[i] = ar[ left + i] ;
    for(j = 0  ; j < rightsize ; j++)
        Rarr[j] = ar[mid + j + 1] ;
    i = 0 , j = 0 , k = left ;
    while (i < leftsize && j < rightsize) {
        if( Larr[i] <= Rarr[j])
            ar[k++] = Larr[i++] ;
        else
            ar[k++] = Rarr[j++] ;
    }
    while(i < leftsize)
        ar[k++] = Larr[i++] ;
    while(j < rightsize)
        ar[k++] = Rarr[j++] ;
}
void SORT(int ar[] , int left , int right) {
    if( left < right ) {
        int mid = left + (right - left) / 2 ;
        SORT(ar , left , mid) ;
        SORT(ar , mid + 1 , right) ;
        merge(ar , left , mid , right) ;
    }
    return  ;
}
void MergeSort(int ar[] , int n) {
    SORT(ar , 0 , n - 1) ;
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
	MergeSort(ar , n) ;
	cout << "\nSorted List In ascecnding order : " ;
	for(int i  = 0  ; i  < n ; i++) {
		cout <<  ar[i] << " " ;
	}
	cout << "\n" ;
	return 0 ;
}
