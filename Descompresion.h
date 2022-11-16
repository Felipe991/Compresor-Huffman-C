#ifndef stdlib_h
#define stdlib_h
#include <stdlib.h>
#endif /* stdlid_h */

#ifndef stdio_h
#define stdio_h
#include <stdio.h>
#endif /* stdio_h */

typedef struct byte{											//almacena los "bits" del archivo .huf
	char bits[8];		
	struct byte *sgte;
	
}Byte;

Byte *iniciar_byte();
void descomprimir(const char txt[12], const char huf[12]);
Fila *leer_tabla(FILE *archivo);
void extraer_bits(Byte *aux, unsigned char byte);
void generar_caracteres(Nodo *Arbol, Byte *Codigo,int frec_total, const char txt[12]);

void descomprimir(const char txt[12], const char huf[12]){
	Byte *Codigo = iniciar_byte();								//codigo contiene la referencia a la lista de bytes que seran decodificados
	unsigned char byte;
	Byte *aux = Codigo;
	FILE *archivo = fopen(huf, "rb");	
	Fila *Tabla = leer_tabla(archivo);							//En primer lugar se lee la tabla de frecuencias
	int frec_total = sumar_freccias(Tabla);						//se calcula la frecuencia total para saber cuantos caracteres se deben escribir
	while(1){
		fread(&byte,sizeof(unsigned char),1,archivo);
		extraer_bits(aux,byte);									//toma un byte y guarda sus bits en el arreglo de la estructura tipo Byte
		if( feof(archivo) ){
			break;
		}
		else{
			aux->sgte = iniciar_byte();
			aux = aux->sgte;
		}
	};
	//Es necesario recrear el Arbol a partir de la Tabla
	Nodo *hojas[MAX];
	crear_hojas(Tabla,hojas);
	Nodo *Arbol = crear_arbol(hojas);
	generar_caracteres(Arbol,Codigo,frec_total,txt);//A partir del arbol se transforman todos los bytes de la estructura Codigo a caracteres
}

Byte *iniciar_byte(){
	Byte *nuevo = malloc(sizeof(struct byte));
	nuevo->sgte=NULL;
	int i=0;
	for(i=0;i<8;i++){
		nuevo->bits[i]=' ';
	};
	return nuevo;
}

Fila *leer_tabla(FILE *archivo){ //Lee el binario correspondiente a los componentes de la tabla y lo retorna.
	Fila *Tabla = iniciar_tabla();
	Fila *aux = Tabla;
	int cardinalidad;
	rewind(archivo);
	fread(&cardinalidad,sizeof(int),1,archivo);
	while(cardinalidad > 0){
		int i = 0;
		fread(&aux->caract, sizeof(char),1,archivo);
		fread(&aux->frec, sizeof(int),1,archivo);
		cardinalidad--;
		if(cardinalidad != 0){
			aux->sgte = iniciar_tabla();
			aux = aux->sgte;
		}
	}
	return Tabla;
}

void extraer_bits(Byte *aux, unsigned char byte){//a partir de un byte extrae sus bits y los guarda en el arreglo de la estructura tipo Byte
	unsigned char mask;
	unsigned char bit;
	int i=0;
	for(i=0;i<8;i++){
		mask = 1;
    	mask = mask << (7-i); 
    	bit = byte & mask; 
    	bit = bit >> (7-i);
    	if(bit==1){
    		aux->bits[i]='1';
		}
		else{
			aux->bits[i]='0';
		}
	};	
}

void generar_caracteres(Nodo *Arbol, Byte *Codigo,int frec_total, const char txt[12]){
	Byte *aux = Codigo;
	Nodo *aux_arbol = Arbol;
	FILE *archivo = fopen(txt, "at");
	int i=0;	
	while(frec_total>0){
		for(i=0;i<8;i++){											//recorro el arreglo de la estructura tipo Byte
			if(aux->bits[i]=='0'){									//si el "bit" es cero, avanzo a la izquierda
				aux_arbol = aux_arbol->izq;
			}
			else{													//si el "bit" es uno, avanzo a la derecha
				aux_arbol = aux_arbol->der;
			};
			if(aux_arbol->izq==NULL && aux_arbol->der==NULL){ 		//si estoy en una hoja
				fwrite(&aux_arbol->caract, sizeof(char),1,archivo);	//escribo el caracter de la hoja el .txt
				aux_arbol = Arbol;									//vuelvo a la raiz del arbol
				frec_total--;
				if(frec_total==0){									//si ya escribi todos los caracteres salgo del ciclo for
					break;
				}
			}
		}
		aux=aux->sgte;												//avanzo para buscar el siguiente arreglo
	}
	fclose(archivo);
}
