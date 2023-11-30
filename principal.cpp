


// 4904954-8 Masliah Felipe
// 5251766-1 Pirotto Franco



/*
Módulo principal de la tarea 1.FILE SYSTEM

Intérprete de comandos para probar los módulos.

  Laboratorio de EDA 2023
  UTU - LATU - Turno Nocturno 
  Profesor Ferando Arrieta
 */

#include "include/archivo.h"
#include "include/linea.h"
#include "include/fila.h"
#include "include/directorio.h"
#include "include/utils.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cstddef>
#include <limits.h>
#define MAX_PALABRA 65 // TEXTO DE HASTA 64 LETRAS MAS UNO PARA CARACTER NULO    \0
#define MAX_LINEA 256
#define MAX_RUTA 256
#define MAX_PARAMETRO 10
#define MAX_PARAMETRODIR 1
#define MAX_COMANDO 10
#define MAX_NOMBRE 19
#define MAX_EXTENSION 3
#define TEXTO_MAX 50

enum _retorno {
    OK, ERROR, NO_IMPLEMENTADA
};
typedef enum _retorno TipoRet;
typedef char* Cadena;


TipoRet CREARSISTEMA(TDirectorio &s);
TipoRet CREATE(TDirectorio &sistema, char *nombreArchivo);
TipoRet DELETE(TDirectorio &sistema, char *nombreArchivo);
TipoRet ATTRIB(TDirectorio &sistema, char *nombreArchivo, char* parametro);
TipoRet IF(TDirectorio &sistema, char *nombreArchivo, char* texto);
TipoRet IN(TDirectorio &sistema, char *nombreArchivo, char* texto);
TipoRet DF(TDirectorio &sistema, char *nombreArchivo, int cantidad);
TipoRet TYPE(TDirectorio &sistema, char *nombreArchivo);
TipoRet DESTRUIRSISTEMA(TDirectorio &sistema);

//              directorios
TipoRet CD(TDirectorio &sistema, Cadena nombreDirectorio);
TipoRet MKDIR(TDirectorio &sistema, Cadena nombreDirectorio);
TipoRet RMDIR(TDirectorio &sistema, Cadena nombreDirectorio);
TipoRet DIR (TDirectorio &sistema, Cadena parametro);
TipoRet MOVE (TDirectorio &sistema, Cadena nombre, Cadena directorioDestino);

bool sistemaInicializado = false;
TDirectorio raiz;


// programa principal

int main() {
    char restoLinea[MAX_LINEA + 1];
    char comando[MAX_PALABRA];
    char parametro[MAX_PALABRA];
    char texto[MAX_PALABRA];
    char nombrearchivo[MAX_NOMBRE];
    char nombreDirectorio[15];
    char directorioDestino[MAX_RUTA];
    long int cantidad;
    //char parametro;
    TDirectorio sistema;
    bool salir = false;


    while (!salir) {
        printf("#");
        // leer el comando
        memset(parametro, 0, sizeof(parametro));
        memset(comando, 0, sizeof(comando));
        memset(texto, 0, sizeof(texto));
        memset(nombreDirectorio, 0, sizeof(nombreDirectorio));
        memset(nombrearchivo, 0, sizeof(nombrearchivo));
        memset(directorioDestino, 0, sizeof(directorioDestino));
        leerChars(comando);
        if (!strcmp(comando, "ATTRIB")) {
            leerChars(nombrearchivo);
            leerChars(parametro);
        } else if (!strcmp(comando, "CREATEFILE"))
            leerChars(nombrearchivo);

        else if (!strcmp(comando, "DELETE"))
            leerChars(nombrearchivo);

        else if (!strcmp(comando, "IF")) {
            leerChars(nombrearchivo);
            leerRestoLinea(texto);
        } else if (!strcmp(comando, "IN")) {
            leerChars(nombrearchivo);
            leerRestoLinea(texto);
        } else if (!strcmp(comando, "TYPE")) {
            leerChars(nombrearchivo);
        } else if (!strcmp(comando, "DF")) {
            leerChars(nombrearchivo);
        while (1) {
        if (scanf("%ld", &cantidad) == 1) {
            if (cantidad <= INT_MAX) {
                break;  // Salir del bucle si la entrada es válida
            } else {
                printf("Error: El valor ingresado es mayor que INT_MAX (%d)\n", INT_MAX);
            }
        } else {
            printf("Error: Entrada no válida. \nIngrese un valor entero válido: ");
            // Limpiar el búfer de entrada para evitar problemas con entradas futuras
            while (getchar() != '\n');
        }
    }
        }else if (!strcmp(comando, "MKDIR")) {
            leerChars(nombreDirectorio);
            nombreDirectorio[15] = '\0'; 						// Corto el arreglo a 15 char (no se porque pero en el archivo entregado por profesor se pueden guardar n chars en un arreglo acotado) asi que lo corto a mano.
    		strncpy(nombreDirectorio, nombreDirectorio, 15);

        } else if (!strcmp(comando, "CD")) {
            leerChars(nombreDirectorio);
            nombreDirectorio[15] = '\0'; 						// Corto el arreglo a 15 char (no se porque pero en el archivo entregado por profesor se pueden guardar n chars en un arreglo acotado) asi que lo corto a mano.
            
    		strncpy(nombreDirectorio, nombreDirectorio, 15);
        } else if (!strcmp(comando, "RMDIR")) { // 20:16
            leerChars(nombreDirectorio);
            nombreDirectorio[15] = '\0'; 						// Corto el arreglo a 15 char (no se porque pero en el archivo entregado por profesor se pueden guardar n chars en un arreglo acotado) asi que lo corto a mano.
    		strncpy(nombreDirectorio, nombreDirectorio, 15);
        } else if (!strcmp(comando, "DIR")) {
            leerRestoLinea(parametro);
            
        } else if (!strcmp(comando, "MOVE")) {
            leerChars(nombreDirectorio);
            nombreDirectorio[19] = '\0'; 						// Corto el arreglo a 15 char (no se porque pero en el archivo entregado por profesor se pueden guardar n chars en un arreglo acotado) asi que lo corto a mano.
    		strncpy(nombreDirectorio, nombreDirectorio, 19);
    		leerChars(directorioDestino);
		}


        // *********************** Procesamiento de comandos ***********************************


        if (0 == strcmp(comando, "CREARSISTEMA")) {
            if (!sistemaInicializado) {
                TipoRet salida = CREARSISTEMA(sistema);
                if (salida == OK) {
                    sistemaInicializado = true;
                    printf("*** SYSTEM INICIALIZED ***\n");
                    printf("OK\n");
                }
            } else
                printf("EL SISTEMA YA FUE INICIALIZADO\n");
            printf("\n--------------------------------------\n");
        } else if (0 == strcmp(comando, "CREATEFILE")) {
        	if (nombrearchivo[0] !='\0'){
            	TipoRet salida = CREATE(sistema, nombrearchivo);
            	if (salida == OK)
               		 printf("OK: El archivo se creo exitosamente. \n");
            	else if (salida == NO_IMPLEMENTADA)
                	printf("NO_IMPLEMENTADA\n");
                	
            	printf("\n--------------------------------------\n");
            	 
    		 }else { 
    		 	printf("ERROR: No se ingreso un nombre.");
            	printf("\n--------------------------------------\n");
             }
        } else if (0 == strcmp(comando, "DELETE")) {
        	if (nombrearchivo[0] !='\0'){
            	TipoRet salida = DELETE(sistema, nombrearchivo);
            	if (salida == OK)
                	printf("OK: El archivo se elimino exitosamente. \n");
            	else if (salida == NO_IMPLEMENTADA)
                	printf("NO_IMPLEMENTADA\n");
                	
            	printf("\n--------------------------------------\n");
            	 
            }else {
            	printf("ERROR: No se ingreso un nombre.");
            	printf("\n--------------------------------------\n");
             }
        } else if (0 == strcmp(comando, "ATTRIB")) {
        	if (nombrearchivo[0] !='\0'){
        		if (parametro[0] !='\0'){
            		TipoRet salida = ATTRIB(sistema, nombrearchivo, parametro);
            		if (salida == OK)
                		printf("OK: El permiso fue modificado exitosamente. \n");
            		else if (salida == NO_IMPLEMENTADA)
               	 		printf("NO_IMPLEMENTADA\n");
               	 		
            		printf("\n--------------------------------------\n");
            		
            	}else{
            		printf("ERROR: No se ingreso un parametro.");
            		printf("\n--------------------------------------\n");
            	 }
            }else {
            	printf("ERROR: No se ingreso un nombre.");
            	printf("\n--------------------------------------\n");
             }
        } else if (0 == strcmp(comando, "IF")) {
        	if (nombrearchivo[0] !='\0'){
        		if (texto[0] !='\0'){
            		TipoRet salida = IF(sistema, nombrearchivo, texto);
            		if (salida == OK)
                		printf("OK: El texto se inserto exitosamente. \n");
            		else if (salida == NO_IMPLEMENTADA)
                		printf("NO_IMPLEMENTADA\n");
                		
            		printf("\n--------------------------------------\n");
            		 
            	}else{
            		printf("ERROR: No se ingreso un texto.");
            		printf("\n--------------------------------------\n");
            	 }
             }else {
            	printf("ERROR: No se ingreso un nombre.");
            	printf("\n--------------------------------------\n");
             } 		
        } else if (0 == strcmp(comando, "IN")) {
        	if (nombrearchivo[0] !='\0'){
        		if (texto[0] !='\0'){
            	TipoRet salida = IN(sistema, nombrearchivo, texto);
            	if (salida == OK){
                	printf("OK: El texto se inserto exitosamente. \n");
            	}else if (salida == NO_IMPLEMENTADA){
                	printf("NO_IMPLEMENTADA\n");
                }	
           	 	printf("\n--------------------------------------\n");
           	 	
            	}else{
            		printf("ERROR: No se ingreso un texto.");
            		printf("\n--------------------------------------\n");
            	 }
             }else {
            	printf("ERROR: No se ingreso un nombre.");
            	printf("\n--------------------------------------\n");
             } 		
        } else if (0 == strcmp(comando, "DF")) {
        	if (nombrearchivo[0] !='\0'){
            	TipoRet salida = DF(sistema, nombrearchivo, cantidad);
            	if (salida == OK)
                	printf("OK: Los characteres fueron eliminados exitosamente\n");
            	else if (salida == NO_IMPLEMENTADA)
                	printf("NO_IMPLEMENTADA\n");
                	
            	printf("\n--------------------------------------\n");
            	 
             }else {
            	printf("ERROR: No se ingreso un nombre.");
            	printf("\n--------------------------------------\n");
             } 		
        } else if (0 == strcmp(comando, "TYPE")) {
        	if (nombrearchivo[0] !='\0'){
            	TipoRet salida = TYPE(sistema, nombrearchivo);
           		if (salida == OK)
               	 	printf("OK\n");
            	else if (salida == NO_IMPLEMENTADA)
                	printf("NO_IMPLEMENTADA\n");
                	
            	printf("\n--------------------------------------\n");

             }else {
            	printf("ERROR: No se ingreso un nombre.");
            	printf("\n--------------------------------------\n");
             } 		
        } else if (0 == strcmp(comando, "DESTRUIRSISTEMA")) {
            TipoRet salida = DESTRUIRSISTEMA(sistema);
            if (salida == OK) {
                sistemaInicializado = false;
                printf("OK: El sistema ha sido eliminado exitosamente\n");
            } else if (salida == NO_IMPLEMENTADA)
                printf("NO_IMPLEMENTADA\n");
                
            printf("\n--------------------------------------\n");

        } else if (0 == strcmp(comando, "MKDIR")) {
        	if (nombreDirectorio[0] !='\0'){
            	TipoRet salida = MKDIR(sistema, nombreDirectorio);
            	if (salida == OK)
                	printf("OK: El directorio se agrego  exitosamente. \n");
            	else if (salida == NO_IMPLEMENTADA) 
                	printf("NO_IMPLEMENTADA\n");
                	
            	printf("\n--------------------------------------\n");
				
             }else {
            	printf("ERROR: No se ingreso un nombre.");
            	printf("\n--------------------------------------\n");
             } 		
        } else if (0 == strcmp(comando, "CD")) {
        	if (nombreDirectorio[0] !='\0'){
            	TipoRet salida = CD(sistema, nombreDirectorio);
            	if (salida == OK)
                	printf("OK: Desplazado correctamente. \n");
            	else if (salida == NO_IMPLEMENTADA) 
            	    printf("NO_IMPLEMENTADA\n");
            	    
            	printf("\n--------------------------------------\n");
            	
             }else {
            	printf("ERROR: No se ingreso un nombre.");
            	printf("\n--------------------------------------\n");
             } 		
        } else if (0 == strcmp(comando, "RMDIR")) {
        	if (nombreDirectorio[0] !='\0'){
            	TipoRet salida = RMDIR(sistema, nombreDirectorio);
            	if (salida == OK)
                	printf("OK: El directorio se elimino  exitosamente. \n");
            	else if (salida == NO_IMPLEMENTADA) 
                	printf("NO_IMPLEMENTADA\n");
                	
            	printf("\n--------------------------------------\n");

             }else {
            	printf("ERROR: No se ingreso un nombre.");
            	printf("\n--------------------------------------\n");
             } 		
        }else if (0 == strcmp(comando, "DIR")) {
        	if ( strcmp(parametro, " /S")==0 || parametro[0] == '\0'){
            	TipoRet salida = DIR(sistema, parametro);
           		 if (salida == OK)
                	printf("OK.\n");
            	else if (salida == NO_IMPLEMENTADA)
                	printf("NO_IMPLEMENTADA\n");
                	
            	printf("\n--------------------------------------\n");
			}else  {
				printf("Parametro no valido.\n");
				printf("\n--------------------------------------\n");
			}
        }else if (0 == strcmp(comando, "MOVE")) {
        	if (nombreDirectorio[0] !='\0'){
        		if (directorioDestino[0] !='\0'){
            		TipoRet salida = MOVE (sistema, nombreDirectorio, directorioDestino);
            		if (salida == OK)
                		printf("con exito.\n");
            		else if (salida == NO_IMPLEMENTADA)
                		printf("NO_IMPLEMENTADA\n");
             	}else {
            		printf("ERROR: No se ingreso una ruta.");
             	} 		
             }else {
            	printf("ERROR: No se ingreso un nombre.");
             }
			 printf("\n--------------------------------------\n"); 	
        }
        
        
        else{
            printf("Comando no reconocido.\n");
			printf("\n--------------------------------------\n");
		}
        fgets(restoLinea, MAX_LINEA + 1, stdin);
    } // while

    return 0;
} // main



//****************************** Funciones a implementar ************************************

TipoRet CREARSISTEMA(TDirectorio &sistema) {

    sistema = createRootDirectory();
    raiz=sistema;
    return OK;
}

TipoRet CREATE(TDirectorio &sistema, Cadena nombreArchivo) {
    if (sistemaInicializado) { // Si el sistema esta inicializado continuo caso contrario retorno error "sistema no inicializado".
        if (existFileDirectory(sistema, nombreArchivo)) { // Si ya existe el archivo en el directorio retorno error.
            printf("ERROR: Ya existe un archivo con el nombre ingresado. \n");
            return ERROR;
        } else { // Si no existe el archivo y el sistema esta inicializado.
            createFileInDirectory(sistema, nombreArchivo); // Creo el nuevo archivo.
            return OK;
        }
    } else {
        printf("Sistema no inicializado.\n");
        return ERROR;
    }


    return NO_IMPLEMENTADA;
}

TipoRet DELETE(TDirectorio &sistema, Cadena nombreArchivo) {
    if (sistemaInicializado) { // Si el sistema esta inicializado continuo caso contrario retorno error "sistema no inicializado".
        if (existFileDirectory(sistema, nombreArchivo) && haveWritePermission(getFileDirectory(sistema, nombreArchivo))) { // Si existe el archivo en el directorio y tiene permiso de escritura.
            deleteFileDirectory(sistema, nombreArchivo); // Elimino el archivo del directorio.
            return OK;
        } else {
            if (!existFileDirectory(sistema, nombreArchivo)) // Si no existe	el archivo en el directorio.
                printf("ERROR: No existe el archivo. \n"); // Imprimo mensaje de error correspondiente.
            else
                printf("ERROR: El archivo solo tiene permiso de lectura. \n"); // En caso contrario no tiene permiso de Escritura.
            return ERROR;
        }
    } else {
        printf("Sistema no inicializado.\n");
        return ERROR;
    }

    return NO_IMPLEMENTADA;
}

TipoRet ATTRIB(TDirectorio &sistema, Cadena nombreArchivo, Cadena parametro) {
    if (sistemaInicializado) { // Si el sistema esta inicializado continuo caso contrario retorno error "sistema no inicializado".
        if (existFileDirectory(sistema, nombreArchivo)) { // Si existe el archivo en el directorio.		
            if (strcmp(parametro, "+w") == 0 || strcmp(parametro, "+W") == 0) { // Si el paramentro ingresado es +W o +w.
                setFilePermission(sistema, nombreArchivo, true); // Seteo el permiso de escritura en true.
                return OK;
            } else if (strcmp(parametro, "-w") == 0 || strcmp(parametro, "-W") == 0) { // Si el parametro ingresado es -W o -w.
                setFilePermission(sistema, nombreArchivo, false); // Seteo el permiso de escritura en false.
                return OK;
            }
            printf("ERROR: Parametro invalido ingresa +W o -W . \n"); // Casos contrarios retorno errores.
            return ERROR;
        } else {
            printf("ERROR: El archivo no existe. \n");
            return ERROR;
        }
    } else {
        printf("Sistema inicializado.\n");
        return ERROR;
    }


    return NO_IMPLEMENTADA;
}

TipoRet IF(TDirectorio &sistema, Cadena nombreArchivo, Cadena texto) {
    if (sistemaInicializado) { // Si el sistema esta inicializado continuo caso contrario retorno error "sistema no inicializado".
        if (existFileDirectory(sistema, nombreArchivo) && haveWritePermission(getFileDirectory(sistema, nombreArchivo))) { // Si existe el archivo en el directorio y tiene permiso de escritura.
            insertCharsFileFirstLine(sistema, nombreArchivo, texto); // Agrego al comienzo de la primera fila del archivo de nombre nombreArchivo los caracteres de texto.
            return OK;
        } else {
            if (!existFileDirectory(sistema, nombreArchivo)) { // Si no existe	el archivo en el directorio.
                printf("ERROR: El archivo no existe. \n"); // Imprimo mensaje de error.
                return ERROR;
            } else { // Caso contrario imprimo mensaje de error.
                printf("ERROR: El archivo solo tiene permiso de lectura. \n");
                return ERROR;
            }
        }
    } else {
        printf("Sistema no inicializado.\n");
        return ERROR;
    }


    return NO_IMPLEMENTADA;
}

TipoRet IN(TDirectorio &sistema, Cadena nombreArchivo, Cadena texto) {
    if (sistemaInicializado) { // Si el sistema esta inicializado continuo caso contrario retorno error "sistema no inicializado".
        if (existFileDirectory(sistema, nombreArchivo) && haveWritePermission(getFileDirectory(sistema, nombreArchivo))) { // Si existe el archivo en el directorio y tiene permiso de escritura.
            insertTextFile(sistema, nombreArchivo, texto); // Inserto una nueva fila al comienzo del archivo nombreArchivo conteniendo los chars texto.
            return OK;
        } else {
            if (!existFileDirectory(sistema, nombreArchivo)) { // Si no existe	el archivo en el directorio.
                printf("ERROR: El archivo no existe. \n"); // Imprimo mensaje de error.
                return ERROR;
            } else { // Caso contrario imprimo mensaje de error.
                printf("ERROR: El archivo solo tiene permiso de lectura. \n");
                return ERROR;
            }
        }
    } else {
        printf("Sistema no inicializado.\n");
        return ERROR;
    }
    return NO_IMPLEMENTADA;
}

TipoRet DF(TDirectorio &sistema, Cadena nombreArchivo, int cantidad) {
    if (sistemaInicializado) { // Si el sistema esta inicializado continuo caso contrario retorno error "sistema no inicializado".
        if (existFileDirectory(sistema, nombreArchivo) && haveWritePermission(getFileDirectory(sistema, nombreArchivo))) { // Si existe el archivo en el directorio y tiene permiso de escritura.
            deleteCharsFile(sistema, nombreArchivo, cantidad); // Elimina los "cantidad" caracteres finales del archivo nombreArchivo.
            return OK;
        } else {
            if (!existFileDirectory(sistema, nombreArchivo)) { // Si no existe	el archivo en el directorio.
                printf("ERROR: El archivo no existe. \n"); // Imprimo mensaje de error.
                return ERROR;
            } else { // Caso contrario imprimo mensaje de error.
                printf("ERROR: El archivo solo tiene permiso de lectura. \n");
                return ERROR;
            }

        }
    } else {
        printf("Sistema no inicializado.\n");
        return ERROR;
    }

    return NO_IMPLEMENTADA;
}

TipoRet TYPE(TDirectorio &sistema, Cadena nombreArchivo) {
    if (sistemaInicializado) { // Si el sistema esta inicializado continuo caso contrario retorno error "sistema no inicializado".
        if (existFileDirectory(sistema, nombreArchivo)) { // Si existe el archivo en el directorio.
            printf("Archivo %s:\n", nombreArchivo);
            printFile(sistema, nombreArchivo); // Imprime el contenido del archivo "nombreArchivo".
            return OK;
        } else { // Si el archivo no existe imprimo mensaje de error.
            printf("ERROR: El archivo no existe. \n");
            return ERROR;
        }
    } else {
        printf("Sistema no inicializado.\n");
        return ERROR;
    }

    return NO_IMPLEMENTADA;
}

TipoRet DESTRUIRSISTEMA(TDirectorio &sistema) {
    if (sistemaInicializado) { // Si el sistema esta inicializado continuo caso contrario retorno error "sistema no inicializado".
        destroyDirectory(raiz); // Elimino toda la memoria de directorio.
        return OK;
    } else {
        printf("Sistema no inicializado.\n");
        return ERROR;
    }

    return NO_IMPLEMENTADA;
}

TipoRet CD(TDirectorio &sistema, Cadena nombreDirectorio) {
    if (sistemaInicializado) {
        if (0 == strcmp(nombreDirectorio, "RAIZ")) {
            if (isRootDirectory(sistema)) {
                return OK;
            } else {
                sistema = moveRootDirectory(sistema);
                return OK;
            }
        } else if (0 == strcmp(nombreDirectorio, "..")) {
            if (isRootDirectory(sistema)) {
                printf("ERROR: El directorio actual es la RAIZ.\n");
                return ERROR;
            } else {
                sistema = moveFatherDirectory(sistema);
                return OK;
            }
        } else {
            if (existChildrenDirectory(sistema, nombreDirectorio)) {
                sistema = moveChildrenDirectory(sistema, nombreDirectorio);
                return OK;
            } else {
                printf("ERROR: No existe ningun subdirectorio con el nombre: %s .\n", nombreDirectorio);
                return ERROR;
            }
        }
    } else {
        printf("Sistema no inicializado\n");
        return ERROR;
    }
    return NO_IMPLEMENTADA;
}

TipoRet MKDIR(TDirectorio &sistema, Cadena nombreDirectorio) { // crea un directorio
    if (sistemaInicializado) {
    	if (strchr(nombreDirectorio, '.') == NULL) { 					//Si no contiene un .
        	if (!existChildrenDirectory(sistema, nombreDirectorio)) {
            	createChildrenDirectory(sistema, nombreDirectorio);
            	return OK;
        	} else {
            	printf("ERROR: Ya existe un subdirectorio con el nombre: (%s) . \n", nombreDirectorio);
            	return ERROR;
        	}
        }else {
        	printf("El nombre del directorio no puede contener un (.)");
        	return ERROR;
        } 
    } else {
       	printf("Sistema no inicializado.\n");
        return ERROR;

	}
    return NO_IMPLEMENTADA;
}

TipoRet RMDIR(TDirectorio &sistema, Cadena nombreDirectorio) { // arreglarla rompe en remove
    if (sistemaInicializado) {
        if ( strcmp(nombreDirectorio, "RAIZ")!=0) { // si no directorio root 
            if (existChildrenDirectory(sistema, nombreDirectorio)) { // si existe el directorio 
            	TDirectorio sistemaactual = sistema;
            	moveChildrenDirectory(sistema, nombreDirectorio);
               removeChildrenDirectory(sistema, nombreDirectorio); // REVISAR DESTROY DIRECTORY
               	sistema=sistemaactual;
                return OK;
            } else { 
                    printf("Error: directorio ingresado no existe.\n");
                return ERROR;
            }
        } else {
            printf("Error: directorio raiz no se puede eliminar.\n");
            //REVISAR
            return ERROR;
        }
    } else {
        printf("ERROR:  Sistema no inicializado.\n");
        return ERROR;
    }
    return NO_IMPLEMENTADA;
}

TipoRet DIR (TDirectorio &sistema, Cadena parametro){
	 if (sistemaInicializado) {
	 	if ( strcmp(parametro, " /S")==0) {
	 	  	printDirectoryDirS(sistema);
	 	   	return OK;
	 	}else{
	 		printDirectoryDir(sistema);
	 		return OK;
	 	}
    } else {
        printf("ERROR:  Sistema no inicializado.\n");
        return ERROR;
    }
    return NO_IMPLEMENTADA;
}

TipoRet MOVE (TDirectorio &sistema, Cadena nombre, Cadena directorioDestino){
	TDirectorio dir = directorioDestinoRuta(raiz, directorioDestino);
	if (sistemaInicializado) {
		char buscar = '.';
		if ((strchr(nombre, buscar)==NULL)) {														// si se encuentra un . en el nombre es un archivo
			if (!existChildrenDirectory(sistema, nombre)){
				printf("ERROR: El directorio no existe en el directorio actual.\n");
				return ERROR;	
			}else if ((strcmp(directorioDestino, getruta(moveChildrenDirectory(sistema ,nombre)))==0)){
				printf("ERROR: El directorio destino no puede ser el mismo directorio.\n");
				sistema=moveFatherDirectory(sistema);
				return ERROR;
			}	
			sistema=moveFatherDirectory(sistema);
			
		TDirectorio ori = (moveChildrenDirectory(sistema ,nombre));
		sistema=moveFatherDirectory(sistema);
		if (directorioDestinoRuta(raiz, directorioDestino)==NULL){								// Si el destino no es subdirectorio (no salio con el if de arriba) chekeo que destino exista.
				printf("ERROR: El directorio destino no existe.\n");
				return ERROR;
		}else if (isSubDirectoryRoot(ori, directorioDestino))	{						// Si el destino es subdirectorio da error
			printf("ERROR: El directorio destino no puede ser un subdirectorio.\n");
			return ERROR;
		}else if (strcmp(directorioDestino, getruta(moveFatherDirectory(ori)))==0){
				printf("ERROR: El directorio ya se encuentra en esta ruta.\n");
				return ERROR;
			}else{
				moveSubDirectory(sistema ,ori , dir);
				return OK;	
			}
			
		}else if (!existFileDirectory(sistema, nombre)){
			printf("ERROR: El archivo no existe en el directorio actual.\n");
			return ERROR;
		}else if (directorioDestinoRuta(raiz, directorioDestino)==NULL){								// Si el destino no es subdirectorio (no salio con el if de arriba) chekeo que destino exista.
			printf("ERROR: El directorio destino no existe.\n");
			return ERROR;
		}else{
				TArchivo archivo = getFileDirectory(sistema, nombre);		
				moveSubArchive(sistema, archivo, dir);
				return OK;
			}	
                
	} else {
        printf("ERROR:  Sistema no inicializado.\n");
        return ERROR;
    }	
		return NO_IMPLEMENTADA;
}
	


