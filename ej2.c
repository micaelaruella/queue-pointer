/*Bibliotecas*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*Declaración de tipos de datos personalizados*/
typedef char tString60 [60];
typedef char tString [30];

typedef struct{
	/*nombre y apellido, número de teléfono, DNI, código de lugar de procedencia (01-Corrientes 02-Chaco).*/
	tString nombre;
	tString apellido;
	tString60 nombreCompleto;
	int telefono;
	int dni;
	int codProcedencia;
}tDatosLlamada;

typedef struct nodo{
	tDatosLlamada datos;
	struct nodo * siguiente;
}tNodo;

typedef struct{
	tNodo * principio;
	tNodo * final;
}tColaLlamadas;

/*Declaración de prototipo*/
void inicializarCola();
bool colaVacia(tColaLlamadas );
void push(tDatosLlamada);
void pop();
void mostrarLlamadas(tColaLlamadas );
void registrarLlamadas();
tNodo * primerLlamada(tColaLlamadas );
int cantTotalLlamadas();	 /*la cantidad total de llamadas en cola de espera*/ 
int cantLlamadasProced(int);/*Conocer la cantidad de llamadas provenientes de cada lugar de procedencia*/
void listadoLlamadasCtes();
void menu();

/*Declaración de variables globales*/
tColaLlamadas  llamadas;


/*Funcion principal*/
int main (){
	inicializarCola();
	menu();

	return 0;
}
/*Implementación de funciones*/
void inicializarCola(){
	llamadas.principio = NULL;
	llamadas.final = NULL;
	printf("Cola de llamadas inicializada... \n");
}

bool colaVacia(tColaLlamadas pColaLlamadas){
	return (pColaLlamadas.principio == NULL && pColaLlamadas.final == NULL);
}

void push(tDatosLlamada pDatosLlamada){
	/*Crear nodo*/
	tNodo * nuevoNodo;
	/*Guardar espacio en la memoria y asignarsela al puntero*/
	nuevoNodo = (tNodo *) malloc (sizeof (tNodo));
	/*Asignarle valores al dato del campo y al campo siguiente*/
	nuevoNodo->datos = pDatosLlamada;
	nuevoNodo->siguiente = NULL;
	/**/
	if(colaVacia(llamadas)){
	/*No hay elementos*/
	/*Ambos punteros de la cola apuntan al nuevo nodo (insertamos primer nodo)*/
		llamadas.principio = nuevoNodo;
		llamadas.final = nuevoNodo;
	}else{
		/*Hay elementos*/
		/*Actualizar el puntero final*/	
		llamadas.final->siguiente = nuevoNodo;
		llamadas.final = nuevoNodo;
	}
	printf("****************************************\n");
	printf("Los datos de la llamada registrada son: \n\tCliente: %s \n\tTelefono: %d \n\tDNI: %d \n\tProcedencia: %s \n", pDatosLlamada.nombreCompleto, pDatosLlamada.telefono, 
	pDatosLlamada.dni, (pDatosLlamada.codProcedencia == 1) ? "Corrientes" : "Chaco");
	
}

void pop(){
	if(!colaVacia(llamadas)){
		/*Resguarda el nodo del principio para eliminar*/
		tNodo * llamadaSuprimir = llamadas.principio;
		if(llamadas.principio == llamadas.final){
			inicializarCola();
		}else{
			llamadas.principio = llamadaSuprimir->siguiente;
		}
		printf("Los datos de la llamada eliminada son: \n\tCliente: %s \n\tTelefono: %d \n\tDNI: %d \n\tProcedencia: %s \n", llamadaSuprimir->datos.nombreCompleto, llamadaSuprimir->datos.telefono,
		llamadaSuprimir->datos.dni, (llamadaSuprimir->datos.codProcedencia == 1) ? "Corrientes" : "Chaco");
		/*Liberar memoria*/
		free (llamadaSuprimir);
		/*Asigna NULL al nodo eliminado*/
		llamadaSuprimir = NULL;
	}else{
		printf("No hay llamadas registradas para eliminar\n");
	}
}

void mostrarLlamadas(tColaLlamadas  pColaLlamadas){
	if(colaVacia(llamadas)){
		printf("No hay llamadas registradas para mostrar \n");
	}else{
		tNodo * aux = pColaLlamadas.principio;
		printf("Llamadas registradas: \n");
		printf("NOMBRE DEL CLIENTE | TELEFONO | DNI | PROCEDENCIA | \n");
		while(aux != NULL){
			printf(" %s | %d | %d | %s \n", aux->datos.nombreCompleto, aux->datos.telefono, aux->datos.dni, (aux->datos.codProcedencia == 1 ) ? "Corrientes" : "Chaco");
			aux = aux->siguiente;
		}
	}
}

void registrarLlamadas(){
 	tDatosLlamada info;
	printf("Ingresar los datos de la llamada: \n");
	printf("Nombre: ");
	fflush(stdin);
	gets(info.nombre);
	printf("Apellido: ");
	fflush(stdin);
	gets(info.apellido);
	/*Concatenar*/
	strcpy(info.nombreCompleto, info.apellido );
	strcat(info.nombreCompleto, ", ");
	strcat(info.nombreCompleto, info.nombre);
	
	printf("Telefono: ");
	scanf("%d", &info.telefono);
	printf("DNI: ");
	scanf("%d", &info.dni);
	printf("1-Corrientes 2-Chaco\n");
	printf("Seleccione un codigo de procedencia:");
	scanf("%d", &info.codProcedencia);
	/*Insertar*/
	push(info);
}

tNodo * primerLlamada(tColaLlamadas  pColaLlamadas){
	return (pColaLlamadas.principio);
}

int cantTotalLlamadas(){
	/*la cantidad total de llamadas en cola de espera*/ 
	int contTotalLlamadas = 0;
	tNodo * aux;
	aux = llamadas.principio;

	while(aux != NULL){	
		contTotalLlamadas = contTotalLlamadas + 1;		
		aux = aux->siguiente;
	}		
	return contTotalLlamadas;	
}

int cantLlamadasProced(int cant){
	/*Conocer la cantidad de llamadas provenientes de cada lugar de procedencia*/
	int cont = 0;

	tNodo * aux = llamadas.principio;
	while(aux != NULL){
		if(aux->datos.codProcedencia == cant){
			cont = cont + 1;	
		}
			aux = aux->siguiente;	
	}
	return cont;		
}

void listadoLlamadasCtes(){
	tNodo * aux = llamadas.principio;
	printf("NOMBRE DEL CLIENTE | TELEFONO | DNI | \n");
	while(aux!=NULL){
		if(aux->datos.codProcedencia == 1){
			printf(" %s | %d | %d \n", aux->datos.nombreCompleto, aux->datos.telefono, aux->datos.dni);
		}
		aux = aux->siguiente;
	}	
}
void menu(){
	int opcion;
	do{
		printf("\t\t\t---------------------------------------------------------\n");
		printf("\t\t\t|\t\t\tM E N U\t\t\t\t|\n");
		printf("\t\t\t---------------------------------------------------------\n");
		printf("\t\t\t|\t1. Registrar llamada\t\t\t\t|\n");
		printf("\t\t\t|\t2. Eliminar llamada\t\t\t\t|\n");	
		printf("\t\t\t|\t3. Mostrar datos de las llamadas\t\t|\n");
		printf("\t\t\t|\t4. Mostrar cantidad de llamadas de Corrientes\t|\n");
		printf("\t\t\t|\t5. Mostrar cantidad de llamadas de Chaco \t|\n");
		printf("\t\t\t|\t6. Mostrar cantidad total llamadas en espera\t|\n");	
		printf("\t\t\t|\t7. Mostrar listado de llamadas de Corrientes\t|\n");				
		printf("\t\t\t|\t0. Salir\t\t\t\t\t|\n");
		printf("\t\t\t---------------------------------------------------------\n");
		printf("\n\t\t\tSeleccione una opcion del menu:");
		scanf("%d", &opcion);
		system("cls");		
		switch(opcion){
			case 0:
				printf("Programa finalizado...\n");
				break;
			case 1:
				registrarLlamadas();
				break;
			case 2:
				pop();
				break;
			case 3:
				mostrarLlamadas(llamadas);
				break;

			case 4:{
				if (colaVacia(llamadas)){
					printf("No hay ninguna llamada registrada \n");
				}else{
					int cantLlamadas = cantLlamadasProced(1);
					printf("Cantidad de llamadas provenientes de Corrientes: %d\n", cantLlamadas);	
				}
				break;
			}
			case 5:{
				if (colaVacia(llamadas)){
					printf("No hay ninguna llamada registrada \n");
				}else{
					int cantLlamadas = cantLlamadasProced(2);
					printf("Cantidad de llamadas provenientes de Chaco: %d\n", cantLlamadas);	
				}
				break;
			}

			case 6:{
					if(colaVacia(llamadas)){
						printf("No hay ninguna llamada registrada \n");
					}else{
						printf("La cantidad total de llamadas en espera es: %d\n",cantTotalLlamadas());	
					}
				break;
			}
			case 7:{
				if(!colaVacia(llamadas)){
					printf("Listado de llamadas provenientes de Corrientes\n");	
					listadoLlamadasCtes();
				}else{
					printf("No hay llamadas registradas \n");
				}
				break;
			}

			default :
					printf("La opcion ingresada es incorrecta...\n");
					break;
		}
		system("pause");
		system("cls");		
	}while(opcion != 0);
}

