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
#include "parser.h"

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
	asignar_min(c);
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
void asignar_min(pcastillo_t c){//asigna defensores del castillo
	if (c != NULL)
		c->min = (obtener_a(c)< (obtener_g(c)+obtener_m(c)))?(obtener_g(c)+obtener_m(c)):obtener_a(c);
}
void asignar_g(pcastillo_t c,int g){//asigna minimo soldados para capturar castillo
	if(c!=NULL)
		c->g = g;
}
pcastillo_t cargar_castillo(pcastillo_t c,int nro_castillo){
	char * cadena=NULL;
	char * p;
	int i=0,j=0,aux=0;
	if( c == NULL){
		#ifdef DEBUG
			fprintf(stderr,"pcastillo: %s\nCastillo nro:%d\n",MSJ_ERR_PUNTERO_NULL,nro_castillo);
		#endif
		return NULL;
	}
	if (nro_castillo < NRO_MIN_CASTILLO || nro_castillo > NRO_MAX_CASTILLO){
		#ifdef DEBUG
			fprintf(stderr,"%s\nCastillo nro:%d\n",MSJ_ERR_VALOR_NO_PERMITIDO,nro_castillo);
		#endif
		reset_castillo(c);
		return NULL;
	}
	asignar_nro_castillo(c,nro_castillo);
	if((cadena = readline(stdin))==NULL){ //leo la cadena de stdin
		#ifdef DEBUG
			fprintf(stderr,"cadena: %s\nCastillo nro:%d\n",MSJ_ERR_PUNTERO_NULL,nro_castillo);
		#endif
		return NULL;
	}
	/*********************** Parseo Ataque  **********************************/
	if((p = strtok(cadena," ")) == NULL){//primer tag
		#ifdef DEBUG
			fprintf(stderr,"%s\nCastillo nro:%d\tp1\n",MSJ_ERR_PUNTERO_NULL,nro_castillo);;
		#endif
		free(cadena);
		return NULL;
	}
	for(j=i=0;isdigit(p[i]);) i++;//chequeo cadena bien formada
	if ((j=strlen(p)) != i){
		#ifdef DEBUG
			fprintf(stderr,"%s\nCastillo nro:%d\tp3:%s\n",MSJ_ERR_NAN,nro_castillo,p);
		#endif
		free(cadena);
		return NULL;
	}
	aux=(int)atoi(p);
	if (aux < MIN_A || aux > MAX_A){// RANGO DE A
		#ifdef DEBUG
			fprintf(stderr,"%s\nCastillo nro:%d\tAtaque:%d\n",MSJ_ERR_VALOR_NO_PERMITIDO,nro_castillo,aux);
		#endif
		reset_castillo(c);
		free(cadena);
		return NULL;
	}
	asignar_a(c ,aux);
	/*********************** Parseo Mueren **********************************/
	if((p = strtok(NULL," ")) == NULL){//segundo tag
		#ifdef DEBUG
			fprintf(stderr,"%s\nCastillo nro:%d\tp2\n",MSJ_ERR_PUNTERO_NULL,nro_castillo);
		#endif
		free(cadena);
		return NULL;
	}
	for(j=i=0;isdigit(p[i]);) i++;//chequeo cadena bien formada
	if ((j=strlen(p)) != i){
		#ifdef DEBUG
			fprintf(stderr,"%s\nCastillo nro:%d\tp2:%s\n",MSJ_ERR_NAN,nro_castillo,p);
		#endif
		free(cadena);
		return NULL;
	}
	aux=(int)atoi(p);
	if (aux < MIN_M || aux > obtener_a(c)){// RANGO DE M
		#ifdef DEBUG
			fprintf(stderr,"%s\nCastillo nro:%d\tMueren:%d\n",MSJ_ERR_VALOR_NO_PERMITIDO,nro_castillo,aux);
		#endif
		reset_castillo(c);
		free(cadena);
		return NULL;
	}
	asignar_m(c ,aux);
	/*********************** Parseo Defienden **********************************/
	if((p = strtok(NULL," \0")) == NULL){//tercer tag
		#ifdef DEBUG
			fprintf(stderr,"%s\nCastillo nro:%d\tp3\n",MSJ_ERR_PUNTERO_NULL,nro_castillo);
		#endif
		free(cadena);
		return NULL;
	}
	for(j=i=0;isdigit(p[i]);) i++;//chequeo cadena bien formada
	if ((j=strlen(p)) != i){
		#ifdef DEBUG
		fprintf(stderr,"%s\nCastillo nro:%d\tp3:%s\n",MSJ_ERR_NAN,nro_castillo,p);
		#endif
		free(cadena);
		return NULL;
	}
	aux=(int)atoi(p);
	if (aux < MIN_G || aux > MAX_G){// RANGO DE G
		#ifdef DEBUG
			fprintf(stderr,"%s\nCastillo nro:%d\tDefineden:%d\n",MSJ_ERR_VALOR_NO_PERMITIDO,nro_castillo,aux);
		#endif
		reset_castillo(c);
		free(cadena);
		return NULL;
	}
	asignar_g(c ,aux);
	asignar_min(c);
	free (cadena);
	return c;
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
int atacar(int n,pcastillo_t c){//todo probar
	if (c !=NULL){
		return (n < c->a )? n - c->a: n -(c->m + c->g);//
	}
	return MAX_SOLDADOS_FALTANTES; //Devuelvo error
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
		fprintf(fp,"Castillo nro:%d a:%d\tm:%d\tg:%d\tmin:%d\n",c->nro,c->a,c->m,c->g,c->min);
}
void reset_castillo(pcastillo_t c){
	asignar_nro_castillo(c,0);
	asignar_a(c,0);
	asignar_m(c,0);
	asignar_g(c,0);
}

