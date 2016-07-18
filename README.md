# Variable-n strategy generator
# what is varia-n strategy?
Variable-n strategy is the optimal strategy for generalized cut-and-choose game

# What is this code for?
This code search for the optimal strategy given the security parrmeter and cost ratio. Besides, it could randomly pick a strategy subjected to the optimal distribution.

# Prerequisity
This code needs <openssl/rand.h>. You can find openssl library here. https://github.com/openssl/openssl

# How to use it?
Include vn.h at the header and add "vn.c" to the gcc input and "-lcrypto" to the gcc option when compile.
I.e.
gcc vn.c vn-example.c -lcrypto

# How to call scost? What does the result mean?
Call it like this:

scost(s,r);

where s is the security parameter (which means the generator has a winning odds of 2^-s) and r is the cost ratio between oepning and checking. If r is smaller than 1, then call scost(s,1/r) instead.
s is an integer and r is a real number. However, the number of digits in decimal part of r will significantly slow down the search speed. 

The first line of the output will be: security parameter s, upbound of number of objects n, cost ratio r, and the established cost. 
After that there comes a line representing the generated strategy, where 0(1, representatively) in the ith position repesenting check(open, representatively) the ith object, if r<1, the swap opening and checking, i.e. 0 for opening and 1 for checking.

