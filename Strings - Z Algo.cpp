String compression
Given a string s of length n. 
Find its shortest "compressed" representation, that is: find a string t of shortest length such that s can be represented 
as a concatenation of one or more copies of t.
A solution is: compute the Z-function of s, loop through all i such that i divides n. 
Stop at the first i such that i+z[i]=n. Then, the string s can be compressed to the length i.
