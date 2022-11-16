#ifndef stdlib_h
#define stdlib_h
#include <stdlib.h>
#endif /* stdlid_h */

#ifndef stdio_h
#define stdio_h
#include <stdio.h>
#endif /* stdio_h */

#include <time.h>

void main(){
	int contador = 1;
	comprimir("Winrar a prueba1.rar prueba1.txt",&contador);
	comprimir("Winrar a prueba2.rar prueba2.txt",&contador);
	comprimir("Winrar a prueba3.rar prueba3.txt",&contador);
	comprimir("Winrar a prueba4.rar prueba4.txt",&contador);
	comprimir("Winrar a prueba5.rar prueba5.txt",&contador);
	comprimir("Winrar a prueba6.rar prueba6.txt",&contador);
	comprimir("Winrar a prueba7.rar prueba7.txt",&contador);
	comprimir("Winrar a prueba8.rar prueba8.txt",&contador);
	comprimir("Winrar a prueba9.rar prueba9.txt",&contador);
	comprimir("Winrar a prueba10.rar prueba10.txt",&contador);
	contador = 1;
	printf("\nSe debe entrar a la carpeta de ejecucion y borrar todos los prueba.txt para medir bien los tiempos\n");
	system("pause");
	descomprimir("Winrar e prueba1.rar",&contador);
	descomprimir("Winrar e prueba2.rar",&contador);
	descomprimir("Winrar e prueba3.rar",&contador);
	descomprimir("Winrar e prueba4.rar",&contador);
	descomprimir("Winrar e prueba5.rar",&contador);
	descomprimir("Winrar e prueba6.rar",&contador);
	descomprimir("Winrar e prueba7.rar",&contador);
	descomprimir("Winrar e prueba8.rar",&contador);
	descomprimir("Winrar e prueba9.rar",&contador);
	descomprimir("Winrar e prueba10.rar",&contador);
}

void comprimir(char instruccion[],int *contador){
	clock_t begin = clock();
	system(instruccion);
	clock_t end = clock();
	double time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
	printf("\n(%i) Tiempo en comprimir = %f segundos\n",*contador,time_spent);
	(*contador)++;
}

void descomprimir(char instruccion[],int *contador){
	clock_t begin = clock();
	system(instruccion);
	clock_t end = clock();
	double time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
	printf("\n(%i) Tiempo en descomprimir = %f segundos\n",*contador,time_spent);
	(*contador)++;
}
