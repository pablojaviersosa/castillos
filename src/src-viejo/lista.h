#ifndef __LISTA_H
#define __LISTA_H
/*-----------------------------------------------------------------
 	 	 TAD Lista
-------------------------------------------------------------------
*/

typedef int TipoL;

typedef struct ListaNodo
{   TipoL info;
    struct ListaNodo *ant, *sig;
}   ListaNodo, *pListaNodo;

typedef struct TLista
{   pListaNodo primero, ultimo, ventana;
    int longitud;
}   TLista, *Lista;

typedef pListaNodo Ventana;

/*-------------------------------------------------------------------*/
/* 				 OPERACIONES                           */
/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/
/*		Constructora 						  */
/*-------------------------------------------------------------------*/
/* Crea y retorna una lista vac�a */
Lista inicLista(void);
/*-------------------------------------------------------------------*/
/* 		Modificadoras 						  */
/*-------------------------------------------------------------------*/

/* Agrega un elemento despu�s de la ventana */
void anxLista(Lista lst, TipoL elem);

/* Agrega un elemento antes de la ventana */
void insLista(Lista lst, TipoL elem);

/* Elimina el elemento que se encuentra en la ventana */
void elimLista(Lista lst,void (*pf)(void *));

/* Avanza la ventana una posicion */
void sigLista(Lista lst);

/* Coloca la ventana sobre el primer elemento de la lista */
void primLista(Lista lst);

/* Coloca la ventana sobre el �ltimo elemento de la lista */
void ultLista(Lista lst);

/* Coloca la ventana sobre el pos-�simo elemento de la lista */
void posLista(Lista lst, int pos);

/* Coloca la ventana de una lista sobre la marca dada */
void situarLista(Lista lst, Ventana vent);

/* Concatenar Lista */
void concatenarLista(Lista lst1, Lista lst2);

/*-------------------------------------------------------------------*/
/* 		   Analizadoras 						 */
/*-------------------------------------------------------------------*/

/* Retorna el elemento de la ventana */
TipoL infoLista(Lista lst);

/* Retorna el n�mero de elementos de la lista */
int longLista(Lista lst);

/* Informa si la ventana esta indefinida */
int finLista(Lista lst);

/* Retorna una marca sobre la ventana actual de la lista */
Ventana ventanaLista(Lista lst);

/* Recorrer lista */
void recorrerLista(Lista lst, void (*f)(int));

/*-------------------------------------------------------------------*/
/* 							Destructora 							 */
/*-------------------------------------------------------------------*/

/* Destruye el objeto abstracto, retornando toda la memoria ocupada por �ste */
void destruirLista(Lista lst,void (*pf)(void *));
/*-------------------------------------------------------------------*/
/* 							Persistencia 							 */
/*-------------------------------------------------------------------*/

/* Construye una lista a partir de la informaci�n de un archivo */
Lista cargarLista(FILE *fp);

/* Salva la lista en un archivo */
void salvarLista(Lista lst, FILE *fp);

/*-------------------------------------------------------------------*/
/* 							Depuracion 								 */
/*-------------------------------------------------------------------*/

/* Muestra por pantalla toda la lista y la posici�n de la ventana */
void impLista(Lista lst);

/*--------------------------------------------------------------------*/
#endif
