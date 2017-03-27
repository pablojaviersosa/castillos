/*-------------------------------------------------------------------*/
/* TAD Grafo                                                         */
/*-------------------------------------------------------------------*/
/* Autor: Pablo Sosa												 */
/* Fecha:															 */
/*-------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "grafo.h"


/* Crea y retorna un grafo vac�o */
/* post: inicGrafo = ( , ) */
Grafo inicGrafo(void) {
	Grafo g;
	int i, k;
	if((g = (Grafo) malloc(sizeof(TGrafo))) == NULL)
		return NULL;
	if((g->vertices = (Vertice *) calloc(MAX, sizeof(Vertice))) == NULL){
		free(g);
		return NULL;
	}
	if((g->arcos = (int **) malloc(MAX* sizeof(int*))) == NULL){
		free(g->vertices);
		free(g);
		return NULL;
	}
	for (i = 0; i < MAX; i++) {
		if ((g->arcos[i] = (int *) calloc(MAX,sizeof(int ))) == NULL){
			for (k=0;k<i;k++)
				free(g->arcos[k]);
			free(&(*(g->arcos)));
			free(g->vertices);
			free(g);
			return NULL;
		}
		for (k = 0; k < MAX; k++)
			g->arcos[i][k] = SIN_ARCO;
	}
	g->capacidad = MAX;
	g->numElem = 0;
	return &(*g);
}

/* Agrega un v�rtice al grafo con la informaci�n elem asociada */
/* pre: g = ( { v1, ... , vn }, A ) */
/* post: g = ( { v1, ... , vn, vn+1 }, A ), info( vn+1 ) = elem */
void insVertice(Grafo g, TipoG elem) {// Grafo autodimensionable.
	int i,j,cant_elementos = g->numElem+1;
	int *auxi,**aux;
	Vertice * nuevos_vert;
 
	if (g->numElem > TAM_MAX)
		return;
	if (g->numElem == (g->capacidad-1)){
		cant_elementos += MAX;
		fprintf(stdout,"nueva cantidad de elementos %d\n",cant_elementos);
		/*Crea la nueva matriz de arcos y el arreglo de punteros a vertices
		 * */
		if((aux = (int**)malloc(sizeof(int*)*cant_elementos)) == NULL){
			return;
		}
		for (i=0;i<cant_elementos;i++){
			if((auxi = (int*)calloc(cant_elementos,sizeof(int))) == NULL){
				for (j=0; j < i; j++){
					free(aux[j]);
				}
				free(aux);
				return;
			}
			aux[i] = auxi;

			for (j=0; j < cant_elementos; j++){//
				aux[i][j] = SIN_ARCO;
			}
		}
		if((nuevos_vert = (Vertice*)malloc(sizeof(Vertice)*(cant_elementos))) == NULL){
			for (i=0;i<cant_elementos; i++){
				free(aux[i]);
			}
			free(aux);
			return;
		}
		//inicializo matriz
		for (i=0;i<g->numElem; i++){
			for(j=0; j < g->numElem;j++){
				aux[i][j] = g->arcos[i][j];
			}
		}
		//libera la matriz anterior
		for (i=0;i<g->numElem; i++){
			free(g->arcos[i]);
		}
		free(g->arcos);
		//inicializa vertices
		for (i=0;i < g->numElem; i++){
			nuevos_vert[i].info = g->vertices[i].info;
			nuevos_vert[i].marca = g->vertices[i].marca;
		}
		//libera vertices
		free(g->vertices);

		g->arcos = aux;
		g->capacidad = cant_elementos;
		g->vertices =nuevos_vert;
		
	}
	g->vertices[g->numElem].info = elem;
	g->vertices[g->numElem].marca = 0;
	g->numElem++;
}

/* Agrega al grafo el arco x1 x2 con costo c */
/* pre: V = { v1, ... , vn }, x1 = vi, x2 = vk, k ( x1, x2, k ) A, c 0 */
/* post: g = ( V, A U ( x1, x2, c ) */
void insArco(Grafo g, int v, int w, int c) {
	g->arcos[v - 1][w - 1] = c;
}
/*
 * Inserta putero al nodo que le dio origen

void insPadre(Grafo g,int vertice,int padre){
	g->vertices[vertice-1].ppadre = &(g->vertices[padre-1]);

}
*/
/* Elimina del grafo el arco x1 x2 */
/* pre: ( x1, x2, c ) A */
/* post: g = ( V, A - ( x1, x2, c ) ) */
void elimArco(Grafo g, int v, int w) {
	g->arcos[v - 1][w - 1] = -1;
}

/* Marca el v�rtice v */
/* pre: v V, V' = V'ini */
/* post: V' = V'ini + v */
void marcarVertice(Grafo g, int v) {
	g->vertices[v - 1].marca = 1;
}

/* Desmarca el v�rtice v */
/* pre: v V', V' = V'ini */
/* post: V' = V'ini - v */
void desmarcarVertice(Grafo g, int v) {
	g->vertices[v - 1].marca = 0;
}

/* Desmarca todos los v�rtices del grafo */
/* post: V' = */
void desmarcarGrafo(Grafo g) {
	if(g != NULL){
	int i;
	for (i = 0; i < g->numElem; i++)
		g->vertices[i].marca = 0;
	}
}

/* Retorna el costo del arco x1 x2 si �ste existe. En caso contrario retorna -1 */
/* post: ( ( x1, x2, c ) A , costoArco = c ) ( c ( x1, x2, c ) A , costoArco = -1 ) */
int costoArco(Grafo g, int v, int w) {
	return g->arcos[v - 1][w - 1];
}

/* Retorna una lista con los identificadores de los v�rtices sucesores de v */
/* pre: v V */
/* post: sucesores = < x1, ... , xk > | v xi */
void* sucesores(Grafo g, int v) {
	int i;
	int *j;
	Lista listo = inicLista();
	for (i = 0; i < g->numElem; i++)
		if (g->arcos[v - 1][i] != -1){
			if((j=(int*)malloc(sizeof(int)))!=NULL)
				*j=i+1;
				anxLista(listo, j);
		}
	return (Lista)listo;
}

/* Retorna la informaci�n asociada con el v�rtice v */
/* pre: v V */
/* post: infoVertice = info( v ) */
TipoG infoVertice(Grafo g, int v) {
	return g->vertices[v - 1].info;
}

/* Retorna el n�mero de v�rtices del grafo */
/* post: ordenGrafo = n */
int ordenGrafo(Grafo g) {
	return g->numElem;
}

/* Informa si el v�rtice v est� marcado */
/* pre: v V */
/* post: marcadoVertice = ( v V' ) */
int marcadoVertice(Grafo g, int v) {
	return g->vertices[v - 1].marca;
}

/* Destruye el objeto abstracto, retornando toda la memoria ocupada por �ste */
/* post: el grafo g no tiene memoria reservada */
void destruirGrafo(Grafo g,void(*pf)(TipoG)) {
	int i;
	if (g != NULL && pf != NULL) {
		for (i = 0; i < g->numElem; i++){
			pf(g->vertices[i].info);

		}
		for (i = 0; i < g->capacidad; i++){
			free(g->arcos[i]);
		}
		free(&(*(g->arcos)));
		free(g->vertices);
		free(g);
	}
}

/* Construye un grafo a partir de la informaci�n de un archivo */
/* pre: el archivo est� abierto y es estructuralmente correcto, de acuerdo con el esquema de persistencia */
/* post: se ha construido el grafo que corresponde a la imagen de la informaci�n del archivo */
Grafo cargarGrafo(FILE *fp,TipoG (*pf_cargar)(FILE*)) {

	int numVertices, v1, v2, costo;
	Grafo g = inicGrafo();
	TipoG dato;

	fscanf(fp, "%d\n", &numVertices);

	for (; numVertices > 0; numVertices--) {
		//fscanf(fp, "%d", &dato);
		dato = pf_cargar(fp);
		insVertice(g, dato);
	}
	fscanf(fp, "%d %d %d\n", &v1, &v2, &costo);
	//printf("costo %d %d %d  ", v1, v2, costo);
	while (v1 != -1) {
		insArco(g, v1, v2, costo);
		fscanf(fp, "%d %d %d", &v1, &v2, &costo);
	}
	return g;
}

/* Salva el grafo en un archivo */
/* pre: el archivo esta abierto */
/* post: se ha hecho persistir el grafo en el archivo, la ventana de la lista esta indefinida */
void salvarGrafo(Grafo g, FILE *fp, void(*pf_salvar)(FILE*, TipoG)) {
	int i, k;
	//orden del grafo
	fprintf(fp, "%d\n", g->numElem);
	//cada uno de los datos
	for (i = 0; i < g->numElem; i++)
		pf_salvar(fp, infoVertice(g, i + 1));
	//leer la matriz de arcos
	for (i = 0; i < g->numElem; i++)
		for (k = 0; k < g->numElem; k++)
			if (g->arcos[i][k] != -1)
				fprintf(fp, "%d %d %d\n", i + 1, k + 1, g->arcos[i][k]);
	fprintf(fp, "-1 -1 -1\n");
}

/* Imprime la matriz de adyacencias */
void impGrafo(Grafo g,void (*pf_imprimir)(FILE*,TipoG)) {
#ifdef _DEBUG
	int k;
#endif
	int i;
	for (i = 0; i < ordenGrafo(g); i++) {
#ifdef _DEBUG
		fprintf(stderr,"%2d [%c] ", i + 1, (marcadoVertice(g, i + 1) ? '*' : ' '));
		for (k = 1; k < g->numElem; k++)
			fprintf(stderr,"%2d ", g->arcos[i][k]);
		fprintf(stderr,"%s","\n");
#endif
		pf_imprimir(stdout,infoVertice(g, i + 1));
#ifdef _DEBUG
		fprintf(stderr,"numero de elementos:%d\ncapacidad:%d\n",g->numElem,g->capacidad);
		fprintf(stderr,"\n");
#endif
	}
}

void hacerSiPertenece(Grafo g,void (*pf_imprimir)(FILE*,TipoG),void* l) {
	Lista p = (Lista)l;

	int i, k;

	primLista(p);
	for (i = 0; i < ordenGrafo(g)&& finLista(p); i++) {
		if(p->longitud != 0){
			if(i+1 == *((int*)p->ventana->info)){
				printf("%2d [%c] ", i + 1, (marcadoVertice(g, i + 1) ? '*' : ' '));
				for (k = 0; k < g->numElem; k++)
					printf("%2d ", g->arcos[i][k]);
				printf("\n");
				pf_imprimir(NULL,infoVertice(g, i + 1));
				printf("numero de elementos:%d\ncapacidad:%d\n",g->numElem,g->capacidad);
				printf("\n");
				sigLista(p);
			}
		}
	}
}
