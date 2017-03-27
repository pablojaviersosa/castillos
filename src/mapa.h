/*
 * mapa.h
 *
 *  Created on: 23/03/2017
 *      Author: usr
 */

#ifndef MAPA_H_
#define MAPA_H_

#define	MAX_REGIONES	10


typedef struct mapa_t {
	int nro_regiones;
	pRegion_t *regiones;

} *pmapa_t,mapa_t;

pmapa_t mapa(void);
void destruir_mapa(pmapa_t pm);
void imprimir_mapa(FILE* pArchivo,pmapa_t mapa);
#endif /* MAPA_H_ */
