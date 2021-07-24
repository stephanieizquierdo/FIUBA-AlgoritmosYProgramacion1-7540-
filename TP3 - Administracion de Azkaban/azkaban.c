#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "administracion.h"

#define COMANDO_AYUDA "ayuda"
#define COMANDO_PERDONABLES "perdonables"
#define COMANDO_LIBERAR "liberar"
#define COMANDO_ACTUALIZAR "actualizar"
#define COMANDO_MOSTRAR_LIBERADOS "mostrar_liberados"

#define CANT_COMANDOS_AYUDA 2
#define CANT_COMANDOS_PERDONABLES 3
#define CANT_COMANDOS_LIBERAR 5
#define CANT_COMANDOS_ACTUALIZAR 3
#define CANT_COMANDOS_MOSTRAR 3

#define POS_COMANDO 1
#define POS_COMANDO_FECHA 2
#define POS_FECHA_LIBERAR 3
#define POS_NOMBRE_ARCHIVO 2
#define POS_COMANDO_CONDUCTA 4

/*
 *Mensaje de ayuda en caso de que el usuario haya ingresado algo que no se espera
 */
void ingrese_ayuda(){
	printf("No se ejecutó correctamente el programa. Ingrese la siguiente linea para ver los comandos disponibles:\n");
	printf("./azkaban ayuda\n");
}

int main(int argc, char *argv[]){

	int estado;

	if (argc == CANT_COMANDOS_AYUDA && strcmp(argv[POS_COMANDO], COMANDO_AYUDA) == 0){
		mensaje_de_ayuda();
	}
	else if (argc == CANT_COMANDOS_PERDONABLES && strcmp(argv[POS_COMANDO], COMANDO_PERDONABLES) == 0){
		estado = perdonar(argv[POS_NOMBRE_ARCHIVO]);
		mostrar_estado_archivo(estado);
	}
	else if (argc == CANT_COMANDOS_LIBERAR && strcmp(argv[POS_COMANDO],COMANDO_LIBERAR) == 0){
		estado = liberar_presos(argv[POS_NOMBRE_ARCHIVO], argv[POS_FECHA_LIBERAR], *(argv[POS_COMANDO_CONDUCTA]));
		mostrar_estado_archivo(estado);
	}
	else if(argc == CANT_COMANDOS_ACTUALIZAR && strcmp(argv[POS_COMANDO], COMANDO_ACTUALIZAR) == 0){
		estado = actualizar_archivos(argv[POS_NOMBRE_ARCHIVO]);
		mostrar_estado_archivo(estado);
	}
	else if(argc == CANT_COMANDOS_MOSTRAR && strcmp(argv[POS_COMANDO], COMANDO_MOSTRAR_LIBERADOS) == 0){
		estado = mostrar_liberados(argv[POS_COMANDO_FECHA]);
		mostrar_estado_archivo(estado);
	}
	else{
		ingrese_ayuda();
	}
	return 0;
}
