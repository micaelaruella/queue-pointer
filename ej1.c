#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*Declaración de tipos de datos personalizados*/
typedef char tString [20];
typedef struct{
	int nroTurno;
	tString cliente;
	int motivoTurno;
}tDatosTurno;

typedef struct nodo{
	tDatosTurno datos;
	struct nodo * siguiente;
}tNodo;

typedef struct{
	tNodo * principio;
	tNodo * final;
}tColaTurno;

/*Declaración de prototipo*/
void inicializarCola();
bool colaVacia(tColaTurno);
void push(tDatosTurno);
void pop();
void mostrarTurnos(tColaTurno);
void ingresarDatos();
tNodo * primerTurno(tColaTurno);
void menu();
int cantTransfEspera();
int cantConsultaEspera();

/*Declaración de variables globales*/
tColaTurno colaTurno;

/*Función principal*/
int main(){
	inicializarCola();
	menu();
	return 0;
}

/*Implementación de funciones*/
void inicializarCola(){
	colaTurno.principio = NULL;
	colaTurno.final = NULL;
	printf("Cola de turnos inicializada! \n");
}

bool colaVacia(tColaTurno pColaTurno){
	return (pColaTurno.principio == NULL && pColaTurno.final == NULL);
}


void push(tDatosTurno pDatosTurno){
	/*Crear nodo*/
	tNodo * nuevoNodo;
	/*Asignar memoria al nuevo nodo*/
	nuevoNodo = (tNodo *) malloc (sizeof(tNodo));
	/*Asignar valores al dato del nodo y al campo siguiente*/
	nuevoNodo->datos = pDatosTurno;
	nuevoNodo->siguiente = NULL;
	
	if(colaVacia(colaTurno)){
		/*No hay elementos*/
		/*Ambos punteros de la cola apuntan al nuevo nodo (insertamos primer nodo)*/
		colaTurno.principio = nuevoNodo;
		colaTurno.final = nuevoNodo;
	}else{
		/*Hay elementos*/
		/*Actualizar el puntero final*/
		colaTurno.final->siguiente = nuevoNodo;
		colaTurno.final = nuevoNodo;
	}
	printf("\nDatos del turno ingresado: \n\t-Numero de orden: %d \n\t-Nombre del cliente: %s \n\t-Motivo: %s\n", pDatosTurno.nroTurno, pDatosTurno.cliente, (pDatosTurno.motivoTurno == 1) ? "Transaccion" : "Consulta" );
}

void pop(){
	if (!colaVacia(colaTurno)){
		/*Resguardar nodo del principio (q se quita primero)*/
		tNodo * turnoSuprimir = colaTurno.principio;
		if(colaTurno.principio == colaTurno.final){
			inicializarCola();
		}else{
			colaTurno.principio = turnoSuprimir->siguiente;
		}
		printf("Se elimino el turno: \n\t-Numero de orden: %d \n\t-Nombre del cliente eliminado: %s \n\t-Motivo: %s\n", 
		turnoSuprimir->datos.nroTurno, turnoSuprimir->datos.cliente, (turnoSuprimir->datos.motivoTurno == 1)? "Transaccion" : "Consulta");	
		/*Liberar espacio*/
		free (turnoSuprimir);
		/*Asignar NULL*/
		turnoSuprimir = NULL;
	}else{
		printf("No hay turnos para quitar\n");
	}
}

void mostrarTurnos(tColaTurno pColaTurno){
	if (colaVacia(pColaTurno)){
		printf("No hay turnos asignados para mostrar\n");
	}else{
		tNodo * aux = pColaTurno.principio;	
		printf("Turnos en cola\n");
		while (aux != NULL){
			printf ("\t-Numero de orden: %d \n\t-Nombre del cliente: %s \n\t-Motivo: %s\n", aux->datos.nroTurno, aux->datos.cliente, (aux->datos.motivoTurno == 1) ? "Transaccion" : "Consulta" );
	
			aux = aux->siguiente;
		}
	}
}

tNodo * primerTurno(tColaTurno pColaTurno){
	return (pColaTurno.principio);
}

void ingresarDatos(){
	tDatosTurno data;
	int contadorTransacciones = 0;
	int contadorConsulta = 0;
	printf("Ingresar los siguientes datos para registrar\n");
	printf("\tNumero de turno: ");
	scanf("%d", &data.nroTurno);
	printf("\tNombre de cliente: ");
	fflush(stdin);
	gets(data.cliente);
	printf ("\t1. Transaccion \n\t2. Consulta\n");
	printf("\tMotivo del turno: ");
	scanf("%d", &data.motivoTurno);
	push(data);
}

void menu(){
	int opcion;
	do{
		printf("\t\t\t---------------------------------------------------------\n");
		printf("\t\t\t|\t\t\tM E N U\t\t\t\t|\n");
		printf("\t\t\t---------------------------------------------------------\n");
		printf("\t\t\t|\t1. Insertar turno\t\t\t\t|\n");
		printf("\t\t\t|\t2. Eliminar turno\t\t\t\t|\n");	
		printf("\t\t\t|\t3. Mostrar listado de turnos\t\t\t|\n");
		printf("\t\t\t|\t4. Mostrar cantidad de transacciones en espera  |\n");
		printf("\t\t\t|\t5. Mostrar cantidad de consultas en espera\t|\n");
		printf("\t\t\t|\t6. Mostrar primer turno\t\t\t\t|\n");					
		printf("\t\t\t|\t0. Salir\t\t\t\t\t|\n");
		printf("\t\t\t---------------------------------------------------------\n");
		printf("\n\t\t\tSeleccione una opcion del menu: ");
		scanf("%d", &opcion);
		system("cls");
		switch (opcion){
			case 0: 
					printf("Programa finalizado!\n");
					break;					
			case 1: ingresarDatos();					
					break;
			case 2:	pop();
					break;		
			case 3: mostrarTurnos(colaTurno);
					
					break;						
			case 4:	{
				if(!colaVacia(colaTurno)){
					printf("Cantidad de transacciones en espera %d \n", cantTransfEspera());
				}else{
					printf("No hay transacciones en espera! \n");
				}	
				break;
			}

			case 5:	{
				if(!colaVacia(colaTurno)){
					printf("Cantidad de consultas en espera %d \n", cantConsultaEspera());
				}else{
					printf("No hay consultas en espera! \n");
				}
				break;
			}
						
			case 6:{
				tNodo * primero;
				primero = primerTurno(colaTurno);
					if(colaVacia(colaTurno)){
						printf("No hay turnos en la cola");
					}else{
						printf("El primer turno es: %d - %s - %s \n", primero->datos.nroTurno, primero->datos.cliente, (primero->datos.motivoTurno == 1) ? "Transaccion" : "Consulta");
					}
					break;
			}
			default: 
					printf("Opcion ingresada incorrecta\n");
					 break;
		}
		system("pause");
		system("cls");
	}while(opcion != 0);
	
}

int cantTransfEspera(){
	int contTrans = 0;
	tNodo * aux;
	aux = colaTurno.principio;
	while (aux != NULL){
			if(aux->datos.motivoTurno == 1){
				contTrans = contTrans + 1;		
			}
			aux = aux->siguiente;
	}
	
	return contTrans;	
}

int cantConsultaEspera(){
	int cantConsul = 0;
	tNodo * aux;
	aux = colaTurno.principio;
	while (aux != NULL){
			if(aux->datos.motivoTurno == 2){
				cantConsul = cantConsul + 1;			
			}
			aux = aux->siguiente;
		
	}
	
	return cantConsul;
	
}
