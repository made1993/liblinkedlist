#include <assert.h>
#include <stdio.h>

#include "../../includes/linkedList.h"


int intComparator(const void * a, const void * b){

  if (a == NULL || b == NULL) return 0;

  return *(int*)a - *(int*)b;

}

int main(int argc, char ** argv){

  comparator c = &intComparator;
  LinkedList * l = create_list(c);

  assert(l != NULL);

  int a = 1;

  assert(insert_list(l, &a) != ERR);

  destroy_list(l);

  fprintf(stdout, "test_insert passed succesfully.\n");
}
