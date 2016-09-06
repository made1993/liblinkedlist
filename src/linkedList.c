#include <stdbool.h>
#include <stdio.h>
#include <syslog.h>

#include "../includes/linkedList.h"

LinkedList * create_list(comparator c) {

  if (c == NULL) return NULL;

  LinkedList * l;

  if ((l = malloc(sizeof(l[0]))) == NULL) return NULL;

  l->cmp = c;
  l->first = NULL;
  l->last = NULL;

  return l;

}

void destroy_node(Node * n) {

  n->data = NULL;
  n->next = NULL;
  free(n);
  n = NULL;

}

int delete_elem_list(LinkedList * l, void * elem){

  Node * node;
  Node * node_prev;

  /*Error en el paso de argumentos*/
  if (l == NULL || elem == NULL) return ERR;

  /*La lista esta vacia*/
  if (is_empty_list(l) == true) return false;

  /*Si el elemento fuera el primero de todos*/
  node = l->first;
  if (l->cmp(elem, node->data) == true){
    l->first = node->next;
    destroy_node(node);
    return true;
  }
  /*Busqueda del elemento*/
  node_prev = l->first;
  node = l->first->next;
  while (node != NULL){
    if (l->cmp(elem, node->data) == true){
      /*Hemos encontrado el elemento*/
      if (node->next == NULL){
        /*El elemento es el ultimo, redefinimos last*/
        l->last = node_prev;
      }
      node_prev->next = node->next;
      destroy_node(node);
      return true;
    }
    /*No era el objetivo, continuamos buscando*/
    node_prev = node;
    node = node->next;
  }
  /*El elemento no ha sido encontrado*/
  return false;

}

int is_empty_list(LinkedList * l) {

  if (l == NULL) return ERR;

  return l->first == NULL ? true : false;

}

void * find(void * k, LinkedList * l) {

  if (k == NULL || l == NULL) {
    syslog(LOG_ERR, "Error al buscar un elemento en la lista, "
        "debido a un puntero nulo");
    exit(EXIT_FAILURE);
  }

  for (Node * n = l->first; n != NULL; n = n->next) {
    if (l->cmp(k, n->data) == true) return n->data;
  }

  return NULL;

}

int insert_list(LinkedList * l, void * elem){

  if (l == NULL || elem == NULL) return ERR;

  Node * node;
  if ((node = malloc(sizeof(node[0]))) == NULL) return ERR;

  node->data = elem;
  node->next = NULL;
  if (is_empty_list(l) == true){
    l->first = node;
    l->last = node;
    return true;
  }
  l->last->next = node;
  l->last = node;
  return true;

}

void destroy_all_nodes (Node * first){

  if (first != NULL){
    destroy_all_nodes(first->next);
    destroy_node(first);
  }

}

void destroy_list (LinkedList * l){

  if (l != NULL){
    if (!is_empty_list(l)) destroy_all_nodes(l->first);
    l->first = NULL;
    l->last = NULL;
    l->cmp = NULL;
    free(l);
  }
}
