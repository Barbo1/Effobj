#include "../../operation.hpp"

template<typename T>
requires Orderable<T>
void heapsort (T * data, unsigned n) {
	n++;
	T * aux = new T[n];
	unsigned padre, hijo, i;
	for(i = 1; i < n; i++){
		aux[i] = data[i-1];
		hijo = i;
		while(hijo > 1 && aux[hijo] < aux[padre = hijo>>1]){
			std::swap(aux[padre], aux[hijo]);
			hijo = padre;
		}
	}
	for(i = n; i > 1; i--){
		data[n-i] = aux[1];
		hijo = 2;
		padre = 1;
		while((hijo < i && aux[hijo] < aux[i-1]) || (hijo+1 < i && aux[hijo+1] < aux[i-1])){
			if(hijo+1 < i && aux[hijo+1] < aux[hijo])
				hijo++;
			aux[padre] = aux[hijo];
			padre = hijo;
			hijo = hijo<<1;
		}
		aux[padre] = aux[i-1];
	}
	delete [] aux;
}
