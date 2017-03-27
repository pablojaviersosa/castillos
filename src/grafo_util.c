/*-------------------------------------------------------------------*/
/* TAD Grafo                                                         */
/*-------------------------------------------------------------------*/
/* Autor:															 */
/* Fecha:															 */
/*-------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "grafo.h"
#include "grafo_util.h"

/* Lista todos los vertices con el camino de costo m�nimo de v1 a v2, en costo almacena su valor */
/* pre: g = ( V, A, V' ), v1, v2 V, V' tiene los marcados */
/* post: ( hayCamino4 = < v1, ... , v2 > camino de costo m�nimo de v1 a v2, *costo = costo( < v1, ... ,v2 > ) ) v
 ( hayCamino4 = < > , *costo = -1, no hay camino de v1 a v2 ) */


void* hayCamino(Grafo g, int v1, int v2, int *costo) {
	int menor,*aux;
	Lista suc, resp1, resp2 = inicLista();

	if (costo == NULL)
		return NULL;
	if((aux = (int*)malloc(sizeof(int)))== NULL)
		return NULL;
	/*if((resp2 = inicLista())==NULL){
		free(aux);
		return NULL;
	}*/
	if (v1 == v2) {
		*costo = 0;
		*aux = v1;
		insLista(resp2, aux);
	} else {
		suc = sucesores(g, v1);
		marcarVertice(g, v1);
		for (menor = -1, primLista(suc); !finLista(suc); elimLista(suc,free))
			if (!marcadoVertice(g, *((int*)infoLista(suc)))) {
				resp1 = (Lista) hayCamino(g, *((int*)infoLista(suc)), v2, costo);
				if (*costo != -1) {
					*costo += costoArco(g, v1, *((int*)infoLista(suc)));
					if (menor == -1 || *costo < menor) {
						menor = *costo;
						destruirLista(resp2,free);
						resp2 = resp1;
					} else
						destruirLista(resp1,free);
				}
			}
		desmarcarVertice(g, v1);
		*costo = menor;
		if (*costo != -1) {
			primLista(resp2);
			*aux = v1;
			insLista(resp2, aux);
		}
	}
	return (Lista)resp2;
}
/*
 *
 */
void* sumideros(Grafo g) {
	int i, *aux,numVert = ordenGrafo(g);
	Lista lst, resp;

	if((resp = inicLista())==NULL){
		return NULL;
		}
	for (i = 1; i <= numVert; i++) {
		if (longLista(lst = sucesores(g, i)) == 0){
			aux = (int*)malloc(sizeof(int));
			*aux= i;
			anxLista(resp, aux);
			destruirLista(lst,free);
		}
	}
	return (Lista)resp;
}


static void profundidadVertice(Grafo g, int v, void (*pf_visitar)(FILE*,TipoG)) {
	Lista lst = sucesores(g, v);

	pf_visitar(NULL,infoVertice(g,v));
	marcarVertice(g, v);
	for (primLista(lst); !finLista(lst); elimLista(lst,free))
		if (!marcadoVertice(g, *((int*)infoLista(lst))))
			profundidadVertice(g, *((int*)infoLista(lst)), pf_visitar);
	destruirLista(lst,free);
}

/* Recorrido en profundidad */
/* pre: g = ( V, A, V' ), v V */
/* post: se ha hecho un recorrido en profundidad a partir del v�rtice v */
void profundidadGrafo(Grafo g, int v, void (*pf_visitar)(FILE*,TipoG)) {
	int i, numVert = ordenGrafo(g);
	desmarcarGrafo(g);
	profundidadVertice(g, v, pf_visitar);
	for (i = 1; i <= numVert; i++)
		if (!marcadoVertice(g, i))
			profundidadVertice(g, i, pf_visitar);
	desmarcarGrafo(g);

}

static void nivelVertice(Grafo g, int v, void (*pf_visitar)(FILE*, TipoG)) {
	Lista lst1 = sucesores(g, v);
	pf_visitar(NULL,infoVertice(g,v));
	marcarVertice(g, v);
	for (primLista(lst1); !finLista(lst1); elimLista(lst1,free))
		if (!marcadoVertice(g, *((int*)infoLista(lst1)))) {
			concatenarLista(lst1, sucesores(g, *((int*)infoLista(lst1))));
			pf_visitar(NULL,infoVertice(g,*((int*)infoLista(lst1))));
			marcarVertice(g, *((int*)infoLista(lst1)));
		}
	destruirLista(lst1,free);
}

/* Recorrido por nivel */
/* pre: g = ( V, A, V' ), v V */
/* post: se ha hecho un recorrido por nivel a partir del v�rtice v */
void nivelGrafo(Grafo g, int v, void (*f)(FILE*,TipoG)) {
	int i, numVert = ordenGrafo(g);
	desmarcarGrafo(g);
	nivelVertice(g, v, f);
	for (i = 1; i <= numVert; i++)
		if (!marcadoVertice(g, i))
			nivelVertice(g, i, f);
}

static int min(int v1, int v2) {
	return (v1 < v2) ? v1 : v2;
}

/* pre: g = ( V, A ), costo[ i ] -1, costo[ i ] 0 si i+1 V' */
/* post: ( siguienteVertice = v V, v V', costo [ v-1 ] 1, costo [ v-1 ] es m�nimo entre todos los v posibles )
 ( siguienteVertice = -1, si no existe un v que cumpla las condiciones anteriores ) */
static int siguienteVertice(Grafo g, int costo[], int numElem) {
	int i, menor = -1;
	for (i = 0; i < numElem; i++)
		if (!marcadoVertice(g, i + 1) && costo[i] != -1)
			if (menor == -1 || costo[menor] > costo[i])
				menor = i;
	return (menor == -1) ? -1 : menor + 1;
}

/* Retorna un array con los costos m�nimos para llegar a cada vertice desde el vertice v */
/* pre: g = ( V, A ), v V, card ( V ) = N */
/* post: dijkstra =[D 1  N-1], dijkstra [ i ] = costo del camino m�nimo de v al v�rtice i+1 */
int *dijkstra(Grafo g, int v) {
	int contador_dij=0,c=0, i=0, numElem = ordenGrafo(g);
	int *costo;
	desmarcarGrafo(g);

	if (g == NULL || v < 1)
		return NULL;
	if((costo = (int *) calloc(numElem, sizeof(int))) == NULL)
		return NULL;
	for (i = 0; i < numElem; i++)
		costo[i] = costoArco(g, v, i + 1);
	marcarVertice(g, v);
	costo[v - 1] = 0;
	while ((v = siguienteVertice(g, costo, numElem)) != -1) {
		marcarVertice(g, v);
		for (i = 0; i < numElem; i++)
			if (!marcadoVertice(g, i + 1)
					&& (c = costoArco(g, v, i + 1)) != -1) {
				if (costo[i] == -1)
					costo[i] = costo[v - 1] + c;
				else
					costo[i] = min(costo[i], costo[v - 1] + c);
			}
		contador_dij++;
		if(!(contador_dij%100))
			printf("%d",contador_dij);
	}
	return costo;
}
/* pre: g = ( V, A, V' ), v V, está definida una función h( v ) */
/* post: se ha hecho un recorrido heurístico a partir del vértice v */

void heuristicaGrafo(Grafo graf, int v,void* list,void (*pf_visitar)(void*, int ,void*),int h(TipoG t))
{
	int i=0, numVert=0;
	Grafo g = graf;
	Lista lst_soluciones = (Lista)list;
	if(g==NULL || lst_soluciones == NULL || pf_visitar == NULL|| h == NULL )
		return;
	numVert = ordenGrafo( g );
	desmarcarGrafo( g );
	heuristicaVertice( g, v ,lst_soluciones,pf_visitar,h );
	if (longLista(lst_soluciones)){
		for ( i = 1; i <= numVert;  i++ )
			if ( !marcadoVertice( g, i ) )
				heuristicaVertice( g, i ,lst_soluciones,pf_visitar,h);
		printf("\n");
	}
}

/* pre: g = ( V, A, V' ), v V, V' tiene los vértices ya recorridos, está definida una función h( v ) */
/* post: se ha hecho un recorrido heurístico a partir del vértice v de los vértices alcanzables desde
dicho punto y se han marcado a medida que se van visitando */

 void heuristicaVertice( Grafo g, int v,void* laux,void (*pf_visitar)(void*, int , void*),int h(TipoG t))
{
	int x,*aux;
	Lista lst, frente,lst_soluciones;
	lst_soluciones = (Lista)laux;


	if(g == NULL || lst_soluciones == NULL || pf_visitar == NULL|| h == NULL || v < 1 ){
#ifdef	_DEBUG
		fprintf(stderr,"%s\n","NULL en Heuristica de Vertice");
#endif
		return;
	}
	if((aux = (int*)malloc(sizeof(int)))== NULL)
		return;
	*aux =v;
	frente = inicLista( );
	/*if((frente = inicLista( ))==NULL){
		free(aux);
		return;
	}*/
	anxLista( frente, aux );
	while( longLista( frente ) != 0){
		primLista( frente );
		x = *((int*)infoLista(frente));
		elimLista( frente ,free);

		if( marcadoVertice( g, x ) )
			continue;
		pf_visitar( g, x, lst_soluciones);
		marcarVertice( g, x );
	
		lst = sucesores( g, x );
		for ( primLista( lst ); !finLista( lst ); elimLista( lst,free ) )
			if ( !marcadoVertice( g, *((int*)infoLista(lst))))
				insHeuristica( frente, g, *((int*)infoLista(lst)),h );
		destruirLista(lst,free);
	}
}

/* pre: frente es una lista ordenada de acuerdo con la función h( x ), v frente, frente = F */
/* post: frente = F + v, frente es una lista ordenada de acuerdo con la función h( x ) */

void insHeuristica( void* laux, Grafo g, int v,int h(TipoG t))
{
	Lista frente = (Lista)laux;
	int *aux;

	if( longLista( frente ) == 0 ){
		if((aux = (int*)malloc(sizeof(int)))== NULL)
			return;
		*aux =v;
		insLista( frente, aux );
	}
	else
	{
		for( primLista( frente ); !finLista( frente ); sigLista( frente ) ){
			if( h( infoVertice( g, v ) ) < h( infoVertice( g, *((int*)infoLista(frente))) ) ){
				if((aux = (int*)malloc(sizeof(int)))== NULL)
					return;
				*aux =v;
				insLista( frente, aux );
			return;
			}
		}
		if((aux = (int*)malloc(sizeof(int)))== NULL)
				return;
			*aux =v;
		ultLista( frente );
		anxLista( frente, aux );
	}
}
