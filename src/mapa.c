/*
 * mapa.c

 *
 *  Created on: 23/03/2017
 *      Author: usr
 */
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "grafo.h"
#include "castillo.h"
#include "region.h"
#include "mapa.h"


pmapa_t mapa(void){
	pmapa_t m =	(pmapa_t)malloc(sizeof(mapa_t));
	if(m != NULL){
		m->nro_regiones = 0;
		m->regiones = NULL;
	}
	return m;
}
void destruir_mapa(pmapa_t pm){
	int i=0;
	for(i=0;i< pm->nro_regiones ; i++)
		destruir_region(pm->regiones[i],destruir_castillo);
	free(pm);
}

void imprimir_mapa(FILE* pArchivo,pmapa_t mapa){
	int i=0;
	if(mapa == NULL)
		return;
	for(;i<mapa->nro_regiones;i++)
		imprimir_region(pArchivo,mapa->regiones[i]);
}
