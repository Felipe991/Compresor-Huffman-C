#ifndef stdlib_h
#define stdlib_h
#include <stdlib.h>
#endif /* stdlid_h */

#ifndef stdio_h
#define stdio_h
#include <stdio.h>
#endif /* stdio_h */

typedef struct arbol{	//Elementos de un arbol;
	char caract; 		//caracter, el caracter es nulo si estamos en una raiz
	int peso;			//frecuencia
	struct arbol *der;	//si los hijos apuntan a NULL, estamos en una hoja
	struct arbol *izq;	
}Nodo;

Nodo *iniciar_raiz();
void crear_hojas(Fila *Tabla, Nodo *hojas[MAX]);
void llenar_hojas(Nodo *hojas[MAX]);
void mostrar_hojas(Nodo *hojas[MAX]);
Nodo *crear_arbol(Nodo *hojas[MAX]);
Nodo *crear_raiz(Nodo *hoja1, Nodo *hoja2);
void buscar_indices(int pesos[MAX], int *i1, int *i2);
void mostrar_arbol(Nodo *Arbol);
void llenar_arreglo_pesos(int pesos[MAX], Nodo *hojas[MAX]);
void llenar_codigos(Fila *Tabla, Nodo *Arbol);
void buscar_codigo(int i,Fila *Tabla, Nodo *Arbol, char codigo[MAX_CODE]);

Nodo *iniciar_raiz(){									//crea una raiz vacía que apunta a NULL						
	Nodo *Raiz = malloc(sizeof(struct arbol)); 
	Raiz->caract='\0';
	Raiz->peso=0;
	Raiz->der=NULL;
	Raiz->izq=NULL;	
	return Raiz;
};

void crear_hojas(Fila *Tabla, Nodo *hojas[MAX]){		//crea una raiz por cada fila de huffman y las guarda en un arreglo.
	Fila *aux = Tabla;
	int  i=0;										
	llenar_hojas(hojas);					
	while(aux!=NULL){									//recorre la tabla 	
		hojas[i]->caract = aux->caract;					//las raices toman valores de la tabla de huffman
		hojas[i]->peso = aux->frec;						
		aux=aux->sgte;
		i++;
	};	
}

void llenar_hojas(Nodo *hojas[MAX]){					//llena el arreglo hojas con raices vacías
	int i=0;
	for(i=0;i<MAX;i++){
		hojas[i]=iniciar_raiz();
	}
};

void mostrar_hojas(Nodo *hojas[MAX]){
	int i=0;
	for(i=0;i<MAX;i++){
		if(hojas[i]->peso!=0){
			printf("[%c-%i] ",hojas[i]->caract,hojas[i]->peso);
		};
	}
}

Nodo *crear_arbol(Nodo *hojas[MAX]){					//retorna el arbol completo a partir de las raices creadas de la tabla de huffman
	int i1,i2,n;										//indice 1, indice 2
	int flag=2;
	int pesos[MAX];										//sirve como auxiliar para no modificar los pesos en la estructura
	llenar_arreglo_pesos(pesos,hojas);					//copia los pesos de las raices en el arreglo pesos
	while(flag>1){
		buscar_indices(pesos,&i1,&i2);					//encuentra las posiciones de los 2 pesos menores y las guarda en i1 e i2
		hojas[i1]= crear_raiz(hojas[i1],hojas[i2]);		//crea la raiz en la posicion de la izquierda
		pesos[i1]= hojas[i1]->peso;
		pesos[i2]= 0;									//el peso del segundo numero se vuelve 0 para ignorarlo en la siguiente busqueda
		
		flag=0;
		for(n=0;n<MAX;n++){
			if((pesos[n])>0){							//cuenta la cantidad de raices que quedan en el arreglo
				flag++;									//si solo queda 1 raiz, flag sera exactamente igual a 1 y el ciclo terminara
			};
		};		
	}
	return hojas[i1]; 									//al terminar el algortimo, el arbol final queda almacenado en i1
}

void llenar_arreglo_pesos(int pesos[MAX], Nodo *hojas[MAX]){
	int i=0;
	for(i=0;i<MAX;i++){
		pesos[i]=hojas[i]->peso;
	};	
}

void buscar_indices(int pesos[MAX], int *i1, int *i2){//busca los 2 menores pesos dentro del arreglo hojas para crear una nueva raiz
	int i=0,j=1,aux;
	while(j<MAX){										//busca el primer peso menor
		if(pesos[j]>0 && pesos[j]<=pesos[i]){			//el peso debe ser mayor a 0 para evitar espacios vacios o  eliminados
			i=j;
		};
		j++;		
	}
	*i2=i;												//guarda la posicion donde se encuentra el peso menor 
	i=0;j=1;
	while(j<MAX){										//busca el segundo menor
		if(pesos[j]>0 && pesos[j]<=pesos[i] && j!=*i2){	//el segundo menor debe estar en una posicion diferente del primero
			i=j;
		}
		j++;	
		if(j==MAX && i==*i2){							//i se encuentra estancado en la primera posicion, con 
			do{
				i++;									//cambio la posicion de i desestancar la busqueda
			}while(pesos[i]==0);						//evitando que i quede sobre un espacio vacio o eliminado
			j=1;		
		};	
	}	
	*i1=i;
	if(*i2<*i1){										//i1 debe ser menor a i2, el arbol se forma sobre i1 y el peso de i2 se elimina
		aux=*i2;
		*i2=*i1;
		*i1=aux;
	};
}

Nodo *crear_raiz(Nodo *hoja1, Nodo *hoja2){				//retorna una raiz con caracter nulo unida a 2 nodos
	Nodo *nueva_raiz = iniciar_raiz();
	nueva_raiz->izq = hoja1;
	nueva_raiz->der = hoja2;
	nueva_raiz->peso = hoja1->peso + hoja2->peso;		//el peso de al razi es la suma del peso de sus hijos
	return nueva_raiz;	
}

void mostrar_arbol(Nodo *Arbol){	
	printf("\n\n");
	Nodo *Aux = Arbol;
	if(Arbol->caract != '\0'){//solo muestra las hojas del arbol
		printf("\nCaracter -> %c",Aux->caract);
		printf("\nPeso -> %i",Aux->peso);	
	}
	if(Aux->der != NULL){
		mostrar_arbol(Aux->der);
	}
	if(Aux->izq != NULL){
		mostrar_arbol(Aux->izq);
	}
}

void llenar_codigos(Fila *Tabla, Nodo *Arbol){			//a partir del Arbol de huffman llena las filas de codigo de la Tabla
	Fila *aux = Tabla;
	int i=0;
	char codigo[MAX_CODE];								//auxiliar para guardar el binario de huffman en una funcion recursiva
	int n;
	for(n=0;n<MAX_CODE;n++){
		codigo[n]=' ';
	};
	while(aux!=NULL){
		buscar_codigo(i,aux,Arbol,codigo);
		aux=aux->sgte;
	}
}

/*recorre el arbol en busca del simbolo de la tabla y en el proceso escribe el binario, una vez lo encuentra lo almacena en la fila del caracter*/
void buscar_codigo(int i,Fila *Tabla, Nodo *Arbol, char codigo[MAX_CODE]){
	Nodo *aux= Arbol;
	if(aux->der!=NULL){
		codigo[i]='1';
		buscar_codigo(i+1,Tabla,aux->der,codigo);
		codigo[i]=' ';
	};
	if(aux->izq!=NULL){
		codigo[i]='0';
		buscar_codigo(i+1,Tabla,aux->izq,codigo);
		codigo[i]=' ';
	};
	if(aux->izq==NULL && aux->der==NULL){
		if(aux->caract == Tabla->caract){
			int n=0;
			for(n=0;n<i;n++){
				Tabla->codigo[n]=codigo[n];					//guarda el codigo final en la Fila de la tabla que corresponde					
			};
		};
	};
}
