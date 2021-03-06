//An array based implementation of a stack

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "Item.h"
#include "Stack.h"
#include "assert.h"

#define DEFAULT_SIZE 10

struct stackImp{
    Item * items;	//array
    int top;		//number of items in a stack
    int maxSize;	//capacity of array
};

//A stack is created with a default initial size of 10
Stack createStack (void){
    Stack s = malloc(sizeof(struct stackImp)); 
    assert(s != NULL);
    s->items = malloc(DEFAULT_SIZE * sizeof(Item));
    assert(s->items != NULL);
    s->top = 0; 
    s->maxSize = DEFAULT_SIZE;
    return s;
}

void destroyStack(Stack stack){
    assert(stack != NULL);
    free(stack->items);
    free(stack);
}

//You need to modify this
void push (Stack stack, Item item){ 
	Stack s = stack;
	Item object = item;
	Item *newArray = NULL;
	int counter = 0;
	
	assert(stack != NULL);
	
	if(stack->top >= stack->maxSize){
		printf("stack overflow\n");
		newArray = malloc(2 * s->maxSize * sizeof(object));
		for (counter = 0; counter < s->maxSize ; counter++){
			newArray[counter] = stack->items[counter];
		}
		free(stack->items);
		stack->items = newArray;
		s->maxSize = 2 * s->maxSize;
	}
    stack->items[stack->top] = object;
    stack->top++;
}

//You need to modify this
Item pop (Stack stack){
	Stack s = stack;
	Item *newArray = NULL;
	int counter = 0;
	
	if(stack->top == 0){
		printf("stack underflow\n");
		abort();
	} 
	else if(stack->top <= ((stack->maxSize)/4)){
		printf("resizing stack\n");
		newArray = malloc(s->maxSize *sizeof(Item)/2);
		
		for(counter = 0; counter < s->maxSize; counter++){
			newArray[counter] = stack->items[counter];
		}
		free(stack->items);
		stack->items = newArray;
		s->maxSize = (s->maxSize/2);
	}

    stack->top--;
    return stack->items[stack->top];
}

int stackSize(Stack stack){
    assert(stack != NULL);
    return stack->top;
}

//You need to write these
void whiteBoxTests(void){
	int stuff; 		//used for push many

	//s, first test
    printf("White box tests\n");
    printf("Test 1: Create a stack\n");
    Stack s = createStack();
    assert(s != NULL);
    assert(stackSize(s) == 0);
    destroyStack (s);
    printf("passed\n");
	printf("\n");

	//t, second test 		question this
	printf("Test 2: Push 3\n");
	Stack j = createStack();
	push (j, 3);
	assert(stackSize(j) ==1);
	Item i = pop(j);
	assert(i ==3);
	destroyStack (j);
	printf("Passed\n");
	printf("\n");

	//u, third test
	printf("Test 3: Push lots of stuff\n");
	Stack u = createStack();
	for(stuff = 0; stuff < 100; stuff++){
		push(u, stuff);
		printf("%d		%d\n", stuff, u->top);
	}
	printf("%d\n", stuff);
	
	assert(stackSize(u) == 100);
	
	for(stuff = 99; stuff >= 0; stuff--){
		i = pop(u);
		printf("%d		%d\n", stuff, i);
		assert(i == stuff);
	}
	destroyStack (u);
	printf("Passed\n");
	printf("\n");
	   
}
