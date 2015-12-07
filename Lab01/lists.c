#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "lists.h"
void printDList (dlink dlist);


void printList (link list) {
  link curr = list;
  while (curr != NULL) {
    printf ("[%d]->", curr->item);
    curr = curr->next;
  }
  printf ("[X]\n");
}


int sumListItems (link ls) {
  int sum = 0;
  int i = 0;
  link tmp = ls;
  while(tmp !=NULL){
    i = tmp->item;
    sum = sum + i;
    tmp = tmp->next;
  }
  printf("%d\n", sum);
  return 0;
}

void freeList(link list){
  link tmp = NULL;
  link head = list;

  while(head != NULL){
    tmp = head;
    head = head->next;
    free(tmp);
  }
}

link fromTo (int start, int end) {  
  link head = NULL;
  link newNode = NULL;
  link tmp = NULL;
  int i;


  if(start <= end){ 
    for(i = start; i<=end; i++){

      newNode = malloc(sizeof(node));
      newNode->item = i;
      newNode->next = NULL;

      if(head == NULL){
	head = newNode;
	tmp = head;
      }

      else{
	tmp->next=newNode;
	tmp = tmp->next;
      }

    }

  }
  
   return head;
}

dlink doublify (link list) {
  dlink dhead = NULL;
  dlink dnewNode = NULL;
  dlink dtmp = NULL;
  link tmp = list;

  while(tmp != NULL){

    dnewNode = malloc(sizeof(dnode));
    dnewNode->item = tmp->item;
    dnewNode->next = NULL;

    if(dhead == NULL){
      dhead = dnewNode;
      dtmp = dhead;
    }

    else{
      dnewNode->prev = dhead;
      dtmp->next = dnewNode;
      dtmp = dtmp->next;
    }
    tmp = tmp->next;
  }
  return dhead;

}

void freeDList(dlink dlist){
  dlink dtmp = NULL;
  dlink dhead = dlist;

  while(dhead != NULL){
    dtmp = dhead;
    dhead = dhead->next;
    free(dtmp);
  }
}

void printDList (dlink dlist){
  dlink curr = dlist;
  while(curr !=NULL){
    printf("[%d]<->", curr->item);
    curr = curr->next;
  }
  printf("[X]\n");
}
