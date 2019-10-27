        // Permutation..

1 . for n objects how many distinct permutations exists ?
    n (n - 1) (n - 2) (n - 3)...(1) = n!

2. if an integer n >= 0 , n factorial denoted n! .. is defined as 
    
    0! = 1
    n! = n (n - 1) (n - 2)..(1) , for n >= 1

3. if there are n distinct objects , the number of permutations of size k ,
    with 1 <= k <= n , for the n objects is

        P(n , k) = n (n - 1) (n - 2) (n - 3) ... (n - k + 1) 

        or 

        P(n , k) = n! / (n - k)!

4. P(n , n) = n!

5 . permutations with repeatation :
    
    If we have n1 indistingushable objects of a first type , n2 indistingushable objects
    of a second type ,, and Nr indistingushable objects of kth type , where n1 + n2 + .. + nr = n ,
    then there are , 

    P(n , n) = n! / (n1!n2!..nk!)    

