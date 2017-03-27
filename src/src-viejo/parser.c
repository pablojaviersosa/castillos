#include <stdio.h>
#include <stdlib.h>
#include "parser.h"


void * parser(FILE* pArchivo,void*(*pCargarDato)(FILE* pArchivo)){
	return pCargarDato(pArchivo);
}

/*=============================================================*/
#define INIT_CHOP  30  /*Cantidad de elementos iniciales para la cadena*/
#define CHOP 10  /*Cantidad de elementos que se agregaran a la cadena por cada realloc()*/

char * readline(FILE*fp){
     char *s, *aux;
     int c;
     size_t alloc_size, used_size;

     if(fp==NULL)
    	return NULL;
     if((s=(char *)malloc(INIT_CHOP*sizeof(char)))==NULL)
            return NULL;
     alloc_size=INIT_CHOP;
     used_size=0;
     while((c=getc(fp))!='\n' && c!=EOF){
            if(used_size==alloc_size-1){
                 aux=realloc(s,(alloc_size+CHOP)*sizeof(char));
                 if(aux==NULL){
                      free(s);
                      return NULL;
                 }
                 s=aux;
                 alloc_size+=CHOP;
            }
            s[used_size++]=c;
            s[used_size]='\0';
     }
     return s;
}
/*=============================================================*/
