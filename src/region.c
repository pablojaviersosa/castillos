#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "lista.h"
#include "grafo.h"
#include "grafo_util.h"
#include "castillo.h"
#include "region.h"



/* Constructoras */


pRegion_t region(void){
	pRegion_t r;
	if ((r=(pRegion_t)malloc(sizeof(Region_t)))==NULL)
		return NULL;
	r->lim_sup_soldados_conquista = 0;
	r->lim_inf_soldados_conquista = 0;
	r->nro_castillos = 0;
	r->gcastillos = inicGrafo();
	return r;
}

/*  Destructoras */
void destruir_region(pRegion_t r,void (*dest_cast)(void *)){
	if (r == NULL )
		return;
	destruirGrafo(r->gcastillos,dest_cast);
//	destruirLista(r->lcastillos,dest_cast);
	free(r);
	return;
}
/* Getters*/
int obtener_nro_castillos(pRegion_t pr){
	return pr->nro_castillos;
}
int obtener_nro_region(pRegion_t pr){
	return pr->nro_region;
}
/* Setters*/
void asignar_nro_castillos(pRegion_t pr,int nro_castillos){
	pr->nro_castillos = nro_castillos;
}
void asignar_nro_region(pRegion_t pr,int nro_region){
	pr->nro_region = nro_region;
}

/* Analizadoras */
void imprimir_region(FILE *pArchivo,pRegion_t r){
	if(r == NULL)
		return;
	fprintf(pArchivo,"Region Nro:%d\n",(int)r->nro_region);
	impGrafo(r->gcastillos,imprimir_castillo);


}

