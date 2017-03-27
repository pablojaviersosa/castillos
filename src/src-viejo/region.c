#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "lista.h"
#include "grafo.h"
#include "parser.h"
#include "castillo.h"
#include "region.h"

#define MSJ_ERR_MEMORIA_INSUF "Memoria insuficiente"

/* Constructoras */

/* Recibe arreglo de punteros a regiones y un puntero entero para guardar la cantidad cargada
 * Devuelve el arreglo
 * */
pRegion_t * cargar_regiones(pRegion_t *regiones,int * nro_regiones){
	int i=0,j=0,k=0,l=0,aux1=0,aux2=0;
	int ncastillos=0,cant_regiones=0,min_ataque1=0,min_ataque2=0;
	pcastillo_t pcas1;
	char * cadena = NULL;
	char * pchar;

	if (regiones== NULL || nro_regiones== NULL)
		return NULL;
	while((cadena = readline(stdin))!= NULL && strcmp(cadena,CADENA_DE_CORTE)){
			for(j=i=0 ;isdigit(cadena[i]);) i++;//chequeo cadena bien formada
			if ((j=strlen(cadena)) != i){
				#ifdef DEBUG
					fprintf(stderr,"%s\ncadena amiwo:%s\n",MSJ_ERR_NAN,cadena);
				#endif
				free(cadena);
				/* Si no puedo cargar una region por mal formato, destruyo todas las regiones creadas */
				for(i=0;i < cant_regiones;i++){
					destruir_region(&(*regiones[i]),destruir_castillo);
				}
				return NULL;
			}
			ncastillos=(int)atoi(cadena);
			free(cadena);
			if (ncastillos < NRO_MIN_CASTILLOS || ncastillos > NRO_MAX_CASTILLOS){
				#ifdef DEBUG
					fprintf(stderr,"%s\nCastillo nro:%d\n",MSJ_ERR_VALOR_NO_PERMITIDO,ncastillos);
				#endif
				/* Si no puedo cargar una region por mal formato, destruyo todas las regiones creadas */
				for(i=0;i < cant_regiones;i++)
					destruir_region(regiones[i],destruir_castillo);
				return NULL;
			}
			if ((regiones[cant_regiones]= region())==NULL){
				/* Si no puedo cargar una region por mal formato, destruyo todas las regiones creadas */
				for(i=0;i < cant_regiones;i++)
					destruir_region(regiones[i],destruir_castillo);
				#ifdef DEBUG
					fprintf(stderr,"%s\t%s\ncadena:%s\n",MSJ_ERR_MEMORIA_INSUF,"Iniciar Estructura de datos",cadena);
				#endif
				return NULL;
			}
			/**************** insertar castillos en region *****************/
			for(i=0;i < ncastillos;i++){
				if ((pcas1 = cargar_castillo(castillo(0,0,0,0),i+1)) == NULL){
					/* Si no puedo cargar un castillo, destruyo todas las regiones creadas */
					for(i=0;i < cant_regiones;i++)
						destruir_region(regiones[i],destruir_castillo);
					#ifdef DEBUG
						fprintf(stderr,"%s\t%s%d\t%s%d\n",MSJ_ERR_MEMORIA_INSUF,"Insertar Castillo nro:",i+1,"Region:",cant_regiones);
					#endif
					return NULL;
				}
				insVertice(regiones[cant_regiones]->gcastillos,pcas1);
			}
			/**************** conectar castillos de la region **************/
			for(i=0,j=ncastillos-1;i < j;i++){
				pcas1 = infoVertice(regiones[cant_regiones]->gcastillos,i+1);
				if((cadena = readline(stdin))== NULL){
				/* Problema al leer arcos de una region destruyo todas las regiones creadas */
					for(i=0;i < cant_regiones;i++)
						destruir_region(regiones[i],destruir_castillo);
					#ifdef DEBUG
						fprintf(stderr,"%s\t%s%d\n",MSJ_ERR_PUNTERO_NULL,"No se pudo leer arco Region:",cant_regiones+1);
					#endif
					return NULL;
				}
				/* Vertice origen*/
				pchar = strtok(cadena," ");
				for(k=l=0;isdigit(pchar[k]);k++);//chequeo cadena bien formada
				if ((l=strlen(pchar)) != k){
					/* Problema al leer arcos de una region destruyo todas las regiones creadas */
					for(i=0;i < cant_regiones;i++)
						destruir_region(regiones[i],destruir_castillo);
					#ifdef DEBUG
						fprintf(stderr,"%s\t%s%d\n",MSJ_ERR_PUNTERO_NULL,"No se pudo leer arco Region:",cant_regiones+1);
					#endif
					free(cadena);
					return NULL;
				}
				aux1=(int)atoi(pchar);
				pchar = strtok(NULL," ");
				/*Vertice destino*/
				for(k=l=0;isdigit(pchar[k]);k++);//chequeo cadena bien formada
				if ((l=strlen(pchar)) != k){
					/* Problema al leer arcos de una region destruyo todas las regiones creadas */
					for(i=0;i < cant_regiones;i++)
						destruir_region(regiones[i],destruir_castillo);
					#ifdef DEBUG
						fprintf(stderr,"%s\t%s%d\n",MSJ_ERR_PUNTERO_NULL,"No se pudo leer arco Region:",cant_regiones+1);
					#endif
					free(cadena);
					return NULL;
				}
				aux2=(int)atoi(pchar);
				min_ataque1 = obtener_min(infoVertice(regiones[cant_regiones]->gcastillos,aux1));
				min_ataque2 = obtener_min(infoVertice(regiones[cant_regiones]->gcastillos,aux2));
				//El arco de 1 a 2 lleva el peso del minimo de soldados necesarios para atacar a 2 y viceversa
				insArco(regiones[cant_regiones]->gcastillos,aux1,aux2,min_ataque2);
				insArco(regiones[cant_regiones]->gcastillos,aux2,aux1,min_ataque1);
			}
			regiones[cant_regiones]->nro_castillos= ncastillos;
			regiones[cant_regiones]->nro_region =cant_regiones+1;
			cant_regiones++;
	}
	*nro_regiones = cant_regiones;
	return regiones;
}
pRegion_t region(void){
	pRegion_t r;
	if ((r=(pRegion_t)malloc(sizeof(Region_t)))==NULL)
		return NULL;
	r->min_soldados_conquista = 0;
	r->nro_castillos = 0;
	r->gcastillos = inicGrafo();
	r->lcastillos = inicLista();
	return r;
}

/*  Destructoras */
void destruir_region(pRegion_t r,void (*dest_cast)(void *)){
	if (r == NULL )
		return;
	destruirGrafo(r->gcastillos,dest_cast);
	destruirLista(r->lcastillos,dest_cast);
	free(r);
	return;
}



/*
 * Analizadoras
 * */
void imprimir_region(pRegion_t r){
	if(r == NULL)
		return;
	fprintf(stdout,"Region Nro:%d\n",(int)r->nro_region);
	impGrafo(r->gcastillos,imprimir_castillo);


}

