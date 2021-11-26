#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "LinkedList.h"

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this;

    this=(LinkedList*)malloc(sizeof(LinkedList));

    if(this!=NULL)
    {
        this->size=0;
        this->pFirstNode=NULL;
    }

    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int returnAux=-1;

    if(this!=NULL)
    {
        returnAux=this->size;
    }

    return returnAux;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
    Node* pNode=NULL;

    if(this!=NULL && nodeIndex>=0 && nodeIndex<ll_len(this))
    {
        pNode=this->pFirstNode;

        while(nodeIndex>0)
        {
            pNode=pNode->pNextNode;
            nodeIndex--;
        }
    }

    return pNode;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex, void* pElement)
{
    int error=-1;
    Node* newNode=NULL;
    Node* previousNode=NULL;

    if(this!=NULL && nodeIndex>=0 && nodeIndex<=ll_len(this))
    {
        newNode=(Node*)malloc(sizeof(Node));

        if(newNode!=NULL)
        {
            newNode->pElement=pElement;
            newNode->pNextNode=getNode(this, nodeIndex);

            if(!nodeIndex)
            {
                this->pFirstNode=newNode;
            }
            else
            {
                previousNode=getNode(this, nodeIndex-1);
                previousNode->pNextNode=newNode;
            }

            this->size++;

            error=0;
        }
    }

    return error;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    return addNode(this, ll_len(this), pElement);
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    void* pElement=NULL;
    Node* node=NULL;

    if(this!=NULL && index>=0 && index<ll_len(this))
    {
        node=getNode(this, index);

        if(node!=NULL)
        {
            pElement=node->pElement;
        }
    }
    return pElement;
}

/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
    int error=-1;
    Node* aux=NULL;

    if(this!=NULL && index>=0 && index<ll_len(this))
    {
        aux=getNode(this, index);

        if(aux!=NULL)
        {
            aux->pElement=pElement;
            error=0;
        }
    }
    return error;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
    int error=-1;
    Node* nodeToRemove=NULL;
    Node* previousNode=NULL;

    if(this!=NULL && index>=0 && index<ll_len(this))
    {
        nodeToRemove=getNode(this, index);

        if(nodeToRemove!=NULL)
        {
            if(!index)
            {
                this->pFirstNode=nodeToRemove->pNextNode;
            }
            else
            {
                previousNode=getNode(this, index-1);

                if(previousNode!=NULL)
                {
                    previousNode->pNextNode=nodeToRemove->pNextNode;
                }
            }

            free(nodeToRemove);
            this->size--;
            error=0;
        }
    }

    return error;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int error=-1;

    if(this!=NULL)
    {
        while(ll_len(this))
        {
            error=ll_remove(this, 0);

            if(error)
            {
                break;
            }
        }
        error=0;
    }
    return error;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int error=-1;

    if(this!=NULL)
    {
        if(!ll_clear(this))
        {
            free(this);
            error=0;
        }
    }

    return error;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int index=-1;

    if(this!=NULL)
    {
        for(int i=0; i<ll_len(this); i++)
        {
            if(ll_get(this, i)==pElement)
            {
                index=i;
                break;
            }
        }
    }
    return index;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int isEmpty=-1;

    if(this!=NULL)
    {
        if(!ll_len(this))
        {
            isEmpty=1;
        }
        else if(ll_len(this)>0)
        {
            isEmpty=0;
        }
    }

    return isEmpty;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    return addNode(this, index, pElement);
}

/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this, int index)
{
    void* pElement=NULL;

    if(this!=NULL && index>=0 && index<ll_len(this))
    {
        pElement=ll_get(this, index);
        ll_remove(this, index);
    }

    return pElement;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int error=-1;

    if(this!=NULL)
    {
        error=0;

        if(ll_indexOf(this, pElement)!=-1)
        {
            error=1;
        }
    }

    return error;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this, LinkedList* this2)
{
    int error=-1;

    if(this!=NULL && this2!=NULL)
    {
        error=1;

        for(int i=0; i<ll_len(this); i++)
        {
            if(!ll_contains(this, ll_get(this2, i)))
            {
                error=0;
                break;
            }
        }
    }
    return error;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this, int from, int to)
{
    LinkedList* cloneArray=NULL;

    if(this!=NULL && from<to && from>=0 && to<=ll_len(this))
    {
        cloneArray=ll_newLinkedList();

        if(cloneArray!=NULL)
        {
            for(int i=from; i<to; i++)
            {
                ll_add(cloneArray, ll_get(this, i));
            }
        }
    }
    return cloneArray;
}

/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    return ll_subList(this, 0, ll_len(this));
}

/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)
{
    int error=-1;
    void* auxElement=NULL;

    if(this!=NULL && pFunc!=NULL && order>=0 && order<=1)
    {
        int tam=ll_len(this);

        for(int i=0; i<tam-1; i++)
        {
            for(int j=i+1; j<tam; j++)
            {
                if((pFunc(ll_get(this, i), ll_get(this, j)) >0 && order) || (pFunc(ll_get(this, i), ll_get(this, j)) <0 && !order))
                {
                    auxElement=ll_get(this, i);
                    ll_set(this, i, ll_get(this, j));
                    ll_set(this, j, auxElement);

                }
            }
        }
        error=0;
    }
    return error;
}

/** \brief Mapea valores
 * \param *pFunc Puntero a funcion
 * \return LinkedList* ll_map(LinkedList* this,
 */
LinkedList* ll_map(LinkedList* this, void*(*pFunc) (void* element))
{
    int len;
    void* auxElement=NULL;

    if(this!=NULL && pFunc!=NULL)
    {
        len=ll_len(this);

        srand(time(NULL));

        for(int i=0; i<len; i++)
        {
            auxElement=ll_get(this, i);
            auxElement=pFunc(auxElement);
            ll_set(this, i, auxElement);
        }
    }
    return this;
}

/** \brief Devuelve un nuevo LinkedList cargado con los elementos que pasan la funcion filtro
 * \return LinkedList* this LinkedList a filtrar
 * \param int(*pFunc)(void* element) Puntero a la funcion que filtra
 * \return Nuevo puntero a LinkedList con los elementos que pasaron la funcion
 */
LinkedList* ll_filter(LinkedList* this, int (*pFunc)(void* element))
{
    LinkedList* filteredList=NULL;

    if(this!=NULL && pFunc!=NULL)
    {
        filteredList=ll_newLinkedList();
        if(filteredList!=NULL)
        {
            int len=ll_len(this);
            for(int i=0; i<len; i++)
            {
                if(pFunc(ll_get(this, i)))
                {
                    ll_add(filteredList, ll_get(this, i));
                }
            }
        }
    }
    return filteredList;
}
