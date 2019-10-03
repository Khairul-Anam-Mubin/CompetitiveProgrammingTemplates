1 : GCD property :  
    For non-negative integers a and b, where a and b are not both zero, provable by considering the Euclidean algorithm in base n :

    // gcd((n^a) − 1, (n^b) − 1) = (n^gcd(a,b)) − 1

    // If gcd(x,n)=1, then gcd(n−x,n)=1

2 : GCD and LCM relations , It is based on the formula that , 
  
    // LCM(A , B) × GCD( A , B) = A × B
    
3 : Number of divisors (NOD) of a number N can be calculated using Prime power factorization.
    Let , N = P1^a1 * P2^a2 * P3^a3 * ... * Pn^ak , is the prime power factorization of a number N , where P is the prime number and
    a is number of times occurs that prime number.
    Then , NOD(N) defines as :

    // NOD(N) = (a1 + 1) * (a2 + 1) * (a3 + 1) * ... * (ak + 1)

4 : Sum of divisors (SOD) of a number N can be calculated using prime power factorization.
   Let ,  N = P1^a1 * P2^a2 * P3^a3 * ... * Pn^ak , s the prime power factorization of a number N , where P is the prime number and
    a is number of times occurs that prime number.
  Then , SOD(N) defines as :
  
    // SOD(N) = (P1^0 + P1^1 + p1^2 + ... + P1^a1) * (P2^0 + P2^1 + P2^2 + ... + P2^a2) * (Pk^0 + Pk^1 + ... + Pk^ak)

5 : Logarithm base calculation :

    //logB(x)=logC(x) / logC(B)

6 : Trailing zeros in N! in decimal number system ,
    Let , a is frequency of 2 in N! prime factorisation and b is frequency of 5 in N! prime factorisation..
    Then ,
    
    // Number of Trailing zeros = min(a , b) ;

7 : Trailing zeros in N! in different base system :
    
    We find number of trailing zero using the following steps:
        Factorize the base B
        If B = pa11 × pa22…× pakk, then find out occurance of xi=factorialPrimePower(pi).
        But we can’t use xi directly. In order to create B we will need to combine each pi into paii. So we divide each xi by ai.
            Number of trailing zero is MIN(x1,x2,…,xk).
    
 8 : Leading Numbers :
    We need to execute the following steps to find the first K leading digits of a number x ( in our problem x=N! ):
        Find the log value of the number whose leading digits we are seeking. y=log10(x).
        Decompose y into two parts. Integer part p and fraction part q.
        The answer is ⌊10q×10K−1⌋.

9 : Euler Phi Extension Theorem
    Theorem: 
    
        Given a number N, let d be a divisor of N. Then the number of pairs a,N, where 1≤a≤N and gcd(a,N)=d, is ϕ(N / d).

10 : Euler Phi Divisor Sum Theorem 
    Theorem: 
        For a given integer N, the sum of Euler Phi of each of the divisors of N equals to N, i.e, N = ∑d | N ϕ(d)

            
11 : Eulers Totient Function (Eulers Phi): 
        Given an integer N, how many numbers less than or equal N are there such that they are coprime to N? 
            A number X is coprime to N if gcd(X,N) = 1.
               
            // ϕ(n) = n × ((p1 − 1) / p1) × ((p2 − 1) / p2) … × ((pk − 1) / pk)
                
12 : Given two sequences of numbers A=[a1,a2,…,an] and M=[m1,m2,…,mn], find the smallest solution to the following linear congruence equations if it exists:

        x ≡ a1(mod m1)
        x ≡ a2(mod m2)
        …
        x ≡ an(mod mn)

 13 : GCD Sum Function – g(n)
     Given a positive integer N, find the value of g(N), where
            g(n) = gcd(1,n) + gcd(2,n) + gcd(3,n) +⋯+ gcd(n,n) =  i=1 to n ∑ gcd(i,n)
            
            // there is a direct formula for calculating the value of g(n).

                    If the prime factorization of n is p1^a1 × p2^a2 × … *pk^ak, then
                        g(n) = i=0 to k ∏ ((ai + 1)pi^ai) – (ai * pi^(ai−1))
   
  14 : Sum of Co-prime Numbers of an Integer
        Problem
        Given a number N, find the sum of all numbers less than or equal to N that are co-prime with N.
        Let us define a function f(n), which gives us sum of all numbers less than or equal to n that are co-prime to n. 
            Then we can calculate the value of f(n) with the following formula:

                //  f(n)= (phi(n) * n) / 2    
        

