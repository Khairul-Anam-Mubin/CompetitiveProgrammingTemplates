1 : GCD property :  
    For non-negative integers a and b, where a and b are not both zero, provable by considering the Euclidean algorithm in base n :

    // gcd((n^a) − 1, (n^b) − 1) = (n^gcd(a,b)) − 1

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
