#ifndef stdlib_h
#define stdlib_h
#include <stdlib.h>
#endif /* stdlid_h */

#ifndef stdio_h
#define stdio_h
#include <stdio.h>
#endif /* stdio_h */

#ifndef string_h
#define string_h
#include<string.h>
#endif /* string_h */

#ifndef time_h
#define time_h
#include<time.h>
#endif /* time_h */

#define MAX 90	//define la cantidad de caracteres diferentes que el programa recibe	
#define MAX_CODE 25 //define el largo de los codigos binarios de huffman
#include "Tabla_huffman.h" 
#include "Arbol.h"
#include "Compresion.h"
#include "Descompresion.h"
#include "Crear_textos.h" //Libreria extra encargada de crear los archivos de texto en orden creciente de 1 decimo.

void compresionConTiempoyTamano(char txt[],char huf[],int *contador);//Comprime un archivo y retorna el tiempo que le tomo y los tamaños de los archivos.
void descompresionConTiempoyTamano(char txt[],char huf[],int *contador);//Descomprime un archivo y retorna el tiempo que le tomo y los tamaños de los archivos.
void verTamanoArchivo(char archivo[]);//Modulo encargado de imprimir el tamaño de un archivo en bytes.
void tasaDeCompresion(char txt[],char huf[]);//Modulo encargado de realizar la operatoria para ver la tasa de compresion de los archivos.
int VerificarExistenciaArchivos(char condicion[]);//Verifica que existan los archivos txt de prueba para evitar errores.

void main(int argc, const char * argv[]){
	int decision = 5;
	int contador = 1;
	while(decision != 0){
		printf("\n1.Comprimir\n2.Descomprimir\n3.Crear textos de prueba\n0.Salir\n->");
		scanf("%i",&decision);
		if(decision == 1 && VerificarExistenciaArchivos("txt")){
			contador = 1;
			compresionConTiempoyTamano("prueba1.txt","comprimido1.huf",&contador);
			compresionConTiempoyTamano("prueba2.txt","comprimido2.huf",&contador);
			compresionConTiempoyTamano("prueba3.txt","comprimido3.huf",&contador);
			compresionConTiempoyTamano("prueba4.txt","comprimido4.huf",&contador);
			compresionConTiempoyTamano("prueba5.txt","comprimido5.huf",&contador);
			compresionConTiempoyTamano("prueba6.txt","comprimido6.huf",&contador);
			compresionConTiempoyTamano("prueba7.txt","comprimido7.huf",&contador);
			compresionConTiempoyTamano("prueba8.txt","comprimido8.huf",&contador);
			compresionConTiempoyTamano("prueba9.txt","comprimido9.huf",&contador);
			compresionConTiempoyTamano("prueba10.txt","comprimido10.huf",&contador);
			contador = 0;
		}
		if(decision == 2  && VerificarExistenciaArchivos("huf")){
			contador = 1;
			descompresionConTiempoyTamano("prueba1.txt","comprimido1.huf",&contador);
			descompresionConTiempoyTamano("prueba2.txt","comprimido2.huf",&contador);
			descompresionConTiempoyTamano("prueba3.txt","comprimido3.huf",&contador);
			descompresionConTiempoyTamano("prueba4.txt","comprimido4.huf",&contador);
			descompresionConTiempoyTamano("prueba5.txt","comprimido5.huf",&contador);
			descompresionConTiempoyTamano("prueba6.txt","comprimido6.huf",&contador);
			descompresionConTiempoyTamano("prueba7.txt","comprimido7.huf",&contador);
			descompresionConTiempoyTamano("prueba8.txt","comprimido8.huf",&contador);
			descompresionConTiempoyTamano("prueba9.txt","comprimido9.huf",&contador);
			descompresionConTiempoyTamano("prueba10.txt","comprimido10.huf",&contador);
			contador = 0;
		}
		if(decision == 3){
			crear_textos();
		}
	}
}

void compresionConTiempoyTamano(char txt[],char huf[],int *contador){
	clock_t begin = clock();
	comprimir(txt,huf);	
	clock_t end = clock();
	double time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
	printf("\n(%i) Tiempo en comprimir = %f segundos",*contador,time_spent);
	verTamanoArchivo(txt);
	verTamanoArchivo(huf);
	tasaDeCompresion(txt,huf);
	(*contador)++;
}

void descompresionConTiempoyTamano(char txt[],char huf[],int *contador){
	FILE *archivo = fopen(txt,"w");
	fclose(archivo);
	clock_t begin = clock();
	descomprimir(txt,huf);
	clock_t end = clock();
	double time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
	printf("\n(%i) Tiempo en descomprimir = %f segundos",*contador,time_spent);
	verTamanoArchivo(txt);
	verTamanoArchivo(huf);
	printf("\n");
	(*contador)++;
}

void verTamanoArchivo(char archivo[]){
	FILE *fichero=fopen(archivo,"r");
	fseek(fichero,0L, SEEK_END);
	printf("\n    %s ocupa %d bytes",archivo,ftell(fichero));
	fclose(fichero);
}

void tasaDeCompresion(char txt[],char huf[]){
	FILE *fichero=fopen(txt,"r");
	FILE *fichero2=fopen(huf,"r");
	fseek(fichero,0L, SEEK_END);
	fseek(fichero2,0L, SEEK_END);
	float tamanoHuf = ftell(fichero2);
	float tamanoTxt = ftell(fichero);
	float tasadecompresion = tamanoHuf/tamanoTxt;
	printf("\n    Tasa de compresion = %f\n",tasadecompresion*100);
	fclose(fichero);
	fclose(fichero2);
}

int VerificarExistenciaArchivos(char condicion[]){
	FILE *archivo1 = NULL,*archivo2 = NULL,*archivo3 = NULL ,*archivo4 = NULL ,*archivo5 = NULL ,*archivo6 = NULL ,*archivo7 = NULL, *archivo8 = NULL, *archivo9 = NULL, *archivo10 = NULL; 
	if(condicion == "txt"){
		archivo1 = fopen("prueba1.txt","r");
		archivo2 = fopen("prueba2.txt","r");
		archivo3 = fopen("prueba3.txt","r");
		archivo4 = fopen("prueba4.txt","r");
		archivo5 = fopen("prueba5.txt","r");
		archivo6 = fopen("prueba6.txt","r");
		archivo7 = fopen("prueba7.txt","r");
		archivo8 = fopen("prueba8.txt","r");
		archivo9 = fopen("prueba9.txt","r");
		archivo10 = fopen("prueba10.txt","r");
	}
	if(condicion == "huf"){
		archivo1 = fopen("comprimido1.huf","rb");
		archivo2 = fopen("comprimido2.huf","rb");
		archivo3 = fopen("comprimido3.huf","rb");
		archivo4 = fopen("comprimido4.huf","rb");
		archivo5 = fopen("comprimido5.huf","rb");
		archivo6 = fopen("comprimido6.huf","rb");
		archivo7 = fopen("comprimido7.huf","rb");
		archivo8 = fopen("comprimido8.huf","rb");
		archivo9 = fopen("comprimido9.huf","rb");
		archivo10 = fopen("comprimido10.huf","rb");
	}
	if(archivo1 != NULL && archivo2 != NULL && archivo3 != NULL && archivo4 != NULL && archivo5 != NULL){
		if(archivo6 != NULL && archivo7 != NULL && archivo8 != NULL && archivo9 != NULL && archivo10 != NULL){
			fclose(archivo1);fclose(archivo2);fclose(archivo3);fclose(archivo4);fclose(archivo5);fclose(archivo6);fclose(archivo7);fclose(archivo8);fclose(archivo9);fclose(archivo10);
			return 1;
		}
	}
	printf("\nFaltan archivos para realizar la funcion\n");
	fclose(archivo1);fclose(archivo2);fclose(archivo3);fclose(archivo4);fclose(archivo5);fclose(archivo6);fclose(archivo7);fclose(archivo8);fclose(archivo9);fclose(archivo10);
	return 0;
}
