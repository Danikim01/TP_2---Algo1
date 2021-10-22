#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "detector_personajes.h"
#include "escape_laboratorio.h"
#include "utiles.h"

#define VALIDO  0
#define PERDIDO -1
#define GANADO 1

int main(){
  
  	srand((unsigned)time(NULL));
	
	printf("HOLA NOAH\n");
	printf("Dexter es un niño genio de 10 años, de pelo rojo, que tiene laboratorio lleno de inventos suyos al que accede pronunciando variadas contraseñas o activando los interruptores ocultos en un estante para libros, que es realmente una puerta.\n");
	printf("Dexter se encuentra constantemente en conflicto con su extremadamente escandalosa hermana Dee Dee, de 12 años, quien siempre logra entrar a su laboratorio a pesar de sus esfuerzos por mantenerla afuera.\n");
	printf("Pero, Dee Dee se las ingenia para merodear por su laboratorio, y terminar saboteando accidentalmente todos sus trabajos.\n");
	printf("Por eso, Dexter instaló un sistema de seguridad que, al detectar otro personaje, que no fuese él, se activa encerrando al personaje en habitaciones con obstáculos, guardias robots y artefactos raros, con una única forma de salir, obteniendo la llave maestra de dicha habitación.\n");
	printf("Pero Dee Dee conoce a su hermano, y sabía que algo raro estaba pasando con su laboratorio. Para asegurarse de que ella no corra peligro, te pide que vayas a recoger una de sus muñecas que dejó olvidada.\n");
	printf("A pesar de que has implementado su sistema de detección de personajes para poder burlarlo, eres reconocido como un intruso por el sistema, y tienes que escapar del laboratorio lo antes posible...\n");
	
	printf("Presione ENTER para detectar al personaje\n");
	while(getchar() != '\n');

	system("clear");
	char personaje_detectado;
	detectar_personaje(&personaje_detectado);
	
	while(getchar() != '\n');
	system("clear");
	printf("Salir del laboratorio es una tarea difícil pero no imposible, Dexter tiene una llave maestra protegida por ciertos artefactos y cosas para que no cualquiera la encuentre.\n");
	printf("La llave está escondida en el último de los 4 niveles de su laboratorio, y cada uno de estos niveles presenta algunas dificultades particulares.\n");
	printf("Una nota en la entrada del laboratorio reza el siguiente mandamiento: CUIDADO: En este laboratorio, las baldosas son resbaladizas!!\n");
	printf("Los personajes solo podrán moverse de una pared a la otra, es decir que sus movimientos no serán baldosa a baldosa, sino que al moverse, irán hasta la próxima pared.\n");

	printf("Presione ENTER para continuar\n");
	while(getchar() != '\n');


  	juego_t juego;

	inicializar_juego(&juego,personaje_detectado);

	
	char movimiento;

	while(estado_juego(juego) == VALIDO){
		mostrar_juego(juego);
		printf("Ingrese movimiento : \n");
		printf("(w)arriba - (s)abajo - (d)derecha - (a)izquierda \n");
		scanf(" %c",&movimiento);
		mover_personaje(&juego,movimiento);
	}


	if(estado_juego(juego) == PERDIDO){
		system("clear");
		printf("Has perdido el juego \n");
	} else if(estado_juego(juego) == GANADO){
		system("clear");
		printf("Has ganado el Juego!!\n");
	}
		
		
	return 0;

 }

