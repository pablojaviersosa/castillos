/*
 * castillo.c
 *
 *  Created on: 16/03/2017
 *      Author: usr
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "castillo.h"


/*
 * Constructores
 * */
pcastillo_t castillo(int nro_castillo,int a,int m,int g){
	castillo_t *c;
	if ((c =(pcastillo_t)malloc(sizeof(castillo_t)))==NULL)
		return NULL;
	asignar_a(c,a);
	asignar_m(c,m);
	asignar_g(c,g);
	recalcular(c);
	return c;
}
/*
 * Destructores
 * */
void destruir_castillo(void * c){
	if ((pcastillo_t)c == NULL)
		return;
	free((pcastillo_t)c);
}
/*
 * Getters
 * */
int obtener_nro_castillo(pcastillo_t c){//obtiene minimo atacantes necesarios
	return (c != NULL)?c->nro:-1;
}
int obtener_a(pcastillo_t c){//obtiene minimo atacantes necesarios
	return (c != NULL)?c->a:-1;
}
int obtener_m(pcastillo_t c){//obtiene muertes en batalla
	return (c != NULL)?c->m:-1;}
int obtener_g(pcastillo_t c){//obtiene defensores del castillo
	return (c != NULL)?c->g:-1;
}
int obtener_min(pcastillo_t c){//obtiene minimo soldados necesarios para atacar el castillo
	return (c != NULL)?c->min:-1;
}
int obtener_exce(pcastillo_t c){return c->exce;}
/*
 * Setters
 * */
void asignar_nro_castillo(pcastillo_t c,int nro){//asigna nro de castillo
	if (c != NULL)
		c->nro = nro;
}

void asignar_a(pcastillo_t c,int a){//asigna minimo atacantes necesarios
	if (c != NULL)
		c->a = a;
}
void asignar_m(pcastillo_t c,int m){//asigna muertes en batalla
	if (c != NULL)
		c->m = m;
}

void recalcular(pcastillo_t c){//recalcula min y exceso
	if (c != NULL){
		c->min = (obtener_a(c)< (obtener_g(c)+obtener_m(c)))?(obtener_g(c)+obtener_m(c)):obtener_a(c);
		c->exce = obtener_a(c)-(obtener_g(c)+obtener_m(c));
//		c->exce = (obtener_a(c)>=(obtener_g(c)+obtener_m(c)))?obtener_a(c)-(obtener_g(c)+obtener_m(c)):0;
	}
}
void asignar_g(pcastillo_t c,int g){//asigna minimo soldados para capturar castillo
	if(c!=NULL)
		c->g = g;
}

/*
 * Analizadoras
 * */
/*
 * Recibe un soldados atacantes la dir de un castillo.
 * Devuelve si n > a -> cantidad de soldados exedentes
 * 			si n < a -> cantidad de soldados falantes
 * 			sino ERROR devuelvo mas faltantes que el tope superior de atacantes permitidos
 * */
int atacar(int n,pcastillo_t c){//probar
	if (c ==NULL)
		return -1;
	return (n < c->a )? n - c->a: n -(c->m + c->g);//

}
estado_cas_t validar_castillo(pcastillo_t c){
	estado_cas_t e;

	if (c->nro < NRO_MIN_CASTILLO || c->nro > NRO_MAX_CASTILLO){
		e=ERROR_NRO;
	}
	else if (c->a < MIN_A || c->a > MAX_A){// RANGO DE A
		e=ERROR_A;
	}
	else if (c->m < MIN_M || c->m > obtener_m(c)){// RANGO DE M
		e=ERROR_M;
	}
	else if (c->g < MIN_G || c->g > MAX_G){
		e=ERROR_G;
	}
	else
		e=OK;
	return e;
}
void persistir_castillo(pcastillo_t c){
	fprintf(stdout,"%d %d %d\n",obtener_a(c),obtener_m(c),obtener_g(c));
}
void imprimir_castillo(FILE* fp,void * pcas){
	pcastillo_t c = (pcastillo_t)pcas;
	if (c != NULL)
		fprintf(fp,"Castillo :%d a:%d\tm:%d\tg:%d\tmin:%5d\texce:%5d\n",c->nro,c->a,c->m,c->g,c->min,c->exce);
}
void reset_castillo(pcastillo_t c){
	asignar_nro_castillo(c,0);
	asignar_a(c,0);
	asignar_m(c,0);
	asignar_g(c,0);
}

