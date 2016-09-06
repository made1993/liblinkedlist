#include "../includes/linkedList.h"

LinkedList * create_list(comparator comparacion) {
  if(comparacion == NULL) return NULL;

  LinkedList * lista = (LinkedList *) malloc(sizeof(LinkedList));
  if(lista == NULL) return NULL;

  lista->cmp = comparacion;
  lista->first = NULL;
  lista->last = NULL;

  return lista;
}

void *  destroy_node(Node * n) {
  n->data = NULL;
  n->next = NULL;
  free(n);
  n = NULL;

  return (void*) n;
}

int delete_elem_list(LinkedList * l, void * elem){
  Node * node;
  Node * node_anterior;
  /*Error en el paso de argumentos*/
  if (l == NULL || elem == NULL){
    return -1;
  }
  /*La lista esta vacia*/
  if (is_empty_list(l)==true){
    return -1;
  }

  /*Si el elemento fuera el primero de todos*/
  node = l->first;
  if(l->cmp(elem, node->data)==true){
    l->first = node->next;
    node = destroy_node(node);
    return 1;
  }
  /*Busqueda del elemento*/
  node_anterior = l->first;
  node = l->first->next;
  while(node!=NULL){
    if(l->cmp(elem, node->data)==true){
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

int is_empty_list(LinkedList * l) {
  if(l == NULL){
    return -1;
  }
  if(l->first == NULL){
    return true;
  }
  return false;
}

void* find(void *clave, LinkedList *l) {
  Node *nodoaux = NULL;

  if (!clave || !l) {
    syslog(LOG_ERR, "Error al buscar un elemento en la lista, "
                    "debido a un puntero nulo");
    exit(EXIT_FAILURE);
  }


  for (nodoaux = l->first; nodoaux != NULL; nodoaux = nodoaux->next) {
    if (l->cmp(clave, nodoaux->data) == true) {
      return nodoaux->data;
    }
  }
  return NULL;
}

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
  if (is_empty_list(l)==true){
    l->first = node;
    l->last = node;
    return 1;
  }
  l->last->next = node;
  l->last = node;
  return 1;
}
int destroy_all_nodes (Node * first){
  if (first != NULL){
    destroy_all_nodes(first->next);

    first = destroy_node(first);
  }
  return 0;
}

int destroy_list (LinkedList * lista){

  if (lista == NULL)
    return -1;

  if (is_empty_list(lista) == false){
    destroy_all_nodes(lista->first);
  }

  lista->first = NULL;
  lista->last = NULL;
  lista->cmp = NULL;
  free(lista);

  return 0;
}
