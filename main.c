#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "iterator.h"
#include "string.h"

int main(int argc, char **argv)
{
	FILE * fp = NULL;
	FILE * ficheroFinal = NULL;
	int factorDeCombinacion = atoi(argv[2]);
	char * linea = NULL;
	int valoresTemporal[1024];
	size_t longitud = 0;
	int numberOfLines = 0;
    	
	// Aqui se abre el fichero y se coloca la ruta.
	fp = fopen(argv[1], "r");
	ficheroFinal = fopen("Combinaciones.txt","wt");

	// Caso en el que no te permita abrir el fichero
	if (fp == NULL || ficheroFinal == NULL)
	{
		printf("No se pudo abrir el fichero, asegurate de haberlo escrito bien. El proceso se aborto. \n");
		exit(EXIT_FAILURE);
	}

	// Se guarda en valoresTemporal todos los elementos del fichero y a la
	// vez se va contando el numero de lineas
	while(getline(&linea, &longitud, fp) != -1)
	{
		valoresTemporal[numberOfLines] = atoi(linea);
		numberOfLines++;
	}

	// Aqui estaran todos los valores del archivo de los numeros
	int valores[numberOfLines];
	int x;
	for (x=0; x < numberOfLines; x++)
	{
		valores[x] = valoresTemporal[x];
	}

	// Se "libera" el array
	valoresTemporal[0] = '\0';

	// Liberacion del puntero
	if (linea) free(linea);
	// Cierre del archivo
	fclose(fp);
	
	int i,j,p = 0;
	int suma = 0;
	
	// Vector con los indices de las combinaciones sin repeticion
	int* a=calloc(factorDeCombinacion,sizeof(int)); 
		
	for(p = 0; p < factorDeCombinacion; p++)
	{
		// Establecemos los valores de inicializacion para evitar que 
		// la primera combinación sea 0,0,0
		a[p] = p;
	}

	int total = getNumOfCombinations(numberOfLines,factorDeCombinacion);
	int numLeft = total;
	
	// Empezamos a contar el tiempo
	clock_t empieza = clock(); 

	i = 0;
	while(numLeft > 0)
	{
		// En numLeft se almacenan el numero de combinaciones posibles que aun 
		// faltan por evaluar
		numLeft=getNext(&a,numLeft,factorDeCombinacion,numberOfLines,total);

		// Se calcula la suma de los elementos de la combinacion
		suma = 0;
		for(j = 0; j < factorDeCombinacion; j++)
		{
			suma += valores[a[j]];
		}
	
		if(suma %2 != 0)// si es impar
		{
    			//Guardamos las combinaciones IMPARES en el fichero y en el vectorConsola
			for(p = 0; p < factorDeCombinacion; p++)
			{
        			fprintf(ficheroFinal,"%d",valores[a[p]]);
        			if(p+1 != factorDeCombinacion)
				{
          				fprintf(ficheroFinal,",");
        			}
			}
			fprintf(ficheroFinal,"\n");
		}
	}
  	// Fin del bucle de fuerza bruta

	// Capturamos el tiempo al acabar el bucle
	clock_t acaba = clock();

	// --------------------------------------------

	if(argc == 4 && strcmp(argv[3],"-t") == 0)
	{
		double tiempo_transcurrido = (double)(acaba-empieza) / CLOCKS_PER_SEC;
		printf("Tiempo transucrrido en el iterador: %f secs\n", tiempo_transcurrido);
	}
	fclose (ficheroFinal);

	// Mostramos todas las combinaciones IMPARES por consola
	if(argc == 5 && strcmp(argv[4],"-m") == 0)
	{
		printf("\nSe procede a mostar las combinaciones por consola...\n");
		int c;
		FILE *file;
		file = fopen("Combinaciones.txt", "r");
		if(file)
		{
			while ((c = getc(file)) != EOF)
			{
				putchar(c);
			}
			printf("[FIN]\n");
			fclose(file);
		}
	}
	exit(EXIT_SUCCESS);
	return 0;
}
