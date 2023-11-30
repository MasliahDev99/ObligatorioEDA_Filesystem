/* 1111111 */ // sustituiir con los 7 dígitos de la cédula
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "../include/fila.h"
#include "../include/linea.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TEXTO_MAX 64 
typedef char* Cadena;

// Estructura para la lista enlazada de Filas.
struct _rep_fila {
    TLinea contenido;
    _rep_fila *sig;
};

//Pos-condición crea una fila vacía.
TFila createRow(){
	TFila nuevaFila = new _rep_fila;			// Creo el nodo Fila.
	nuevaFila->contenido = createLine ();		// Creo un nodo de linea vacio (para nunca tener que actualizar el puntero al primer nodo de linea de las filas).
	nuevaFila->sig = NULL;					
return nuevaFila;								// Retorno el puntero a la nueva Fila.
}
//Pos-Condición retorna true si la fila es vacía.
bool isEmptyRow(TFila fila){
		return (fila==NULL);					// Si la fila es NULL retorno true caso contrario false.
	}

//Pos-Condición Inserta una nueva fila al principio de "fila"
 void insertRow (TFila &fila){
 	TFila antiguafila = fila;					// Inicializo variable TFila apuntando a la direccion de memoria de fila
 	if (isEmptyRow(fila)){						// Si el puntero es NULL (no existe primer Fila).
 		fila = createRow();						// Creo la primer fila.
 	}
	else{
		fila = createRow();						// En caso contrario creo la primer fila.
		fila->sig = antiguafila;				// Enlazo la nueva fila a la anterior (insertandola "adelante").
 	}
 }
//pre-condicion: fila !=NULL
//pos-condicion: retorna un puntero al primer nodo de la fila "fila"
TLinea headRow(TFila fila){
	return 	fila->contenido;							// Retorno el puntero a la primer linea de la fila "fila".
 }
//pre-condicion: fila !=NULL
//pos-condicion: Retorna un puntero al siguente elemento de la fila "fila"
TFila nextRow (TFila fila){
	return 	fila->sig;									// Retorno el puntero al siguiente nodo de la fila "fila".
	}
 
//pre-condicion: fila != NULL
//elimina el ultimo nodo de la fila "fila"
void deleteFirstRow (TFila &fila){
	TFila anterior = NULL;
	while (fila->sig!= NULL){							// Itero hasta que fila esta en el ultimo nodo de la fila.
		anterior=fila;									// Guardo un puntero al anterior nodo de la fila.
		fila=fila->sig;
	}
    delete fila;										// Elimino el elemento fila "fila".				
	anterior->sig= NULL;								// Ahora anterior es el ultimo nodo asi que el puntero a sig apunta a NULL.
}
 
//Elimina toda la memoria de la fila "fila"
void deleteRows(TFila& fila) {
	TFila anterior = NULL;
    while (fila != NULL) {
		anterior=fila;									// Mientras el puntero fila no sea NULL recorro.
        TLinea linea = headRow(fila);					// Inicializo variable TLinea apuntando a la primera linea de la fila "fila".
        destroyLine(linea);								// Elimino toda la memoria utilizada por la linea.
		fila=fila->sig;                                    
        delete anterior;								// Elimino el primer nodo de la fila "fila".
    }    
  	anterior=NULL;
} 



//Pos-Condición modifica el primer elemento de la fila "fila" agregando los caracteres al inicio del primer elemento "linea" de la fila.
void modifyRow (TFila &fila, Cadena caracteres);
                                                                      	