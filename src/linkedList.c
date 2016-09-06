#include "../includes/linkedList.h"

/**
 * @page create_list \b create_list
 *
 * @brief Creates a new list.
 * 
 * @param comparacion Pointer to function that campares the key of the data.
 * @return The new list if all was OK, NULL otherwise.
 * @section SYNOPSIS
 *  \b #include \b "/includes/lista.h"
 *  \b lib/libLista.a 
 *
 * \b LinkedList* \b create_list(\b comparator comparacion \b)
 *
 * @section descripcion DESCRIPCIÓN
 *
 * This funcition creates a linked list and returns it. 
 *
 * recives:
 * 	-A pointer type function that compares two argumets.
 * 	the ponter type funcition must be as this:
 * 	int compare(const void *a, const void *b);
 *
 * @section return RETORNO
 *
 * Retrurn an empty linked list.
 *
 * @section seealso VER TAMBIÉN
 * \b destroy_node(3), \b destroy_list(3), \b delete_elem_list(3),\b is_empty_list(3), \b find(3), \b insert_list(3), \b destroy_all_nodes(3)
*/
 
LinkedList * create_list(comparator comparacion) {
    if(comparacion == NULL) return NULL;
    
    LinkedList * lista = (LinkedList *) malloc(sizeof(LinkedList));
    if(lista == NULL) return NULL;
 
    lista->cmp = comparacion;
    lista->first = NULL;
    lista->last = NULL;
 
    return lista;
}

/**
 * @page destroy_node \b destroy_node
 *
 * @brief Destroys a node.
 *
 * @param n Node to be destroyed.
 * @return The destroyed node.
 * @section SYNOPSIS
 *  \b #include \b "/includes/lista.h"
 *  \b lib/libLista.a 
 *
 * \b void* \b destroy_node(\b Node * n \b)
 *
 * @section descripcion DESCRIPCIÓN
 *
 * This funcition destroys a node.
 *
 * recives:
 * 	-A node.
 *
 * @section return RETORNO
 *
 * A destroyed node.
 *
 *
 * @section seealso VER TAMBIÉN
 * \b create_list(3), \b destroy_list(3), \b delete_elem_list(3),\b is_empty_list(3), \b find(3), \b insert_list(3), \b destroy_all_nodes(3)
*/
void *  destroy_node(Node * n) {
    n->data = NULL;
    n->next = NULL;
    free(n);
    n = NULL;
    
    return (void*) n;
}


/**
 * @page delete_elem_list \b delete_elem_list
 *
 * @brief Deletes a element of a list
 * @param l A list.
 * @param elem The element to be deleted.
 * @return int.
 *
 * @section SYNOPSIS
 *  \b #include \b "/includes/lista.h"
 *  \b lib/libLista.a 
 *
 *  \b int \b delete_elem_list (\b Lista * l \b , \b void * elem \b )
 * 
 * @section descripcion DESCRIPCIÓN
 *
 * This function deletes an element elem of the lis l if this element is in the list.
 * 
 * Recives:
 *    - l The list.
 *    - elem The element to be deleted.
 *
 * @section retorno RETORNO
 * 
 * 1 On succes, 0 on faliure.
 *
 * @section seealso VER TAMBIÉN
 * \b create_list(3), \b destroy_node(3), \b destroy_list(3), \b is_empty_list(3), \b find(3), \b insert_list(3), \b destroy_all_nodes(3)
 *
 * @section authors AUTOR
 * Manuel Reyes (manuel.reyes@estudiante.uam.es)
 * Jorge Guillen (jorge.guillen@estudiante.uam.es)
*/
 
int delete_elem_list(LinkedList * l, void * elem){
    Node * node;
    Node * node_anterior;
    /*Error en el paso de argumentos*/
    if (l == NULL || elem == NULL){
        return -1;
    }
    /*La lista esta vacia*/
    if (is_empty_list(l)==TRUE){
        return -1;
    }
 
    /*Si el elemento fuera el primero de todos*/
    node = l->first;
    if(l->cmp(elem, node->data)==TRUE){
        l->first = node->next;
        node = destroy_node(node);
        return 1;
    }
    /*Busqueda del elemento*/
    node_anterior = l->first;
    node = l->first->next;
    while(node!=NULL){
        if(l->cmp(elem, node->data)==TRUE){ 
            /*Hemos encontrado el elemento*/
            if(node->next==NULL){
                /*El elemento es el ultimo, redefinimos last*/
                l->last = node_anterior;
            }
            node_anterior->next = node->next;
            node = destroy_node(node);
            return 1;
        }
        /*No era el objetivo, continuamos buscando*/
        node_anterior = node;
        node = node->next;
    }
    /*El elemento no ha sido encontrado*/
    return 0;
}



/**
 * @page delete_elem_list \b delete_elem_list
 *
 * @brief Tells if the list is empty or not.
 * @param l List to check
 * @return -1 if an error happened, TRUE if empty or FALSE if not empty.
 *
 * @section SYNOPSIS
 *  \b #include \b "/includes/lista.h"
 *  \b lib/libLista.a 
 *
 *  \b int \b is_empty_list(\b LinkedList * l \b)
 * 
 * @section descripcion DESCRIPCIÓN
 * This function tells if the list is empty.
 *
 * recives:
 * 	- l A list
 * @section retorno RETORNO
 * 
 * 1 When TRUE, 0 When FALSE, -1 On ERROR.
 *
 * @section seealso VER TAMBIÉN
 * \b create_list(3), \b destroy_node(3), \b destroy_list(3), \b delete_elem_list(3), \b find(3), \b insert_list(3), \b destroy_all_nodes(3)
 */
int is_empty_list(LinkedList * l) {
    if(l == NULL){
        return -1;
    }
    if(l->first == NULL){
        return TRUE;
    }
    return FALSE;
}



/**
 * @page find \b find
 *
 * @brief This function is used when you want to find something in the list
 * @param clave Key to be find
 * @param l List to check
 * @return NULL if an error happened, the element of the list.
 *
 * @section SYNOPSIS
 *  \b #include \b ""
 *
 *  \b void \b find \b (\b void *\b )
 * 
 * @section descripcion DESCRIPCIÓN
 *
 * When you want to find some element than you introduced in the list
 * 
 * 
 * You have to pass the key of the element that you want to find, and the list where the element is.
 *
 * @section retorno RETORNO
 * Returns the element
 *
 * @section seealso VER TAMBIÉN
 * \b create_list(3), \b destroy_node(3), \b destroy_list(3), \b delete_elem_list(3),\b is_empty_list(3), \b insert_list(3), \b destroy_all_nodes(3)
 * @section authors AUTOR
 * Silvia Anguita (silvia.anguita@estudiante.uam.es)
 * Ángel Fuente (angel.fuente@estudiante.uam.es)
*/

void* find(void *clave, LinkedList *l) {
    Node *nodoaux = NULL;

    if (!clave || !l) {
        syslog(LOG_ERR, "Error al buscar un elemento en la lista, debido a un puntero nulo");
        exit(EXIT_FAILURE);
    }


    for (nodoaux = l->first; nodoaux != NULL; nodoaux = nodoaux->next) {
        if (l->cmp(clave, nodoaux->data) == TRUE) {
            return nodoaux->data;
        }
    }
    return NULL;
}


/*
 * @page insert_list \b insert_list
 *
 * @brief Insert an element on a list.
 * @param elem Element to be inserted.
 * @param l List to check.
 * @return -1 if an error ocurred, 1 on succes.
 *
 * @section SYNOPSIS
 *  \b #include \b ""
 *
 *  \b int \b insert_list( \b LinkedList * l \b, \b void * elem \b){
 * 
 * @section descripcion DESCRIPCIÓN
 *
 * Inserts an elemet at the end of a linked list.
 * 
 * recives:
 * 	- l a linked list.
 *	- elem the element to be inserted.
 *
 * @section retorno RETORNO
 * -1 if an error ocurred, 1 on succes.
 *
 * @section seealso VER TAMBIÉN
 * \b create_list(3), \b destroy_node(3), \b destroy_list(3), \b delete_elem_list(3),\b is_empty_list(3), \b find(3), \b destroy_all_nodes(3)
 */

int insert_list(LinkedList * l, void * elem){
    Node * node;
    if (l == NULL || elem == NULL){
        return -1;
    }
    node = (Node *) malloc(sizeof (Node));
    if (node == NULL){
        return -1;
    }
    node->data = elem;
    node->next = NULL;
    if (is_empty_list(l)==TRUE){
        l->first = node;
        l->last = node;
        return 1;
    }
    l->last->next = node;
    l->last = node;
    return 1;
}




/**
 * @page destroy_all_nodes \b destroy_all_nodes
 *
 * @brief Destroy all nodes of a list.
 *
 * @param first Node to be destroyed.
 * @return 0 always.
 *
 * @section SYNOPSIS
 *  \b #include \b "/includes/lista.h"
 *  \b lib/libLista.a 
 *
 *  \b int \b destroy_all_nodes (\b Nodo * first \b)
 * 
 * @section descripcion DESCRIPCIÓN
 *
 * Deletes the "first" node of a list an al the "next" nodes of that node.
 * This function shuld be called from destroy_list(3)
 * 
 * recives:
 *    - first The first node of the list
 *
 * @section return RETORNO
 * 0 always.
 *
 * @section seealso VER TAMBIÉN
 * \b create_list(3), \b destroy_node(3), \b destroy_list(3), \b delete_elem_list(3),\b is_empty_list(3), \b find(3), \b insert_list(3)
 *
 * @section authors AUTOR
 * Nestor Campillo (nestor.campillo@estudiante.uam.es)
 * Adrian Bueno (adrian.buenoj@estudiante.uam.es)
*/
int destroy_all_nodes (Node * first){
    if (first != NULL){ 
        destroy_all_nodes(first->next);
        
        first = destroy_node(first);
    }
    return 0;
}


/**
 * @page destroy_list \b destroy_list
 *
 * @brief Destroya a linked list.
 *
 * @param lista List to be destroyed.
 * @return 0 On succes, -1 if an error ocurred..
 *
 * @section SYNOPSIS
 *  \b #include \b "/includes/lista.h"
 *  \b lib/libLista.a 
 *
 *  \b int \b destroy_list (\b Lista * lista \b)
 * 
 * @section descripcion DESCRIPCIÓN
 *
 * Destroys the whole list.
 * 
 * recives:
 *    - lista List to be destroyed
 *
 * @section return RETORNO
 * 0 On succes, -1 if an error ocurred.
 *
 * @section seealso VER TAMBIÉN
 * \b create_list(3), \b destroy_node(3), \b delete_elem_list(3),\b is_empty_list(3), \b find(3), \b insert_list(3), \b destroy_all_nodes(3)
 *
 * @section authors AUTOR
 * Nestor Campillo (nestor.campillo@estudiante.uam.es)
 * Adrian Bueno (adrian.buenoj@estudiante.uam.es)
*/
int destroy_list (LinkedList * lista){
 
    if (lista == NULL)
        return -1;
 
    if (is_empty_list(lista) == FALSE){
        destroy_all_nodes(lista->first);
    }
 
    lista->first = NULL;
    lista->last = NULL;
    lista->cmp = NULL;
    free(lista);
 
    return 0;
}
