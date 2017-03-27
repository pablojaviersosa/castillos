/*
 * regiones.h
 *
 *  Created on: 16/03/2017
 *      Author: usr
 */

#ifndef REGION_H_
#define REGION_H_

#define	MIN_N	2	//MIN CASTILLOS POR REGION
#define	MAX_N	100	//MAX CASTILLOS POR REGION
#define CADENA_DE_CORTE "0"
#define NRO_MIN_CASTILLOS 2
#define NRO_MAX_CASTILLOS	 100
#define MSJ_ERR_CADENA_MAL_FORMADA "No se puede convertir a entero la cadena"

typedef struct Region_t{
	size_t nro_region; //nro region
	size_t nro_castillos; //cantidad de castillos
	int min_soldados_conquista; //min de soldados
	Grafo gcastillos; // grafo de la region
	Lista lcastillos; //orden camino solucion
}* pRegion_t,Region_t;

pRegion_t region(void);
pRegion_t *cargar_regiones(pRegion_t *regiones,int*cant_regiones);
void imprimir_region(pRegion_t r);
void destruir_region(pRegion_t regiones,void (*dest_castillo)(void*));

#endif /* REGION_H_ */
