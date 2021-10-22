#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "detector_personajes.h"

const int MAX_NACIMIENTO = 2008;
const int MIN_NACIMIENTO = 1988;
const int MIN_TALLA = 33;
const int MAX_TALLA = 47;
const int TALLA_CERO = 0;
const int MIN_ALTURA = 10;
const int MAX_ALTURA = 250;
const int MAX_TALLA_2 = 37;
const int MIN_TALLA_3 = 38;
const int MAX_TALLA_3 = 42;
const int MIN_TALLA_4 = 43;
const int PUNTAJE_MIN = 1;
const int PUNTAJE_MAX_1 = 80;
const int PUNTAJE_MIN_2 = 81;
const int PUNTAJE_MAX_2 = 160;
const int PUNTAJE_MIN_3 = 161;
const int PUNTAJE_MAX = 240;
const char DULCE = 'D';
const char SALADO = 'S';
const char AMARGO = 'A';
const int PUNTAJE_AMARGO = 20;
const int PUNTAJE_SALADO = 5;
const int PUNTAJE_DULCE = 15;
const int CERO = 0;
const int DIVISOR_NACIMIENTO = 20;
const int PUNTOS_ROSA_AMARILLO = 5;
const int PUNTOS_NEGRO_BLANCO = 15;
const int PUNTOS_AZUL_VERDE = 20;
const char VALIDO = 'V';
const char NO_VALIDO = 'F';
const char ES_VALIDO = 'V';
const char INVALIDO = 'F';
const char AMARILLO = 'Y';
const char AZUL = 'A';
const char VERDE = 'V';
const char NEGRO = 'N';
const char BLANCO = 'B';
const char ROSA = 'R';
const int POR_UNO = 1;
const int POR_DOS = 2;
const int POR_TRES = 3;
const int POR_CUATRO = 4;
const int NOSE = 0;
const int ALTURA_JOHNNY = 180;
const int ALTURA_BELLOTA = 120;
const int ALTURA_POLLITO = 50;
const int ALTURA_BLUE = 140;
const int ALTURA_PURO_HUESO = 200;
const int ALTURA_CORAJE = 30;
const int NOSE2 = 0;
const char JOHNNY = 'J' ;
const char BELLOTA = 'B' ;
const char POLLITO =  'P' ;
const char BLUE = 'L';
const char PURO_HUESO = 'H';
const char CORAJE = 'C';
const char ES_PERSONAJE = 'S';

/*
Pre condiciones: -
Post condiciones: devuelve 1 si la fecha ingresada esta entre MIN_NACIMIENTO Y MAX_NACIMIENTO, 
sino devuelve 0.
*/
bool es_fecha_de_nacimiento_valido (int* fecha){

	return ((*fecha >= MIN_NACIMIENTO) && (*fecha <= MAX_NACIMIENTO));
}

/*
Pre condiciones : -
Post condiciones : devuelve 'V' si el sabor ingresado es DULCE, SALADO O AMARGO, sino 
devuelve 'F'
*/

char es_sabor_valido (char* sabor){

	char retorno = VALIDO;

	if (*sabor != DULCE && 
		*sabor != SALADO &&
		*sabor != AMARGO)
	{

		retorno = NO_VALIDO;
	}

	return retorno;
}

/*
Pre condiciones: -
Post condiciones: devuelve 1 si la talla ingresada esta entre MIN_TALLAY MAX_TALLA, 
sino devuelve 0.
*/

bool es_talla_valido(int* talla){

	return  (((*talla >= MIN_TALLA) && (*talla <= MAX_TALLA)) || (*talla == TALLA_CERO));
}

/*
Pre condiciones : -
Post condiciones : devuelve 'V' si el color esta entre los válidos, sino 
devuelve 'F'.
*/

char es_color_valido (char* color) {

	char retorno2 = ES_VALIDO;

	if( *color != AMARILLO && 
		*color != AZUL &&
		*color != NEGRO &&
		*color != ROSA &&
		*color != BLANCO &&
		*color != VERDE) {

		retorno2 = INVALIDO;
	}

	return retorno2;
}

/*
Pre condiciones: -
Post condiciones: devuelve 1 si la altura ingresada esta entre MIN_ALTURA MAX_ALTURA, 
sino devuelve 0.
*/

bool son_alturas_validas(int* alturas){

return ( (*alturas >= MIN_ALTURA) && (*alturas <= MAX_ALTURA) );

}

/*
Pre condiciones : Los sabores ingresadas tienen que ser AMARGO, DULCE, O SALADO
Post condiciones : devuelve PUNTAJE_AMARGO si el sabor es amargo, PUNTAJE_SALADO si es salado, 
y PUNTAJE DULCE si es dulce.
*/

int asignar_puntos_por_sabores(char sabores) {

	int numero_a_asignar = CERO;

	if (sabores == AMARGO) {

		numero_a_asignar = PUNTAJE_AMARGO;
	}
	if (sabores == SALADO) {

		numero_a_asignar = PUNTAJE_SALADO;
	}
	if (sabores == DULCE) {

		numero_a_asignar = PUNTAJE_DULCE;
	}

	return numero_a_asignar;
}

/*
Pre condiciones : Las fechas ingresadas tienen que estar entre MIN_NACIMIENTO Y MAX_NACIMIENTO.
Post condiciones : devuelve el resto del cociente entre la altura y 20, sumado 1.
*/

int puntaje_por_fecha( int fecha_nacimiento){

	int puntos_nacimiento = ((fecha_nacimiento % DIVISOR_NACIMIENTO) + POR_UNO);

	return puntos_nacimiento;
}

/*
Pre condiciones : Los colores ingresados deben estar entre los validados.
Post condiciones : devuelve PUNTOS_ROSA_AMARILLO si el color es rosa o amarillo, 
PUNTOS_NEGRO_BLANCO si es negro o blanco, y PUNTOS_AZUL_VERDE si es azul o verde.
*/

int asignar_puntos_colores(char colores){

	int puntaje_a_asignar = CERO;

	if ((colores == ROSA) || (colores == AMARILLO)){

		puntaje_a_asignar = PUNTOS_ROSA_AMARILLO;

		}

	if ((colores == NEGRO) || (colores == BLANCO)){

		puntaje_a_asignar = PUNTOS_NEGRO_BLANCO;

		}

	if ( (colores == AZUL) || (colores == VERDE)){

		puntaje_a_asignar = PUNTOS_AZUL_VERDE;
	}

	return puntaje_a_asignar;

	}

/*
Pre condiciones : Las tallas ingresados deben estar entre MIN_TALLA Y MAX_TALLA.
Post condiciones : devuelve POR_DOS si talla está entre MIN_TALLA Y MAX_TALLA_2, POR_TRES si está entre MIN_TALLA_3 Y MAX_TALLA_3, y 
POR_CUATRO si está entre MIN_TALLA_4 Y MAX_TALLA.
*/

int multiplicador_talla_zapatos (int talla_zapato){

	int retornar = NOSE;


	if ((talla_zapato >= MIN_TALLA) && (talla_zapato <= MAX_TALLA_2)){

		retornar = POR_DOS;
	}

	else if ( (talla_zapato >= MIN_TALLA_3) && (talla_zapato <= MAX_TALLA_3) ){

		retornar = POR_TRES;

		}

	else if ((talla_zapato >= MIN_TALLA_4) && (talla_zapato <= MAX_TALLA)){

		retornar = POR_CUATRO;

		}

	else if ( (talla_zapato) == CERO ){

		retornar = POR_UNO;
	}
	
	return retornar;
}

/*
Pre condiciones : 
- Los sabores, las fechas, los colores, y las tallas ingresadas tienen que estar dentro del rango validado.
 
Post condiciones : devuelve el resultado algebraico de hacer la suma de los puntajes de sabores, colores, y fechas 
multiplcado por el puntaje de la talla. 
*/

int calcular_puntos_totales(char sabores, int fecha_nacimiento, char colores, int talla_zapato){

	int asignacion_sabores = asignar_puntos_por_sabores (sabores);
	int asignacion_fechas = puntaje_por_fecha (fecha_nacimiento);
	int asignacion_colores = asignar_puntos_colores(colores);
	int multiplicador_por_talla = multiplicador_talla_zapatos(talla_zapato);

	int puntaje_total = ((asignacion_sabores + asignacion_colores + asignacion_fechas) * multiplicador_por_talla);
	
	return puntaje_total;

}

/*
Pre condiciones : 
- La altura ingresada tiene que estar dentro del rango validado.

Post condiciones : 
- Devuelve POR_UNO si el valor absoluto de la diferencia de alturas entre el personaje 1 y 
la altura ingresada es menor o igual al valor absoluto de la diferencia de alturas entre el personaje dos y la altura ingresada,
devuelve 2 si el valor absoluto de la diferencia de alturas entre el personaje 1 y 
la altura ingresada es mayor  al valor absoluto de la diferencia de alturas entre el personaje dos y la altura ingresada, 
y devuelve 3 en el resto de los casos.
*/

int calcular_diferencia_altura(int altura1, int altura2, int altura){

	int retorno3 = NOSE2;


	int diferencia_personaje_1 = abs(altura1 - altura);
	int diferencia_personaje_2 = abs(altura2 - altura);
	

	if ( diferencia_personaje_1 <= diferencia_personaje_2 ){

		retorno3 = POR_UNO;
	}
	else if (diferencia_personaje_1 > diferencia_personaje_2){

		retorno3 = POR_DOS;
	} 
	else {
		retorno3 = POR_TRES;
	}

	return retorno3;

}

/*
Pre condiciones : 
- 	Los sabores, las fechas, los colores, las tallas y las alturas ingresadas
	tienen que estar dentro del rango validado.

Post condiciones : 
-	Si el puntaje total calculado mediante calcular_puntos_totales esta entre PUNTAJE_MIN y PUNTAJE_MAX_1 (ambos inclusive):
	Devuelve el puntaje total junto a JOHNNY si al usar la funcion calcular_diferencia_altura 
	entre ALTURA_JOHNNY, ALTURA_CORAJE y la altura ingresada es igual a POR_UNO, sino devuelve a CORAJE.

	Si el puntaje total calculado mediante calcular_puntos_totales esta entre PUNTAJE_MIN_2 y PUNTAJE_MAX_2 (ambos inclusive):
-	Devuelve el puntaje total junto a PURO_HUESO si al usar la funcion calcular_diferencia_altura 
	entre ALTURA_PURO_HUESO, ALTURA_POLLITO y la altura ingresada es igual a POR_UNO, sino devuelve a POLLITO.

	Si el puntaje total calculado mediante calcular_puntos_totales esta entre PUNTAJE_MIN_3 y PUNTAJE_MAX (ambos inclusive):
-	Devuelve el puntaje total junto a BLUE si al usar la funcion calcular_diferencia_altura 
	entre ALTURA_BLUE, ALTURA_BELLOTA y la altura ingresada es igual a POR_UNO, sino devuelve a BELLOTA.

*/

char diferencia_personajes(char sabores, int fecha_nacimiento, char colores, int talla_zapato, int altura){

	int devolver_puntaje_total = calcular_puntos_totales(sabores, fecha_nacimiento, colores, talla_zapato);

	char personaje_detectado = ES_PERSONAJE;

	if (( devolver_puntaje_total >= PUNTAJE_MIN) && (devolver_puntaje_total <= PUNTAJE_MAX_1)) {

		int mas_cercano = calcular_diferencia_altura(ALTURA_JOHNNY, ALTURA_CORAJE, altura);

	if (mas_cercano == POR_UNO) {

			

			personaje_detectado = JOHNNY;

	} else {

	

		personaje_detectado = CORAJE;
	}

	} else if ( (devolver_puntaje_total >= PUNTAJE_MIN_2) && (devolver_puntaje_total <= PUNTAJE_MAX_2) ){

		int mas_cercano = calcular_diferencia_altura(ALTURA_PURO_HUESO, ALTURA_POLLITO, altura);

		if (mas_cercano == POR_UNO) {

			
			personaje_detectado = PURO_HUESO;

	} else {

		

		personaje_detectado = POLLITO;
	}


	} else if ( (devolver_puntaje_total >= PUNTAJE_MIN_3) && (devolver_puntaje_total <= PUNTAJE_MAX) ){

		int mas_cercano = calcular_diferencia_altura(ALTURA_BLUE, ALTURA_BELLOTA, altura);

		if (mas_cercano == POR_UNO) {

			

			personaje_detectado = BLUE;

	} else {

		

		personaje_detectado = BELLOTA;
	}

	}

		return personaje_detectado;
	}

	void determinar_personaje (char sabores, int fecha_nacimiento, char colores, int talla_zapato, int altura, char* personaje_detectado){

		(*personaje_detectado) = diferencia_personajes(sabores,fecha_nacimiento, colores, talla_zapato, altura);

		if (*personaje_detectado == JOHNNY){
			
			(*personaje_detectado) = JOHNNY;
			
		} else if (*personaje_detectado == CORAJE){

			(*personaje_detectado) = CORAJE;
			
		} else if (*personaje_detectado == PURO_HUESO){

			(*personaje_detectado) = PURO_HUESO;
			
		}else if (*personaje_detectado == POLLITO){
			
			(*personaje_detectado) = POLLITO;
			
		}else if (*personaje_detectado == BLUE){
			
			(*personaje_detectado) = BLUE;
			
		} else {
			
			(*personaje_detectado) = BELLOTA;
			
		}
	}

	

/*
Pre condiciones : -
Post condiciones : imprime por pantalla "La fecha de nacimiento tienen que estar entre 1988 y 2008 (ambos inclusive):".
*/

void mostrar_convencion_fecha_nacimiento(){
	printf("La fecha de nacimiento tienen que estar entre 1988 y 2008 (ambos inclusive):\n");
}

/*
Pre condiciones : -
Post condiciones : imprime por pantalla "Los sabores correspondientes son 'D' para dulce 'S'para salado y 'A' para amargo:".
*/

void mostrar_convencion_sabores(){
	printf("Los sabores correspondientes son 'D' para dulce 'S'para salado y 'A' para amargo:\n");
}

/*
Pre condiciones : -
Post condiciones : imprime por pantalla "Las tallas de zapatos tienen que ser un numero entre 33 y 47 (ambos inclusive) 
o 0 si no usa zapatos:".
*/

void mostrar_convencion_tallas(){
	printf("Las tallas de zapatos tienen que ser un numero entre 33 y 47 (ambos inclusive) o 0 si no usa zapatos:\n");
}

/*
Pre condiciones : -
Post condiciones : imprime por pantalla "Azul (A), Amarillo (Y), Verde (V), Negro (N), Blanco (B), Rosa (R):".
*/

void mostrar_convencion_colores(){
	printf("Azul (A), Amarillo (Y), Verde (V), Negro (N), Blanco (B), Rosa (R):\n");
}

/*
Pre condiciones : -
Post condiciones : imprime por pantalla "Ingrese un numero entre 10 y 250 (ambos inclusive)".
*/

void mostrar_convencion_altura(){
	printf("Ingrese un numero entre 10 y 250 (ambos inclusive) :\n");
}

/*
Pre condiciones : 
-	Los sabores, las fechas, los colores, las tallas y las alturas ingresadas
	tienen que estar dentro del rango validado.

Post condiciones : 
-	imprime por pantalla lo que devuelve la funcion diferencia_personajes, mostrando el personaje detectado.
*/

void mostrar_personaje(char sabores, int fecha_nacimiento, char colores, int talla_zapato, int altura){

	char que_personaje_es = diferencia_personajes(sabores,fecha_nacimiento, colores, talla_zapato, altura);

     printf( "%c", que_personaje_es);
}

/*
Pre condiciones : -
Post condiciones : 
-	imprime por pantalla la pregunta al usuario sobre la fecha de nacimiento del personaje.
-	si se cumple la condicion es_fecha_de_nacimiento_valido(fecha_nacimiento) == false,
	vuelve a realizar la pregunta al usuario hasta que ingrese una fecha válida entre MIN_NACIMIENTO y MAX_NACIMIENTO.
*/

void preguntar_fecha_nacimiento(int* fecha_nacimiento){

	printf("Cuál es la fecha de nacimiento?:\n");
	mostrar_convencion_fecha_nacimiento();
	scanf(" %i", fecha_nacimiento);

	while(es_fecha_de_nacimiento_valido(fecha_nacimiento) == false){

		mostrar_convencion_fecha_nacimiento();
		scanf(" %i", fecha_nacimiento);
	}

}

/*
Pre condiciones : -
Post condiciones : 
-	Imprime por pantalla la pregunta al usuario sobre la preferencia de sabor del personaje.
-	si se cumple la condicion es_sabor_valido(sabores) == NO_VALIDO, vuelve a realizar la pregunta al usuario,
	hasta que ingrese un sabor valido entre DULCE, SALADO o AMARGO.
*/

void preguntar_sabor(char* sabores){

	printf("Cuál es la preferencia de sabor: \n");
	mostrar_convencion_sabores();
	scanf(" %c", sabores);

	while(es_sabor_valido(sabores) == NO_VALIDO){

		printf("Cuál es la preferencia de sabor: \n");
		mostrar_convencion_sabores();
		scanf(" %c", sabores);

	}
}

/*
Pre condiciones : -
Post condiciones : 
-	imprime por pantalla la pregunta al usuario sobre la talla de zapato del personaje.
-	si se cumple la condicion es_talla_valido(talla_zapato) == false, vuelve a realizar la pregunta al usuario,
	hasta que ingrese un numero valido entre MIN_TALLA Y MAX_TALLA.
*/

void preguntar_talla_zapato(int* talla_zapato){

	printf("Cual es la talla de zapatos? :\n");
	mostrar_convencion_tallas();
	scanf(" %i", talla_zapato);

	while(es_talla_valido(talla_zapato) == false){

		printf("Cual es la talla de zapatos? :\n");
		mostrar_convencion_tallas();
		scanf(" %i", talla_zapato);
	}
}
/*
Pre condiciones : -
Post condiciones : 
-	imprime por pantalla la pregunta al usuario sobre los colores.
-	si se cumple la condicion es_color_valido(colores) == INVALIDO, vuelve a realizar la pregunta al usuario,
	hasta que ingrese un un color entre AMARILLO,AZUL,VERDE,NEGRO,BLANCO y ROSA.
*/

void preguntar_color(char* colores){

	printf("Cuál es el color de preferencia ? :\n");
	mostrar_convencion_colores();
	scanf(" %c", colores);

	while(es_color_valido(colores) == INVALIDO) {

		printf("Cuál es el color de preferencia ? :\n");
		mostrar_convencion_colores();
		scanf(" %c", colores);
	}
}

/*
Pre condiciones : -
Post condiciones : 
-	imprime por pantalla la pregunta al usuario sobre la altura del personaje.
-	si se cumple la condicion son_alturas_validas(altura) == false, vuelve a realizar la pregunta al usuario,
	hasta que ingrese un numero valido entre MIN_ALTURA Y MAX_ALTURA.
*/

void preguntar_altura(int* altura){

	printf("Cuál es la altura (en cm): \n");
	mostrar_convencion_altura();
	scanf(" %i", altura);

	while(son_alturas_validas(altura) == false){

		printf("Cuál es la altura (en cm): \n");
		mostrar_convencion_altura();
		scanf(" %i", altura);

	}
}

void detectar_personaje (char* personaje_detectado){
	
	int fecha_nacimiento = 0;
	char sabores = 'X';
	int talla_zapato = 1;
	char colores = 'Y' ;
	int altura = 0 ;
	

	preguntar_fecha_nacimiento(&fecha_nacimiento);
	preguntar_sabor(&sabores);
	preguntar_talla_zapato(&talla_zapato);
	preguntar_color(&colores);
	preguntar_altura(&altura);
	//mostrar_personaje(sabores, fecha_nacimiento, colores, talla_zapato, altura);
	determinar_personaje (sabores, fecha_nacimiento, colores,  talla_zapato, altura, personaje_detectado);
}


