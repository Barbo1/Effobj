#ifndef __Oper_mod_impl
#define __Oper_mod_impl

#include "./operation.h"
#include <climits>
#include <iostream>

inline constexpr unsigned flog2(unsigned x){
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
    if(pot == 1)
        return obj;
    unsigned char l2 = flog2(pot);
    char i;
    T last;
    T * arr = new T[l2];
    arr[0] = obj;
    for(i = 0; i < l2-1; i++)
        arr[i+1] = arr[i] * arr[i];
    last = arr[i] * arr[i];
    for(i = l2-1; i >= 0; i--)
        if((1 << i) & pot)
            last *= arr[i];
    delete [] arr;
    return last;
}

unsigned* successionPrimes(unsigned E){
    if(E == 0)
        return new unsigned[1]{ 0 };
    unsigned char o = 2;
    unsigned a, i, P = 4, r = 3;
    long unsigned n = 7, rc = 9;
    unsigned* S = new unsigned[E];
    if(1 <= E) *S = 2;
    if(2 <= E) *(S+1) = 3;
    if(3 <= E) *(S+2) = 5;
    if(4 <= E) *(S+3) = 7;
    while(P < E){
        i = 2;
        a = 5;
        o ^= 6;
        n += o; 
        if(n >= rc){
           r++;
           rc = r*r;
        }
        while(a <= r && n % a){
            ++i;
            a = *(S+i);
        }
        if(a > r){
            *(S+P) = n;
            ++P;
        }
    }
    return S;
}

unsigned* discompressPrimes(unsigned E){
    unsigned* S = new unsigned[UINT_WIDTH+1];
    unsigned char P = 1, i; 
    unsigned r = 2, n = 2;
    bool b = true;
    if(E == 0){
        *S = 1;
        *(S+1) = 0;
        return S;
    }
    while(E != 1){
        i = 1;
        r += n == r*r;
        while(i < P && *(S+i) <= r && (b = n % *(S+i)))
            i++;
        if(!(E % n) && b){
           *(S+P) = n;
            P++; 
            while(!(E % n))
                E /= n;
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
    for(i = 1; i < A[0]; i++){
        n /= A[i];
        n *= A[i]-1;
    }
    delete [] A;
    return n;
}

template<typename T>
void static aux_merge(T * arr, unsigned n, T * arr_2){
    if(n != 1){
        unsigned j, i, mit = (n+1)>>1;
        aux(arr, mit, arr_2);
        aux(arr+mit, n>>1, arr_2);
        i = 0;
        j = mit;
        while(i < mit){
            if(j == n || arr[i] <= arr[j]){
                arr_2[j+i-mit] = arr[i];
                i++;
            }else{
                arr_2[j+i-mit] = arr[j];
                j++;
            }
        }
        for(i=0; i<j; i++)
            arr[i] = arr_2[i];
    }
}

template<typename T>
void mergesort(T * arr, unsigned n){
    T * arr_2 = new T[n];
    aux_merge(arr, n, arr_2);
    delete [] arr_2;
}

double pi_aprox(unsigned precition){
   int n;
   double or_2;
   int or_1 = 1; 
   int cinco_pot = 5; 
   int dos_pot = 239;
   int menos_1 = 4;
   double var_1 = (double)4/5; 
   double var_2 = (double)4/239;
   for(n = 1; n < precition; n++){
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