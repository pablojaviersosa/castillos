/*
 * resolver.c
 *
 *  Created on: 24/03/2017
 *      Author: usr
 */

#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "grafo.h"
#include "grafo_util.h"
#include "castillo.h"
#include "region.h"
#include "mapa.h"
#include "resolver.h"

/* qsort funcion para comparar */
int cmp( void *v1, void *v2){
	pcastillo_t pv1 = (pcastillo_t)v1;
	pcastillo_t pv2 = (pcastillo_t)v2;

	if(obtener_exce(pv1)>obtener_exce(pv2))
		return -1;
	else if(obtener_exce(pv1)<obtener_exce(pv2))
		return 1;
	else
		return 0;
}

void resolver(FILE * pArchivo,pmapa_t mapa){
	int i=0,j=0;
	int min_soldados_region = 0,max_soldados_region = 0;
	int n=0;
	pcastillo_t vert_ord_exced;
	pRegion_t r;
//	Lista l = inicLista();
	Lista suce = NULL;

	for(i=0;i<mapa->nro_regiones;i++){
		r= mapa->regiones[i];
		vert_ord_exced = (pcastillo_t )malloc(r->nro_castillos*sizeof(castillo_t));
		for (j=0;j<r->nro_castillos;j++){
			asignar_a(&vert_ord_exced[j],obtener_a(infoVertice(r->gcastillos,j+1)));
			asignar_m(&vert_ord_exced[j],obtener_m(infoVertice(r->gcastillos,j+1)));
			asignar_g(&vert_ord_exced[j],obtener_g(infoVertice(r->gcastillos,j+1)));
			asignar_nro_castillo(&vert_ord_exced[j],obtener_nro_castillo(infoVertice(r->gcastillos,j+1)));
			recalcular(&vert_ord_exced[j]);
		}
		for (j=0;j<r->nro_castillos-1;j++)
			imprimir_castillo(stdout,&vert_ord_exced[j]);

		qsort(vert_ord_exced,r->nro_castillos,sizeof(castillo_t), cmp);

		for (j=0;j<r->nro_castillos-1;j++)
			imprimir_castillo(stdout,&vert_ord_exced[j]);

//		for (n =r->lim_inf_soldados_conquista ;n <= r->lim_sup_soldados_conquista ;n++)

//		min_soldados_region = calcular_min_soldados(mapa->regiones[i]);


//		imprimir_region(pArchivo,mapa->regiones[i]);
		fprintf(pArchivo,"%s%d\n","Case: ",min_soldados_region);
		free(vert_ord_exced);
	}
}
int calcular_min_soldados(pRegion_t r){
	/* recorrer hasta quedarme vertice de mayor excedente*/
//	int max_exce;
//	Lista sumi = NULL;
//	pListaNodo pnodol;
//
//
//	suce = sucesores(mapa->regiones[i]->gcastillos);
//	if (longLista(sumi) == 1){ //tiene 1 sumidero sii 1 nodo
//		destruirLista(sumi,free);
//		return obtener_min(infoVertice(r->gcastillos,1));
//	}
//	pnodol = sumi->primero;
//	while(sigLista(l) != l->ultimo){
//		infoLista(l);
//	}
//	return;
//}
//int h(void* vp){
//	pcastillo_t castillo = (pcastillo_t)vp;
//	if(castillo == NULL)
//		return -3000;
	return obtener_exce(castillo);

}
