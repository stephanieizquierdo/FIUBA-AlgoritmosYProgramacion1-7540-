#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

#include "laberinto.h"
#include "copa.h"

#define CYAN "\033[1;36m"
#define AZUL "\033[0;34m"
#define ROJO "\033[0;31m"
#define VIOLETA "\033[0;95m"
#define AMARILLO "\033[0;93m"
#define VERDE "\033[0;32m"
#define COLOR_OFF "\033[0m"
#define PARED '#'

#define COPA 'C'
#define JUGADOR 'J'
#define RIVAL 'G'
#define POCIONES 'P'
#define IMPEDIMENTA 'I'
#define RIDDIKULUS 'R'
#define ESCREGUTO 'E'
#define ACROMANTULA 'A'
#define BOGGART 'B'
#define ESFINGE 'F'

#define IZQUIERZA 'a'
#define ABAJO 's'
#define DERECHA 'd'
#define ARRIBA 'w'

#define TAMANIO 15
#define MINIMA_POSICION 0
#define DISTANCA_MAX 10
#define MAX_COORD 20
#define CANTIDAD_POCIONES 3

#define DANIO_ESCREGUTO 20
#define DANIO_ACROMANTULA 10
#define DANIO_BOGGART 15

#define MAX_VIDA 50
#define VIDA_POCIONES 15
#define VIDA_POR_PASO 1
#define VIDA_APARICION_COPA 15
#define SIN_VIDA 0

#define JUEGO_EN_CURSO 0
#define JUEGO_GANADO 1
#define JUEGO_PERDIDO -1


char laberinto_aux[TAMANIO][TAMANIO];

//Devolverá una coordenada aleatoria dentro del tamaño del laberinto.
//No valida que dicha coordenada coincida con un pasillo ni que exista otro objeto en esa posición.

coordenada_t posicion_aleatoria(){
	coordenada_t coordenada_aleatoria;
	coordenada_aleatoria.fil= rand()%TAMANIO;
	coordenada_aleatoria.col= rand()%TAMANIO;

	return coordenada_aleatoria;
}

/***INICIALIZACIONES***/


//PRE: Recibe dos coordenada_t
//POS: Devolvera verdadero si es que dichas coordenadas se encuentra a una distancia mayor de 10

bool distancia_manhattan(coordenada_t pos_copa, coordenada_t pos_elem){
	int distancia = abs(pos_copa.fil-pos_elem.fil)+ abs(pos_copa.col -pos_elem.col);

	if(distancia>DISTANCA_MAX){
		return true;
	}else{
		return false;
	}
}

//PRE: Recibe una coordenada a verificar. Además recibe un vector de coordenadas, su tope y el laberinto.
//POS: Devuelve verdadero si es que la coordenada recibida no se encuentra en elvector de coordenadas ya anteriormente asignadas.

bool coordenada_valida(coordenada_t coor_elemento, coordenada_t coordenadas_ocupadas[MAX_COORD], int* tope_coordenadas_ocupadas, char laberinto_original[TAMANIO][TAMANIO]){
	int i = 0;
	bool es_valido = true;

	while(i <= (*tope_coordenadas_ocupadas) && es_valido){
		if((coordenadas_ocupadas[i].fil==coor_elemento.fil && coordenadas_ocupadas[i].col==coor_elemento.col) || laberinto_original[coor_elemento.fil][coor_elemento.col] == PARED){
			es_valido= false;
		}
		i++;
	}
	return(es_valido);
}

//PRE: recibe una coordenada. Además recibe el vector de coordenadas validas, con su respectivo tope ya inicializado.
//POS: inserta la coordenada en el vector.

void guardar_coordenadas(coordenada_t coordenadas_ocupadas[MAX_COORD], int *tope_coordenadas_ocupadas, coordenada_t coordenada){
	coordenadas_ocupadas[(*tope_coordenadas_ocupadas)]=coordenada;
	(*tope_coordenadas_ocupadas)++;
}

//PRE: el tope del vector coordenadas ocupadas debe estar inicializado. El laberinto debe tener inicializadas las paredes.
//POS: Asigna a la copa una coordenada. Dicha coordenada es valida.

void inicializar_copa(copa_t* copa,char laberinto_original[TAMANIO][TAMANIO],coordenada_t coordenadas_ocupadas[],int* tope_coordenadas_ocupadas){
	copa->codigo= COPA;
	coordenada_t coordenada_copa;
	do{
		coordenada_copa=posicion_aleatoria();
	}while(!coordenada_valida(coordenada_copa, coordenadas_ocupadas, tope_coordenadas_ocupadas, laberinto_original));
	copa->posicion= coordenada_copa;

	guardar_coordenadas(coordenadas_ocupadas, tope_coordenadas_ocupadas, coordenada_copa);
}


//*Las siguientes funciones inicializan los obstaculos:
//  PRE: el tope del vector obstaculos y coordenadas ocupadas debe estar inicializado. El laberinto debe tener inicializadas las paredes.
//  POS: Inicializa el codigo, daño y posicion. Dicha posicion es valida.

void inicializar_escreguto(obstaculo_t obstaculos[TOTAL_OBSTACULOS],int* tope_obstaculos,char laberinto_original[TAMANIO][TAMANIO],coordenada_t coordenadas_ocupadas[],int* tope_coordenadas_ocupadas){
	obstaculos[(*tope_obstaculos)].codigo= ESCREGUTO;
	obstaculos[(*tope_obstaculos)].danio= DANIO_ESCREGUTO;

	coordenada_t coordenada_escreguto;
	do{
		coordenada_escreguto=posicion_aleatoria();
	}while(!coordenada_valida(coordenada_escreguto,coordenadas_ocupadas, tope_coordenadas_ocupadas, laberinto_original));
	obstaculos[(*tope_obstaculos)].posicion=coordenada_escreguto;
	(*tope_obstaculos)++;
	guardar_coordenadas(coordenadas_ocupadas, tope_coordenadas_ocupadas, coordenada_escreguto);
}

void inicializar_acromantula(obstaculo_t obstaculos[TOTAL_OBSTACULOS],int* tope_obstaculos,char laberinto_original[TAMANIO][TAMANIO],coordenada_t coordenadas_ocupadas[],int* tope_coordenadas_ocupadas){
	obstaculos[(*tope_obstaculos)].codigo= ACROMANTULA;
	obstaculos[(*tope_obstaculos)].danio= DANIO_ACROMANTULA;
	coordenada_t coordenada_acromantula;
	do{
		coordenada_acromantula=posicion_aleatoria();
	}while(!coordenada_valida(coordenada_acromantula,coordenadas_ocupadas, tope_coordenadas_ocupadas, laberinto_original));
	obstaculos[(*tope_obstaculos)].posicion=coordenada_acromantula;
	(*tope_obstaculos)++;
	guardar_coordenadas(coordenadas_ocupadas, tope_coordenadas_ocupadas, coordenada_acromantula);
}

void inicializar_boggart(obstaculo_t obstaculos[TOTAL_OBSTACULOS],int* tope_obstaculos,char laberinto_original[TAMANIO][TAMANIO],coordenada_t coordenadas_ocupadas[],int* tope_coordenadas_ocupadas){
	obstaculos[(*tope_obstaculos)].codigo= BOGGART;
	obstaculos[(*tope_obstaculos)].danio= DANIO_BOGGART;
	coordenada_t coordenada_boggart;
	do{
		coordenada_boggart=posicion_aleatoria();
	}while(!coordenada_valida(coordenada_boggart,coordenadas_ocupadas, tope_coordenadas_ocupadas, laberinto_original));
	obstaculos[(*tope_obstaculos)].posicion=coordenada_boggart;
	(*tope_obstaculos)++;
	guardar_coordenadas(coordenadas_ocupadas, tope_coordenadas_ocupadas, coordenada_boggart);
}
//*

//*Las siguientes funciones inicializan las ayudas:
//  PRE: el tope del vector ayudas y coordenadas ocupadas debe estar inicializado. El laberinto debe tener inicializadas las paredes.
//  POS: Inicializa el codigo y posicion. La posicion sera valida
void inicializar_impedimenta(ayuda_t ayudas[TOTAL_AYUDAS], int* tope_ayudas,char laberinto_original[TAMANIO][TAMANIO],coordenada_t coordenadas_ocupadas[],int* tope_coordenadas_ocupadas){
	ayudas[(*tope_ayudas)].codigo= IMPEDIMENTA;
	coordenada_t coordenada_impedimenta;
	do{
		coordenada_impedimenta=posicion_aleatoria();
	}while(!coordenada_valida(coordenada_impedimenta,coordenadas_ocupadas, tope_coordenadas_ocupadas, laberinto_original));
	ayudas[(*tope_ayudas)].posicion=coordenada_impedimenta;
	(*tope_ayudas)++;
	guardar_coordenadas(coordenadas_ocupadas, tope_coordenadas_ocupadas, coordenada_impedimenta);
}

void inicializar_riddikulus(ayuda_t ayudas[TOTAL_AYUDAS], int* tope_ayudas,char laberinto_original[TAMANIO][TAMANIO],coordenada_t coordenadas_ocupadas[],int* tope_coordenadas_ocupadas){
	ayudas[(*tope_ayudas)].codigo= RIDDIKULUS;
	coordenada_t coordenada_riddikulus;
	do{
		coordenada_riddikulus=posicion_aleatoria();
	}while(!coordenada_valida(coordenada_riddikulus,coordenadas_ocupadas, tope_coordenadas_ocupadas, laberinto_original));
	ayudas[(*tope_ayudas)].posicion=coordenada_riddikulus;
	(*tope_ayudas)++;
	guardar_coordenadas(coordenadas_ocupadas, tope_coordenadas_ocupadas, coordenada_riddikulus);
}

void inicializar_esfinge(ayuda_t ayudas[TOTAL_AYUDAS], int* tope_ayudas,char laberinto_original[TAMANIO][TAMANIO],coordenada_t coordenadas_ocupadas[],int* tope_coordenadas_ocupadas){
	ayudas[(*tope_ayudas)].codigo= ESFINGE;
	coordenada_t coordenada_esfinge;
	do{
		coordenada_esfinge=posicion_aleatoria();
	}while(!coordenada_valida(coordenada_esfinge,coordenadas_ocupadas, tope_coordenadas_ocupadas, laberinto_original));
	ayudas[(*tope_ayudas)].posicion=coordenada_esfinge;
	(*tope_ayudas)++;
	guardar_coordenadas(coordenadas_ocupadas, tope_coordenadas_ocupadas, coordenada_esfinge);
}

void inicializar_pociones(ayuda_t ayudas[TOTAL_AYUDAS], int* tope_ayudas,char laberinto_original[TAMANIO][TAMANIO],coordenada_t coordenadas_ocupadas[],int* tope_coordenadas_ocupadas){
	ayudas[(*tope_ayudas)].codigo= POCIONES;
	ayudas[(*tope_ayudas)].vida_a_recuperar= VIDA_POCIONES;
	coordenada_t coordenada_pociones;
	do{
		coordenada_pociones=posicion_aleatoria();
	}while(!coordenada_valida(coordenada_pociones,coordenadas_ocupadas, tope_coordenadas_ocupadas, laberinto_original));
	ayudas[(*tope_ayudas)].posicion=coordenada_pociones;
	(*tope_ayudas)++;
	guardar_coordenadas(coordenadas_ocupadas, tope_coordenadas_ocupadas, coordenada_pociones);
}
//*


//PRE: el tope del vector coordenadas ocupadas debe estar inicializado. El laberinto debe tener inicializadas las paredes.
//POS: Inicializa el codigo y posicion del Rival. La posicion estara a una distancia mayor a diez que
//     la copa y sera distinta a la pared y las posiciones anteriormente asignadas.

void inicializar_rival(rival_t* rival,coordenada_t coordenada_copa,char laberinto_original[TAMANIO][TAMANIO],coordenada_t coordenadas_ocupadas[],int* tope_coordenadas_ocupadas){
	rival->codigo=RIVAL;
	rival->cantidad_pasos=0;

	coordenada_t coordenada_rival;
	do{
		coordenada_rival=posicion_aleatoria();
	}while(!coordenada_valida(coordenada_rival, coordenadas_ocupadas, tope_coordenadas_ocupadas, laberinto_original) || !distancia_manhattan(coordenada_copa, coordenada_rival));
	
	rival->posicion= coordenada_rival;
	guardar_coordenadas(coordenadas_ocupadas, tope_coordenadas_ocupadas, coordenada_rival);
}

//PRE: el tope del vector coordenadas ocupadas debe estar inicializado. El laberinto debe tener inicializadas las paredes.
//POS: Inicializa el codigo, vida y posicion del jugador. La posicion estara a una distancia mayor a diez que
//     la copa y sera distinta a la pared y las posiciones anteriormente asignadas.

void inicializar_jugador(jugador_t* jugador,coordenada_t coordenada_copa,char laberinto_original[TAMANIO][TAMANIO],coordenada_t coordenadas_ocupadas[],int* tope_coordenadas_ocupadas){
	jugador->codigo=JUGADOR;
	coordenada_t coordenada_jugador;
	jugador->vida = MAX_VIDA;
	do{
		coordenada_jugador=posicion_aleatoria();
	}while(!coordenada_valida(coordenada_jugador, coordenadas_ocupadas, tope_coordenadas_ocupadas, laberinto_original)|| !distancia_manhattan(coordenada_copa, coordenada_jugador));
	
	jugador->posicion= coordenada_jugador;
	guardar_coordenadas(coordenadas_ocupadas, tope_coordenadas_ocupadas, coordenada_jugador);
}

// Inicializará todas las estructuras con los valores correspondientes, creará el laberinto, posicionará todos los elementos.

void inicializar_laberinto(juego_t* juego){

	coordenada_t coordenadas_ocupadas[MAX_COORD];
	int tope_coordenadas_ocupadas=0;

	juego->tope_obstaculos=0;
	juego->tope_ayudas=0;
	juego->jugador.tope_ayudas=0;

	inicializar_paredes_laberinto(juego->laberinto_original);
	//copa:
	inicializar_copa(&juego->copa, juego->laberinto_original, coordenadas_ocupadas,&tope_coordenadas_ocupadas);
	//obstaculos:
	inicializar_escreguto(juego->obstaculos, &juego->tope_obstaculos,juego->laberinto_original, coordenadas_ocupadas,&tope_coordenadas_ocupadas);
	inicializar_acromantula(juego->obstaculos, &juego->tope_obstaculos,juego->laberinto_original, coordenadas_ocupadas,&tope_coordenadas_ocupadas);
	inicializar_boggart(juego->obstaculos, &juego->tope_obstaculos,juego->laberinto_original, coordenadas_ocupadas,&tope_coordenadas_ocupadas);
	//ayudas:
	inicializar_impedimenta(juego->ayudas, &juego->tope_ayudas,juego->laberinto_original, coordenadas_ocupadas,&tope_coordenadas_ocupadas);
	inicializar_riddikulus(juego->ayudas, &juego->tope_ayudas,juego->laberinto_original, coordenadas_ocupadas,&tope_coordenadas_ocupadas);
	inicializar_esfinge(juego->ayudas, &juego->tope_ayudas,juego->laberinto_original, coordenadas_ocupadas,&tope_coordenadas_ocupadas);
	for(int i=0; i<CANTIDAD_POCIONES; i++){
		inicializar_pociones(juego->ayudas, &juego->tope_ayudas,juego->laberinto_original, coordenadas_ocupadas,&tope_coordenadas_ocupadas);
	}
	//jugadores:
	inicializar_rival(&juego->rival,juego->copa.posicion,juego->laberinto_original, coordenadas_ocupadas,&tope_coordenadas_ocupadas);
	inicializar_jugador(&juego->jugador,juego->copa.posicion,juego->laberinto_original, coordenadas_ocupadas,&tope_coordenadas_ocupadas);
}


/***VISUALIZACIONES***/

//PRE: Recibe un caracter
//POS: Si el caracter recibido representa algun elemento, le asignara el color correspondiente.

void asignar_color(char objeto){

	switch(objeto){
		case JUGADOR: 
			printf("%s", CYAN);
			break;

		case RIVAL:
			printf("%s", AZUL);
			break;

		case ACROMANTULA:
			printf("%s", ROJO);
			break;

		case ESCREGUTO:
			printf("%s", ROJO);
			break;

		case BOGGART:
			printf("%s", ROJO);
			break;

		case POCIONES:
			printf("%s", VIOLETA);
			break;

		case IMPEDIMENTA:
			printf("%s", VIOLETA);
			break;

		case RIDDIKULUS:
			printf("%s", VIOLETA);
			break;

		case ESFINGE:
			printf("%s", VIOLETA);
			break;

		case COPA:
			printf("%s", AMARILLO);
			break;

		default:
			printf("%s", VERDE);
			break;
	}
}

//PRE: recibe un laberinto (matriz de caracteres) ya inicializado.
//POS: Mostrara el laberinto por pantalla

void mostrar_laberinto(char laberinto[TAMANIO][TAMANIO]){
	for(int i=0;i<TAMANIO;i++){
		printf("\n");
		for(int j=0; j<TAMANIO;j++){
			asignar_color(laberinto[i][j]);
			printf(" %c", laberinto[i][j]);
		}
	}
	printf("%s", COLOR_OFF);
}

/***MOVIMIENTOS***/


//PRE: recibe un juego_t y un caracter.
//POS: Verifica que la direccion cumpla con un movimiento valido, es decir que no pise paredes ni que se vaya del laberinto.

bool es_movimiento_valido(juego_t* juego, char tecla){
	bool es_valido=false;
	switch(tecla){
		case ARRIBA:
			if((juego->laberinto_original[(juego->jugador.posicion.fil)-1][juego->jugador.posicion.col]!=PARED) && ((juego->jugador.posicion.fil)-1 >= MINIMA_POSICION))
				es_valido=true;
			break;
		case ABAJO:
			if((juego->laberinto_original[(juego->jugador.posicion.fil)+1][juego->jugador.posicion.col]!=PARED) && ((juego->jugador.posicion.fil)+1 <TAMANIO))
				es_valido=true;
			break;
		case IZQUIERZA:
			if((juego->laberinto_original[(juego->jugador.posicion.fil)][juego->jugador.posicion.col-1]!=PARED) && (juego->jugador.posicion.col-1)>=MINIMA_POSICION)
				es_valido=true;
			break;
		case DERECHA:
			if((juego->laberinto_original[(juego->jugador.posicion.fil)][juego->jugador.posicion.col+1]!=PARED) && (juego->jugador.posicion.col+1)<TAMANIO)
				es_valido=true;
			break;
	}
	return es_valido;
}

//PRE: Recibe un jugador y un caracter.
//POS: Moverá el jugador hacia la dirección especificada. Dicho movimiento es válido.

void mover_jugador(jugador_t* jugador, char direccion){
	switch(direccion){
		case ARRIBA:
			jugador->posicion.fil-=1;
			break;
		case ABAJO:
			jugador->posicion.fil+=1;
			break;
		case IZQUIERZA:
			jugador->posicion.col-=1;
			break;
		case DERECHA:
			jugador->posicion.col+=1;
			break;
	}
}

//PRE: Recibe un rival, el laberinto ya inicializado y un caracter (en representacion a la direccion)
//POS: Verifica que la direccion del rival cumpla con un movimiento valido, es decir que no pise paredes ni que se vaya del laberinto.

bool movimiento_valido_rival(rival_t rival, char laberinto_original[TAMANIO][TAMANIO], char direccion){
	bool es_mov_valido=false;
	switch(direccion){
		case ABAJO:
			if(laberinto_original[rival.posicion.fil+1][rival.posicion.col]!=PARED && (rival.posicion.fil+1)<TAMANIO)
				es_mov_valido=true;
			break;
			
		case ARRIBA:
			if(laberinto_original[rival.posicion.fil-1][rival.posicion.col]!=PARED && (rival.posicion.fil-1)>=MINIMA_POSICION)
				es_mov_valido=true;
			break;
		case DERECHA:
			if(laberinto_original[rival.posicion.fil][rival.posicion.col+1]!=PARED && (rival.posicion.col+1)<TAMANIO)
				es_mov_valido=true;
			break;
		case IZQUIERZA:
			if(laberinto_original[rival.posicion.fil][rival.posicion.col-1]!=PARED &&(rival.posicion.col-1)>=MINIMA_POSICION)
				es_mov_valido=true;
			break;
	}
	return es_mov_valido;
}

//PRE: La cantidad de pasos del rival debe estar inicializada.
//POS: El procedimiento le asigna la posicion al rival de acuerdo al movimiento por turno
void obtener_direccion_rival(rival_t *rival){
	int movimiento_turno =(rival->cantidad_pasos)% 16;

	if(movimiento_turno>=0 && movimiento_turno<=3)
		rival->direccion= DERECHA;
	else if(movimiento_turno>3 && movimiento_turno<=7)
		rival->direccion= ABAJO;
	else if(movimiento_turno>7 && movimiento_turno<=11)
		rival->direccion= IZQUIERZA;
	else if(movimiento_turno>11 && movimiento_turno<=15)
		rival->direccion = ARRIBA;
}

// Moverá el rival a la próxima posición.
void mover_rival(juego_t* juego){

	bool se_movio =false;
	
	do{
		obtener_direccion_rival(&(juego->rival));
		if((juego->rival.direccion==DERECHA) && movimiento_valido_rival(juego->rival, juego->laberinto_original, juego->rival.direccion)){
			juego->rival.posicion.col +=1;
			se_movio=true;
		}else if((juego->rival.direccion==ABAJO) && movimiento_valido_rival(juego->rival, juego->laberinto_original, juego->rival.direccion)){
			juego->rival.posicion.fil+=1;
			se_movio=true;
		}else if((juego->rival.direccion==IZQUIERZA) && movimiento_valido_rival(juego->rival, juego->laberinto_original, juego->rival.direccion)){
			juego->rival.posicion.col -=1;
			se_movio=true;
		}else if((juego->rival.direccion==ARRIBA) && movimiento_valido_rival(juego->rival, juego->laberinto_original, juego->rival.direccion)){
			juego->rival.posicion.fil-=1;
			se_movio=true;
		}
		juego->rival.cantidad_pasos+=1;
	}while(se_movio==false);
}


/***POSICIONAMIENTOS***/


//devuelve verdadero si es que la posicion del jugador es igual a la posicion de la copa

bool tiene_la_copa(coordenada_t coordenada, copa_t copa){
	bool la_tiene= false;
	if(coordenada.fil == copa.posicion.fil  && coordenada.col == copa.posicion.col)
		la_tiene=true;
	return la_tiene;
}


//Posiciona la copa en el laberinto a mostrar

void posicionar_copa(juego_t* juego, char laberinto_aux[TAMANIO][TAMANIO]){
	laberinto_aux[juego->copa.posicion.fil][juego->copa.posicion.col]=COPA;
}


//Posiciona los obstaculos en el laberinto a mostrar

void posicionar_obstaculos(juego_t* juego, char laberinto_aux[TAMANIO][TAMANIO]){
	for(int i=0; i<(juego->tope_obstaculos); i++){
		laberinto_aux[juego->obstaculos[i].posicion.fil][juego->obstaculos[i].posicion.col]=juego->obstaculos[i].codigo;
	}
}

//Posiciona las ayudas del juego en el laberinto a mostrar

void posicionar_ayudas(juego_t* juego, char laberinto_aux[TAMANIO][TAMANIO]){
	for(int i=0; i<(juego->tope_ayudas); i++){
		laberinto_aux[juego->ayudas[i].posicion.fil][juego->ayudas[i].posicion.col]=juego->ayudas[i].codigo;
	}
}

//Posiciona el rival en el laberinto a mostrar

void posicionar_rival(juego_t* juego, char laberinto_aux[TAMANIO][TAMANIO]){
	laberinto_aux[juego->rival.posicion.fil][juego->rival.posicion.col]=RIVAL;
}

//Posiciona el rival en el laberinto a mostrar

void posicionar_jugador(juego_t* juego, char laberinto_aux[TAMANIO][TAMANIO]){
	laberinto_aux[juego->jugador.posicion.fil][juego->jugador.posicion.col]=JUGADOR;
}

//Posiciona en el laberinto a mostrar las paredes y espacios del laberinto original

void posicionar_laberinto(juego_t* juego, char laberinto_aux[TAMANIO][TAMANIO]){
	for(int i=0; i<TAMANIO; i++){
		for(int j=0; j<TAMANIO; j++){
			laberinto_aux[i][j]=juego->laberinto_original[i][j];
		}
	}
}

//Devuelve true si es que la Esfinge se encuentra dentro del vector de ayudas que tiene el jugador.
bool encontro_la_esfinge(ayuda_t ayudas[], int tope_ayudas){

	bool encontro_esfinge=false;
	for(int i= 0; i<tope_ayudas; i++){

		if(ayudas[i].codigo == ESFINGE){
			encontro_esfinge=true;
		}
	}
	return encontro_esfinge;
}

//Devolverá el estado del juego, 1 ganado, 0 en curso, -1 perdido.
int estado_juego(juego_t juego){
	int estado;

	bool jugador_tiene_la_copa= tiene_la_copa(juego.jugador.posicion, juego.copa);
	bool rival_tiene_la_copa = tiene_la_copa(juego.rival.posicion, juego.copa);

	if(jugador_tiene_la_copa){
		estado= JUEGO_GANADO;
	}
	else if(juego.jugador.vida<= SIN_VIDA || rival_tiene_la_copa){
		estado = JUEGO_PERDIDO;
	}
	else{
		estado = JUEGO_EN_CURSO;
	}
	
	return estado;
}

//Actualizará la matriz mostrada al usuario, con los elementos presentes en el juego.

void actualizar_laberinto(juego_t juego, char laberinto[TAMANIO][TAMANIO]){
	posicionar_laberinto(&juego, laberinto);
	posicionar_obstaculos(&juego, laberinto);
	posicionar_ayudas(&juego, laberinto);
	if(encontro_la_esfinge(juego.jugador.ayudas, juego.jugador.tope_ayudas) || (juego.jugador.vida)<= VIDA_APARICION_COPA){
		posicionar_copa(&juego, laberinto);
	}
	posicionar_rival(&juego, laberinto);
	posicionar_jugador(&juego, laberinto);
}


/***ACTUALIZACIONES***/


//Inserta la ayuda que encuentra el jugador al vector de ayudas del jugador.

void insertar_ayudas_jugador(ayuda_t ayudas_jugador[],int *tope_ayudas_jugador, ayuda_t ayuda_a_insertar){
	ayudas_jugador[(*tope_ayudas_jugador)]= ayuda_a_insertar;
	(*tope_ayudas_jugador)++;
}


//Elimina la ayuda que encontró el jugador del vector de ayudas del juego.

void eliminar_ayudas(ayuda_t ayudas[], int* tope_ayudas,int posicion){
	for(int i=posicion; i<(*tope_ayudas)-1; i++){
		ayudas[i]=ayudas[i+1];
	}
	(*tope_ayudas)--;
}

//Sumara los puntos de vida de la pocion al jugador. El jugador no puede tener mas de 50 puntos de vida.

void asignar_vida_pociones(jugador_t *jugador, ayuda_t ayudas[], int posicion){
	int supuesta_vida;
	supuesta_vida= jugador->vida + ayudas[posicion].vida_a_recuperar;
			if(supuesta_vida>MAX_VIDA){
				(jugador->vida)=MAX_VIDA;
			}else{
				jugador->vida=supuesta_vida;
			}
}

//Si el jugador esta sobre una ayuda, la cargara en el vector de ayudas de jugador o
//sumara los puntos de vida, segun sea el caso. Eliminara dicha ayuda del vector del juego.

void actualizar_ayudas(jugador_t *jugador, ayuda_t ayudas[], int *tope_ayudas){
	int pos=-1;
	for(int i=0; i<(*tope_ayudas);i++){
		if((ayudas[i].posicion.fil== jugador->posicion.fil) && (ayudas[i].posicion.col ==(jugador->posicion.col))){
			pos=i;
		}
	}
	if(pos!=-1){
		if(ayudas[pos].codigo==IMPEDIMENTA || ayudas[pos].codigo==RIDDIKULUS || ayudas[pos].codigo==ESFINGE){
			insertar_ayudas_jugador(jugador->ayudas, &jugador->tope_ayudas, ayudas[pos]);

		}else if(ayudas[pos].codigo==POCIONES){
			asignar_vida_pociones(jugador, ayudas, pos);
		}
		eliminar_ayudas(ayudas,tope_ayudas,pos);
		
	}
}

//Elimina el obstaculo que encontró el jugador del vector de obstaculos del juego.

void eliminar_obstaculos(obstaculo_t obstaculos[], int* tope_obstaculos, int pos){
	for(int i=pos; i<(*tope_obstaculos)-1;i++){
		obstaculos[i]=obstaculos[i+1];
	}
	(*tope_obstaculos)--;
}

//Verifica si tiene la ayuda necesaria para contrarrestar el obstaculo.

bool tiene_ayuda_necesaria(jugador_t jugador, obstaculo_t obstaculo){
	bool la_tiene=false;
	for(int j=0; j<(jugador.tope_ayudas);j++){
		if(obstaculo.codigo==ESCREGUTO && jugador.ayudas[j].codigo== IMPEDIMENTA){
			la_tiene=true;
		}else if(obstaculo.codigo==BOGGART && jugador.ayudas[j].codigo== RIDDIKULUS){
			la_tiene=true;
		}
	}
	return la_tiene;
}

//Si el jugador esta sobre un obstaculo, restara el daño segun sea el caso.
//Eliminara dicha ayuda del vector del juego.

void actualizar_obstaculos(jugador_t *jugador, obstaculo_t obstaculos[], int *tope_obstaculos){
	int posicion=-1;
	for(int i= 0; i<(*tope_obstaculos); i++){
		if(obstaculos[i].posicion.fil== jugador->posicion.fil && obstaculos[i].posicion.col== jugador->posicion.col){
			posicion=i;
		}
	}
	if(posicion != -1){
		if(tiene_ayuda_necesaria(*jugador, obstaculos[posicion])==false){
			jugador->vida -= obstaculos[posicion].danio;
		}
		eliminar_obstaculos(obstaculos,tope_obstaculos, posicion);	
	}
}

//Actualizará el juego. Restará vida si el jugador está sobre un obstáculo o lo
//eliminará si cuenta con el hechizo, aprenderá hechizos y todo lo que pueda suceder luego de un turno.

void actualizar_juego(juego_t* juego){
	(juego->jugador.vida)-=VIDA_POR_PASO;
	actualizar_ayudas(&juego->jugador,juego->ayudas, &juego->tope_ayudas);
	actualizar_obstaculos(&juego->jugador,juego->obstaculos, &juego->tope_obstaculos);
}