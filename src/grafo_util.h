#ifndef __GRAFO_UTIL_H
#define __GRAFO_UTIL_H

/*-------------------------------------------------------------------*/
/* TAD Grafo                                                         */
/*-------------------------------------------------------------------*/
/* Autor:															 */
/* Fecha:															 */
/*-------------------------------------------------------------------*/


/*-------------------------------------------------------------------*/
/* 							Analizadoras 							 */
/*-------------------------------------------------------------------*/

/* Lista todos los vertices con el camino de costo minimo de v1 a v2, en costo almacena su valor */
void* hayCamino(Grafo g, int v1, int v2, int *costo);

/* Retorna una lista con todos los vertices que son sumideros */
void* sumideros(Grafo g);

/* Recorrido en profundidad */
void profundidadGrafo(Grafo g, int v, void (*f)(FILE*,TipoG));

/* Recorrido por nivel */
void nivelGrafo(Grafo g, int v, void (*f)(FILE*,TipoG));

/* Retorna un array con los costos minimos para llegar a cada vertice desde el vertice v */
int *dijkstra(Grafo g, int v);

void heuristicaGrafo( Grafo g, int v,void* lst_soluciones,void (*pf_visitar)(void*, int ,void*),int h(TipoG t));

void heuristicaVertice( Grafo g, int v,void* lst_soluciones,void (*pf_visitar)(void*, int,void*),int h(TipoG t));

void insHeuristica( void* listafrente, Grafo g, int v,int h(TipoG t) );

/*-------------------------------------------------------------------*/
#endif

