#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "lists.h"

void printDList (dlink dlist);
// insert proper tests here
int main (int argc, const char * argv[]) {
  link list = fromTo (0, 10);
  dlink dlist = doublify (list);
  printList (list);
  sumListItems (list);
  freeList (list);
  //  sumListItems (list);
  printDList (dlist);
  freeDList (dlist);
  return 0;
}

