/* 1111111 */ // sustituiir con los 7 dígitos de la cédula
/*
 Modulo que implemente el archivo linea.h
 
 */

#include "../include/linea.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Estructura para la lista enlazada de linea.
struct _rep_linea {
    char caracter;
    _rep_linea *sig;
};


//Pos-condicion: Crea una linea vacía
TLinea createLine (){
	TLinea	nuevaLinea = new _rep_linea;			// Creo un nuevo nodo linea.
        nuevaLinea->caracter='\0';					// Cargo los valores nulos.
        nuevaLinea->sig=NULL;
    return nuevaLinea;								// Retorno el puntero al nuevo nodo linea.
    }

//pos-condicion: Retorna true si la linea "linea" es vacia
bool isEmptyLine (TLinea linea){
	return (linea->caracter == '\0');					// Si el nodo linea es vacio retorno true.
 }
//pre-condicion: linea != NULL
//Inserta el caracter letra al inicio de la linea.
void insertCharLine(char letra, TLinea& linea){			 
		TLinea aux = linea;								// Inicializo variable TLinea apuntando a "linea".
		aux = createLine ();							// Creo una nueva linea vacia.
		aux->caracter = letra;							// Cargo su letra correspondiente.
		if(linea->sig==NULL)							// Si es el primer nodo insertado => el nuevo nodo es el ultimo elemento de la lista (ya que inserto por el inicio) => aux->sig = NULL.
			aux->sig = NULL;
		else											// En caso contrario.
			aux->sig = linea->sig;						// El puntero al siguiente nodo del nuevonodo apunta al nodo que apunta la celda dummy.
		linea->sig = aux;								// El puntero de la celda dummy se actualiza al nuevo primer nodo.
	}
	
//pre-condición linea != NULL
//Retorna el primer caracter de la linea "linea"
char firstCharLine(TLinea linea){
	return linea->caracter;								// Retorno el primer caracter de la linea "linea".
}	


//Retorna la cantidad de elementos que tiene la linea "linea"
int countNodesLine(TLinea linea) {						// Cuenta los caracteres sin contar "\0" (character nulo (hay un char nulo al principio de la lista y otro al final)).
    int contador = 0;
    while (linea != NULL) {								// Mientras la linea no sea NULL recorro.
        char pl = firstCharLine(linea); 				// Almaceno en pl la primera letra de linea.
        if (pl != '\0')									// Si no es caracter nulo incremento contador.
            contador++;
        linea = nextLine(linea);						// Avanzo al siguiente nodo de linea.
    }
    return contador;									// Retorno la cantidad de chars que tiene la linea.
}


//pre-condicion linea !=NULL
//Retorna un puntero a al siguiente nodo de "linea"
TLinea nextLine(TLinea linea){
	return linea->sig;								// Retorno el puntero al siguiente nodo de la linea "linea".
		}
		

//pre-condicion: linea != NULL
//pos-condicion: Elimina el primer nodo de la linea "linea"
void deleteFirstChar(TLinea& linea);							// No utilizada.

//pre-condicion: linea != NULL
//pos-condicion: Elimina el ultimo nodo de la linea "linea"
void deleteLastChar(TLinea& linea) {							
    if (linea->sig == NULL) {										// Si el siguiente nodo de la linea es NULL.
        delete linea;												// Lo elimino.
        linea = NULL;
    } else {														// Caso contrario recorro hasta llegar al ultimo.
        TLinea ant = NULL;
        while (linea->sig != NULL) {
            ant = linea; 											// Guardo un puntero al anterior (para actualizar su puntero al siguiente luego de elinarlo) y recorro.
            linea = linea->sig;
        }
        delete linea;												// Elimino linea.
        linea = NULL;
        ant->sig = NULL;

    }
}
//Pos-condicion: Destruye toda la memoria utilizada por linea

void destroyLine(TLinea& linea) {
    while (linea != NULL) {										// Mientras la linea no sea NULL recorro.
        TLinea tmp = linea;										// Inicializo variable TLinea apuntando a linea "linea".
        linea = linea->sig;										// Avanzo en la lista linea.
        delete tmp;												// Elimino el nodo anterior.
    }

}