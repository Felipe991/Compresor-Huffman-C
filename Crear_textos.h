#ifndef stdlib_h
#define stdlib_h
#include <stdlib.h>
#endif /* stdlid_h */

#ifndef stdio_h
#define stdio_h
#include <stdio.h>
#endif /* stdio_h */
void crear_textos();
void CopiarTexto(char nombre[],FILE *archivo,int *numerador,int frec_total);
void LimpiarTexto(char nombre[]);

void crear_textos(){
	Fila *Tabla = iniciar_tabla();
	Rellenar_Tabla(Tabla,"archivo.txt");
	int frec_total = sumar_freccias(Tabla);
	FILE *archivo =fopen("archivo.txt","r");
	int numerador = 1;
	CopiarTexto("prueba1.txt",archivo,&numerador,frec_total);
	CopiarTexto("prueba2.txt",archivo,&numerador,frec_total);
	CopiarTexto("prueba3.txt",archivo,&numerador,frec_total);
	CopiarTexto("prueba4.txt",archivo,&numerador,frec_total);
	CopiarTexto("prueba5.txt",archivo,&numerador,frec_total);
	CopiarTexto("prueba6.txt",archivo,&numerador,frec_total);
	CopiarTexto("prueba7.txt",archivo,&numerador,frec_total);
	CopiarTexto("prueba8.txt",archivo,&numerador,frec_total);
	CopiarTexto("prueba9.txt",archivo,&numerador,frec_total);
	CopiarTexto("prueba10.txt",archivo,&numerador,frec_total);
	fclose(archivo);
	printf("\nArchivos creados con exito\n");
}

void CopiarTexto(char nombre[],FILE *archivo,int *numerador,int frec_total){
	int aux = frec_total * (*numerador)/10;
	FILE *archivo2 = fopen(nombre,"w");
	char letra;
	rewind(archivo);
	while(aux>0){
		fread(&letra,sizeof(char),1,archivo);
		fwrite(&letra,sizeof(char),1,archivo2);
		aux--;
	}
	fclose(archivo2);
	(*numerador)++;
}

void LimpiarTexto(char nombre[]){
	FILE *fichero = fopen(nombre,"w");
	fclose(fichero);
}
