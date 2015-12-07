#include <stdlib.h>
#include <stdio.h>
#include "Item.h"
#include "Queue.h"
#include <assert.h>

#define DEFAULT_SIZE 10

struct queueImp{
    Item *items;
    int size;
    int maxSize;
};

//O(1)
Queue createQueue(){
    Queue q = malloc(sizeof(struct queueImp));
    q->items = malloc(DEFAULT_SIZE * sizeof(Item));
    q->size =0;
    q->maxSize = DEFAULT_SIZE;
    return q;
}

void destroyQueue(Queue q){
    assert(q != NULL);
    free(q->items);
    free(q);
}

//O(1)
int queueSize(Queue q){
    assert(q != NULL);
    return (q->size);
}

//O(1);
void putQueue(Queue q, Item i){
    assert(q != NULL);
    assert(q->size < q->maxSize);
    q->items[q->size++]  = i;
}

//O(n)
Item getQueue(Queue q){
    int i;
    assert(q != NULL);
    if(q->size > 0){
        Item item = q->items[0];
        q->size--;
        //shift the elements across
        for(i=0;i<q->size;i++){
            q->items[i] = q->items[i+1];
        }
        return item;
    } else {
        fprintf(stderr,"queue underflow\n");
        abort();
    }
}

void queueWhiteBoxTests(void){
	int j;
	
    printf("White box tests\n");
    
    printf("Test 1: Create a stack\n");
    Queue s = createQueue();
    assert(s != NULL);
    assert(queueSize(s) == 0);
    
    printf("Passed\n");

    printf("Test 2: Push 3\n");
    putQueue(s,3);
    assert(queueSize(s) == 1);
    Item i = getQueue(s);
    assert(i == 3);
    printf("Passed\n");

    printf("Test 3: Push lots of stuff\n");
    for(j=0; j < 100; j++){
        putQueue(s,j);
    }
    assert(queueSize(s) == 100);
    for(j=99; j>=0; j--){
        i = getQueue(s);
        assert(i == j);
    }
    printf("Passed\n");

    
}
