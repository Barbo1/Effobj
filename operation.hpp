#pragma once

#include "./needed.hpp"
#include "./graph.hpp"
#include "./matrix.hpp"

#include <type_traits>
#include <array>

GraphUndirected<int> MtoG(Matrix<bool> & M);


/*********************
 *    Successions    *
 *********************/

/* Generate and return an array of unsigened's that contains primes. Depending 
 * on the neccessity, you can deside if you want a fixed quantity of elemens, 
 * this is, only N primes, or a bound for the elements, so you get all element 
 * below it.
 * */
std::vector<unsigned> primes_by_bound (unsigned top); 
std::vector<unsigned> primes_by_many (unsigned many); 

/* Generate and return an array of unsigened's that contain the primes that 
 * divide the number (passed by parameter). the array have 33 slots, where the 
 * position 0 contains the quantity of positions ocupied, and the reminded 
 * space is garbage.
 * */
std::array<unsigned, 33> discompress_primes(unsigned E);

/* Generate and return the lucas sequence with the numbers the numbers P and Q,
 * defined by the formula X_n = P * X_n-1 - Q * X_n-2
 * */
std::vector<int> lucas (int P, int Q, unsigned many);


/***********************
 *    Bit Functions    *
 ***********************/

/* Get two sequences of N bits and combine them, giving the first 'point' 
 * bits from 'seq1' and the rest N-point bits from 'seq2'.
 * Precondition: 
 *  - 1 <= point <= N + 1, 
 *  - T is in {uint8_t, uint16_t, uint32_t, uint64_t},
 * */
template<typename T> 
requires std::is_integral_v<T> 
constexpr T combines (T seq1, T seq2, unsigned point);

/* Return the parity of the bits in the N bits sequence. If false, then there
 * are a pair number of 1 bits, if true, there are an odd number of 1 bits.
 * */
template<typename T> 
requires std::is_integral_v<T> 
constexpr bool bitsp (T x);

/* calculate the floor of the logarithm base 2 of the number passed by parameter. 
 * Precondition: 
 *  - T is in {uint8_t, uint16_t, uint32_t, uint64_t}
 * */
template<typename R, typename T> 
requires std::is_integral_v<T> && std::is_fundamental_v<R>
constexpr R flog2 (T x);

/* Return de reverse of the N bits sequence passed by parameter. 
 * Precondition: 
 *  - T is in {uint8_t, uint16_t, uint32_t, uint64_t}
 * */
template<typename T> 
requires std::is_integral_v<T>
constexpr T reverse (T x);


/************************
 *    Math Functions    *
 ************************/

/* get an Multipliable object and an integer, and make the "object" to the
 * "integer" operation. It needs that pot > 0.
 * */
template<typename T>
requires Multipliable<T>
constexpr T int_pot(const T &, unsigned pot);

/* Euler's totient function. */
unsigned phi(unsigned n);

/* This function generate an aproximation of pi. Its probably useless in the mayority 
 * of cases but is here if you need. It needs a presition to be passed, but with a small
 * number(like 5) the aproximation will match well.
 * */
double pi (unsigned precition);


/*****************
 *    Sorting    *
 *****************/

/* Algorithm to sort elements that have the requirement Orderable. The implementation
 * use recursiveness.
 * */
template<typename T>
requires Orderable<T>
void mergesort(T * arr, unsigned n);

/* Algorithm to sort elements that have the requirement Orderable. The implementation
 * DON'T use recursiveness.
 * */
template<typename T>
requires Orderable<T>
void heapsort (T * data, unsigned n);
