#ifndef stdlib_h
#define stdlib_h
#include <stdlib.h>
#endif /* stdlid_h */

#ifndef stdio_h
#define stdio_h
#include <stdio.h>
#endif /* stdio_h */

typedef struct tabla{//La tabla almacena un caracter, su frecuencia y su codigo de huffman
	char caract;
	int frec;
	char codigo[MAX_CODE]; 	
	struct tabla *sgte;	
}Fila;

Fila *iniciar_tabla();
void add_simbolo(char simbolo, Fila *Tabla);
Fila *agregar_fila(char simbolo);
void mostrar_tabla(Fila *Tabla);
void Rellenar_Tabla(Fila *Tabla, const char txt[12]);
int contar_caracteres(Fila *Tabla);
int sumar_freccias(Fila *Tabla);

Fila *iniciar_tabla(){									//crea la priemra fila de la tabla, fija la frecuencia en 0 para indicar que está vacia
	Fila *Tabla = malloc(sizeof(struct tabla)); 
	Tabla->caract='\0';
	Tabla->frec=0;
	int i=0;
	for(i=0;i<MAX_CODE;i++){
		Tabla->codigo[i]=' ';
	};
	Tabla->sgte=NULL;
	return Tabla;
}

void add_simbolo(char simbolo, Fila *Tabla){			//siendo el simbolo sacado del mensaje y Tabla, la referencia inicial a la Tabla de huffman
	Fila *aux = Tabla;
	if(aux->frec!=0){									//si la tabla no está vacia
		while(aux!=NULL){								//recorre la tabla en busca de la existencia del simbolo				
			if(simbolo==aux->caract){					//si el simbolo concuerda con el de la tabla
				(aux->frec)++;							//aumenta su frecuencia
				break;									//encontro el simbolo dentro de los que ya existían, y sale.
			};
			if(aux->sgte!=NULL){
				aux=aux->sgte;
			}
			else{										//si llego al final y no encontró el simbolo
				aux->sgte= agregar_fila(simbolo);		//agrega una fila con el simbolo y frecuencia 1
				break;
			}		
		};
	}
	else{												//si la tabla está vacía
		aux->caract=simbolo;							//agrega el simbolo directamente en la primera fila
		aux->frec=1;									//fija su frecuencia en 1 (la tabla ya no esta vacia)
	};
}

Fila *agregar_fila(char simbolo){						//crea una fila nueva, contiene el simbolo nuevo y deja su frecuencia en 1
	Fila *aux= iniciar_tabla();
	aux->caract = simbolo;
	aux->frec = 1;
	return aux;
}

void mostrar_tabla(Fila *Tabla){
	Fila *aux = Tabla;
	printf("\nSimbolo - Frecuencia - Codigo\n");
	while(aux!=NULL){																
		printf("   %c\t\t%i\t",aux->caract,aux->frec);
		int i;
		for(i=0;i<MAX_CODE;i++){
			printf("%c",aux->codigo[i]);
		};
		printf("\n");
		aux=aux->sgte;
	};
}

void Rellenar_Tabla(Fila *Tabla, const char txt[12]){	//rellena las frecuencias de la tabla de huffman a partir de un archivo .txt
	FILE *archivo = fopen(txt, "r");
    char letra;
	while(!feof(archivo)){
        fread(&letra, sizeof(char),1,archivo);
        if(letra != '\0'){
        	add_simbolo(letra,Tabla);
		}
        letra = '\0';
    }
    fclose(archivo);
}

int contar_caracteres(Fila *Tabla){ 					//Cuenta la cardinalidad de caracteres y lo retorna.
	int contador = 0;
	int flag = 0;
	Fila *aux = Tabla;
	while(aux != NULL){
		contador++;
		aux = aux->sgte;
	}
	return contador;
}

int sumar_freccias(Fila *Tabla){						//Suma todas las frecuencias para saber cuantos caracteres hay en el mensaje
	Fila *aux = Tabla;
	int suma = 0;
	while(aux != NULL){
		suma = suma + aux->frec;
		aux = aux->sgte;
	}
	return suma;
}
