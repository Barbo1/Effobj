#ifndef __Oper_mod_impl
#define __Oper_mod_impl

#include "./operation.h"
#include <vector>
#include <concepts>

constexpr int32_t pop(int32_t x) {
    x = x - ((x >> 1) & 0x55555555);
    x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
    x = (x + (x >> 4)) & 0x0F0F0F0F;
    x = x + (x >> 8);
    return (x + (x >> 16)) & 0x0000003f;
}

constexpr int32_t flog2(int32_t x) {
   unsigned n = 0;
   if(x > 0x0000FFFF) { n += 16; x = x>>16; }
   if(x > 0x000000FF) { n += 8; x = x>>8; }
   if(x > 0x0000000F) { n += 4; x = x>>4; }
   if(x > 0x00000003) { n += 2; x = x>>2; }
   if(x > 0x00000001) n += 1;
   return n;
}

template<typename T>
requires Multipliable<T>
constexpr T int_pot(const T & obj, unsigned pot){
    if(pot == 1) {
        return obj;
    }
    unsigned char l2 = flog2(pot);
    char i;
    T last;
    T * arr = new T[l2];
    arr[0] = obj;
    for (i = 0; i < l2-1; i++) {
        arr[i+1] = arr[i] * arr[i];
    }
    last = arr[i] * arr[i];
    for (i = l2-1; i >= 0; i--) {
        if ((1 << i) & pot) {
            last *= arr[i];
        }
    }
    delete [] arr;
    return last;
}

void moreComplexSieve(std::vector<unsigned>& vec, unsigned limit) {
    bool mark[limit];
    for (unsigned i = 0; i < limit; i++) {
        mark[i] = i & 1;
    }
    for (unsigned i=9; i<limit; i+=3) {
        mark[i] = false;
    }
    for (unsigned p=5, o=2; p*p<limit; p+=o, o^=6) {
        if (mark[p]) {
            for (unsigned i=p*p; i<limit; i+=p) {
                mark[i] = false;
            }
        }
    }

    vec.push_back (2);
    vec.push_back (3);
    for (unsigned p=5, o=2; p<limit; p+=o, o^=6) {
        if (mark[p]) {
            vec.push_back (p);
        }
    }
}

std::vector<unsigned> segmentedMoreComplexSieve (unsigned n) {
    unsigned limit = floor (sqrt (n)) + 1;
    std::vector<unsigned> initial_primes;
    initial_primes.reserve (limit);
    moreComplexSieve (initial_primes, limit);

    std::vector<unsigned> reminding_primes;
    reminding_primes.reserve (n - limit);
    
    unsigned size = limit;
    bool mark[limit];
    unsigned high = limit*2;

    for (unsigned low = limit; low < n; low += limit) {
        if (high > n) {
            high = n;
            size = high - low;
        }
   
        memset (mark, true, size);
        for (auto p: initial_primes) {
            for (unsigned i = ((low - 1)/p + 1) * p; i < high; i += p) {
                mark [i-low] = false;
            }
        }

        for (unsigned i = 0; i < size; i++) {
            if (mark[i]) {
                reminding_primes.push_back(i + low);
            }
        }

        high += limit;
    }
    initial_primes.insert(initial_primes.end(), reminding_primes.begin(), reminding_primes.end());
    return initial_primes;
}

unsigned* discompressPrimes(unsigned E){
    unsigned* S = new unsigned[UINT_WIDTH+1];
    unsigned char P = 1, i; 
    unsigned r = 2, n = 2;
    bool b = true;
    if (E == 0) {
        *S = 1;
        *(S+1) = 0;
        return S;
    }
    while (E != 1) {
        i = 1;
        r += n == r*r;
        while (i < P && *(S+i) <= r && (b = n % *(S+i))) {
            i++;
        }
        if (!(E % n) && b) {
           *(S+P) = n;
            P++; 
            while (!(E % n)) {
                E /= n;
            }
        }
        n++;
    }
    *S = P;
    return S;
}

unsigned phi(unsigned n){
    unsigned i, *A;
    if(n < 2) 
        return 1;
    A = discompressPrimes(n);
    for (i = 1; i < A[0]; i++) {
        n /= A[i];
        n *= A[i]-1;
    }
    delete [] A;
    return n;
}

template<typename T>
void static aux_merge (T * arr, unsigned n, T * arr_2) {
    if (n != 1) {
        unsigned j, i, mit = (n+1)>>1;
        aux(arr, mit, arr_2);
        aux(arr+mit, n>>1, arr_2);
        i = 0;
        j = mit;
        while (i < mit) {
            if (j == n || arr[i] <= arr[j]) {
                arr_2[j+i-mit] = arr[i];
                i++;
            } else {
                arr_2[j+i-mit] = arr[j];
                j++;
            }
        }
        for (i=0; i<j; i++) {
            arr[i] = arr_2[i];
        }
    }
}

template<typename T>
void mergesort (T * arr, unsigned n) {
    T * arr_2 = new T[n];
    aux_merge(arr, n, arr_2);
    delete [] arr_2;
}

double pi_aprox (unsigned precition) {
    int n;
    double or_2;
    int or_1 = 1; 
    int cinco_pot = 5; 
    int dos_pot = 239;
    int menos_1 = 4;
    double var_1 = (double)4/5; 
    double var_2 = (double)4/239;
    for (n = 1; n < precition; n++) {
        or_1 += 2;
        menos_1 *= -1;
        cinco_pot *= 25;
        dos_pot *= 57121;
        or_2 = (double)menos_1/or_1;
        var_1 += (double)or_2/cinco_pot;
        var_2 += (double)or_2/dos_pot;
    }
    return 4*var_1 - var_2;
}

#endif
