#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

const char TERMINAR = 'N';
const int EDAD_MINIMA = 17;
const int RANGO_MIN = 0, RANGO_MAX = 10;
const char CATEGORIA_BUENA = 'B', CATEGORIA_REGULAR = 'R',  CATEGORIA_MALA = 'M';


/*Pre: recibe una letra
  Pos: Guarda dicha letra en mayuscula */
void ingreso_alumnos(char *ingresar_alumnos){
    printf("Desea ingresar un alumno? (N para ​ NO​ , cualquier otra tecla para sí) ");
    scanf(" %c", ingresar_alumnos);
}

/*Pre: recibe una letra previamente ingresada
  Pos: verifica que la letra corresponga a alguna de las esperadas.*/
bool verificar_categoria(char *categoria){
    return ((*categoria) == CATEGORIA_MALA || (*categoria) == CATEGORIA_REGULAR || (*categoria) == CATEGORIA_BUENA);
}

/*Pre:recibe un numero previamente ingresado
  Pos: valida si es que el numero ingresado corresponde al intervalo esperado*/
bool verificar_rango(int *numero){
    return ((*numero) >= RANGO_MIN && (*numero) <= RANGO_MAX);
}

/*pre: recibe un numero para representar la edad del alumno
  pos: guarda dicho numero como la edad el alumno*/
void pedir_edad (int *edad){
    printf("Ingrese edad del alumno: ");
    scanf(" %i", edad);
}

/*pre: recibe un numero como representacion de la inteligencia
  pos: guarda el numero como la inteligencia del alumno si es que cumple con el rango esperado*/
void pedir_inteligencia(int *inteligencia){
    do {
        printf("Ingrese su inteligencia (de 0 a 10 inclusives): ");
        scanf(" %i", inteligencia );
    } while (!verificar_rango(inteligencia));
}

/*Pre: Recibe un numero como representacion de la fuerza del alumno
  Pos: guarda dicho valor si pertenece el rango esperado*/
void pedir_fuerza(int *fuerza){
    do {
        printf("Ingrese su fuerza (de 0 a 10 inclusives): ");
        scanf(" %i", fuerza );
    } while (!verificar_rango(fuerza));
}

/*Pre:Recibe una letra. Dicha letra debe ser 'B', 'R' o 'M'
  Pos:La letra sera guardada, en mayuscula, como categoria del alumno*/
void pedir_cat_magica(char *categoria){
    do {
        printf("Ingrese su categoria (B,M o R): ");
        scanf(" %c", categoria);
    } while (!verificar_categoria(categoria));
}
/*
 * Pide los datos del alumno para poder evaluarlo
 */
void pedir_datos(&inteligencia_alumno, &fuerza_alumno, &categoria_alumno){
    pedir_inteligencia(&inteligencia_alumno);
    pedir_fuerza(&fuerza_alumno);
    pedir_cat_magica(&categoria_alumno);
}


/*Pre:recibe los datos del alumno y del campeon.
      Ademas tambien recibe la cantidad de alumnos ingresados y la posicion del campeon.
  Pos:Se actualizaran los datos del campeon y su posición*/
void evaluar_campeon(int *posicion_campeon,int *inteligencia_campeon, int *fuerza_campeon, char *categoria_campeon, int alumnos, int inteligencia_alumno, int fuerza_alumno, char categoria_alumno){
    if (*inteligencia_campeon < inteligencia_alumno) {
        ((*inteligencia_campeon) = inteligencia_alumno);
        ((*fuerza_campeon) = fuerza_alumno);
        ((*categoria_campeon) = categoria_alumno);
        (*posicion_campeon) = alumnos;
    } else if (*inteligencia_campeon == inteligencia_alumno) {
        if ((*fuerza_campeon) < fuerza_alumno) {
            ((*fuerza_campeon) = fuerza_alumno);
            (*posicion_campeon) = alumnos;
        } else if (*fuerza_campeon == fuerza_alumno) {
            if (*categoria_campeon == CATEGORIA_MALA && (categoria_alumno == CATEGORIA_REGULAR || categoria_alumno == CATEGORIA_BUENA)) {
                ((*categoria_campeon) = categoria_alumno);
                (*posicion_campeon) = alumnos;
            } else if ((*categoria_campeon) == CATEGORIA_REGULAR && categoria_alumno == CATEGORIA_BUENA) {
                ((*categoria_campeon) = categoria_alumno);
                (*posicion_campeon) = alumnos;
            }
  	     }
     }
}

/*
 * Imprime el resultado de la competencia. En caso de que haya un campeon, se imprimen sus datos
 */
void mostrar_resultado(int posicion_campeon,int inteligencia_campeon, int fuerza_campeon, char categoria_campeon){
    if (posicion_campeon > 0) {
        printf("El campeon es el numero %i :)\n", posicion_campeon);
        printf("Los datos del campeon son:\n");
        printf("inteligencia: %i \n", inteligencia_campeon);
        printf("fuerza: %i\n", fuerza_campeon);
        printf("categoria: %c\n", categoria_campeon);
    } else {
        printf("No hay campeon :(");
    }
}

int main(){
    int alumnos = 0, posicion_campeon = 0;

    int edad_alumno, inteligencia_alumno, fuerza_alumno;
    char categoria_alumno;

    int inteligencia_campeon, fuerza_campeon;
    char categoria_campeon;

    while (ingreso_alumnos(&ingresar_alumnos) != TERMINAR) {
        pedir_edad(&edad_alumno);
        alumnos++;
        if (edad_alumno >= EDAD_MINIMA ) {
            pedir_datos(&inteligencia_alumno, &fuerza_alumno, &categoria_alumno);
            evaluar_campeon(&posicion_campeon, &inteligencia_campeon, &fuerza_campeon, &categoria_campeon, alumnos, inteligencia_alumno, fuerza_alumno, categoria_alumno);
        }
    }
    mostrar_resultado(posicion_campeon, inteligencia_campeon, fuerza_campeon, categoria_campeon);

    return 0;
}
