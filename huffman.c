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

#define MAX 90	//define la cantidad de caracteres diferentes que el programa recibe	
#define MAX_CODE 25	//define el largo de los codigos binarios de huffman
#include "Tabla_huffman.h"
#include "Arbol.h"
#include "Compresion.h"
#include "Descompresion.h"
#include <time.h>

int main(int argc, const char * argv[]) {
    //if(argc==4){
	   // if(strcmp(argv[1], "-c") == 0){			//si el segundo argumento es "-c"  
	   // clock_t begin = clock();
	    comprimir("archivo.txt","archivo.huf");			//comprimo
	    //clock_t end = clock();
	   // double time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
	   // printf("\nTiempo en comprimir = %f segundos",time_spent);
	   //     printf("\nCompresion realizada\n");      
	  /*  }else if(strcmp(argv[1], "-d") == 0){	//si el segundo argumento es "-d"       
	    	descomprimir(argv[3],argv[2]);		//descomprimo
	        printf("Descompresion realizada\n");     
	    }else{
	        printf("\n Argumentos invalidos, pruebe con los siguientes comandos:\n");     //si no es ninguna de las anteriores, manda un error
	        printf("\n huffman -c archivo.txt archivo.huf\n huffman -d archivo.huf archivo.txt");
	    }
	}
	else{
		printf("\n Cantidad de argumentos invalida, pruebe con los siguientes comandos:\n");
		printf("\n huffman -c archivo.txt archivo.huf\n huffman -d archivo.huf archivo.txt\n");
	}
    return 0;*/
}

