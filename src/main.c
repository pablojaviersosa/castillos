#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "lista.h"
#include "grafo.h"
#include "grafo_util.h"
#include "castillo.h"
#include "region.h"
#include "mapa.h"
#include "parser.h"
#include "resolver.h"

#define MSJ_ERR_NO_ES_ENTERO "Lo ingresado no es u numero entero:"

void visitar(FILE * pa,void * );

int main(void) {
	pmapa_t mapa;

	if((mapa = parsear_mapa(stdin))==NULL)
		return 1;
//	imprimir_mapa(stdout,mapa);
	resolver(stdout,mapa);
	destruir_mapa(mapa);
	return 0;
}

/*=======================================================================*/
//	int i=0,j=0,k=0,cant_regiones=0,*resultado_dijkstra;
//	char * cadena = NULL;
//
//	pcastillo_t pcastillo;
//	if(cargar_regiones(regiones,&cant_regiones)== NULL){
//		free (regiones);
//		return 2;
//	}
//	for(i=0;i<cant_regiones;i++)
//		for(j=0;j< regiones[i]->nro_castillos;j++){
//			profundidadGrafo(regiones[i]->gcastillos,j,visitar);
////			resultado_dijkstra = dijkstra(regiones[i]->gcastillos,j+1);
//			for(k=0;k< regiones[i]->nro_castillos;k++)
//				fprintf(stdout,"%d\t",resultado_dijkstra[k]);
//			fprintf(stdout,"\n");
//		}
//

//	for(i=0;i<cant_regiones;i++)
//		for(j=0;j< regiones[i]->nro_castillos;j++){
//			resultado_dijkstra = dijkstra(regiones[i]->gcastillos,j+1);
//			for(k=0;k< regiones[i]->nro_castillos;k++)
//				fprintf(stdout,"%d\t",resultado_dijkstra[k]);
//			fprintf(stdout,"\n");
//		}
//		imprimir_region(regiones[i]);
	/*Destruyo regiones antes de salir*/
//	for (i=0; i < cant_regiones ;i++)
//		destruir_region(regiones[i],destruir_castillo);
//	free(regiones);

/*=======================================================================*/

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
void visitar(FILE * pa,void * pDato){


}
