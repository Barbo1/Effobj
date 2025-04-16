/* 
 * This module was made to generate sequences of random numbers, using spesifically a 
 * Linear Congruential method. The sequence is constructed to generate a complete length
 * to get the most different numbers possible before enter cycle. There are two types:
 *  - FIX_MOD: the length of the cycle will a fixed quantity (2^32 + 1), so calculating 
 *      more effitiently.
 *  - VAR_MOD: the seed is the modulus and the rest of the paramenters are calculated, 
 *      so the random numbers N will be 0 <= N < m
 * */

#include <cstdint>
#include "./operation.hpp"

enum _rand_type {
  FIX_MOD, VAR_MOD
};

template <_rand_type T>
class Random {
  private:
    uint32_t m, c, a, xN;

    static constexpr uint32_t bound[13] {
      6, 7, 8, 10, 12, 17, 24, 41, 85, 256, 1626, 65536, 0xFFFFFFFF
    };

    uint32_t gcd_primes (uint32_t n, uint32_t m);
    void discompress_primes (uint32_t E, uint32_t* S, uint32_t* N);

  public:
    Random (uint32_t m);
    uint32_t generate ();
};

template <>
class Random<FIX_MOD> { 
  private: 
    uint32_t c, a, xN;

    static constexpr uint32_t primes[2] {
      641, 6700417
    };
    
    static constexpr uint32_t relatives[32] {
      19, 8191, 337, 431, 89, 257, 2833, 353, 4649, 673, 193, 449, 9901, 97, 
      1777, 2113, 65537, 113, 953, 683, 1321, 26317, 37171, 1013, 1657, 1103, 
      13367, 5419, 1429, 20857, 241, 101
    };
    
  public:
    Random (uint32_t seed);

    uint32_t generate ();
};
