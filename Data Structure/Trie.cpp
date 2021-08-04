/*********************************Trie(Prefix Tree)**************************************/

/*...........................Trie String matching............................*/
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

/*...........................Trie String matching............................*/
/* Given A Text string , and N Query , in each query one string str given, checking if the query 
string is a sub string of text string or not.*/
#include <bits/stdc++.h>
using namespace std ;
int dp[1010] ;
string str ,text ;
struct node {
    bool endmark ;
    vector <int> pos ;
    node *next[52] ;
    node() {
        endmark = false ;
        for(int i = 0 ; i < 52 ; i++) 
            next[i] = NULL ;
    }
};
node *root = new node() ;
void Insert(int ind) {
    node *curr = root ;
    int len = str.length() ;
    for(int i = 0 ; i < len ; i++) {
        int id ;
        if(str[i] >= 'a' && str[i] <= 'z')
                id = str[i] - 'a' ;
            else
                id = str[i] - 'A' + 26 ; 
        if(curr->next[id] == NULL) 
            curr->next[id] = new node() ;
        curr = curr->next[id] ; 
    }
    curr->endmark = true ;
    curr->pos.push_back(ind) ;
}
void Search() {
    node *curr = root ;
    int len = text.length() ;
    for(int x = 0 ; x < 52 ; x++) {
        for(int i = 0 ; i < len ; i++) {
            int id ;
            if(text[i] >= 'a' && text[i] <= 'z')
                id = text[i] - 'a' ;
            else
                id = text[i] - 'A' + 26 ; 
            //int id = text[i] - 'a' ;
            if(id != x && curr == root)
                continue ;
            if(curr->next[id] != NULL && curr->next[id]->endmark) {
                vector <int> ok = curr->next[id]->pos ;
                for(int j = 0 ; j < ok.size() ; j++) 
                    dp[ok[j]] = 1 ;
                curr = curr->next[id] ;
            }
            else if(curr->next[id] != NULL) 
                curr = curr->next[id] ;
            else if(curr->next[id] == NULL) 
                curr = root ;
        }
    }
}
int main() {
    cin >> text ;
    int n ; cin >> n ; 
    for(int i = 1 ; i <= n ; i++) {
        cin >> str ;
        Insert(i) ;
    }
    Search() ;
    for(int i = 1 ; i <= n ; i++) {
        if(dp[i]) cout << "Y\n" ;
        else  cout << "N\n" ;
    }
    return 0 ;
} 
