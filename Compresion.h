#ifndef stdlib_h
#define stdlib_h
#include <stdlib.h>
#endif /* stdlid_h */

#ifndef stdio_h
#define stdio_h
#include <stdio.h>
#endif /* stdio_h */

void comprimir(const char txt[12], const char huf[12]);
void codificar_mensaje(Fila *Tabla, const char txt[12], const char huf[12]);
void guardar_tabla(Fila *Tabla, const char huf[12]);
void buscar_binario(Fila *Tabla,char letra,char codigo[MAX_CODE]);
void llenar_byte(char byte[8],int *contador,char codigo[MAX_CODE], unsigned char binario[], int *pos);
unsigned char empacar_bits(char binario[8]);
void limpiar_codigo(char codigo[MAX_CODE]);
void escribir_binario(unsigned char binario[], int pos, const char huf[12]);
int calcular_bytes(Fila *Tabla);

void comprimir(const char txt[12], const char huf[12]){
	Fila *Tabla = iniciar_tabla();
	Rellenar_Tabla(Tabla,txt);
	Nodo *hojas[MAX];									//almacena todas las hojas para posteriormente hacer el arbol
	crear_hojas(Tabla,hojas);
	Nodo *Arbol = crear_arbol(hojas);
	llenar_codigos(Tabla,Arbol);	
	codificar_mensaje(Tabla,txt,huf);
	mostrar_tabla(Tabla);
	printf("\nfrecuencia %i - cardinalidad %i",sumar_freccias(Tabla),contar_caracteres(Tabla));
}

void codificar_mensaje(Fila *Tabla, const char txt[12], const char huf[12]){
	int byte_totales = calcular_bytes(Tabla);
	unsigned char binario[byte_totales];				//almacena todo el binario que se escribirá en el archivo .huf
	char codigo[MAX_CODE];								//almacena temporalmente el codigo de una sola letra
	guardar_tabla(Tabla,huf);							//en primer lugar se guarda la tabla dentro del archivo
	system("pause");
	char letra;											//almacena cada caracter del mensaje, uno por uno para conseguir su codigo
	int contador=0; 									//contador cuenta la cantidad de "bits" rescatados para no sobrepasar el "byte"
	int pos=0;											//pos sirve como referencia para el arreglo binario.
	char byte[8] = {'0','0','0','0','0','0','0','0'};	//guarda los 8 "bits" para escribirlos en un unsigned char 
	FILE *archivo = fopen(txt, "r");
	rewind(archivo);
	while(1){	
		fread(&letra, sizeof(char),1,archivo);
    	buscar_binario(Tabla,letra,codigo);				//busca el codigo de la letra y lo almacena en el arreglo codigo
		llenar_byte(byte,&contador,codigo,binario,&pos);//saco el codigo del arreglo para transformarlo en un unsigned char y guardarlo en binario
    	limpiar_codigo(codigo);							//vacia el arreglo para usarlo en la siguiente letra
		if(feof(archivo)){								//si estoy en la ultima letra
			binario[pos] = empacar_bits(byte);			//empaco el ultimo byte
			pos++;
			escribir_binario(binario,pos,huf);	 		//escribe todo el codigo en un archivo a partir del arreglo binario
			fclose(archivo);
			break;
		}	
    }
}
int calcular_bytes(Fila *Tabla){						//calcula los bytes que quedaran luego de comprimir el mensaje
	Fila* aux = Tabla;
	int suma=0,factor=0,largo=0;
	while(aux!=NULL){
		largo=0;
		while(aux->codigo[largo]=='0' || aux->codigo[largo]=='1'){
			largo++;
		}
		factor= aux->frec*largo;						//cantidad de bits por letra
		suma = suma + factor;
		aux=aux->sgte;
	}
	suma= (suma/8)+1;
	return suma;
}
void guardar_tabla(Fila *Tabla, const char huf[12]){	//Guarda las variables de la tabla en un archivo binario.
	Fila *aux = Tabla;
	FILE *archivo = fopen(huf,"wb");
	int cardinalidad = contar_caracteres(Tabla);
	fwrite(&cardinalidad, sizeof(int),1,archivo);
	while(aux!=NULL){
		fwrite(&aux->caract, sizeof(char),1,archivo);	//solo guarda el caracter y la frecuencia, los codigos no son necesarios
		fwrite(&aux->frec, sizeof(int),1,archivo);
		aux = aux->sgte;
	}
	fclose(archivo);	
}

/*Busca en la Tabla el codigo correspondiente a la letra y lo almacena en el arreglo codigo*/
void buscar_binario(Fila *Tabla,char letra,char codigo[MAX_CODE]){
	Fila *aux=Tabla;
	int i=0;
	while(aux!=NULL){
		if(letra == aux->caract){			
			while(aux->codigo[i]== '0' || aux->codigo[i]== '1'){
				codigo[i]=aux->codigo[i];				//rescato el codigo binario para esta letra
				i++;
			}
			break;				
		}
		aux=aux->sgte;
	}	
}

void llenar_byte(char byte[8],int *contador,char codigo[MAX_CODE], unsigned char binario[], int *pos){
	int i=0;
	while(codigo[i]=='1' || codigo[i]=='0'){			//mientras haya codigo
		if(*contador<8){
			byte[*contador]=codigo[i];					//escribo el codigo en el arreglo byte
			i++;
			(*contador)++;
		}
		else{											//si el arreglo byte tiene 8 "bits"
			binario[*pos]= empacar_bits(byte);			//transformo los "bits" en un byte y lo guardo en el arreglo binario
			(*pos)++;
			*contador=0;
		}
	}	
};


unsigned char empacar_bits(char binario[8]){			//pasa los "bits" de un arreglo a un byte unsigned char
	unsigned char byte = 0; //0 0 0 0 0 0 0 0
	unsigned char aux = 1;  //0 0 0 0 0 0 0 1
	int i=0;
	for(i=0;i<8;i++){
		if(binario[i]=='1'){
			aux = aux<<7-i;
			byte= byte | aux;
			aux=1;
		};
	};
	return byte;
}

void limpiar_codigo(char codigo[MAX_CODE]){
	int i=0;
	while(codigo[i]=='0'||codigo[i]=='1'){
		codigo[i]=' ';
		i++;
	}
}

void escribir_binario(unsigned char binario[], int pos, const char huf[12]){
	FILE *archivo = fopen(huf, "ab");
	int i=0;
	for(i=0;i<pos;i++){
		fwrite(&binario[i], sizeof(unsigned char),1,archivo);
	}	
	fclose(archivo);
}
