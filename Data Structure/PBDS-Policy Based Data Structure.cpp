#include <bits/stdc++.h>
using namespace std ;

#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
#include <ext/pb_ds/detail/standard_policies.hpp>
using namespace __gnu_pbds;
typedef tree < 
        int, 
        null_type , 
        less < int > , 
        rb_tree_tag , 
        tree_order_statistics_node_update > 
        ordered_set ;
// *st.find_by_order(k) ; kth element
//  st.order_of_key(k) ; number of element less than k 
// Other operations are same as set.
