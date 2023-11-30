/* 1111111 */ // sustituiir con los 7 dígitos de la cédula
#include "../include/archivo.h"
#include "../include/fila.h"
#include "../include/linea.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TEXTO_MAX 64    // Texto de hasta 64 letras mas uno para character nulo (\0).


// Estructura para archivo.
struct _rep_archivo {
  char nombreArchivo[16];			// Array que contiene nombre.
  char extensionArchivo[4];			// Array que contiene extension.
  TFila filas;						// Puntero a la primer fila.
  int cant_fila;     				// Cantidad de filas.
  int cant_letras;   				// Cantidad de chars.
  bool escritura;					// Permiso escritura.
};

//Crea un archivo vacío con nombre nombreArchivo, extensión extension y con permiso de lectura/escritura
//El archivo no contiene filas.
TArchivo createEmptyFile (Cadena nombreArchivo, Cadena extension)
{
  	TArchivo nuevoArchivo = new _rep_archivo ();                       // Creo el nuevo nodo.
  	nuevoArchivo->filas = NULL;											// Seteo sus valores.
  	nuevoArchivo->cant_fila = 0;
  	nuevoArchivo->cant_letras = 0;
  	strcpy (nuevoArchivo->nombreArchivo, nombreArchivo);
  	nuevoArchivo->escritura = true;
	strcpy (nuevoArchivo->extensionArchivo, extension);
	return nuevoArchivo;												// Retorno su puntero.
}

//Retorna un puntero a un array con el nombre del archivo "archivo"
char * getFileName (TArchivo archivo)
{
	char nombre[20];                                           			// Inicializo un array para el nombre + extension.        
  	strcpy(nombre, archivo->nombreArchivo);								// Copio el nombre en el array.
  	int longitud = strlen(nombre);										// Guardo el tamño del nombre.
  	nombre[longitud] = '.';												// En la posisicion del character nulo (\0) (posicion = tamaño total del arreglo) coloco el punto para la extension.
   	nombre[longitud + 1] = '\0';										// En la nueva posicion final coloco el character nulo. (longitud + 1).
  	strcat(nombre, archivo->extensionArchivo);							// Concateno arreglo nombre (nombre + . ) con nuestra extension.
  	char *resultado = strdup(nombre);									// Hago la copia en una cadena de chars para retornarlo.
  	
  	
  	
  return resultado;														// Retorno la cadena de chars.
} 

//Retorna true si archivo tiene permiso de escritura
bool haveWritePermission (TArchivo archivo){
  return (archivo->escritura == true);                                 // Retorno true si tiene permiso false si no los tiene.
}

//retorna true si archivo no tiene filas;
bool isEmptyFile (TArchivo archivo){
  return (archivo->filas == NULL);										//  Retorno true si el puntero a la primer fila es NULL, false si no es NULL.
}




//Retorna retorna un puntero a la linea de la primer fila del archivo "archivo"
TLinea getFirstRow (TArchivo archivo){                                 // Sin utilizar.
	return 0;
}	






//Retorna un puntero a la siguiente Fila de archivo
 TLinea getNextRow (TArchivo archivo){								// Sin utilizar.
 	return 0;
} 




//Retorna la cantidad de Fila que tiene el archvio "archivo"
int getCountRow (TArchivo archivo){								
  return archivo->cant_fila;									// Retorna el contador que hay para las filas en la estructura del correspondiente archivo.
}

//Retorna la cantidad de caracteres que tiene el archvio "archivo"
int getCountChars (TArchivo archivo){
  return archivo->cant_letras;									// Retorna el contador que hay para los char en la estructura del correspondiente archivo.
}

//imprime la Linea del archivo indicada por "numero_linea"
//pre-condición el archivo tiene por lo menos numero_linea de lineas
void printLineFile(TArchivo archivo, int numero_linea){			// Sin utilizar.
}	

    
void deleteCharterFile (TArchivo &archivo, int cant){	
		TFila fila = firstRowFile (archivo);						// Seteo fila a la primer fila del archivo.
		TFila inicial = NULL;										
		TLinea linea = NULL;			
if (cant >= TEXTO_MAX || cant >= archivo->cant_letras){				// Si la cantidad de chars a eliminar es mayor a el maximo texto del archivo O a la cantidad de chars que contiene el archivo =>
	cant = TEXTO_MAX;											    // La cantidad de chars a eliminar es el maximo contenido.
	deleteRows(fila);                        						// Deleteo toda la memoria de las filas del archivo (lo vacio).
	archivo->filas = NULL;											// El puntero en archivo a la primer fila ahora apunta a NULL.
	cant=0;															// La cantidad de chars por eliminar son 0.
	archivo->cant_letras=0;											// La cantidad de chars que contiene el archivo son 0.
}else{
		
while (cant!=0){													// En caso contrario mientras cant no sea 0.
	fila = firstRowFile (archivo);									// Seteo fila a la primer fila del archivo.
	inicial = fila;													// Inicial apunta a donde apunta fila.
	while (nextRow(fila) !=NULL){									// Mientras la fila siguiente no sea NULL itero.
		fila=nextRow(fila);											// Fila = fila siguiente(cuando salgo del bucle estoy en el ultimo elemento fila).
	}
		linea = headRow(fila);											// Linea = al puntero a la primera linea contenido en fila.
		if (cant >= countNodesLine(linea)){								// Si la cantidad a eliminar es mayor a la cantidad de nodos de la linea (countnodesline no cuenta la primer celda dummy).
			archivo->cant_letras -= countNodesLine(linea);				// La cantidad de letras en el archivo = la cantidad de letras en el archivo - la cantidad de nodos en la linea.
			cant -= countNodesLine(linea);								// La cantidad a eliminar = la cantidad a eliminar - la cantidad de nodos en la linea.
			deleteFirstRow (inicial);									// Deleteo toda la memoria de la ultima fila del archivo.
		}																
			else{															// Si la cantidad a eliminar es menor a la cantidad de nodos que contiene la linea de la ultima fila.																				
				deleteLastChar(linea);									// Elimino el ultimo char que esta en el ultimo nodo linea contenida en la ultima fila.				
				archivo->cant_letras--;									// Resto uno a la cantidad de letras.
				cant--;													// Resto uno a la cantidad a eliminar.
			}	
		}																// El bucle termina cuando cant = 0 (ya termine de eliminar la cantidad de chars necesaria).
	}
}


	void setName(TArchivo &archivo, Cadena nuevoNombre){					// Sin utilizar.
}	

//Cambia la extension del "archivo" por nuevoNombre
void setExtension(TArchivo &archivo, Cadena nuevaExtension){			// Sin utilizar.
}	

//Inserta el texto "texto" como una nueva fila al comienzo del archivo 
//Inserta el texto "texto" como una nueva fila al comienzo del archivo 
void insertChartsNewRow(TArchivo &archivo, Cadena texto){
insertRow (archivo->filas);											// Inserto una nueva Fila al inicio (ya que es pasaje por referencia el puntero de la estructura archivo a la primer fila se actualiza).
size_t contador = 0;												// Inicializo contador en 0.
TFila fila = firstRowFile (archivo);								// Seteo fila a la primer fila del archivo.
TLinea linea = headRow(fila);										// Linea = al puntero a la primera linea contenido en fila.
size_t tam=strlen(texto);											// Almaceno en tam el tamaño del texto a insertar.
int iter;															// Declaro un int iterador.
	if (tam==TEXTO_MAX){											// Filtro por tamaños, Si el tamaño es igual a la cantidad maxima del archivo.
		tam--;														// Resto uno al tamaño del texto (para no contar el ultimo character nulo (\0).
		iter = tam;													// Igualo iter a tamaño.
	}else															// En caso contrario.
		if (tam > TEXTO_MAX){										// Si el tamaño del texto a insertar es mayor a la capacidad del archivo.
			tam = TEXTO_MAX;										// Tam = capacidad del archivo (acoto el texto desde el char 0 hasta la posicion del char = a la capacidad de tecto  (en este caso 64)).
			iter = tam;												// Iter = tam.
	}else{															// En caso contrario (el tamaño es menor a la capacidad del archivo).
		tam--;														// Resto uno al tamaño del texto (para no contar el ultimo character nulo (\0).
		iter = tam;													// Iter = tam.
	}
	
	if(archivo->cant_letras + tam > TEXTO_MAX)						// Si la cantidad de letras a insertar mas la cantidad de letras ya insertadas superan la capacidad del archivo.
		deleteCharterFile(archivo, ((archivo->cant_letras + tam) - TEXTO_MAX));		// Elimino la cantidad de letras necesarias para insertar la cantidad de letras contenidas en tam.		                                       
	while(contador!=tam){    										// Bucle para insertar todo el texto.
		insertCharLine(texto[iter], linea);							// Inserto el ultimo char como una primera linea (al insertar como primera linea el primero en insertarse va a ser el ultimo en la cola).
		contador++;													// Incremento el contador.
		archivo->cant_letras++;										// Incremento el contador de chars del archivo.
		iter--;														// Decremento el iterador.
		} 
	}
  	
	
	

//pre-condicion El archivo tiene por lo menos una fila
//Inserta el texto "texto" al inicio de la primer fila del archivo
void insertChartsFirstRow(TArchivo &archivo, Cadena texto){	
	size_t tam=strlen(texto);											// Almaceno en tam el tamaño del texto a insertar.
	TFila fila = firstRowFile (archivo);								// Seteo fila a la primer fila del archivo.
	TLinea linea = headRow(fila);										// Linea = al puntero a la primera linea contenido en fila.
	int iter;															// Declaro un int iterador.
	if (tam==TEXTO_MAX){												// Filtro por tamaños, Si el tamaño es igual a la cantidad maxima del archivo.
		tam--;															// Resto uno al tamaño del texto (para no contar el ultimo character nulo (\0).
		iter = tam;														// Igualo iter a tamaño.
	}else																// En caso contrario.
		if (tam > TEXTO_MAX){											// Si el tamaño del texto a insertar es mayor a la capacidad del archivo.
			tam = TEXTO_MAX;											// Tam = capacidad del archivo (acoto el texto desde el char 0 hasta la posicion del char = a la capacidad de tecto  (en este caso 64)).
			iter = tam;													// Iter = tam.
	}else{																// En caso contrario (el tamaño es menor a la capacidad del archivo).
		tam--;															// Resto uno al tamaño del texto (para no contar el ultimo character nulo (\0).
		iter = tam;														// Iter = tam.
	}
										
		if (tam == TEXTO_MAX && fila!=NULL){ 							// Si el tamaño del texto a insertar es igual a la capacidad maxima del archivo y el archivo no esta vacio.		
			deleteRows(fila);                        					// Deleteo toda la memoria de las filas del archivo.
			archivo->filas = NULL;										// El puntero en archivo a la primer fila ahora apunta a NULL.
			archivo->cant_letras=0;										// Seteo la cantidad de letras del archvio a 0.
			insertChartsNewRow(archivo, texto);							// Inserto el texto como una nueva primera fila.
	} 													
		else if (tam == TEXTO_MAX)										// Caso contrario si el tamaño del texto a insertar es igual a la capacidad del archivo y el archivo esta vacio (no tiene filas).
			insertChartsNewRow(archivo, texto);							// Inserto el texto como una nueva fila.
		else{															// Caso contrario (el tamaño del texto no es igual a la capacidad del archivo).									
		if (tam + archivo->cant_letras > TEXTO_MAX) 					// Si el tamaño del texto mas la cantidad de letras ya almacenadas es mayor a la capacidad del archivo.
			deleteCharterFile (archivo, ((archivo->cant_letras + tam) - TEXTO_MAX));	// Deleteo la cantidad de chars necesarias para que la cantidad de chars almacenada en tam entren en la capacidad dela rchivo.	
			
		while(iter!=0){    												// Bucle para insertar el texto
			insertCharLine(texto[iter], linea);							// Inserto el ultimo char como una primera linea (al insertar como primera linea el primero en insertarse va a ser el ultimo en la cola).												// Incremento el contador.
			archivo->cant_letras++;										// Incremento el contador de chars del archivo.
			iter--;														// Decremento el iterador.
		} 
	} 
}    						                                               									
		

//si valor == true se le asigna el permiso de escritura de "archivo"
//si valor == false se le quita el permiso de escritura de "archivo"
//pre-condicion archivo !=NULL
void setWritePermission(TArchivo &archivo, bool valor) {
    archivo->escritura = valor;											// Cambio el permiso de escritura del archivo al booleano correnspondiente (true o false).
}

//elimina toda la memoria utilizada por "archivo"
void destroyFile(TArchivo & archivo) {
    deleteRows(archivo->filas);											// Elimino la memoria de Fila, lo cual elimina la memoria de linea.
    delete archivo;														// Luego elimino el archivo.
}


//Retorna retorna un puntero a la primer fila del archivo "archivo"
TFila firstRowFile (TArchivo archivo){
	return archivo->filas;												// Retorno el puntero a la primer fila del archivo.
}	


