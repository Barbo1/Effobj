#include "../../operation.hpp"

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
