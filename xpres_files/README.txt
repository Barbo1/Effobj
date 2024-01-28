estas son notas para poner en el readme.

The program is not already optimized. Optimizations in some funtionality will happend when I consider that no major changes 
are needed. This is particularly upset, for you because efficiency is a desirable property of a program, and for me because
I fucking hate to make a not optimized program, but (please :)) be patient if efficiency are needed.

For now, some of the valid expresions are not considered in the program, for exemple when you try to use a not recognized 
function (see recognized_funcions vector in xpres.cpp). In this cases the program may crash, so try for now not to use one.
In future version, you will be able to create you own function to use in practice.

Another two things that will be implemented are the capacity of create secuences and contexts. A secuence is an ordered set
of expresions that can be interpreted as derivation of the same "mother expresion", useful to keep track of the changes made
in a particular expresion. A context is a colection of expresions, iterators and secuences that can be used to save information
to be opend in the future.

Funcions that are not already supported, but will be, are:
    - log2 (base 2 logarithm).
    - log10 (base 10 logarithm).
    - randM (return a matrix of double random numbers).
    - randI (return a matrix of integer random numbers).
    - randd (return a double random number).
    - randd (return a integer random number).

Possibly functions with more than one parameter will be supported.

The objects Xpres that are used to manipulate expresion can be used in other contexts, because only depends on the matrices.
