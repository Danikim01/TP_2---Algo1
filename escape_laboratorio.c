#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "escape_laboratorio.h"
#include "utiles.h"

#define MAX_OBSTACULOS 25
#define MAX_HERRAMIENTAS 25
#define MAX_NIVELES 4
#define MAX_PAREDES 250
#define DIMENSION_MAX 17
#define DIMENSION_MIN 12
#define DIVISOR 2
#define BELLOTA 'S'
#define CORAJE 'C'
#define BLUE 'B'
#define PURO_HUESO 'H'
#define POLLITO 'P'
#define JOHNNY_BRAVO 'J'
#define BALDOSAS_PINCHE 'P'
#define GUARDIAS_ROBOTS 'G'
#define BOMBA 'B'
#define INTERRUPTOR 'I'
#define MONEDA 'M'
#define BALDOSA_TP 'T'
#define LLAVE 'L'

#define PRIMER_NIVEL 0
#define SEGUNDO_NIVEL 1
#define TERCER_NIVEL 2
#define CUARTO_NIVEL 3

#define CANT_PINCHES_1 4
#define CANT_GUARDIAS_1 2
#define CANT_PINCHES_2 6
#define CANT_GUARDIAS_2 3
#define CANT_PINCHES_3 6
#define CANT_GUARDIAS_3 3
#define CANT_PINCHES_4 10
#define CANT_GUARDIAS_4 4
#define MAX_BALDOSAS_TP 4

#define ARRIBA 'w'
#define ABAJO 's'
#define DERECHA 'd'
#define IZQUIERDA 'a'

#define SALIDA 'S'

const int CANT_MOVIMIENTOS = 20;
const int NIVEL_UNO = 1;
const int NIVEL_DOS = 2;
const int NIVEL_TRES = 3;
const int NIVEL_CUATRO = 4;
const int CANT_LLAVES = 1;
const int CANT_BOMBAS = 1;
const int CANT_INTERRUPTOR = 1;

/*
* Pre : El numero de nivel que recibe tiene que estar entre 1 y 4
* Post : Devuelve la dimension del mapa segun el nivel: Si el nivel es par el tamaño del mapa es 17, 
* y en caso contrario, la dimension del mapa es 12. 
*/
int dimension_segun_nivel(int numero_nivel){
	int dimension = DIMENSION_MIN;
	if (numero_nivel % DIVISOR == 0){
		dimension = DIMENSION_MAX;
	}

	return dimension;
}

/*
* Pre : El struct nivel tiene que estar previamente incializado (caso contrario la funcion no recibe ningun elemento inicializado del struct).
* Las filas y columnas recibidas tienen que estar validadas previamente mediante bool coordenada_valida.
* Post : Valida si una posicion es adyacente o no a la fila y columna recibida si el tipo de obstaculo es BALDOSAS_PINCHE. 
* Si es adyacente devuelve true, sino devuelve false.
*/

bool es_adyacente(nivel_t* nivel,int fil_nueva,int col_nueva){
	bool esta_alado = false;
	for(int i = 0; i < nivel->tope_obstaculos;i++){
  		if(nivel->obstaculos[i].tipo == BALDOSAS_PINCHE){
  			if((nivel->obstaculos[i].posicion.fil == fil_nueva && nivel->obstaculos[i].posicion.col+1 == col_nueva) || 
		(nivel->obstaculos[i].posicion.fil == fil_nueva && nivel->obstaculos[i].posicion.col-1 == col_nueva ) || 
		(nivel->obstaculos[i].posicion.fil-1 == fil_nueva && nivel->obstaculos[i].posicion.col == col_nueva) ||
		(nivel->obstaculos[i].posicion.fil+1 == fil_nueva && nivel->obstaculos[i].posicion.col == col_nueva )){
			esta_alado = true;
    	}
  	}
   
  }
	return esta_alado;
}

/*
* Pre : El struct nivel tiene que estar previamente incializado (caso contrario la funcion no recibe ningun elemento inicializado del struct)
*.Las filas y columnas recibidas tienen que ser coordenas aleatorias dentro de la dimension del mapa.
* Post : Valida si una posicion es valida o no a la fila y columna recibida. La coordenada es valida si no choca 
* con ningun obstaculo,salida,entrada, y herramienta. Si es valida devuelve true, sino devuelve false.
*/

bool coordenada_valida(nivel_t* nivel,int fil, int col){

	bool esta_vacio = true;

	for(int i = 0; i < nivel->tope_paredes;i++ ){
      if(fil == nivel->paredes[i].fil && col == nivel->paredes[i].col){
         esta_vacio = false;

      }
   }
   	if((fil == nivel->entrada.fil && col == nivel->entrada.col) || (fil == nivel->salida.fil && col == nivel->salida.col)){
         esta_vacio = false;
      }
	
  
  	for(int i = 0; i < nivel->tope_obstaculos; i++ ){
     
      if(fil == nivel->obstaculos[i].posicion.fil && col == nivel->obstaculos[i].posicion.col){
         
         esta_vacio = false;
      	}
      }

    for(int i = 0; i < nivel->tope_herramientas; i++ ){
     
      if(fil == nivel->herramientas[i].posicion.fil && col == nivel->herramientas[i].posicion.col){
         
         esta_vacio = false;
      	}
      }


   return esta_vacio;
}

/*
* Post : genera posiciones validas dentro de las dimensiones del mapa, validadas por coordenada_valida.
*/

void obtener_posicion_vacia(nivel_t* nivel,int numero_nivel, int* fila, int* columna){
	int dimension = dimension_segun_nivel(numero_nivel);
	
	do{
		*fila = rand() % dimension;
		*columna = rand() % dimension;
	} while(!coordenada_valida(nivel,*fila,*columna));
}
/*
* Pre : El struct juego tiene que estar previamente incializado. Las filas y columnas recibidas tienen que ser coordenas aleatorias dentro de la dimension del mapa.
* Post : Valida si una posicion es valida o no a la fila y columna recibida. La coordenada es valida si no choca 
* con alguna pared,obstaculo,salida,entrada,herramienta, y con el personaje. Si es valida devuelve true, sino devuelve false.
*/
bool coordenada_valida2(juego_t* juego,int fil, int col){

	bool esta_vacio = true;

	for(int i = 0; i < juego->niveles[juego->nivel_actual - 1].tope_paredes;i++ ){
      if(fil == juego->niveles[juego->nivel_actual - 1].paredes[i].fil && col == juego->niveles[juego->nivel_actual - 1].paredes[i].col){
         esta_vacio = false;

      }
   }
   	if((fil == juego->niveles[juego->nivel_actual - 1].entrada.fil && col == juego->niveles[juego->nivel_actual - 1].entrada.col) || (fil == juego->niveles[juego->nivel_actual - 1].salida.fil && col == juego->niveles[juego->nivel_actual - 1].salida.col)){
         esta_vacio = false;
      }

    if((fil == juego->personaje.posicion.fil && col == juego->personaje.posicion.col) || (fil == juego->personaje.posicion.fil && col == juego->personaje.posicion.col)){
         esta_vacio = false;
      }
	
  
  	for(int i = 0; i < juego->niveles[juego->nivel_actual - 1].tope_obstaculos; i++ ){
     
      if(fil == juego->niveles[juego->nivel_actual - 1].obstaculos[i].posicion.fil && col == juego->niveles[juego->nivel_actual - 1].obstaculos[i].posicion.col){
         
         esta_vacio = false;
      	}
      }

    for(int i = 0; i < juego->niveles[juego->nivel_actual - 1].tope_herramientas; i++ ){
     
      if(fil == juego->niveles[juego->nivel_actual - 1].herramientas[i].posicion.fil && col == juego->niveles[juego->nivel_actual - 1].herramientas[i].posicion.col){
         
         esta_vacio = false;
      	}
      }


   return esta_vacio;
}

/*
* Pre  : Recibe un struct juego previamente inicializado.
* Post : genera posiciones validas dentro de las dimensiones del mapa, validadas por coordenada_valida2.
*/

void obtener_posicion_vacia2(juego_t* juego,int* fila,int* columna){
	int dimension = dimension_segun_nivel(juego->nivel_actual);

	do{
		*fila = rand() % dimension;
		*columna = rand() % dimension;
	} while(!coordenada_valida2(juego,*fila,*columna));
}

/*
* Pre : El numero de nivel tiene que estar entre 1 y 4.
* Post : Inicializa la posicion de la entrada del nivel, cuya posicion esta dentro de las dimensiones del mapa y 
* es validada por coordenada_valida.
*/

void inicializar_entrada(nivel_t* nivel,int numero_nivel){
	int dimension = dimension_segun_nivel(numero_nivel);
	int entrada_fila;
	int entrada_columna;
	do {
		entrada_fila = rand() % dimension;
		entrada_columna = rand() % dimension;
	} while(!coordenada_valida(nivel,entrada_fila,entrada_columna));
	nivel->entrada.fil = entrada_fila;
	nivel->entrada.col = entrada_columna;
}
/*
* Pre : El numero de nivel tiene que estar entre 1 y 4.
* Post : Inicializa la posicion de la salida del nivel, cuya posicion esta dentro de las dimensiones del mapa y 
* es validada por coordenada_valida.
*/
void inicializar_salida(nivel_t* nivel,int numero_nivel){
	int dimension = dimension_segun_nivel(numero_nivel);
	int salida_fila;
	int salida_columna;
	do {
		salida_fila = rand() % dimension;
		salida_columna = rand() % dimension;
	} while(!coordenada_valida(nivel,salida_fila,salida_columna));
	nivel->salida.fil = salida_fila;
	nivel->salida.col = salida_columna;
}
/*
* Pre : El numero de nivel tiene que estar entre 1 y 4.
* Post : Inicializa las posiciones,cantidad, y tipos de herramientas y obstaculos correspondientes al nivel,dependiendo de la cantidad elementos de los parametros recibidos.
- Ademas las posiciones de los obstaculos y herramientras son generadas obtener_posicion_vacia, el cual genera posiciones validas.
*/
void inicializar_obstaculos_y_herramientas(nivel_t* nivel,int numero_nivel, int cantidad_baldosas_pinches, 
	int cantidad_guardia, bool hay_bomba){

	int cantidad_bomba = 0;
	int fila,columna;
	int cantidad_monedas;
	int cantidad_baldosas_tp;
	int cantidad_interruptor = 0;
	int cantidad_llaves = 0;
	cantidad_monedas = cantidad_baldosas_pinches / DIVISOR;
	cantidad_baldosas_tp = cantidad_guardia;
	cantidad_interruptor = cantidad_bomba;
	cantidad_llaves = CANT_LLAVES;
	
	if(numero_nivel == MAX_NIVELES-1 || numero_nivel == MAX_NIVELES){
		hay_bomba = true;
		cantidad_bomba = CANT_BOMBAS;
		cantidad_interruptor = CANT_INTERRUPTOR;
	}

	int cantidad_obstaculos = cantidad_bomba + cantidad_baldosas_pinches + cantidad_guardia;

	while((nivel->tope_obstaculos) < cantidad_obstaculos){

		if (nivel->tope_obstaculos < cantidad_guardia){
				
				obtener_posicion_vacia(nivel,numero_nivel,&fila,&columna);
				nivel->obstaculos[nivel->tope_obstaculos].posicion.fil = fila;
				nivel->obstaculos[nivel->tope_obstaculos].posicion.col = columna;
				nivel->obstaculos[nivel->tope_obstaculos].tipo = GUARDIAS_ROBOTS;
				nivel->tope_obstaculos++;
		}
		else if((nivel->tope_obstaculos) < (cantidad_guardia + cantidad_baldosas_pinches)){
			
			if(nivel->tope_obstaculos == cantidad_guardia){
				obtener_posicion_vacia(nivel,numero_nivel,&fila,&columna);
				nivel->obstaculos[nivel->tope_obstaculos].posicion.fil = fila;
				nivel->obstaculos[nivel->tope_obstaculos].posicion.col = columna;
				nivel->obstaculos[nivel->tope_obstaculos].tipo = BALDOSAS_PINCHE;
				nivel->tope_obstaculos++;
			} else 
			{
				do{
					obtener_posicion_vacia(nivel,numero_nivel,&fila,&columna);
			}	while(!coordenada_valida(nivel,fila,columna) || !es_adyacente(nivel,fila,columna));

	 			nivel->obstaculos[nivel->tope_obstaculos].posicion.fil = fila;
				nivel->obstaculos[nivel->tope_obstaculos].posicion.col = columna;
				nivel->obstaculos[nivel->tope_obstaculos].tipo = BALDOSAS_PINCHE;
				nivel->tope_obstaculos++;
			}
		} 
		else {
			if(hay_bomba){
				obtener_posicion_vacia(nivel,numero_nivel,&fila,&columna);
				nivel->obstaculos[nivel->tope_obstaculos].posicion.fil = fila;
				nivel->obstaculos[nivel->tope_obstaculos].posicion.col = columna;
				nivel->obstaculos[nivel->tope_obstaculos].tipo = BOMBA;
				nivel->tope_obstaculos++;
			
			}
		
	
		}
	}


	int cantidad_herramientas = cantidad_monedas + cantidad_baldosas_tp + cantidad_interruptor + cantidad_llaves;
	

	while((nivel->tope_herramientas) < cantidad_herramientas){
		

		if (nivel->tope_herramientas < cantidad_baldosas_tp){
			
			obtener_posicion_vacia(nivel,numero_nivel,&fila,&columna);
			
				nivel->herramientas[nivel->tope_herramientas].posicion.fil = fila;
				nivel->herramientas[nivel->tope_herramientas].posicion.col = columna;
				nivel->herramientas[nivel->tope_herramientas].tipo = BALDOSA_TP;
				nivel->tope_herramientas++;
		}
		else if((nivel->tope_herramientas) < (cantidad_baldosas_tp + cantidad_monedas)){
			
			obtener_posicion_vacia(nivel,numero_nivel,&fila,&columna);
				
				nivel->herramientas[nivel->tope_herramientas].posicion.fil = fila;
				nivel->herramientas[nivel->tope_herramientas].posicion.col = columna;
				nivel->herramientas[nivel->tope_herramientas].tipo = MONEDA;
				nivel->tope_herramientas++;

		} else if ((nivel->tope_herramientas) < (cantidad_baldosas_tp + cantidad_monedas + cantidad_interruptor)){
			obtener_posicion_vacia(nivel,numero_nivel,&fila,&columna);
			
			
				if(hay_bomba){
					nivel->herramientas[nivel->tope_herramientas].posicion.fil = fila;
					nivel->herramientas[nivel->tope_herramientas].posicion.col = columna;
					nivel->herramientas[nivel->tope_herramientas].tipo = INTERRUPTOR;
					nivel->tope_herramientas++;
				}
			
			
		} else {
			obtener_posicion_vacia(nivel,numero_nivel,&fila,&columna);
			
				nivel->herramientas[nivel->tope_herramientas].posicion.fil = fila;
				nivel->herramientas[nivel->tope_herramientas].posicion.col = columna;
				nivel->herramientas[nivel->tope_herramientas].tipo = LLAVE;
				nivel->tope_herramientas++;
			
		}
	}
	
}

/*
 * Inicializara un nivel cargando su entrada,
 * salida, obtáculos, herramientas y paredes.
 */

void inicializar_nivel(nivel_t* nivel,int numero_nivel, int cantidad_baldosas_pinches, 
	int cantidad_guardia, bool hay_bomba){

	obtener_paredes(numero_nivel,nivel->paredes,&nivel->tope_paredes);

	nivel->tope_obstaculos = 0;
	nivel->tope_herramientas = 0;

	inicializar_entrada(nivel,numero_nivel);
	inicializar_salida(nivel,numero_nivel);
	inicializar_obstaculos_y_herramientas(nivel,numero_nivel, cantidad_baldosas_pinches,cantidad_guardia,hay_bomba);
    }

/*
 * Inicializará el juego, cargando la informacion de los cuatro niveles
 * y los datos del personaje.
 */
void inicializar_juego(juego_t* juego, char tipo_personaje){
		
	juego->nivel_actual = NIVEL_UNO;

	inicializar_nivel(&juego->niveles[PRIMER_NIVEL],NIVEL_UNO,CANT_PINCHES_1,CANT_GUARDIAS_1,false);
	inicializar_nivel(&juego->niveles[SEGUNDO_NIVEL],NIVEL_DOS,CANT_PINCHES_2,CANT_GUARDIAS_2,false);
	inicializar_nivel(&juego->niveles[TERCER_NIVEL],NIVEL_TRES,CANT_PINCHES_3,CANT_GUARDIAS_3,true);
	inicializar_nivel(&juego->niveles[CUARTO_NIVEL],NIVEL_CUATRO,CANT_PINCHES_4,CANT_GUARDIAS_4,true);

	juego->personaje.tipo = tipo_personaje;
	juego->personaje.tiene_llave = false;
	juego->personaje.presiono_interruptor = false;
	juego->personaje.murio = false;
	juego->personaje.posicion.fil = juego->niveles[juego->nivel_actual - 1].entrada.fil;
	juego->personaje.posicion.col = juego->niveles[juego->nivel_actual - 1].entrada.col;
	juego->personaje.movimientos = CANT_MOVIMIENTOS;
	
	
	
}

/*
 * Recibe un juego con todas sus estructuras válidas.
 * El juego se dará por ganado si el personaje está en el último nivel
 * y posicionado en la salida.
 * El juego se dará por perdido, si el personaje queda sin movimientos.
 * Devolverá:
 * ->  0 si el estado es jugando.
 * -> -1 si el estado es perdido.
 * ->  1 si el estado es ganado.
 */

int estado_juego(juego_t juego){
	int estado;
	estado = 0;
	if(juego.personaje.movimientos <= 0){
		estado = -1;
	} else if(juego.personaje.posicion.fil == juego.niveles[CUARTO_NIVEL].salida.fil && juego.personaje.posicion.col == juego.niveles[CUARTO_NIVEL].salida.col && juego.nivel_actual == NIVEL_CUATRO){
		estado = 1;
	} else {
		estado = 0;
	}
	return estado;
}

/*
 * Recibe el personaje con todas sus estructuras válidas, y la coordenada de la salida del nivel en ejecución.
 * El nivel se dará por ganado cuando el personaje se
 * posicione en la salida habiendo obtenido previamente la llave.
 * Devolverá:
 * ->  0 si el estado es jugando.
 * ->  1 si el estado es ganado.
 */
int estado_nivel(personaje_t personaje, coordenada_t salida){
	int estado = 0;
	if(personaje.posicion.fil == salida.fil && personaje.posicion.col == salida.col && personaje.tiene_llave){
		estado = 1;
	}
	return estado;
}
	
/*
* Pre : El struct juego tiene que estar previamente inicializado(en caso contrario la funcion no recibe nada).
* Post : Devuelve la posicion de la moneda agarrada por el personaje.
*/
int devolver_posicion_moneda_agarrada(juego_t juego){
  int i = 0;
  int posicion_buscada = -1;
  
 for(i = 0; i < juego.niveles[juego.nivel_actual -1 ].tope_herramientas;i++){
 	 if(juego.personaje.posicion.fil == juego.niveles[juego.nivel_actual -1 ].herramientas[i].posicion.fil && juego.personaje.posicion.col == juego.niveles[juego.nivel_actual -1 ].herramientas[i].posicion.col){
		if(juego.niveles[juego.nivel_actual -1 ].herramientas[i].tipo == MONEDA){
			posicion_buscada = i;

			}
		}
 }
 
  return posicion_buscada;
}

/*
* Pre : El struct juego tiene que estar previamente inicializado(en caso contrario la funcion no recibe nada).
* Post : Teniendo la posicion de la moneda agarrada por el personaje, si la agarro, la elimina del vector de herramientas y 
* si el personaje pasa por la moneda, le suma 1 movimiento.
*/
void agarrar_moneda(juego_t* juego){	

	int posicion_moneda = devolver_posicion_moneda_agarrada(*juego);

	for(int i = 0; i < juego->niveles[juego->nivel_actual - 1].tope_herramientas;i++){
		if(juego->personaje.posicion.fil == juego->niveles[juego->nivel_actual - 1].herramientas[i].posicion.fil && juego->personaje.posicion.col == juego->niveles[juego->nivel_actual - 1].herramientas[i].posicion.col){
			if(juego->niveles[juego->nivel_actual - 1].herramientas[i].tipo == MONEDA){

				juego->personaje.movimientos += 1;
				juego->niveles[juego->nivel_actual - 1].herramientas[posicion_moneda] = juego->niveles[juego->nivel_actual - 1].herramientas[juego->niveles[juego->nivel_actual - 1].tope_herramientas-1];
	    		(juego->niveles[juego->nivel_actual - 1].tope_herramientas)--;
				}
			}
		} 
}


/*
* Pre : El struct juego tiene que estar previamente inicializado(en caso contrario la funcion no recibe nada).
* Post : En caso de que el personaje se pare sobre una bomba, esta es eliminada del vector de obstaculos.
*/
void pisar_bomba(juego_t* juego){
  int i = 0;
  int posicion_buscada = 0;
  bool esta = false;

  while ((!esta) && (i < juego->niveles[juego->nivel_actual -1 ].tope_obstaculos)){
    if(juego->personaje.posicion.fil == juego->niveles[juego->nivel_actual -1 ].obstaculos[i].posicion.fil && juego->personaje.posicion.col == juego->niveles[juego->nivel_actual -1 ].obstaculos[i].posicion.col){
      if(juego->niveles[juego->nivel_actual -1 ].obstaculos[i].tipo == BOMBA){
      	posicion_buscada = i;
      	esta = true;
      }
    }
    i++;
  }

  if(esta){
    juego->niveles[juego->nivel_actual - 1].herramientas[posicion_buscada] = juego->niveles[juego->nivel_actual - 1].obstaculos[(juego->niveles[juego->nivel_actual - 1].tope_obstaculos)-1];
    (juego->niveles[juego->nivel_actual - 1].tope_obstaculos)--;
  }
	
}


/*
* Pre : El struct juego tiene que estar previamente inicializado(en caso contrario la funcion no recibe nada).
* Post : Si el personaje se para sobre una llave, el elemento tiene_llave dentro del struct juego, se vuelve verdadera. 
* O sea que el personaje efectivamente agarra una llave. 
*/
void agarrar_llave(juego_t* juego){
	for(int i = 0; i < juego->niveles[juego->nivel_actual - 1].tope_herramientas;i++){
		if(juego->personaje.posicion.fil == juego->niveles[juego->nivel_actual - 1].herramientas[i].posicion.fil && juego->personaje.posicion.col == juego->niveles[juego->nivel_actual - 1].herramientas[i].posicion.col){
			if(juego->niveles[juego->nivel_actual - 1].herramientas[i].tipo == LLAVE){
				juego->personaje.tiene_llave = true;
			} 
		}
	} 
}
/*
* Pre : El struct juego tiene que estar previamente inicializado(en caso contrario la funcion no recibe nada).
* Post : Si el personaje se para sobre un interruptor, el elemento presiono_interruptor dentro del struct juego, se vuelve verdadera. 
* O sea que el personaje efectivamente presiona un interruptor. 
*/
void agarrar_interruptor(juego_t* juego){
	for(int i = 0; i < juego->niveles[juego->nivel_actual - 1].tope_herramientas;i++){
		if(juego->personaje.posicion.fil == juego->niveles[juego->nivel_actual - 1].herramientas[i].posicion.fil && juego->personaje.posicion.col == juego->niveles[juego->nivel_actual - 1].herramientas[i].posicion.col){
			if(juego->niveles[juego->nivel_actual - 1].herramientas[i].tipo == INTERRUPTOR){
				juego->personaje.presiono_interruptor = true;
			} 		}
	} 
}

/*
* Pre : El struct juego tiene que estar previamente inicializado(en caso contrario la funcion no recibe nada).
* Post : Si el personaje se para sobre un pinche, le resta 2 movimientos. 
*/

void restar_movimientos_pinches(juego_t* juego){	

for(int i = 0; i < juego->niveles[juego->nivel_actual - 1].tope_obstaculos;i++){
	if(juego->personaje.posicion.fil == juego->niveles[juego->nivel_actual - 1].obstaculos[i].posicion.fil && juego->personaje.posicion.col == juego->niveles[juego->nivel_actual - 1].obstaculos[i].posicion.col){
		
		if(juego->niveles[juego->nivel_actual - 1].obstaculos[i].tipo == BALDOSAS_PINCHE && juego->personaje.tipo != PURO_HUESO && juego->personaje.tipo != POLLITO )
			juego->personaje.movimientos -= 2;
		}
	}

}

/*
* Pre : El struct juego tiene que estar previamente inicializado(en caso contrario la funcion no recibe nada).
* Post : Si el personaje se para en una BALDOSA_TP se cambia de posicion a la siguiente baldosa que se encuentre en vector coordenada_t que fue incializada
* por coordenadas de BALDOSA_TP. Si la posicion del personaje coincide con el la baldosa de la posicion final, su posicion se le asigna a la primera BALDOSA_TP
* que se encuentre dentro del vector coordada_tp.
*/

void telenstransportar(juego_t* juego){
	
	int tope_vector = 0;
	coordenada_t coordenada_tp[MAX_BALDOSAS_TP];
	int inicial;

	for(int i = 0; i < juego->niveles[juego->nivel_actual-1].tope_herramientas;i++){
		if(juego->niveles[juego->nivel_actual-1].herramientas[i].tipo == BALDOSA_TP){
			coordenada_tp[tope_vector].fil = juego->niveles[juego->nivel_actual-1].herramientas[i].posicion.fil;
			coordenada_tp[tope_vector].col = juego->niveles[juego->nivel_actual-1].herramientas[i].posicion.col;
			tope_vector++;
		}
	}
	
	int posicion_fin = tope_vector - 1;

	for(inicial = 0; inicial < tope_vector;inicial++){
		if(juego->personaje.posicion.fil == coordenada_tp[inicial].fil && juego->personaje.posicion.col == coordenada_tp[inicial].col){
			if(inicial == posicion_fin){
				juego->personaje.posicion.fil = coordenada_tp[0].fil;
				juego->personaje.posicion.col = coordenada_tp[0].col;
			} else if (inicial < posicion_fin){
				juego->personaje.posicion.fil = coordenada_tp[inicial + 1].fil;
				juego->personaje.posicion.col = coordenada_tp[inicial + 1].col;
				return;
			}
		}
	}
}

/*
* Pre : El struct juego tiene que estar previamente inicializado(en caso contrario la funcion no recibe nada).
* Post : Si el personaje se coloca sobre un guardia o una bomba muere. En caso de que el personaje sea Johnny Bravo o Coraje, estos 
* no seran afectados por los guarias Robots y en caso de que el personaje sea Bellota o Blue, ambos tendran una segunda oportunidad, es decir,
* Si se mueren por primera vez, sea porque se chocan contra los guardias robots, contra las bombas o pierden todos sus movimientos, tienen una segunda oportunidad
* con CANT_MOVIMIENTOS movimientos adicionales.
*/

void perder_movimientos(juego_t* juego){

	for(int i = 0; i < juego->niveles[juego->nivel_actual - 1].tope_obstaculos;i++){
		if(juego->personaje.posicion.fil == juego->niveles[juego->nivel_actual - 1].obstaculos[i].posicion.fil && juego->personaje.posicion.col == juego->niveles[juego->nivel_actual - 1].obstaculos[i].posicion.col){
			if(juego->niveles[juego->nivel_actual - 1].obstaculos[i].tipo == GUARDIAS_ROBOTS && juego->personaje.tipo != JOHNNY_BRAVO && juego->personaje.tipo != CORAJE){
				
				if(!juego->personaje.murio && (juego->personaje.tipo == BELLOTA || juego->personaje.tipo == BLUE)){
					juego->personaje.movimientos = CANT_MOVIMIENTOS;
        			juego->personaje.murio = true;
					}
				else
					{
        			juego->personaje.movimientos -= juego->personaje.movimientos;
					juego->personaje.murio = true;	
					}
				
				} if(juego->niveles[juego->nivel_actual - 1].obstaculos[i].tipo == BOMBA){
				
					if(!juego->personaje.murio && (juego->personaje.tipo == BELLOTA || juego->personaje.tipo == BLUE)){
						juego->personaje.movimientos = CANT_MOVIMIENTOS;
	        			juego->personaje.murio = true;
						}
					else
						{
	        			juego->personaje.movimientos -= juego->personaje.movimientos;
						juego->personaje.murio = true;	
						}
				
					}
					
				} 
				
				
			} 

			if(juego->personaje.movimientos <= 0){
				if(!juego->personaje.murio && (juego->personaje.tipo == BELLOTA || juego->personaje.tipo == BLUE)){
						juego->personaje.movimientos = CANT_MOVIMIENTOS;
	        			juego->personaje.murio = true;
						}
					else
						{
	        			juego->personaje.movimientos -= juego->personaje.movimientos;
						juego->personaje.murio = true;	
						}
			}
		}



/*
* Pre : El struct juego tiene que estar previamente inicializado(en caso contrario la funcion no recibe nada) y recibe una coordenada de movimiento.
* Post : Si la coordenada por donde se va a realizar el cambio de posicion hay una pared devuelve true, en caso contrario ,false.
*/
bool hay_pared(juego_t* juego, coordenada_t coordenada){
	bool hay_pared = false;
	for(int i = 0; i < juego->niveles[juego->nivel_actual - 1].tope_paredes;i++){
		if((coordenada.fil == juego->niveles[juego->nivel_actual - 1].paredes[i].fil) && (coordenada.col == juego->niveles[juego->nivel_actual - 1].paredes[i].col)){
			hay_pared = true;
		} 
	}
	return hay_pared;
}

/*
* Pre : El struct juego tiene que estar previamente inicializado(en caso contrario la funcion no recibe nada), recibe una direccion de movimiento que puede ser 
* ARRIBA, ABAJO, IZQUIEDA,O DERECHA,y tambien recibe una coordenada, que es una coordenada valida del personaje posicionada en la entrada del nivel.
* Post : Si la coordenada por donde se va a realizar el cambio de posicion no puede realizar el movimiento y en caso de que haya una pared no realiza el movimiento.
*/

bool puede_moverse(juego_t* juego,coordenada_t coordenada,char movimiento){
	
		if(movimiento == ARRIBA){
			coordenada.fil--;
			
			return(!hay_pared(juego,coordenada));
		} else if(movimiento == IZQUIERDA){
			coordenada.col--;
			
			return(!hay_pared(juego,coordenada));
		} else if(movimiento == ABAJO){
			coordenada.fil++;
			
			return(!hay_pared(juego,coordenada));
		} else {
			coordenada.col++;
			
			return(!hay_pared(juego,coordenada));
		}
}

/*
* Pre : El struct juego tiene que estar previamente inicializado(en caso contrario la funcion no recibe nada), y recibe un bool por referencia inicializado en true.
* Post : Es una funcion que me regula el movimiento, es decir, va a dejar de moverse si la coordenada en donde esta hay una salida (si tiene la llave) , una entrada, una bomba 
* o un guardia (si el personaje no es coraje o johnny bravo.
*/
void regular_movimiento(juego_t juego,bool* movete){
	
	
	for(int i = 0; i < juego.niveles[juego.nivel_actual -1 ].tope_obstaculos;i++){
		if(juego.personaje.posicion.fil == juego.niveles[juego.nivel_actual -1 ].obstaculos[i].posicion.fil && juego.personaje.posicion.col == juego.niveles[juego.nivel_actual -1 ].obstaculos[i].posicion.col){
			if(juego.niveles[juego.nivel_actual -1 ].obstaculos[i].tipo == GUARDIAS_ROBOTS && juego.personaje.tipo != CORAJE && juego.personaje.tipo != JOHNNY_BRAVO && juego.personaje.tipo != BELLOTA && juego.personaje.tipo != BLUE){
				*movete = false;
			} else if(juego.niveles[juego.nivel_actual -1 ].obstaculos[i].tipo == BOMBA && juego.personaje.tipo != BELLOTA && juego.personaje.tipo != BLUE ){
				*movete = false;
			}
		}
	}
	
	
	for(int i = 0; i < juego.niveles[juego.nivel_actual -1 ].tope_herramientas;i++){

		if(juego.personaje.posicion.fil == juego.niveles[juego.nivel_actual -1 ].herramientas[i].posicion.fil && juego.personaje.posicion.col == juego.niveles[juego.nivel_actual -1 ].herramientas[i].posicion.col){
			if(juego.niveles[juego.nivel_actual -1 ].herramientas[i].tipo == BALDOSA_TP){
			*movete = false;
			} 
		}
		
	}
	
	if(juego.personaje.posicion.fil == juego.niveles[juego.nivel_actual -1 ].salida.fil && juego.personaje.posicion.col == juego.niveles[juego.nivel_actual -1 ].salida.col && juego.personaje.tiene_llave){
		*movete = false;
	}
	if(juego.personaje.posicion.fil == juego.niveles[juego.nivel_actual -1 ].entrada.fil && juego.personaje.posicion.col == juego.niveles[juego.nivel_actual -1 ].entrada.col){
		*movete = false;
	}

}



/*
* Pre : El struct juego tiene que estar previamente inicializado(en caso contrario la funcion no recibe nada).
* Post : Asigna posiciones aleatorias validadas por obtener_posicion_vacia2 a los guardias.
*/

void cambiar_posicion_guardias(juego_t* juego){
	int fila,columna;
	for(int i = 0; i< juego->niveles[juego->nivel_actual - 1].tope_obstaculos;i++){
		if( juego->niveles[juego->nivel_actual - 1].obstaculos[i].tipo == GUARDIAS_ROBOTS){
			
			obtener_posicion_vacia2(juego,&fila,&columna);
			juego->niveles[juego->nivel_actual - 1].obstaculos[i].posicion.fil = fila;
			juego->niveles[juego->nivel_actual - 1].obstaculos[i].posicion.col = columna;


		}
	}
}

/*
* Pre : El struct juego tiene que estar previamente inicializado(en caso contrario la funcion no recibe nada).
* Post : Por cada movimiento que realice el personaje, este realiza interacciones con sus alrededores, esta funcion revisa cuales son las consecuencias de dichas interacciones como resultado de las funciones
* agarrar_moneda, agarrar_llave, agarra_interruptor, restar_movimientos_pinches,perder_movimientos y telenstrasportar. Por otra parte, la funcion pasa al nivel siguiente si ve que 
* el resultado de la funcion estado_nivel da 1 como consecuencia de pasar de nivel o ganar el nivel. 
*/

void interacciones_personaje(juego_t* juego){

	agarrar_moneda(juego);
	agarrar_llave(juego);
	agarrar_interruptor(juego);
	restar_movimientos_pinches(juego);
	perder_movimientos(juego);
	telenstransportar(juego);
	pisar_bomba(juego);

	if((estado_nivel(juego->personaje,juego->niveles[juego->nivel_actual - 1].salida) == 1) && (juego->nivel_actual <= CUARTO_NIVEL)){
		juego->nivel_actual++;
		juego->personaje.movimientos += CANT_MOVIMIENTOS;
		juego->personaje.tiene_llave = false;
		juego->personaje.presiono_interruptor = false;
		juego->personaje.posicion = juego->niveles[juego->nivel_actual-1].entrada;
	}
	
}

/*
 * Mueve el personaje en la dirección indicada por el usuario
 * y actualiza el juego según los elementos que haya en el camino
 * del personaje.
 * El juego quedará en un estado válido al terminar el movimiento.
 * El movimiento será:
 * -> w: Si el personaje debe moverse para la arriba.
 * -> d: Si el personaje debe moverse para la derecha.
 * -> s: Si el personaje debe moverse para la abajo.
 * -> a: Si el personaje debe moverse para la izquierda.
 * En caso de que en la dirección que se quiere mover haya una pared
 * se contará como un movimiento, los guardias se moverán y
 * el personaje quedará en la misma baldosa.
 */

void mover_personaje(juego_t* juego,char movimiento){
	
	bool movete = true;

	juego->personaje.movimientos--;

	while(movete && puede_moverse(juego,juego->personaje.posicion,movimiento)){
		
		if(movimiento == ARRIBA){
			juego->personaje.posicion.fil--;
			interacciones_personaje(juego);
			regular_movimiento((*juego),&movete);
		
			
		} else if(movimiento == IZQUIERDA){
			juego->personaje.posicion.col--;
			interacciones_personaje(juego);
			regular_movimiento((*juego),&movete);
			
			
		} else if(movimiento == ABAJO){
			juego->personaje.posicion.fil++;
			interacciones_personaje(juego);
			regular_movimiento((*juego),&movete);
			
			
		} else if(movimiento == DERECHA){
			juego->personaje.posicion.col++;
			interacciones_personaje(juego);
			regular_movimiento((*juego),&movete);
			
			
		}
		mostrar_juego(*juego);
		detener_el_tiempo(0.125);
	}


	cambiar_posicion_guardias(juego);
	
	
}

/*
* Pre : El struct juego tiene que estar previamente inicializado(en caso contrario la funcion no recibe nada).
* Post : Llena o inicializa el mapa con todos sus elementos correspondientes: Se llenan las paredes con un determinado caracter,se llena el mapa 
* con obstaculos, y herramientas. A su vez, se define con que caracter se va a ver representando el personaje en el mapa.
*/

void llenar_mapa(juego_t juego,char matriz[MAX_PAREDES][MAX_PAREDES]){

	int dimension_matriz = dimension_segun_nivel(juego.nivel_actual);

	for (int i = 0; i < dimension_matriz; i++){
		for (int j = 0; j < dimension_matriz; j++){
			matriz[i][j] = ' ';
		}
	}

	for (int i = 0; i < juego.niveles[juego.nivel_actual -1 ].tope_paredes; i++){

		matriz[juego.niveles[juego.nivel_actual -1 ].paredes[i].fil][juego.niveles[juego.nivel_actual -1 ].paredes[i].col] = '*';
		
	}
	
	for (int i = 0; i < juego.niveles[juego.nivel_actual -1 ].tope_herramientas; i++){
		if(juego.nivel_actual == NIVEL_UNO || juego.nivel_actual == NIVEL_DOS){
			matriz[juego.niveles[juego.nivel_actual -1 ].herramientas[i].posicion.fil][juego.niveles[juego.nivel_actual -1 ].herramientas[i].posicion.col] = juego.niveles[juego.nivel_actual -1 ].herramientas[i].tipo;
		}
		else if(juego.nivel_actual == NIVEL_TRES || juego.nivel_actual == NIVEL_CUATRO){
				if(juego.niveles[juego.nivel_actual -1].herramientas[i].tipo != LLAVE){
					matriz[juego.niveles[juego.nivel_actual -1 ].herramientas[i].posicion.fil][juego.niveles[juego.nivel_actual -1 ].herramientas[i].posicion.col] = juego.niveles[juego.nivel_actual -1 ].herramientas[i].tipo;
				}
		}
	}
	
	if(juego.personaje.presiono_interruptor){
		printf("Activaste el interruptor!\n");
		for(int i = 0; i < juego.niveles[juego.nivel_actual-1].tope_herramientas;i++){
			if(juego.niveles[juego.nivel_actual -1].herramientas[i].tipo == LLAVE){
				matriz[juego.niveles[juego.nivel_actual-1].herramientas[i].posicion.fil][juego.niveles[juego.nivel_actual-1].herramientas[i].posicion.col] = juego.niveles[juego.nivel_actual-1].herramientas[i].tipo;
			}
			
					
		}
	}
				 
	if(juego.personaje.tiene_llave){
		printf("Agarraste la Llave!\n");
		matriz[juego.niveles[juego.nivel_actual -1 ].salida.fil][juego.niveles[juego.nivel_actual -1 ].salida.col] = SALIDA;
	}

	
	for (int i = 0; i < juego.niveles[juego.nivel_actual -1 ].tope_obstaculos; i++){
		
    	matriz[juego.niveles[juego.nivel_actual -1 ].obstaculos[i].posicion.fil][juego.niveles[juego.nivel_actual -1 ].obstaculos[i].posicion.col] = juego.niveles[juego.nivel_actual -1 ].obstaculos[i].tipo;

	}

	matriz[juego.personaje.posicion.fil][juego.personaje.posicion.col] = juego.personaje.tipo;
	
}
/*
* Pre: Recibe un struct personaje_t que tiene que tener el personaje cargado del tp1.
* Post: Muestra por pantalla el personaje seleccionado y su respectiva habilidad.
*/
void mostrar_personaje_y_habilidades(personaje_t personaje){
	if(personaje.tipo == CORAJE){
		printf("Tu personaje es CORAJE\n");
		printf("Habilidad : No es afectado por los guardias robots  ('G')\n");
	} else if(personaje.tipo == JOHNNY_BRAVO){
		printf("Tu personaje es JOHNNY BRAVO\n");
		printf("Habilidad : No es afectado por los guardias robots ('G')\n");
	} else if(personaje.tipo == BELLOTA){
		printf("Tu personaje es BELLOTA\n");
		printf("Habilidad : Obtiene una segunda oportunidad con 10 movimientos adicionales si es que muere\n");
	} else if(personaje.tipo == BLUE){
		printf("Tu personaje es BLUE\n");
		printf("Habilidad : Obtiene una segunda oportunidad con 10 movimientos adicionales si es que muere\n");
	} else if(personaje.tipo == PURO_HUESO){
		printf("Tu personaje es PURO_HUESO\n");
		printf("Habilidad: No es afectado por los pinches ('P')\n");
	} else {
		printf("Tu personaje es POLLITO\n");
		printf("Habilidad: No es afectado por los pinches ('P')\n");
	}
}
/*
 * Mostrará el juego por pantalla.
 * Se recomienda mostrar todo aquello que le sea de
 * utilidad al jugador, como los movimientos restantes,
 * el nivel, los obstaculos posicionados, las paredes, etc.
 */
void mostrar_juego(juego_t juego){

	system("clear");
	char matriz[MAX_PAREDES][MAX_PAREDES];
	int dimension_matriz = dimension_segun_nivel(juego.nivel_actual);
	llenar_mapa(juego,matriz);
	
	mostrar_personaje_y_habilidades(juego.personaje);

	printf("NIVEL : %d\n",juego.nivel_actual);

	printf("Movimientos restantes : %d\n",juego.personaje.movimientos);

	for (int i = 0; i < dimension_matriz; i++){
		for (int j = 0; j < dimension_matriz; j++){
			printf(" %c ", matriz[i][j]);
		}
		printf("\n");
	}

	if(juego.nivel_actual == NIVEL_UNO || juego.nivel_actual == NIVEL_DOS){
		printf("'P':Baldosas pinche,'G':Guardias Robots,'M':Algocoins,'T':Baldosas Telenstransportadoras,'L':Llave\n");
	} else if (juego.nivel_actual == NIVEL_TRES || juego.nivel_actual == NIVEL_CUATRO){
		printf("'P':Baldosas pinche,'G':Guardias Robots,'M':Algocoins,'T':Baldosas Telenstransportadoras,'I':Interruptor,'L':Llave,'B':Bomba\n");
	}
	
	
}


	