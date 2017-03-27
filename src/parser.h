/*
 * parser.h
 *
 *  Created on: 21/03/2017
 *      Author: usr
 */

#ifndef PARSER_H_
#define PARSER_H_


char *		readline(FILE*);
pcastillo_t	parsear_castillo(FILE* pArchivo,int nro_castillo);
pRegion_t parsear_region(FILE* pArchivo,int nro_region, char* cadena_cant_castillos);
pmapa_t		parsear_mapa(FILE * parchivo);

#endif /* PARSER_H_ */
