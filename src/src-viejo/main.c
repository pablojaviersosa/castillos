#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "lista.h"
#include "grafo.h"
#include "grafo_util.h"
#include "parser.h"
#include "castillo.h"
#include "region.h"

#define MSJ_ERR_NO_ES_ENTERO "Lo ingresado no es u numero entero:"
#define MSJ_ERR_MEMORIA_INSUF "Memoria insuficiente al crear:"
#define	MAX_REGIONES	10

//Grafo grafo=NULL;
//Lista lst;

int main(void) {
	int i=0,j=0,cant_regiones=0;
	char * cadena = NULL;

	pcastillo_t pcastillo;
	pRegion_t *regiones = NULL;

	/* Creo MAX_REGIONES -todo mejorar regiones ilimitadas*/
	if((regiones = (pRegion_t*)malloc(MAX_REGIONES*sizeof(pRegion_t)))==NULL){
		#ifdef DEBUG
			fprintf(stderr,"%s:%s\n",MSJ_ERR_MEMORIA_INSUF,"regiones");
		#endif
		return 1;
	}
	if(cargar_regiones(regiones,&cant_regiones)== NULL){
		free (regiones);
		return 2;
	}
	for(i=0;i<cant_regiones;i++)
		imprimir_region(regiones[i]);

	/*Destruyo regiones antes de salir*/
	for (i=0; i < cant_regiones ;i++)
		destruir_region(regiones[i],destruir_castillo);
	free(regiones);
	return 0;
}
//pcastillo = castillo(2,3,4,4);
//imprimir_castillo(pcastillo);
//
//if(pcastillo == NULL){
//	printf("error al crear castillo");
//	return 2;
//}
//if(cargar_castillo(pcastillo,101) == NULL)
//	fprintf(stderr,"error en la carga de castillo\n");
////		fprintf(stderr,"%s\nCastillo nro:%d\tok\n","piola hasta aca",obtener_nro_castillo(c));
//fprintf(stderr,"todo piola\n");
//imprimir_castillo(pcastillo);
//destruir_castillo(pcastillo);
