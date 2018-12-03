#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "iterator.h"
#include "string.h"

/**
 * @param n, numero de elementos totales
 * @param r, numero de la combinacion
 * @return Devuelve el numero maximo de combinaciones posibles
 */
int getNumOfCombinations(int n, int r)
{
	if (r > n) {
	   return 0;
	}
	 if (n < 1) {
	   return 0;
	}
	// aqui se siguen las formulas de la combinatoria
	double nFact = getFactorial (n);
	double rFact = getFactorial (r);
	double nminusrFact = getFactorial (n - r);
	double res = (nFact / (rFact * nminusrFact));
	return res;// devuelve el numero total de combinaciones posibles
}

/**
 * Metodo getFactorial()
 *
 * @param n, valor a calcular su factorial
 * @return factorial del valor pasado por parametro
 */
double getFactorial(int n)
{
	double fact = 1;
	int i = n;
	for(i = n; i >= 1; i--)
	{
		fact *= i;
	}
	return fact;
}

int getNext(int **a,int numLeft, int factorDeCombinacion, int size, int total){
	// En tmp se va guardando la combinacion a generar para no modificar a, 
	// posteriormente se le asignará la combinacion VALIDA.
	int* tmp = calloc(factorDeCombinacion, sizeof(int));
	tmp=*a;
	
	if(numLeft == total) // 1 caso, todo ceros
	{
		numLeft--;
	}else{
		int k = factorDeCombinacion - 1;
		int j;
		while (*(tmp+k) == size - factorDeCombinacion + k) {
			k--;
		}

		if(*(tmp) > size - factorDeCombinacion) return 0;
		
		*(tmp+k) = *(tmp+k)+1;

		for (j=k+1; j < factorDeCombinacion; j++) {
		
			*(tmp+j) = *(tmp+k)+ j - k;
		}
		numLeft--;
	}

	(*a) = tmp;
	return numLeft;
}
