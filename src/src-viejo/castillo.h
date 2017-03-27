/*
 * castillos.h
 *
 *  Created on: 16/03/2017
 *      Author: Pablo
 */
#ifndef CASTILLOS_H_
#define CASTILLOS_H_

#define	MIN_A	1
#define	MAX_A	1000
#define MIN_M	0
#define	MIN_G	1
#define MAX_G	1000

#define MAX_SOLDADOS_FALTANTES -3001

#define MSJ_ERR_PUNTERO_NULL "Puntero NULL"
#define EOL '\0'
#define MSJ_ERR_NAN "Lo ingresado no es un numero"
#define MSJ_ERR_VALOR_NO_PERMITIDO "valor no permitido"

#define NRO_MIN_CASTILLO 1
#define NRO_MAX_CASTILLO 100

#define DEBUG


typedef struct castillo_t{
	int a,m,g,nro,min;
}* pcastillo_t,castillo_t;

typedef enum error_castillo_t {ERROR_NRO=0,ERROR_A,ERROR_M,ERROR_G,OK}estado_cas_t;
/* Constructores */
pcastillo_t castillo(int nro_castillo,int a,int m,int g );

/* Destructores */
void destruir_castillo(void *);

/* Getters */
int obtener_nro_castillo(pcastillo_t);//obtiene nro castillo necesarios
int obtener_a(pcastillo_t);//obtiene minimo atacantes necesarios
int obtener_m(pcastillo_t);//obtiene muertes en batalla
int obtener_g(pcastillo_t);//obtiene defensores del castillo
int obtener_min(pcastillo_t c);//obtiene minimo necesario para atacar
/* Setters */
void asignar_nro_castillo(pcastillo_t,int nro);//asigna nro de castillo
void asignar_a(pcastillo_t,int a);//asigna minimo atacantes necesarios
void asignar_m(pcastillo_t,int m);//asigna muertes en batalla
void asignar_g(pcastillo_t,int g);//asigna defensores del castillo
void asignar_min(pcastillo_t c);//asigna minimo soldados para capturar castillo
void reset_castillo(pcastillo_t c);
/* Analizadoras */

/*
 * Recibe un soldados atacantes la dir de un castillo.
 * Devuelve si > 0 cantidad de soldados exedentes
 * 			si < 0 cantidad de soldados exedentes
 * */
int atacar(int n,pcastillo_t);

estado_cas_t validar_castillo(pcastillo_t);
void persistir_castillo(pcastillo_t c);
pcastillo_t cargar_castillo(pcastillo_t c,int nro_castillo);
void imprimir_castillo(FILE*,void*);
#endif /* CASTILLOS_H_ */
