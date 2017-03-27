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
	int nro_region; //nro region
	int nro_castillos; //cantidad de castillos
	int lim_sup_soldados_conquista; //min de soldados
	int lim_inf_soldados_conquista;
	Grafo gcastillos; // grafo de la region
}* pRegion_t,Region_t;

/* Getters*/
int obtenernro_castillos(pRegion_t pr);
int obtener_nro_region(pRegion_t pr);
/* Setters*/
void asignar_nro_castillos(pRegion_t pr,int nro_castillos);
void asignar_nro_region(pRegion_t pr,int nro_region);

pRegion_t region(void);

void imprimir_region(FILE *pArchivo,pRegion_t r);
void destruir_region(pRegion_t regiones,void (*dest_castillo)(void*));

#endif /* REGION_H_ */
