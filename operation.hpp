/*
    it needs to be compiled with -std=c++20
*/

#ifndef __Oper_mod
#define __Oper_mod

#include "./needed.hpp"
#include "./graph.hpp"
#include "./matrix.hpp"
#include <type_traits>

GraphUndirected<int> MtoG(Matrix<bool> & M);

/* get an Multipliable object and an integer, and make the "object" to the
 * "integer" operation. It needs that pot > 0.
 * */
template<typename T>
requires Multipliable<T>
constexpr T int_pot(const T &, unsigned pot);

/* Generate and return an array of unsigened's that contain E primes, ordered from
 * least to greater.
 * */
unsigned* successionPrimes(unsigned E); 

/* Generate and return an array of unsigened's that contain the primes that divide the 
 * number (passed by parameter). the array have 32 slots, where the position 0 contains 
 * the quantity of positions ocupied, and the reminded space is garbage.
 * */
unsigned* discompressPrimes(unsigned);

/*
    Euler's totient function
*/
unsigned phi(unsigned n);

/* Algorithm to sort elements that have the requirement Orderable. The implementation
 * use recursiveness. If it is not desired, other algorithms can be used instead.
 * (std::sort use quicksort or introsort)
 * */
template<typename T>
requires Orderable<T>
void mergesort(T * arr, unsigned n);

/* This function generate an aproximation of pi. Its probably useless in the mayority 
 * of cases but is here if you need. It needs a presition to be passed, but with a small
 * number(like 5) the aproximation will match well.
 * */
double pi_aprox(unsigned precition);

#include "./operation_files/operation.cpp"

#endif
