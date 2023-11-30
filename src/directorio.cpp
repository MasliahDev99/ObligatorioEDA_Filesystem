/* 1111111 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/linea.h"
#include "../include/fila.h"
#include "../include/directorio.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



// Estructura para lista enlazada con punteros a archivos.

struct lista_archivos {
    TArchivo archivo;
    lista_archivos*sig;
};
typedef struct lista_archivos *TLista;
// Estructura para directorio.

struct _rep_directorio {
    char nombreDirectorio[15];
    TLista primer_arch;
    _rep_directorio *ph; // primero  directorio hijo
    _rep_directorio *sh; // siguiente  directorio hermano
    _rep_directorio *pad; // puntero  directorio padre]
    _rep_directorio *ant;
    Cadena ruta;
    int cant_Archivos;
};


TDirectorio RAIZ = NULL;


//Crea el directorio de nombre Raíz del filesystem 

TDirectorio createRootDirectory() {
    RAIZ = new _rep_directorio; // Creo un nodo de directorio.
    strcpy(RAIZ->nombreDirectorio, "RAIZ"); // Le asigno el nombre RAIZ.
    RAIZ->primer_arch = NULL; // No contiene archivos.
    RAIZ->ph = NULL; // nuevo 
    RAIZ->sh = NULL; // nuevo
    RAIZ->pad = NULL; // nuevo 
    RAIZ->ant = NULL;
    RAIZ->ruta = new char[strlen(RAIZ->nombreDirectorio)];
    strcpy(RAIZ->ruta, "RAIZ");
    RAIZ->cant_Archivos = 0;
    
    return RAIZ; // Retorno un puntero de tipo TDirectorio al nodo.
}

//retorna true si el directorio "directorio" no tiene archivos

bool isEmptyDirectory(TDirectorio directorio) {
    return (directorio->primer_arch == NULL); // Si no tiene archivos retorno true si no false.
}

//retorna true si el archivo de nombre "nombreArchivo existe en el directorio "directorio"

bool existFileDirectory(TDirectorio directorio, Cadena nombreArchivo) {
    if (isEmptyDirectory(directorio)) // Si el directorio esta vacio retorno false.
        return false;
    else {
        TLista archivo_Actual = directorio->primer_arch; // Inicializo puntero de tipo TLista apuntando al primer nodo de la lista.
        while (archivo_Actual != NULL) { // Recorro la lista hasta el final (NULL).
            if (strcmp(getFileName(archivo_Actual->archivo), nombreArchivo) == 0) // Si el nombre + extension coinciden con el nombre + extension a buscar.
                return true; // Retorno true (el archivo existe).
            else
                archivo_Actual = archivo_Actual->sig; // En caso contrario avanzo al siguiente nodo.
        }
    }
    return false; // Si termina el while significa que no encontramos el archivo => retorno true.
}

//pre-condicion existe el archivo de nombre nombreArchivo en el directorio "directorio"
//pos-condicion: retorna un puntero al archivo de nombre "nombreArchivo"

TArchivo getFileDirectory(TDirectorio directorio, Cadena nombreArchivo) {
    TLista archivo_Actual = directorio->primer_arch; // Inicializo puntero de tipo TLista apuntando al primer nodo de la lista.
    while (archivo_Actual != NULL) { // Recorro la lista hasta el final (NULL).
        if (strcmp(getFileName(archivo_Actual->archivo), nombreArchivo) == 0) // Si el nombre + extension coinciden con el nombre + extension a buscar.
            return archivo_Actual->archivo; // Retorno el puntero al archivo encontrado.
        else
            archivo_Actual = archivo_Actual->sig; // En caso contrario avanzo al siguiente nodo.
    }
    return NULL; // Nunca retorna NULL ya que el archivo existe (pre-condicion), pero es necesario para que compile.
}




//pre-condicion: No existe en directorio un archivo de nombre "nombreArchivo"
//crea un archivo vacio con nombre nombreArchivo y permiso de lectura/escritura

void createFileInDirectory(TDirectorio& directorio, Cadena nombreArchivo) { //
    char nombre[16]; // Arreglo para almacenar el nombre (máximo 15 caracteres).    
    char extension[4]; // Arreglo para almacenar la extensión (3 caracteres + nulo).
    char def[4] = "txt"; // Arreglo para extension default (en caso que se ingrese nombre pero no extension).
    size_t i = 0, j = 0;

    if (directorio->primer_arch == NULL) {


        // Resetear memoria de los arreglos.
        memset(nombre, 0, sizeof (nombre));
        memset(extension, 0, sizeof (extension));

        // Encontrar el punto en el nombre del archivo.
        for (i = 0; nombreArchivo[i] != '.' && i < strlen(nombreArchivo); i++) {
            if (i < 15) { // Copiar los primeros 15 caracteres en el arreglo 'nombre'.
                nombre[i] = nombreArchivo[i];
            }
        }
        // Al salir del for la I contiene la posicion en el arreglo del punto (si existe un .).
        if (nombreArchivo[i] == '.' && nombreArchivo[i + 3] != '\0' && nombreArchivo[i + 2] != '\0' && nombreArchivo[i + 1] != '\0') { // En caso de existir . y las 3 posiciones siguientes no sean un caracter vacio.					
            for (j = 0, i++; nombreArchivo[i] != '\0' && j < 3; i++, j++) { // Copiar los primeros 3 caracteres después del punto en el arreglo 'extension'.
                extension[j] = nombreArchivo[i];
            }
        } else { // En caso contrario hay un punto pero no una extension o la extension es erronea porque contiene menos de 3 char.
            strcpy(extension, def); // O no existe una extension.
        } // Seteo extension default (txt).
        printf("Nombre: %s\n", nombre); // Imprimo los resultados.
        printf("Extensión: %s\n", extension);

        TLista nuevaLista = new lista_archivos; // Creo el nuevo nodo en la lista de archivos.
        nuevaLista->archivo = createEmptyFile(nombre, extension); // Le cargo sus variables correspondientes.
        nuevaLista->sig = NULL;
        directorio->primer_arch = nuevaLista;
        directorio->cant_Archivos++;

    } else {

        memset(nombre, 0, sizeof (nombre)); // Resetear memoria de los arreglos.
        memset(extension, 0, sizeof (extension));


        for (i = 0; nombreArchivo[i] != '.' && i < strlen(nombreArchivo); i++) { // Encontrar el punto en el nombre del archivo.
            if (i < 15) {
                nombre[i] = nombreArchivo[i]; // Copiar los primeros 15 caracteres en el arreglo 'nombre'.
            }
        }

        // Al salir del for la I contiene la posicion en el arreglo del punto (si existe un .).
        if (nombreArchivo[i] == '.' && nombreArchivo[i + 3] != '\0' && nombreArchivo[i + 2] != '\0' && nombreArchivo[i + 1] != '\0') { // En caso de existir . y las 3 posiciones siguientes no sean un caracter vacio.
            // Copiar los primeros 3 caracteres después del punto en el arreglo 'extension'										// Copiar los primeros 3 caracteres después del punto en el arreglo 'extension'.
            for (j = 0, i++; nombreArchivo[i] != '\0' && j < 3; i++, j++) {
                extension[j] = nombreArchivo[i];
            }
        } else { // En caso contrario hay un punto pero no una extension o la extension es erronea porque contiene menos de 3 char.
            strcpy(extension, def); // O no existe una extension.
        } // Seteo extension default (txt).
        // Imprimir los resultados																						// Imprimo los resultados.
        printf("Nombre: %s\n", nombre);
        printf("Extensión: %s\n", extension);
		
		
        TLista Aactual = directorio->primer_arch;
        TLista nuevaLista2 = new lista_archivos;
        nuevaLista2->archivo = createEmptyFile(nombre, extension);
        
		int bandera=0;
		TLista anterior = NULL;
        while (Aactual != NULL) {
        	if (bandera == 0){
        		if (strcmp(nombreArchivo, getFileName(Aactual->archivo)) < 0 ){
        			bandera=1;
        			nuevaLista2->sig = Aactual;
        			if (anterior == NULL){
        				directorio->primer_arch = nuevaLista2;
        			}else{
        					anterior->sig= nuevaLista2;
        			}
       			}	
    		}
    		anterior = Aactual;
    		Aactual = Aactual->sig;
   		}
    	if (bandera==0){
			anterior->sig = nuevaLista2;
			nuevaLista2->sig = NULL;
     	}
			
    }
        // Incremento el contador de archivos.
        directorio->cant_Archivos++;
}		
/*
        TLista Aactual = directorio->primer_arch; // Inicializo una variable TLista apuntando al primer nodo de la lista.
        while (Aactual->sig != NULL) // Recorro hasta llegar al final de la lista.
            Aactual = Aactual->sig;

        TLista nuevaLista2 = new lista_archivos; // Creo el nuevo nodo de la lista y cargo sos valores.
        nuevaLista2->archivo = createEmptyFile(nombre, extension);
        nuevaLista2->sig = NULL;
        Aactual->sig = nuevaLista2; // Enlazo.

        // Incremento el contador de archivos.
        directorio->cant_Archivos++;
    }
}
*/
//pre condicion: el archivo nombreArchivo existe en directorio
//pos-condicion: inserta una nueva fila al comienzo del archivo nombreArchivo conteniendo los chars texto

void insertTextFile(TDirectorio& directorio, Cadena nombreArchivo, Cadena texto) {
    TArchivo arch = getFileDirectory(directorio, nombreArchivo); // Inicializo variable TArchivo apuntado al nodo del archivo "archivo".
    insertChartsNewRow(arch, texto); // Inserta el texto "texto" como una nueva fila al comienzo del archivo.


}
//pre condicion: el archivo nombreArchivo existe en directorio
//pos-condicion: agrega al comienzo de la primera fila del archivo de nombre nombreArchivo los caracteres de texto
//desplazando los caracteres existentes hacia la derecha

void insertCharsFileFirstLine(TDirectorio& directorio, Cadena nombreArchivo, Cadena texto) {
    TArchivo arch = getFileDirectory(directorio, nombreArchivo); // Inicializo variable TArchivo apuntado al nodo del archivo "archivo".
    if (firstRowFile(arch) == NULL) // Si la primer fila del archivo "archivo" es NULL (no tiene filas)
        insertChartsNewRow(arch, texto); // Inserto el texto "texto" como una nueva fila al comienzo del archivo.
    else // Caso contrario.
        insertChartsFirstRow(arch, texto); // Inserto el texto "texto" al inicio de la primer fila del archivo.


}

//pre-condicion: existe el archivo de nombre "nombreArchivo" en el directorio "directorio"
//pos-condicion: elimina el archivo del directorio "directorio" y toda la memoria utilizada por este.

void deleteFileDirectory(TDirectorio& directorio, Cadena nombreArchivo) {
    TArchivo archivo_borrar = getFileDirectory(directorio, nombreArchivo); // Inicializo variable TArchivo apuntado al nodo del archivo "archivo".
    TLista iter = directorio->primer_arch; // Inicializo una variable TLista apuntando al primer nodo de la lista.
    TLista anterior = NULL; // Inicializo una variable TLista apuntando a NULL.
    while (archivo_borrar != iter->archivo) { // Mientras no encuentro el archivo a borrar en la lista.
        anterior = iter; // Guardo un puntero al anterior.
        iter = iter->sig; // Y avanzo el puntero iter en la lista.
    }
    if (anterior == NULL) // Si anterior es igual a null entonces , se borro el primer archivo .
        directorio->primer_arch = iter->sig;
    else
        anterior->sig = iter->sig;
    delete iter;
    destroyFile(archivo_borrar); // Elimino toda la memoria utilizada por "archivo".
    directorio->cant_Archivos--; // Decremento el contador de archivos en directorio.
}

//pre-condicion: existe el archivo de nombre "nombreArchivo" en el directorio "directorio"
//pos-condicion: elimina los "cantidad" caracteres finales del archivo nombreArchivo

void deleteCharsFile(TDirectorio& directorio, Cadena nombreArchivo, int cantidad) {
    TArchivo archivo_borrar = getFileDirectory(directorio, nombreArchivo); // Inicializo variable TArchivo apuntado al nodo del archivo "archivo".
    if (firstRowFile(archivo_borrar) != NULL)
        deleteCharterFile(archivo_borrar, cantidad); //Elimino los "cantidad" de caracteres finales del "archivo".


}

//pre-condicion: existe el archivo de nombre "nombreArchivo" en el directorio "directorio"
//pos-condicion: le setea el permiso de escritura al archivo de nombre nombreArchivo

void setFilePermission(TDirectorio& directorio, Cadena nombreArchivo, bool permisoEscritura) {
    TArchivo archivo = getFileDirectory(directorio, nombreArchivo); // Inicializo variable TArchivo apuntado al nodo del archivo "archivo".	
    setWritePermission(archivo, permisoEscritura); // Asigno el permiso correspondiente a "archivo" (true o false).

}

//pre-condicion: existe el archivo de nombre "nombreArchivo" en el directorio "directorio"
//pos-condicion: imprime el contenido del archivo "nombreArchivo"

void printFile(TDirectorio& directorio, Cadena nombreArchivo) {
    TFila fila = firstRowFile(getFileDirectory(directorio, nombreArchivo)); // Inicializo variable TFila apuntando a la primer fila del archivo "archivo"
    if (isEmptyRow(fila)) // Si no existe un nodo Fila (NULL), imprimo.
        printf("No posee contenido. \n");
    while (fila != NULL) { // Recorro mientras fila no sea NULL.
        TLinea linea = headRow(fila); // Actualizo la primera linea en cada iteracion de fila .
        while (linea != NULL) { // Recorro mientras la linea no sea NULL.
            printf("%c", firstCharLine(linea)); // Imprimo el character.
            linea = nextLine(linea); // Avanzo a el siguiente nodo de linea.
        }
        printf("\n"); // Cuando termino de imprimir la fila imprimo un salto de linea para la siguiente fila (si hay una)
        fila = nextRow(fila); // Avanzo al siguiente nodo de Fila.
    }
}
//pos-condicion destruye toda la memoria de directorio

void destroyDirectory(TDirectorio& directorio) {
	
		if (directorio->ph != NULL)
	    	destroyDirectory(directorio->ph);
	    	
	    if(directorio->sh != NULL)
	    	destroyDirectory(directorio->sh);
	    			
	    if (isEmptyDirectory(directorio) && directorio->ph == NULL && directorio->sh == NULL ) {
   	    	if(directorio->ant!=NULL){
	    		directorio->ant->sh = NULL;
	    	}else if (directorio!=RAIZ){
	    		directorio->pad->ph=NULL;
	    	}
	    	delete directorio;
		 }else if (directorio->sh == NULL && directorio->ph == NULL && !isEmptyDirectory(directorio)){
    			while (!isEmptyDirectory(directorio)) { // Mientras el directorio tenga archivos (no sea NULL).
        			TLista iterLista = directorio->primer_arch; // Voy iterando
        			TArchivo archivoB = iterLista->archivo;
        			deleteFileDirectory(directorio, getFileName(archivoB)); // Elimino el archivo "archivo" del directorio "directorio" y toda la memoria utilizada por este.
    			}
   	    				if(directorio->ant!=NULL){
	    					directorio->ant->sh = NULL;
	    				}
	    				else if (directorio!=RAIZ){
	    					directorio->pad->ph=NULL;
	    		}
	    	delete directorio;
		}
}


//retorna true si el directorio de nombre nombreDierctorioHijo es hijo del directorio "directorio"

bool existChildrenDirectory(TDirectorio directorio, Cadena nombreDirectorioHijo) {
    TDirectorio dirActual = directorio->ph; // creo un puntero al primer hijo de directorio
    while (dirActual != NULL) {
        if (strcmp(dirActual->nombreDirectorio, nombreDirectorioHijo) == 0) {
            return true;
        }
        dirActual = dirActual->sh;
    }
    return false;
}

//pre-condición el directorio de nombre nombreDirectorioHijo es hijo del directorio Directorio
//pos-condición retorna un puntero al directorio de nombre nombreDirectorioHijo

TDirectorio moveChildrenDirectory(TDirectorio& directorio, Cadena nombreDirectorioHijo) {
    directorio = directorio->ph;
    while (strcmp(directorio->nombreDirectorio, nombreDirectorioHijo) != 0) {
        directorio = directorio->sh;
    }
    return directorio;
}

//retorna un puntero de TDirectorio al padre del directorio directorio

TDirectorio moveFatherDirectory(TDirectorio& directorio) {
    return directorio->pad;
}


//retorna un puntero de TDirectorio al directorio ROOT

TDirectorio moveRootDirectory(TDirectorio& directorio) {
    while (directorio->pad != NULL) {
        directorio = directorio->pad;
    }
    return directorio;
}


//retorna true si el directorio directorio es root

bool isRootDirectory(TDirectorio directorio) {
    return directorio->pad == NULL;
}


//Pre-Condición del directorio de nombre nombreDirectorio no es hijo del directorio "directorio"
//pos-condición crea un directorio vacío, de nombre nombreDirectorio, hijo del directorio "directorio"

void createChildrenDirectory(TDirectorio& directorio, Cadena nombreDirectorio) {
    TDirectorio nuevodir = new _rep_directorio; // Creo un nodo de directorio.

    strcpy(nuevodir->nombreDirectorio, nombreDirectorio); // Le asigno el nombre.
    nuevodir->primer_arch = NULL; // No contiene archivos.
    nuevodir->ph = NULL;
    nuevodir->sh = NULL;
    nuevodir->ant = NULL;
    nuevodir->pad = directorio;
    
    if(directorio->pad==NULL)
    	nuevodir->ruta = new char[strlen(directorio->nombreDirectorio) + 1 + strlen(nombreDirectorio)];  // SI EL PADRE ES LA RAIZ INICIALIZO ASI (EXPLICAR)
    else 
    	nuevodir->ruta = new char[strlen(directorio->ruta) + 1 + strlen(nombreDirectorio)]; // SI EL PADRE NO ES LA RAIZ INICIALIZO ASI EXPLICAR (SI NO SE SALE DE RANGO EN LOS DIR /S) 
    	
    strcpy(nuevodir->ruta, nuevodir->pad->ruta);
    
    strcat(nuevodir->ruta, "/");
    strcat(nuevodir->ruta, nombreDirectorio);
    nuevodir->cant_Archivos = 0;

    if (directorio->ph == NULL) {
        directorio->ph = nuevodir;
       
    } else {
        TDirectorio primerhijo = directorio->ph;
		int bandera=0;
		TDirectorio ultimo;
        while (primerhijo != NULL) {
        	if (bandera == 0){
        		if (strcmp(nombreDirectorio, primerhijo->nombreDirectorio) < 0 ){
        			bandera=1;

        			nuevodir->sh = primerhijo;
        			if (primerhijo->ant!=NULL){
        				primerhijo->ant->sh = nuevodir;
					}else{
						directorio->ph = nuevodir;
					}		
        			nuevodir->ant = primerhijo->ant;
        			primerhijo->ant= nuevodir;
        		}else{
        			if (primerhijo->sh == NULL)
        				ultimo = primerhijo;
       			}
    		}
    		primerhijo = primerhijo->sh;
   		}
    	if (bandera==0){
    		nuevodir->ant = ultimo;
    		ultimo->sh = nuevodir;
    		nuevodir->sh = NULL;
     	}
    }
}

//pre-condición el directorio de nombre nombreDirectorio es hijo del directorio directorio
//pos-condición elimina el directorio de nombre nombreDirectorio que es hijo del directorio directorio
//eliminando toda su memoria

void removeChildrenDirectory(TDirectorio& directorio, Cadena nombreDirectorio) {
	
    TDirectorio origen=directorio;
    if(directorio->ph!=NULL){
    	directorio=directorio->ph;
		destroyDirectory(directorio);
	}	
	if (origen->pad->ph==origen)
		origen->pad->ph= origen->sh;
	if(origen->sh!=NULL)
		origen->sh->ant=origen->ant;
	if(origen->ant!=NULL)
		origen->ant->sh=origen->sh;
	delete origen;
}



void cambiarRutas (TDirectorio directorio) {
	delete directorio->ruta;
    directorio->ruta = new char[strlen(directorio->pad->ruta) + 1 + strlen(directorio->nombreDirectorio)];
	strcpy(directorio->ruta,directorio->pad->ruta);
	strcat(directorio->ruta,	"/");
	strcat(directorio->ruta,	directorio->nombreDirectorio);
	
	if(directorio->ph != NULL)	
		cambiarRutas(directorio->ph);
	    	
	if(directorio->sh != NULL)
	    cambiarRutas(directorio->sh);
		
}

//pre-condición el directorio origen es sub-directorio del directorio "directorio"
//pos-condición mueve el directorio origen y todo su contenido al directorio destino

void moveSubDirectory(TDirectorio& directorio, TDirectorio& origen, TDirectorio& destino) {
	int bandera2=0;
	if (existChildrenDirectory(destino, origen->nombreDirectorio)){
			Cadena directorioDestino = new char[strlen(destino->ruta) + 1 + strlen(origen->nombreDirectorio)];
			strcpy(directorioDestino,destino->ruta);
			strcat(directorioDestino,	"/");
			strcat(directorioDestino,	origen->nombreDirectorio);	
			TDirectorio destruir = directorioDestinoRuta(destino, directorioDestino);
			removeChildrenDirectory(destruir, origen->nombreDirectorio);
			delete directorioDestino;
			bandera2=1;
			printf("OK: El directorio se remplazo ");
	}
		
	if(directorio->ph == origen)	{
		directorio->ph=directorio->ph->sh;
		origen->pad = destino;
		}
		if(origen->sh!=NULL)
			origen->sh->ant=origen->ant;
		if(origen->ant!=NULL)
			origen->ant->sh=origen->sh;
		if (destino->ph==NULL){
			destino->ph=origen;
			origen->sh=NULL;
			origen->ant=NULL;	
    } else {
        TDirectorio primerhijo = destino->ph;
		int bandera=0;
		TDirectorio ultimo;
        while (primerhijo != NULL) {
        	if (bandera == 0){
        		if (strcmp(origen->nombreDirectorio, primerhijo->nombreDirectorio) < 0 ){
        			bandera=1;

        			origen->sh = primerhijo;
        			if (primerhijo->ant!=NULL){
        				primerhijo->ant->sh = origen;
					}else{
						destino->ph = origen;
					}		
        			origen->ant = primerhijo->ant;
        			primerhijo->ant= origen;
        		}else{
        			if (primerhijo->sh == NULL)
        				ultimo = primerhijo;
       			}
    		}
    		primerhijo = primerhijo->sh;
   		}
    	if (bandera==0){
    		origen->ant = ultimo;
    		ultimo->sh = origen;
    		origen->sh = NULL;
     	}
    }
	delete origen->ruta;
    origen->ruta = new char[strlen(destino->ruta) + 1 + strlen(origen->nombreDirectorio)];
	strcpy(origen->ruta,destino->ruta);
	strcat(origen->ruta,	"/");
	strcat(origen->ruta,	origen->nombreDirectorio);
	if (origen->ph!=NULL)
		cambiarRutas (origen->ph);
	if (bandera2==0)	
		printf("OK: El directorio se movio ");
}



//pre-condición el archivo origen es sub archivo del directorio directorio
//pos-condición se mueve el archivo TArchivo como hijo del directorio destino

void moveSubArchive(TDirectorio& directorio, TArchivo origen, TDirectorio destino) {
	int bandera2=0;
	if (existFileDirectory(destino, getFileName(origen))){
		TArchivo remplazar = getFileDirectory(destino, getFileName(origen));
		TLista list = destino->primer_arch;
		TLista ante=NULL;
		while(list->archivo!=remplazar){
			ante=list;
			list=list->sig;
		}
		if(ante!=NULL){
			ante->sig=list->sig;
		} else if (list->sig!=NULL){
			destino->primer_arch=list->sig;
		}else{
			destino->primer_arch=NULL;
		} 	
			delete list;
			destroyFile(remplazar);
			bandera2=1;
			printf("OK: El archivo se remplazo ");
	} 
	
	TLista lista = directorio->primer_arch;
	TLista ant= NULL;
	while (lista->archivo!= origen) {
		ant=lista;
		lista=lista->sig;
	}
	if(ant!=NULL){
		ant->sig=lista->sig;
	}else {
		directorio->primer_arch = lista->sig;
	}
		
	if(destino->primer_arch == NULL){
		destino->primer_arch= lista;
		lista->sig=NULL;
	}else{
		TLista Aactual = destino->primer_arch;
		int bandera=0;
		TLista anterior = NULL;
        while (Aactual != NULL) {
        	if (bandera == 0){
        		if (strcmp(getFileName(lista->archivo), getFileName(Aactual->archivo)) < 0 ){
        			bandera=1;
        			lista->sig = Aactual;
        			if (Aactual == destino->primer_arch)
        				destino->primer_arch= lista;
        			if(anterior!=NULL)
        				anterior->sig= lista;
        			}
       			}	
    		anterior = Aactual;
    		Aactual = Aactual->sig;
   		}
    	if (bandera==0){
			anterior->sig = lista;
			lista->sig = NULL;
     	}
	}
	if (bandera2==0){
		destino->cant_Archivos++;
		directorio->cant_Archivos--;
		printf("OK: El archivo se movio ");
	}else{
		directorio->cant_Archivos--;
	}
}		
	
//pre-condición: directorio no es el directorio ROOT
//pos-condición: retorna un puntero al primer hermano del diretorio "directorio"

TDirectorio firstBrotherDirectory(TDirectorio directorio) {
    return NULL;
}


//pos-condición: retorna un puntero al primer hijo del directorio "directorio"

TDirectorio firstChildrenDirectory(TDirectorio directorio) {
    return directorio->ph;
}


//Retorna true si el directorio subdir es sub-directorio del directorio "directorio" en cualquier nivel.

bool isSubDirectoryRoot(TDirectorio directorio, Cadena ruta) {
    size_t len1 = strlen(directorio->ruta);
    size_t len2 = strlen(ruta);

    // Verifica que la ruta2 sea más larga que la ruta1 y que las primeras partes coincidan
    if (len2 > len1 && strncmp(directorio->ruta, ruta, len1) == 0) {
        	return true;
    }
    return false;
}
/*

void printruta(TDirectorio directorio) {	
		if (directorio->pad != NULL)
	    	printruta(directorio->pad);
		printf("%s/", directorio->nombreDirectorio);				
}
*/


//pos-condición imprime el directorio ejecuando DIR

void printDirectoryDir(TDirectorio directorio) { 
	printf("%s\n",directorio->ruta);
	
  TLista archivos = directorio->primer_arch; // creo un puntero de tipo tlista al primer archivo del directorio
    while (archivos != NULL) { //
        printf("%s", getFileName(archivos->archivo));
        if (haveWritePermission(archivos->archivo)) {
            printf("     Lectura/Escritura\n");
        } else {
            printf("     Lectura\n");
        }
        archivos = archivos->sig;
    }
	directorio=directorio->ph;
       while (directorio != NULL) {
    	printf("%s\n", directorio->nombreDirectorio);
        directorio = directorio->sh;
    }
    
  }  
  
Cadena getruta(TDirectorio directorio){ 
	return directorio->ruta;
}  

void recursionaux(TDirectorio directorio){
		if (directorio!=NULL){
		TLista archivos = directorio->primer_arch;
			printf("%s \n",directorio->ruta);
		if(directorio->primer_arch!=NULL){
			while(archivos!=NULL){
				printf("%s ",directorio->ruta);
				printf("%s \n",getFileName(archivos->archivo));
				archivos = archivos->sig;	
			}	
		}	
		if(directorio->ph != NULL)	
	    	recursionaux(directorio->ph);
	    	
	    if(directorio->sh != NULL)
	    		recursionaux(directorio->sh);
	    
	}    
}    
	
void printDirectoryDirS(TDirectorio directorio){
		TLista archivos = directorio->primer_arch;
			printf("%s \n",directorio->ruta);
		if(directorio->primer_arch!=NULL){
			while(archivos!=NULL){
				printf("%s ",directorio->ruta);
				printf("%s \n",getFileName(archivos->archivo));
				archivos = archivos->sig;	
		}	
	} 	 	
	recursionaux(directorio->ph);	
}

//pos-condición retorna un puntero TDirectorio de la ruta DirectorioDestino
TDirectorio directorioDestinoRuta(TDirectorio directorio, Cadena directorioDestino) {
    if (strcmp(directorio->ruta, directorioDestino) == 0)
        return directorio;

    TDirectorio resultado = NULL;

    if (directorio->ph != NULL)
        resultado = directorioDestinoRuta(directorio->ph, directorioDestino);

    if (resultado == NULL && directorio->sh != NULL)
        resultado = directorioDestinoRuta(directorio->sh, directorioDestino);

    return resultado;
}

Cadena getdirectoryname(TDirectorio directorio){
	return directorio->nombreDirectorio;
	}

