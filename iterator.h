// Cabecera del iterador.

// Funcion que devuelve el numero de combinaciones posibles sin repeticion
// de un total de numeros (n) y un factor de combinacion (r)
int getNumOfCombinations(int n, int r);

// Funcion que se encarga de realizar la operacion del factorial de cierto numero (n)
// y devolverlo
double getFactorial(int n);

// Funcion que se encarga de hacer la combinatoria y buscar una nueva combinacion sin repeticion,
// almacena la combinacion entracontrada en forma de indices en el vector a[]
int getNext(int **a,int numLeft, int factorDeCombinacion, int size, int total);
