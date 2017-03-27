/*-------------------------------------------------------------------*/
/* TAD Lista - Implementacion #1 (Doblemente encadenada)             */
/*-------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

typedef int TipoL;


/*-------------------------------------------------------------------*/
/* Constructora: Crea una lista vacia. La ventana es indefinida      */
/* Complejidad:    O(1)                                              */

/* post: inicLista = < >[] */

Lista inicLista(void) {
	Lista resp;

	resp =(Lista) malloc (sizeof(TLista));

	resp->primero = resp->ultimo = resp->ventana = NULL;
	resp->longitud = 0;
	return resp;
}

/*-------------------------------------------------------------------*/
/* Modificadora: Coloca el nuevo elemento en la posicion siguiente a */
/*               la ventana. Si la lista es vacia lo coloca de       */
/*               primero en la lista                                 */
/* Complejidad:  O(1)                                                */

/* pre: lst = LST, lst = < >[] || lst = < x1 ,... ,[xi] ,... ,xn > */
/* post: ( LST = < >[], lst =<[elem]>) || ( LST = < x1 ,... ,[xi] ,... ,xn >, lst = < x1 ,... ,xi ,[elem] ,... ,xn >) */

void anxLista(Lista lst, TipoL elem) {
	pListaNodo nuevo = (pListaNodo) malloc(sizeof(struct ListaNodo));
	nuevo->info = elem;
	nuevo->ant = nuevo->sig = NULL;
	if (lst->longitud == 0)
		lst->primero = lst->ultimo = nuevo;
	else if (lst->ventana == lst->ultimo) {
		lst->ventana->sig = lst->ultimo = nuevo;
		nuevo->ant = lst->ventana;
	} else {
		nuevo->ant = lst->ventana;
		nuevo->sig = lst->ventana->sig;
		lst->ventana->sig->ant = nuevo;
		lst->ventana->sig = nuevo;
	}
	lst->ventana = nuevo;
	lst->longitud++;
}

/*-------------------------------------------------------------------*/
/* Modificadora: Coloca el nuevo elemento en la posicion anterior a  */
/*               la ventana. Si la lista es vacia lo coloca de       */
/*               primero en la lista                                 */
/* Complejidad:  O(1)                                                */

/* pre: lst = LST, lst = < >[] || lst = < x1 ,... ,[xi] ,... ,xn > */
/* post: ( LST = < >[], lst =<[elem]>) || ( LST = < x1 ,... ,[xi] ,... ,xn >, lst = < x1 ,... ,[elem] ,xi ,... ,xn > ) */

void insLista(Lista lst, TipoL elem) {
	pListaNodo nuevo = (pListaNodo) malloc(sizeof(struct ListaNodo));
	nuevo->info = elem;
	nuevo->ant = nuevo->sig = NULL;
	if (lst->longitud == 0)
		lst->primero = lst->ultimo = nuevo;
	else if (lst->ventana == lst->primero) {
		lst->primero = lst->ventana->ant = nuevo;
		nuevo->sig = lst->ventana;
	} else {
		nuevo->sig = lst->ventana;
		nuevo->ant = lst->ventana->ant;
		lst->ventana->ant->sig = nuevo;
		lst->ventana->ant = nuevo;
	}
	lst->ventana = nuevo;
	lst->longitud++;
}

/*-------------------------------------------------------------------*/
/* Modificadora: Elimina el elemento que se encuentra en la ventana  */
/*               de la lista. La ventana queda sobre el siguiente    */
/*               elemento. Si era el ultimo, la ventana queda        */
/*               indefinida.                                         */
/* Complejidad:  O(1)                                                */

/* pre: lst = LST = < x1 ,... ,[xi] ,... ,xn > */
/* post: ( LST = <[x1]>, lst =< >[] ) || ( LST = < x1 ,... ,[xn] >, lst = < x1 ,... ,[xn-1] >[] ) ||
 ( LST = < x1 ,... ,[xi] ,... ,xn >, lst = < x1 ,... ,xi-1, [xi+1],... ,xn > ) */

void elimLista(Lista lst,void (*pf)(void *)) {
	pListaNodo aux;

	if (lst->ventana == lst->primero) {
		if (lst->ultimo == lst->primero)
			lst->ultimo = NULL;
		lst->primero = lst->primero->sig;
		free(lst->ventana);
		lst->ventana = lst->primero;
	} else {
		if (lst->ultimo == lst->ventana)
			lst->ultimo = lst->ultimo->ant;
		lst->ventana->ant->sig = lst->ventana->sig;
		if (lst->ventana->sig != NULL)
			lst->ventana->sig->ant = lst->ventana->ant;
		aux = lst->ventana;
		lst->ventana = lst->ventana->sig;
		pf(aux);
	}
	lst->longitud--;
}

/*-------------------------------------------------------------------*/
/* Modificadora: Mueve una posicion a la derecha la ventana. Si esta */
/*               sobre el ultimo elemento la ventana queda           */
/*               indefinida                                          */
/* Complejidad:  O(1)                                                */

/* pre: lst = LST = < x1 ,... ,[xi] ,... ,xn > */
/* post: ( LST = < x1 ,... ,[xi] ,... ,xn >, lst = < x1 ,... ,xi ,[xi+1] ,... ,xn > ) ||
 ( LST = < x1 ,... ,[xn] >, lst = < x1 ,... ,xn >[] ) */

void sigLista(Lista lst) {
	lst->ventana = lst->ventana->sig;
}

/*-------------------------------------------------------------------*/
/* Modificadora: Coloca la ventana sobre el primer elemento          */
/* Complejidad:  O(1)                                                */

/* pre: lst = LST */
/* post: ( LST = < >[], lsr = < >[]) ||
 ( LST = < x1 ,... ,xn >, lst = < [x1] ,... ,xn > ) */

void primLista(Lista lst) {
	lst->ventana = lst->primero;
}

/*-------------------------------------------------------------------*/
/* Modificadora: Coloca la ventana sobre el ultimo elemento          */
/* Complejidad:  O(1)                                                */

/* pre: lst = LST */
/* post: ( LST = < >[], lsr = < >[]) ||
 ( LST = < x1 ,... ,xn >, lst = < x1 ,... ,[xn] > ) */

void ultLista(Lista lst) {
	lst->ventana = lst->ultimo;
}

/*-------------------------------------------------------------------*/
/* Modificadora: Coloca la ventana sobre una posicion dada           */
/* Complejidad:  O(N)                                                */

/* post: ( pos < 1 || pos > n, lst = < x1 ,... ,xn >[] ) ||
 ( lst = < x1 ,... ,[xpos] ,... ,xn > ) */

void posLista(Lista lst, int pos) {
	int i;
	for (lst->ventana = lst->primero, i = 1; i < pos; i++)
		lst->ventana = lst->ventana->sig;
}

/*-------------------------------------------------------------------*/
/* Modificadora: Coloca la ventana en vent                           */
/* Complejidad:	O(1) 												 */

/* pre: lst = < x1 ,... ,[xi] ,... ,xj ,... ,xn > */
/* post: lst = < x1 ,... ,xi ,... ,[xj] ,... ,xn > */

void situarLista(Lista lst, Ventana vent) {
	lst->ventana = vent;
}

/*-------------------------------------------------------------------*/
/* Analizadora: Retorna el elemento que se encuentra en la ventana   */
/* Complejidad: O(1)                                                 */

/* pre: lst = < x1 ,... ,[xi] ,... ,xn > */
/* post: infoLista = xi */

TipoL infoLista(Lista lst) {
	return lst->ventana->info;
}

/*-------------------------------------------------------------------*/
/* Analizadora: Retorna la longitud de la lista                      */
/* Complejidad: O(1)                                                 */

/* post: longLista = n */

int longLista(Lista lst) {
	return lst->longitud;
}

/*-------------------------------------------------------------------*/
/* Analizadora: Indica si la ventana se encuentra indefinida         */
/* Complejidad: O(1)                                                 */

/* post: ( lst = < x1 ,... ,xn >[], finLista = TRUE ) || ( lst = < x1 ,... ,[xi] ,... ,xn >, finLista = FALSE ) */

int finLista(Lista lst) {
	return (lst->ventana == NULL);
}

/*-------------------------------------------------------------------*/
/* Analizadora: Retorna la ventana                                   */
/* Complejidad:	O(1)                                                 */

/* pre: lst = < x1 ,... ,[xi] ,... ,xn > tiene una ventana */
/* post: lst = < x1 ,... ,[xi] ,... ,xn > retorna referencia a la ventana */

Ventana ventanaLista(Lista lst) {
	return lst->ventana;
}

/*-------------------------------------------------------------------*/
/* Destructora: Retorna la memoria ocupada por una lista             */
/* Complejidad:	O(N)                                                 */

/* post: la lista lst no tiene memoria reservada */
void destruirLista(Lista lst,void (*pf)(void *)) {
	pListaNodo p, q;
	for (p = lst->primero; p != NULL;) {
		q = p;
		p = p->sig;
		pf(q);
	}
	free(lst);
}


/*-------------------------------------------------------------------*/
/* Persistencia: Carga una lista de un archivo                       */
/* Complejidad:	O(N)                                                 */

/* pre: el archivo est� abierto y es estructuralmente correcto, de acuerdo con el esquema de persistencia */
/* post: se ha construido la lista que corresponde a la imagen de la informaci�n del archivo */

Lista cargarLista(FILE *fp) {
	int longit, elem;
	Lista lst = inicLista();
	fscanf(fp, "%d", &longit);
	for (; longit > 0; longit--) {
		fscanf(fp, "%d", &elem);
		anxLista(lst, elem);
	}
	return lst;
}

/*-------------------------------------------------------------------*/
/* Persistencia: Salva una lista en un archivo                       */
/* Complejidad:	O(N)                                                 */

/* pre: el archivo est� abierto */
/* post: se ha hecho persistir la lista en el archivo, la ventana de la lista est� indefinida */

void salvarLista(Lista lst, FILE *fp) {
	fprintf(fp, "%d\n", longLista(lst));
	for (primLista(lst); !finLista(lst); sigLista(lst))
		fprintf(fp, "%d\n", infoLista(lst));
}

/*-------------------------------------------------------------------*/
/* Depuracion: Imprime el contenido de una lista, mostrando su       */
/*             longitud y la posicion de la ventana                  */
/* Complejidad:	O(N)                                                 */

void impLista(Lista lst) {
	pListaNodo p = lst->primero;

	/* Imprime la longitud */
	printf("\n[%d] <", lst->longitud);

	/* Recorre la lista imprimiendo sus elementos */
	while (p != NULL) { /* Indica la posicion de la ventana */
		if (p == lst->ventana)
			printf("[ ");
		printf("%d ", p->info);
		/* Indica la posicion de la ventana */
		if (p == lst->ventana)
			printf("] ");
		p = p->sig;
	}

	printf(">");
	/* Indica si la ventana se encuentra indefinida */
	if (lst->ventana == NULL)
		printf(" *");
	printf("\n");
}

/* Recorrer lista */
void recorrerLista(Lista lst, void (*f)(int)) {
	pListaNodo p = lst->primero;
	while (p != NULL) {
		f(p->info);
		p = p->sig;
	}
}

/* Concatenar Lista */
void concatenarLista(Lista lst1, Lista lst2) {
	ultLista(lst1);
	for (primLista(lst2); !finLista(lst2); elimLista(lst2,free))
		anxLista(lst1, infoLista(lst2));
	primLista(lst1);
}

