/*
 * parser.h
 *
 *  Created on: 21/03/2017
 *      Author: usr
 */

#ifndef PARSER_H_
#define PARSER_H_

char * readline(FILE*);

void * parser(FILE* pArchivo,void*(*pCargarDato)(FILE* pArchivo));

#endif /* PARSER_H_ */
