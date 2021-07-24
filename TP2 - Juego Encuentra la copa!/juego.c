#include "laberinto.h"
#include "copa.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define TAMANIO 15

#define JUEGO_EN_CURSO 0
#define JUEGO_GANADO 1
#define JUEGO_PERDIDO -1

#define SIN_VIDA 0

//Muestra una explicacion del juego por pantalla.
void explicar_juego(){
	printf("                               ¡Bienvenido al Torneo de los tres magos!\n");
	printf("\n");
	printf("Debes encontrar la Copa (C) para ganar!\n");
	printf("\n");
	printf("En este juego estas representado por la letra J, y debes hallar la copa antes que Greg (G), tu rival, la encuentre!\n");
	printf("Esta estará escondida al menos que tengas menos de 15 puntos de vida.\n");
	printf("Agarra las pociones (P) para recuperar vida, por cada paso que das perderas 3 puntos de vida, usalos bien. \n");
	printf("Puedes aprender hechizos como Impedimenta (I) y Ridikkulus (R) que te ayudaran a enfrentarte a los mounstros!\n");
	printf("La Acromantula (A) te restara 10 puntos, el Escreguto(E) te quitara 20 puntos si no tienes Impedimenta,\n");
	printf("el Boggart(B) te quitara 15 puntos de vida si no tienes Ridikkulus.\n");
	printf("Cuenta la leyenda que si tienes la esfinge(F) se te mostrara la copa!\n");
	printf("\n");
	printf("Buena suerte!\n");
}

//Recibe un caracter, representativo a la direccion del jugador. Dicha direccion debe ser valida.

void pedir_direccion(juego_t juego, char *  direccion){
	do{
		printf("\n Ingrese 'a' (izquierda) 'w' (arriba) 's' (abajo), 'd' (derecha): ");
		scanf(" %c", direccion);
	}while(es_movimiento_valido(&juego,*direccion)==false);
}

//Muestra por pantalla los puntos de vida del jugador, y su inventario.
void mostrar_info(jugador_t jugador){
	printf("\n");
	printf(" Puntos de vida: %d \n", jugador.vida);
	printf(" Inventario: [");
	for(int i=0; i<(jugador.tope_ayudas); i++){
		printf(" %c ",jugador.ayudas[i].codigo);
	}
	printf("]\n");
}

// * muestran mensajes por pantalla segun los distintos casos:
void mensaje_juego_ganado(){
	printf("\nGanaste, encontraste la copa  :D \n");
}

void mensaje_juego_perdido(){
	printf("\nPerdiste :(\n");
}

void mensaje_sin_vida(){
	printf("Te quedaste sin vida! \n");
}
void mensaje_gano_rival(){
	printf("El rival agarro la copa! \n");
}
//*

int main(){
	juego_t juego;
	char direccion;
	char laberinto_aux[TAMANIO][TAMANIO];
	srand((unsigned int)time(NULL));
	system("clear");

	inicializar_laberinto(&juego);
	explicar_juego();
	actualizar_laberinto(juego,laberinto_aux);
	mostrar_laberinto(laberinto_aux);
	do {
		mostrar_info(juego.jugador);
		pedir_direccion(juego, &direccion);
		mover_jugador(&juego.jugador, direccion);

		if (estado_juego(juego) == JUEGO_EN_CURSO){
			mover_rival(&juego);
		}
		actualizar_juego(&juego);
		actualizar_laberinto(juego,laberinto_aux);
		system("clear");
		mostrar_laberinto(laberinto_aux);
	} while (estado_juego(juego) == JUEGO_EN_CURSO);

	if (estado_juego(juego) == JUEGO_GANADO) {
		mensaje_juego_ganado();
	} else if(estado_juego(juego) == JUEGO_PERDIDO) {
		mensaje_juego_perdido();
		if (juego.jugador.vida <= SIN_VIDA) {
			mensaje_sin_vida();
		} else {
			mensaje_gano_rival();
		}
	}
	return 0;
}
