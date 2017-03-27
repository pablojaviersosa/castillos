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

/*=============================================================*/
#define INIT_CHOP  30  /*Cantidad de elementos iniciales para la cadena*/
#define CHOP 10  /*Cantidad de elementos que se agregaran a la cadena por cada realloc()*/

pcastillo_t parsear_castillo(FILE* pArchivo,int nro_castillo){
	//	pcastillo_t cargar_castillo(pcastillo_t c,int nro_castillo){
	char * cadena=NULL;
	char * p;
	int i=0,j=0,aux=0;
	pcastillo_t c;

	if( (c = castillo(nro_castillo,0,0,0)) == NULL){
#ifdef DEBUG
		fprintf(stderr,"pcastillo: %s\nCastillo nro:%d\n",MSJ_ERR_PUNTERO_NULL,nro_castillo);
#endif
		return NULL;
	}
	if (nro_castillo < NRO_MIN_CASTILLO || nro_castillo > NRO_MAX_CASTILLO){
#ifdef DEBUG
		fprintf(stderr,"%s\nCastillo nro:%d\n",MSJ_ERR_VALOR_NO_PERMITIDO,nro_castillo);
#endif
		reset_castillo(c);
		return NULL;
	}
	asignar_nro_castillo(c,nro_castillo);
	if((cadena = readline(stdin))==NULL){ //leo la cadena de stdin
#ifdef DEBUG
		fprintf(stderr,"cadena: %s\nCastillo nro:%d\n",MSJ_ERR_PUNTERO_NULL,nro_castillo);
#endif
		return NULL;
	}
	/*********************** Parseo Ataque  **********************************/
	if((p = strtok(cadena," ")) == NULL){//primer tag
#ifdef DEBUG
		fprintf(stderr,"%s\nCastillo nro:%d\tp1\n",MSJ_ERR_PUNTERO_NULL,nro_castillo);;
#endif
		free(cadena);
		return NULL;
	}
	for(j=i=0;isdigit(p[i]);) i++;//chequeo cadena bien formada
	if ((j=strlen(p)) != i){
#ifdef DEBUG
		fprintf(stderr,"%s\nCastillo nro:%d\tp3:%s\n",MSJ_ERR_NAN,nro_castillo,p);
#endif
		free(cadena);
		return NULL;
	}
	aux=(int)atoi(p);
	if (aux < MIN_A || aux > MAX_A){// RANGO DE A
#ifdef DEBUG
		fprintf(stderr,"%s\nCastillo nro:%d\tAtaque:%d\n",MSJ_ERR_VALOR_NO_PERMITIDO,nro_castillo,aux);
#endif
		reset_castillo(c);
		free(cadena);
		return NULL;
	}
	asignar_a(c ,aux);
	/*********************** Parseo Mueren **********************************/
	if((p = strtok(NULL," ")) == NULL){//segundo tag
#ifdef DEBUG
		fprintf(stderr,"%s\nCastillo nro:%d\tp2\n",MSJ_ERR_PUNTERO_NULL,nro_castillo);
#endif
		free(cadena);
		return NULL;
	}
	for(j=i=0;isdigit(p[i]);) i++;//chequeo cadena bien formada
	if ((j=strlen(p)) != i){
#ifdef DEBUG
		fprintf(stderr,"%s\nCastillo nro:%d\tp2:%s\n",MSJ_ERR_NAN,nro_castillo,p);
#endif
		free(cadena);
		return NULL;
	}
	aux=(int)atoi(p);
	if (aux < MIN_M || aux > obtener_a(c)){// RANGO DE M
#ifdef DEBUG
		fprintf(stderr,"%s\nCastillo nro:%d\tMueren:%d\n",MSJ_ERR_VALOR_NO_PERMITIDO,nro_castillo,aux);
#endif
		reset_castillo(c);
		free(cadena);
		return NULL;
	}
	asignar_m(c ,aux);
	/*********************** Parseo Defienden **********************************/
	if((p = strtok(NULL," \0")) == NULL){//tercer tag
#ifdef DEBUG
		fprintf(stderr,"%s\nCastillo nro:%d\tp3\n",MSJ_ERR_PUNTERO_NULL,nro_castillo);
#endif
		free(cadena);
		return NULL;
	}
	for(j=i=0;isdigit(p[i]);) i++;//chequeo cadena bien formada
	if ((j=strlen(p)) != i){
#ifdef DEBUG
		fprintf(stderr,"%s\nCastillo nro:%d\tp3:%s\n",MSJ_ERR_NAN,nro_castillo,p);
#endif
		free(cadena);
		return NULL;
	}
	aux=(int)atoi(p);
	if (aux < MIN_G || aux > MAX_G){// RANGO DE G
#ifdef DEBUG
		fprintf(stderr,"%s\nCastillo nro:%d\tDefineden:%d\n",MSJ_ERR_VALOR_NO_PERMITIDO,nro_castillo,aux);
#endif
		reset_castillo(c);
		free(cadena);
		return NULL;
	}
	asignar_g(c ,aux);
	recalcular(c);
	free (cadena);
	return c;
}
/*=============================================================*/
pRegion_t parsear_region(FILE* pArchivo,int nro_region, char* cadena_cant_castillos){
	int i=0,j=0,k=0,l=0,aux1=0,aux2=0,costo =0;
	int nro_castillos =0,cant_regiones=0,min_ataque1=0,min_ataque2=0;
	//		int exce1=0,exce2=0;
	char * cadena = NULL;
	char * pchar;
	pRegion_t pregion;
	pcastillo_t pcas1;
	Lista caminos;

	if ((pregion = region()) == NULL || cadena_cant_castillos == NULL)
		return NULL;
	j=strlen(cadena_cant_castillos);
	if((cadena =(char*)malloc(sizeof(char)* (j+1)))==NULL){
		free(pregion);
		return NULL;
	}
	strcpy(cadena,cadena_cant_castillos);

	for(i=0 ;isdigit(cadena[i]);) i++;//chequeo cadena bien formada
	if (j != i){
#ifdef DEBUG
		fprintf(stderr,"%s\ncadena amiwos:%s,%d,%d\n",MSJ_ERR_NAN,cadena,(int)strlen(cadena),(int)strlen(cadena_cant_castillos));
#endif
		/* Si no puedo cargar una region por mal formato, destruyo todas las regiones creadas */
		free(cadena);
		free(pregion);
		return NULL;
	}
	nro_castillos = atoi(cadena);
	if (nro_castillos< NRO_MIN_CASTILLOS || nro_castillos > NRO_MAX_CASTILLOS){
#ifdef DEBUG
		fprintf(stderr,"%s\nCastillo nro:%d\n",MSJ_ERR_VALOR_NO_PERMITIDO,nro_castillos);
#endif
		/* Si no puedo cargar una region por mal formato, destruyo todas las regiones creadas */
		destruir_region(pregion,destruir_castillo);
		return NULL;
	}
	/**************** insertar castillos en region *****************/
	for(i=0;i < nro_castillos;i++){
		if ((pcas1 = parsear_castillo(pArchivo,i+1)) == NULL){
			/* Si no puedo cargar un castillo, destruyo todas las regiones creadas */
			destruir_region(pregion,destruir_castillo);
#ifdef DEBUG
			fprintf(stderr,"%s\t%s%d\t%s%d\n",MSJ_ERR_MEMORIA_INSUF,"Insertar Castillo nro:",i+1,"Region:",cant_regiones);
#endif
			return NULL;
		}
		insVertice(pregion->gcastillos,pcas1);
		recalcular(infoVertice(pregion->gcastillos,i+1));
		pregion->lim_sup_soldados_conquista+=obtener_min(infoVertice(pregion->gcastillos,i+1));
		pregion->lim_inf_soldados_conquista+=obtener_m(infoVertice(pregion->gcastillos,i+1))+obtener_g(infoVertice(pregion->gcastillos,i+1));
	}
	/**************** conectar castillos de la region **************/
	for(i=0,j=nro_castillos-1;i < j;i++){
		pcas1 = infoVertice(pregion->gcastillos,i+1);
		if((cadena = readline(pArchivo))== NULL){
			/* Problema al leer arcos de una region destruyo todas las regiones creadas */
			destruir_region(pregion,destruir_castillo);
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
			destruir_region(pregion,destruir_castillo);
#ifdef DEBUG
			fprintf(stderr,"%s\t%s%d\n",MSJ_ERR_PUNTERO_NULL,"No se pudo leer arco Region:",cant_regiones+1);
#endif
			free(cadena);
			return NULL;
		}
		aux1=(int)atoi(pchar);
		if (aux1 < 0 || aux1 > nro_castillos){
			/* Problema al leer arcos de una region destruyo todas las regiones creadas */
			//						for(i=0;i < cant_regiones;i++)
			destruir_region(pregion,destruir_castillo);
#ifdef DEBUG
			fprintf(stderr,"%s\t%s%d\n%s\t%d\n",MSJ_ERR_VALOR_NO_PERMITIDO,"No se pudo leer arco Region:",cant_regiones+1,"Valor de arco:",aux1);
#endif
			free(cadena);
			return NULL;
		}
		pchar = strtok(NULL," ");
		/*Vertice destino*/
		for(k=l=0;isdigit(pchar[k]);k++);//chequeo cadena bien formada
		if ((l=strlen(pchar)) != k){
			/* Problema al leer arcos de una region destruyo todas las regiones creadas */
			//				for(i=0;i < cant_regiones;i++)
			destruir_region(pregion,destruir_castillo);
#ifdef DEBUG
			fprintf(stderr,"%s\t%s%d\n",MSJ_ERR_PUNTERO_NULL,"No se pudo leer arco Region:",cant_regiones+1);
#endif
			free(cadena);
			return NULL;
		}
		aux2=(int)atoi(pchar);
		free(cadena);
		if (aux2 < 0 || aux2 > nro_castillos){
			/* Problema al leer arcos de una region destruyo todas las regiones creadas */
			//				for(i=0;i < cant_regiones;i++)
			destruir_region(pregion,destruir_castillo);
#ifdef DEBUG
			fprintf(stderr,"%s\t%s%d\n%s\t%d\n",MSJ_ERR_VALOR_NO_PERMITIDO,"No se pudo leer arco Region:",cant_regiones+1,"Valor de arco:",aux2);
#endif
			return NULL;
		}
//		recalcular(infoVertice(pregion->gcastillos,aux1));
//		recalcular(infoVertice(pregion->gcastillos,aux2));
		//			exce1 = obtener_exce(infoVertice(pregion->gcastillos,aux1));
		//			exce2 = obtener_exce(infoVertice(pregion->gcastillos,aux2));
		min_ataque1 = obtener_min(infoVertice(pregion->gcastillos,aux1));
		min_ataque2 = obtener_min(infoVertice(pregion->gcastillos,aux2));
		//El arco de 1 a 2 lleva el peso del minimo de soldados necesarios para atacar a 2 y viceversa
		insArco(pregion->gcastillos,aux1,aux2,min_ataque2);
		insArco(pregion->gcastillos,aux2,aux1,min_ataque1);

	}
	pregion->nro_castillos= nro_castillos;
	/*todo revisar */
	for (i=1;i<nro_castillos-1;i++){
		if ((caminos = hayCamino(pregion->gcastillos,1,(i+1),(int*)&costo)) == NULL){
			fprintf(stderr,"%s\n","region inconexa");
			destruir_region(pregion,destruir_castillo);
			return NULL;
		}
		destruirLista(caminos,free);
	}
	return pregion;
}
/*=============================================================*/
pmapa_t parsear_mapa(FILE * parchivo){
	pmapa_t pmapa;
	char * cadena;
	int i=0;

	if ((pmapa = mapa())== NULL)
		return NULL;

	/* Creo MAX_REGIONES -todo mejorar regiones ilimitadas*/
	if((pmapa->regiones = (pRegion_t*)malloc(MAX_REGIONES*sizeof(pRegion_t)))==NULL){
		free(pmapa);
#ifdef DEBUG
		fprintf(stderr,"%s:%s\n",MSJ_ERR_MEMORIA_INSUF,"regiones");
#endif
		return NULL;
	}
	while((cadena = readline(parchivo))!= NULL && strcmp(cadena,CADENA_DE_CORTE)){
		if ((pmapa->regiones[pmapa->nro_regiones]= parsear_region(parchivo,pmapa->nro_regiones,cadena))==NULL){
			/* Si no puedo cargar una region por mal formato, destruyo todas las regiones creadas */
			for(i=0;i < pmapa->nro_regiones;i++)
				destruir_region(pmapa->regiones[i],destruir_castillo);
#ifdef DEBUG
			fprintf(stderr,"%s\t%s\ncadena:%s\n",MSJ_ERR_MEMORIA_INSUF,"Error al crear region",cadena);
#endif
			free (cadena);
			free(pmapa->regiones);
			free(pmapa);
			return NULL;
		}
		//		pmapa->regiones[i]->nro_castillos=;
		free(cadena);
		pmapa->nro_regiones++;
	}
	return pmapa;
}
/*=============================================================*/
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
