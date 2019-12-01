/*********************************Trie(Prefix Tree)**************************************/

/*...........................String matching............................*/
/* Given N strings , and Query , in each query one string given, checking if exists in the list
or not */

#include <bits/stdc++.h>
using namespace std ;
struct node{
    bool endmark ; 
    node *next[27] ;  // these are connecting edge
    // Constructor for initialise all endmark  false initially and assigning all edges as NULL
    node() {
        endmark = false ;
        for(int i = 0 ; i < 26 ; i++)
            next[i] = NULL ;
    }
};
node *root = new node() ; //Its the root where we are going to always start
//Insert operation in Trie..
//Insert in O(n)
void Insert(string str , int len) {
    node *curr = root ;
    for(int i = 0 ; i < len ; i++ ) {
        int id = str[i] - 'a' ;
        if(curr->next[id] == NULL)
            curr->next[id] = new node() ; // Every time new node creating
        curr = curr->next[id] ;
    }
    curr->endmark = true ; // setting the endmark true after ending inserting
}
// Searching the string if its present in the Tri..
// searchin in O(n)
bool Search(string str , int len) {
    node *curr = root ;
    for(int i = 0 ; i < len ; i++) {
        int id = str[i] - 'a' ;
        if(curr->next[id] == NULL)
            return false ;  // there is no such a letter present in the Trie as edge
        curr = curr->next[id] ;
    }
    return curr->endmark ; // if string present then  return true
}
// To free up all the memory
void ClearMemory(node *cur) {
    for(int i = 0 ; i < 26 ; i++)
        if(cur->next[i])
            ClearMemory(cur->next[i]) ;
    delete(cur) ;
}
int main() {
    cout << "Enter how many words you want to insert in the trie : " ;
    int n ; cin >> n ;
    cout << "Enter the word's...\n\n" ;
    for(int i = 0 ; i < n ; i++) {
        string str ;
        cin >> str ;
        int len = str.size() ;
        Insert(str , len) ;
    }
    cout << "\n\nEnter the query number : " ;
    int query ; cin >> query ;
    while(query--) {
        cout << "\nEnter the string you want to search : " ;
        string str ;
        cin >> str ;
        int len = str.size() ;
        if( Search(str , len) )
            cout << str << " Found !!!" << "\n\n" ;
        else
            cout << str << "Not Found!!!\n\n" ;
    }
    ClearMemory(root) ; // Freeing up the memory's ;
    return 0 ;
}
