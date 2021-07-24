#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "administracion.h"

#define EXTENSION_TXT ".txt"
#define ARCHIVO_CRUCIO "crucio.dat"
#define ARCHIVO_IMPERIUS "imperius.dat"
#define ARCHIVO_CRUCIO_AUX "crucio_aux.dat"
#define ARCHIVO_IMPERIUS_AUX "imperius_aux.dat"

#define LECTURA "r"
#define ESCRITURA "w"

#define BUENA 'B'
#define REGULAR 'R'
#define MALA 'M'

#define ERROR_CRUCIO -1
#define ERROR_IMPERIUS -2
#define ERROR_PERDONABLES -3
#define ERROR_APERTURA_PERDONABLES -5
#define ERROR_FECHA_LIBERADOS -4
#define LIBERADOS_EXISTE -6
#define ERROR_ACTUALIZACION_CRUCIO -7
#define ERROR_ACTUALIZACION_IMPERIUS -8
#define PERDONABLES_NO_EXISTE -9
#define ERROR_LIBERADOS -10
#define ERROR_ARCHIVO_A_MOSTRAR -11

#define EXITO 1

#define NEGRITA "\e[1m"
#define CYAN "\033[1;36m"
#define RESET "\033[0m"


/*
 *Recibe un numero válido (es decir, que represente el estado final de alguna función).
 *Mostrará por pantalla el resultado final del archivo, ya sea si se ejecutó todo correctamente u ocurrió algun error.
 */
void mostrar_estado_archivo(int estado_final){
	if(estado_final == ERROR_CRUCIO){
		printf("Error de apertura de crucio.\n");
	}
	else if(estado_final == ERROR_IMPERIUS){
		printf("Error de apertura de imperius.\n");
	}
	else if(estado_final == ERROR_PERDONABLES){
		printf("Error de creacion de archivo de salida perdonables.\n");
	}
	else if(estado_final == ERROR_APERTURA_PERDONABLES){
		printf("Error de apertura de perdonables.\n");
	}
	else if(estado_final == ERROR_FECHA_LIBERADOS){
		printf("No se encontró el archivo liberados para esa fecha.\n");
	}
	else if (estado_final == PERDONABLES_NO_EXISTE){
		printf("El archivo de perdonables ingresado no existe.\n");
	}
	else if(estado_final == ERROR_LIBERADOS){
		printf("El archivo de liberados no se pudo abrir.\n");
	}
	else if(estado_final == LIBERADOS_EXISTE){
		printf("Ya existía un archivo de liberados para esa fecha.\n");
	}
	else if (estado_final == ERROR_ACTUALIZACION_CRUCIO){
		printf("Error de apertura del archivo de crucio a actualizar.\n");
	}
	else if (estado_final == ERROR_ACTUALIZACION_IMPERIUS){
		printf("Error de apertura del archivo de imperius a actualizar.\n");
	}
	else if(estado_final == ERROR_ARCHIVO_A_MOSTRAR){
		printf("Error de apertura del archivo a mostrar.\n");
	}
	else if(estado_final == EXITO){
		printf("\nEl programa se ejecutó exitosamente.\n");
	}
}

/*
 *Escribe un registro preso_t en un archivo binario.
 */
void escribir_preso(preso_t preso,FILE* archivo){
	fwrite(&preso, sizeof(preso_t), 1, archivo);
}

/*
 *Escribe el nombre de un preso_t en un archivo de texto.
 */
void escribir_nombre_preso(FILE* archivo, preso_t preso){
	fprintf(archivo, "%s\n", preso.nombre);
}

/*
 *Lee un registro preso_t en un archivo binario. Devuelve la cantidad que leyó.
 */
size_t leer_preso(preso_t* preso, FILE* archivo){
	size_t leidos = fread(preso, sizeof (preso_t), 1, archivo);
	return leidos;
}

/*
 *Lee un registro preso_t en un archivo de texto. Devuelve la cantidad que leyó.
 */
int leer_preso_txt(FILE* archivo, preso_t *preso){
	int leido = fscanf(archivo, "%[^\n]\n", preso->nombre);
	return leido;
}


/*====================COMANDO PERDONABLES========================*/

/*
 *PRE: Los archivos deben estar abiertos.
 *POS: Escribirá un archivo con los presos que figuren una sola vez en alguno de los dos archivos recibidos.
 *     El archivo resultante estará ordenado alfabéticamente por nombre.
 */
void diferencia(FILE* crucio_file, FILE* imperius_file, FILE* perdonables_file){
	preso_t preso_1;
	preso_t preso_2;

	size_t leidos_crucio = leer_preso(&preso_1, crucio_file);
	size_t leidos_imperius = leer_preso(&preso_2, imperius_file);

	while (leidos_crucio > 0 && leidos_imperius > 0) {
		if (strcmp(preso_1.nombre, preso_2.nombre) == 0) {
			leidos_crucio = leer_preso(&preso_1, crucio_file);
			leidos_imperius = leer_preso(&preso_2, imperius_file);
		} else if (strcmp(preso_1.nombre, preso_2.nombre) < 0) {
			escribir_preso(preso_1, perdonables_file);
			leidos_crucio = leer_preso(&preso_1, crucio_file);
		} else {
			escribir_preso(preso_2, perdonables_file);
			leidos_imperius = leer_preso(&preso_2, imperius_file);
		}
	}
	while (leidos_crucio > 0) {
		escribir_preso(preso_1, perdonables_file);
		leidos_crucio = leer_preso(&preso_1, crucio_file);
	}
	while (leidos_imperius > 0) {
		escribir_preso(preso_2, perdonables_file);
		leidos_imperius = leer_preso(&preso_2, imperius_file);
	}
}

/*
 *Genera un archivo binario en el cual figuran los presos que realizaron solo una maldición imperdonable.
 *El nombre del archivo binario será el string recibido.
 *Devolverá un numero negativo en caso de que haya ocurrido algún error. Si pudo crear el archivo devuelve 1.
 */
int perdonar(char nombre_perdonables[MAX_NOMBRE]){
	FILE* crucio_file;
	FILE* imperius_file;
	FILE* perdonables_file;

	crucio_file= fopen(ARCHIVO_CRUCIO,LECTURA);
	if (!crucio_file) {
		return ERROR_CRUCIO;
	}

	imperius_file= fopen(ARCHIVO_IMPERIUS, LECTURA);
	if (!imperius_file) {
		fclose(crucio_file);
		return ERROR_IMPERIUS;
	}

	perdonables_file = fopen(nombre_perdonables,ESCRITURA);
	if (!perdonables_file) {
		fclose(imperius_file);
		fclose(crucio_file);
		return ERROR_PERDONABLES;
	}
	diferencia(crucio_file,imperius_file,perdonables_file);

	fclose(crucio_file);
	fclose(imperius_file);
	fclose(perdonables_file);

	return EXITO;
}

/*====================COMANDO LIBERAR======================*/

/*
 * PRE:Recibe dos archivos abiertos, un string representativo de la fecha y un caracter para la conducta.
 * POS:Escribe en un archivo de texto los presos que cumplen con la fecha ingresada y tienen igual o mejor conducta que la ingresada.
 */

void filtrar_presos(FILE* perdonables_file,FILE* liberables, char fecha[MAX_FECHA], char conducta_ingresada){
	preso_t preso_perdonable;

	size_t leidos_perdonables = leer_preso(&preso_perdonable,perdonables_file);

	while (leidos_perdonables > 0) {
		if (strcmp(preso_perdonable.fecha, fecha) <= 0) {
			if (preso_perdonable.conducta == BUENA && conducta_ingresada == BUENA) {
				escribir_nombre_preso(liberables,preso_perdonable);
			}
			else if (conducta_ingresada == REGULAR && (preso_perdonable.conducta == REGULAR || preso_perdonable.conducta == BUENA)) {
				escribir_nombre_preso(liberables,preso_perdonable);
			}
			else if (conducta_ingresada == MALA) {
				escribir_nombre_preso(liberables,preso_perdonable);
			}
		}
		leidos_perdonables = leer_preso(&preso_perdonable,perdonables_file);
	}
}

/*
 *PRE: Recibe dos strings. Un string representa el nombre del archivo y el otro la fecha.
 *POS: Genera el nombre del archivo de texto liberados siguiendo el patrón: "liberados_(fecha ingresada).txt"
 */

void obtener_archivo_liberados(char fecha[MAX_FECHA], char nombre_archivo_liberados[MAX_NOMBRE]){
	strcpy(nombre_archivo_liberados,"liberados_");
	strcat(nombre_archivo_liberados,fecha);
	strcat(nombre_archivo_liberados,EXTENSION_TXT);
}

/*
 *PRE: Recibe un string representando el nombre de un archivo.
 *POS: Verifica si el archivo existe. Devuelve true si existo o false si no.
 */
bool existe_archivo(char nombre_archivo[MAX_NOMBRE]){
	bool ya_existe = true;
	FILE* archivo = fopen(nombre_archivo, LECTURA);
  	archivo? (ya_existe = false) : fclose(archivo);
    return ya_existe;
}

/*
 *Crea un archivo de texto con los nombres de los presos que cumplan con las condiciones necesarias recibidas(fecha y conducta)
 *Si ya existe un archivo para esa fecha, no lo sobreescribira.Devolverá un número negativo en caso de que haya ocurrido algún error.
 *De lo contrario devolverá 1.
 */
int liberar_presos(char nombre_archivo_perdonables[MAX_NOMBRE], char fecha[MAX_FECHA], char conducta){
	char nombre_archivo_liberados[MAX_NOMBRE];
	obtener_archivo_liberados(fecha,nombre_archivo_liberados);

	if (existe_archivo(nombre_archivo_perdonables) && !existe_archivo(nombre_archivo_liberados)) {
		FILE* perdonables_file = fopen(nombre_archivo_perdonables,LECTURA);
		if (!perdonables_file){
			return ERROR_APERTURA_PERDONABLES;
		}
		FILE* liberables= fopen(nombre_archivo_liberados,ESCRITURA);
		if (!liberables){
			fclose(perdonables_file);
			return ERROR_LIBERADOS;
		}
		filtrar_presos(perdonables_file, liberables, fecha, conducta);
		fclose(liberables);
		fclose(perdonables_file);

		return EXITO;
	} else if (!existe_archivo(nombre_archivo_perdonables)) {
		return PERDONABLES_NO_EXISTE;
	} else {
		return LIBERADOS_EXISTE;
	}
}

/*====================COMANDO ACTUALIZAR======================*/

/*
 *PRE: Los archivos que reciben deben estar abiertos.
 *POS: Creará dos archivos binarios auxiliares (uno para la maldicion crucio y otro para imperius) en los cuales
 *	   figuraran los presos que estaban en los archivos originales pero no los que están en el archivo de los liberados.
 *     Devolverá un número negativo en caso de que haya ocurrido algún error. De lo contrario devolverá 1
 */
int actualizar_presos(FILE* crucio_file, FILE* imperius_file,FILE* liberados){
	preso_t preso_crucio;
	preso_t preso_imperius;
	preso_t preso_liberado;

	FILE* crucio_aux;
	crucio_aux = fopen(ARCHIVO_CRUCIO_AUX, ESCRITURA);
	if (!crucio_aux) {
		return ERROR_ACTUALIZACION_CRUCIO;
	}

	FILE* imperius_aux;
	imperius_aux = fopen(ARCHIVO_IMPERIUS_AUX, ESCRITURA);
	if (!imperius_aux) {
		fclose(crucio_aux);
		return ERROR_ACTUALIZACION_IMPERIUS;
	}

	int leidos_liberados = leer_preso_txt(liberados, &preso_liberado);
	size_t leidos_crucio = leer_preso(&preso_crucio, crucio_file);
	size_t leidos_imperius = leer_preso(&preso_imperius, imperius_file);

	while (leidos_liberados > 0 && leidos_crucio > 0 && leidos_imperius > 0) {

		if (strcmp(preso_imperius.nombre,preso_crucio.nombre) < 0 && strcmp(preso_imperius.nombre, preso_liberado.nombre) < 0) {
			escribir_preso(preso_imperius, imperius_aux);
			leidos_imperius = leer_preso(&preso_imperius, imperius_file);
		}
		else if (strcmp(preso_imperius.nombre,preso_crucio.nombre) < 0 && strcmp(preso_imperius.nombre, preso_liberado.nombre) == 0) {
			leidos_imperius = leer_preso(&preso_imperius, imperius_file);
			leidos_liberados = leer_preso_txt(liberados, &preso_liberado);
		}
		else if (strcmp(preso_imperius.nombre,preso_crucio.nombre) >0 && strcmp(preso_crucio.nombre, preso_liberado.nombre) < 0) {
			escribir_preso(preso_crucio, crucio_aux);
			leidos_crucio = leer_preso(&preso_crucio, crucio_file);
		}
		else if (strcmp(preso_imperius.nombre, preso_crucio.nombre) > 0 && strcmp(preso_crucio.nombre, preso_liberado.nombre) == 0) {
			leidos_crucio = leer_preso(&preso_crucio, crucio_file);
			leidos_liberados = leer_preso_txt(liberados, &preso_liberado);
		}
		else if (strcmp(preso_imperius.nombre, preso_crucio.nombre) == 0) {
			escribir_preso(preso_imperius, imperius_aux);
			escribir_preso(preso_crucio, crucio_aux);
			leidos_imperius = leer_preso(&preso_imperius, imperius_file);
			leidos_crucio = leer_preso(&preso_crucio, crucio_file);
		}
	}
	while (leidos_imperius > 0 && leidos_liberados > 0) {
		if (strcmp(preso_imperius.nombre, preso_liberado.nombre) < 0) {
			escribir_preso(preso_imperius, imperius_aux);
			leidos_imperius = leer_preso(&preso_imperius, imperius_file);
		} else if (strcmp(preso_imperius.nombre, preso_liberado.nombre) == 0) {
			leidos_liberados = leer_preso_txt(liberados, &preso_liberado);
			leidos_imperius = leer_preso(&preso_imperius, imperius_file);
		}
	}
	while (leidos_crucio > 0 && leidos_liberados > 0) {
		if (strcmp(preso_crucio.nombre, preso_liberado.nombre) < 0) {
			escribir_preso(preso_crucio, crucio_aux);
			leidos_crucio = leer_preso(&preso_crucio, crucio_file);
		} else if (strcmp(preso_crucio.nombre, preso_liberado.nombre) == 0) {
			leidos_liberados = leer_preso_txt(liberados, &preso_liberado);
			leidos_crucio = leer_preso(&preso_crucio, crucio_file);
		}
	}

	while (leidos_imperius > 0) {
		escribir_preso(preso_imperius, imperius_aux);
		leidos_imperius = leer_preso(&preso_imperius, imperius_file);
	}

	while (leidos_crucio > 0) {
		escribir_preso(preso_crucio, crucio_aux);
		leidos_crucio = leer_preso(&preso_crucio, crucio_file);
	}
	fclose(imperius_aux);
	fclose(crucio_aux);

	return EXITO;
}


/*
 *Actualizará los archivos binarios originales sacando los presos que están en el archivo de los liberados para la fecha recibida.
 *Devolverá un número negativo en caso de que haya ocurrido algún error. De lo contrario devolverá 1.
 */
int actualizar_archivos(char fecha[MAX_FECHA]){
	FILE* crucio_file;
	FILE* imperius_file;
	FILE* archivo_liberados;

	crucio_file = fopen(ARCHIVO_CRUCIO, LECTURA);
	if (!crucio_file) {
		return ERROR_CRUCIO;
	}

	imperius_file = fopen(ARCHIVO_IMPERIUS, LECTURA);
	if (!imperius_file) {
		fclose(crucio_file);
		return ERROR_IMPERIUS;
	}

	char nombre_archivo_liberados[MAX_NOMBRE];
	obtener_archivo_liberados(fecha,nombre_archivo_liberados);

	archivo_liberados = fopen(nombre_archivo_liberados, LECTURA);
	if (!archivo_liberados) {
		fclose(imperius_file);
		fclose(crucio_file);
		return ERROR_FECHA_LIBERADOS;
	}

	int estado_final = actualizar_presos(crucio_file, imperius_file, archivo_liberados);

	fclose(archivo_liberados);
	fclose(imperius_file);
	fclose(crucio_file);

	remove(ARCHIVO_CRUCIO);
	remove(ARCHIVO_IMPERIUS);

	rename(ARCHIVO_CRUCIO_AUX,ARCHIVO_CRUCIO);
	rename(ARCHIVO_IMPERIUS_AUX,ARCHIVO_IMPERIUS);

	return estado_final;
}

/*====================COMANDO MOSTRAR_LIBERADOS=====================*/

/*
 *PRE: Recibe un archivo abierto.
 *POS: Muestra por pantalla los nombres de los presos del archivo recibido.
 */
void imprimir_nombre_presos(FILE* archivo_a_mostrar){
	preso_t preso_mostrar;
	int leidos_liberados = fscanf(archivo_a_mostrar, "%[^\n]\n", preso_mostrar.nombre);
		while (leidos_liberados == 1) {
			printf("%s\n", preso_mostrar.nombre);
			leidos_liberados = fscanf(archivo_a_mostrar, "%[^\n]\n", preso_mostrar.nombre);
		}
}

/*
 *Muestra por pantalla el archivo de presos liberados para la fecha recibida.
 *Devolverá un número negativo en caso de que haya ocurrido algún error. De lo contrario devolverá 1.
 */
int mostrar_liberados(char fecha[MAX_FECHA]){

	char nombre_archivo_liberados[MAX_NOMBRE];
	obtener_archivo_liberados(fecha,nombre_archivo_liberados);

	if (existe_archivo(nombre_archivo_liberados)) {
		FILE* archivo_a_mostrar = fopen(nombre_archivo_liberados, LECTURA);
		if (!archivo_a_mostrar) {
			return ERROR_ARCHIVO_A_MOSTRAR;
		}
		printf("Presos del archivo: %s\n\n", nombre_archivo_liberados);
		imprimir_nombre_presos(archivo_a_mostrar);
		fclose(archivo_a_mostrar);

		return EXITO;
	} else {
		return ERROR_FECHA_LIBERADOS;
	}
}

/*====================COMANDO AYUDA========================*/

/*
 *Muestra por pantalla la ayuda para el comando perdonables
 */
void ayuda_perdonables(){
	printf("\n%sComando perdonables:%s\n", NEGRITA, RESET);
	printf("\tCrea un archivo con aquellos presos que pueden ser perdonables, es decir quienes solo realizaron una maldicion imperdonable.\n");
	printf("\tEl segundo argumento enviado debe ser el nombre con el cual desea que se guarde el archivo de perdonables.\n");
	printf("\tEjemplo:\n");
	printf("\t%s./azkaban perdonables <nombre del archivo>%s\n", CYAN, RESET);
}

/*
 * Muestra por pantalla la ayuda para el comando liberar.
 */
void ayuda_liberar(){
	printf("\n%sComando liberar:%s\n", NEGRITA, RESET);
	printf("\tCreará un archivo de texto con los nombres de los presos que cumplan con las condiciones necesarias\n");
	printf("\tDebe ser seguido del nombre del archivo de presos perdonables, fecha y conducta que desea que se cumpla.\n");
	printf("\tLa fecha es de formato aaaammm y la conducta puede ser: B (buena), R (regular) o M (mala)\n");
	printf("\tEjemplo:\n");
	printf("\t%s./azkaban liberar <nombre del archivo> <fecha> <conducta>%s\n", CYAN, RESET);
}

/*
 *Muestra por pantalla la ayuda para el comando mostrar_liberados.
 */
void ayuda_mostrar_liberados(){
	printf("\n%sComando mostrar_liberados:%s\n", NEGRITA, RESET);
	printf("\tMostrará por pantalla el archivo de presos liberados en un determinado año/mes\n");
	printf("\tEl segundo argumento será la fecha del archivo\n");
	printf("\tEjemplo:\n");
	printf("\t%s./azkaban mostrar_liberados <fecha>%s\n", CYAN, RESET);
}

/*
 *Muestra por pantalla la ayuda para el comando actualizar.
 */
void ayuda_actualizar(){
	printf("\n%sComando actualizar:%s\n", NEGRITA, RESET);
	printf("\tActualizará ambos archivos originales en los cuales figuran los presos que realizaron cada maldición.\n");
	printf("\tEs decir, sacan los presos que se encuentran en el archivo liberados de la fecha que usted indique.\n");
	printf("\tEjemplo:\n");
	printf("\t%s./azkaban actualizar <fecha>%s\n",CYAN, RESET);
}

/*
 *Muestra por pantalla todos los mensajes de ayuda.
 */
void mensaje_de_ayuda(){
	printf("Los comandos disponibles son:\n");
	ayuda_perdonables();
	ayuda_liberar();
	ayuda_mostrar_liberados();
	ayuda_actualizar();
}
