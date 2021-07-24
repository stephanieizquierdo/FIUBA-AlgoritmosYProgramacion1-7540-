#define MAX_NOMBRE 200
#define MAX_FECHA 7

typedef struct preso{
	char nombre[MAX_NOMBRE];
	unsigned int edad;
	char conducta;
	unsigned int pabellon;
	unsigned int celda;
	char fecha[MAX_FECHA];
	unsigned maldicion_realizada;
}preso_t;


/*
 *Recibe un numero válido (es decir, que represente el estado final de alguna función).
 *Mostrará por pantalla el resultado final del archivo, ya sea si se ejecutó todo correctamente u ocurrió algun error.
 */
void mostrar_estado_archivo(int estado_final);


/*
 *Genera un archivo binario en el cual figuran los presos que realizaron solo una maldición imperdonable.
 *El nombre del archivo binario será el string recibido.
 *Devolverá un numero negativo en caso de que haya ocurrido algún error. Si pudo crear el archivo devuelve 1.
 */
int perdonar(char nombre_archivo[MAX_NOMBRE]);

/*
 *Crea un archivo de texto con los nombres de los presos que cumplan con las condiciones necesarias recibidas(fecha y conducta)
 *Si ya existe un archivo para esa fecha, no lo sobreescribira.Devolverá un número negativo en caso de que haya ocurrido algún error.
 *De lo contrario devolverá 1
 */
int liberar_presos(char nombre_archivo[MAX_NOMBRE], char fecha[MAX_FECHA], char conducta);

/*
 *Actualizará los archivos binarios originales sacando los presos que están en el archivo de los liberados para la fecha recibida.
 *Devolverá un número negativo en caso de que haya ocurrido algún error. De lo contrario devolverá 1.
 */
int actualizar_archivos(char fecha[MAX_FECHA]);

/*
 *Muestra por pantalla el archivo de presos liberados para la fecha recibida.
 *Devolverá un número negativo en caso de que haya ocurrido algún error. De lo contrario devolverá 1.
 */
int mostrar_liberados(char fecha[MAX_FECHA]);

/*
 *Muestra por pantalla todos los mensajes de ayuda.
 */
void mensaje_de_ayuda();
