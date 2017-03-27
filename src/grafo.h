#ifndef __GRAFO_H
#define __GRAFO_H
/*-------------------------------------------------------------------
	TAD Grafo
-------------------------------------------------------------------*/
//#include "lista.h"
#define MAX 100			/* Numero maximo de vertices */
#define TAM_MAX 20000
#define SIN_ARCO 	-1

typedef void* TipoG;

typedef struct vertice_t{
	//struct vertice_t *ppadre;
	TipoG info; /* Informaci�n asociada con un v�rtice */
	int marca; /* Marca del v�rtice */

} Vertice;

typedef struct {
	int **arcos; /*Matriz de cualquier tama�o, pedida en ejecuci�n */
	Vertice *vertices; /* Vector de v�rtices de cualquier tama�o, pedido en ejecuci�n */
	int numElem; /* N�mero de v�rtices */
	int capacidad; /* Tama�o de las estructuras de datos */
} TGrafo, *Grafo;

/*-------------------------------------------------------------------*/
/*                             OPERACIONES                           */
/*-------------------------------------------------------------------*/

/*-------------------------------------------------------------------*/
/* 							Constructora 							 */
/*-------------------------------------------------------------------*/

/* Crea y retorna un grafo vac�o */
Grafo inicGrafo(void);

/*-------------------------------------------------------------------*/
/* 							Modificadoras 							 */
/*-------------------------------------------------------------------*/

/* Agrega un v�rtice al grafo con la informaci�n elem asociada */
void insVertice(Grafo g, TipoG elem);

/* Agrega al grafo el arco x1 x2 con costo c */
void insArco(Grafo g, int x1, int x2, int c);

/* Elimina del grafo el arco x1 x2 */
void elimArco(Grafo g, int x1, int x2);

void insPadre(Grafo g,int vertice,int padre);

/* Marca el v�rtice v */
void marcarVertice(Grafo g, int v);

/* Desmarca el v�rtice v */
void desmarcarVertice(Grafo g, int v);

/* Desmarca todos los v�rtices del grafo */
void desmarcarGrafo(Grafo g);

/*-------------------------------------------------------------------*/
/* 							Analizadoras 							 */
/*-------------------------------------------------------------------*/

/* Retorna el costo del arco x1 x2 si �ste existe. En caso contrario retorna -1 */
int costoArco(Grafo g, int x1, int x2);

/* Retorna una lista con los identificadores de los v�rtices sucesores de v */
void* sucesores(Grafo g, int v);

/* Retorna la informaci�n asociada con el v�rtice v */
TipoG infoVertice(Grafo g, int v);

/* Retorna el n�mero de v�rtices del grafo */
int ordenGrafo(Grafo g);

/* Informa si el v�rtice v est� marcado */
int marcadoVertice(Grafo g, int v);

/*Realiza una accion sobre los vertices de la lista*/
void hacerSiPertenece(Grafo g,void (*pf)(FILE*,TipoG),void* l);

/*-------------------------------------------------------------------*/
/* 							Destructora 							 */
/*-------------------------------------------------------------------*/

/* Destruye el objeto abstracto, liberando toda la memoria ocupada por �ste */
void destruirGrafo(Grafo g,void(*pf)(TipoG));

/*-------------------------------------------------------------------*/
/* 							Persistencia 							 */
/*-------------------------------------------------------------------*/

/* Construye un grafo a partir de la informaci�n de un archivo */
Grafo cargarGrafo(FILE *fp, TipoG (*pf_cargar)(FILE*));

/* Salva el grafo en un archivo */
void salvarGrafo(Grafo g, FILE *fp, void(*pf_salvar)(FILE*, TipoG ));

/*-------------------------------------------------------------------*/
/* 							Depuracion 								 */
/*-------------------------------------------------------------------*/

/* Imprime la matriz de adyacencias (Depuracion) */
void impGrafo(Grafo g,void(*pf_imprimir)(FILE*,TipoG));

/*-------------------------------------------------------------------*/
#endif

