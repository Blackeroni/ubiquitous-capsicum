#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
#include "textbuffer.h"

typedef struct node *link;
link createNode (char text[]);
TB createTextBuffer (void);
void printTextBuffer (TB tb1);
void printArray (char array[]);

struct node{
	char *item;		//individual text;
	int strSize;	//length of string
	link next;
};

struct textbuffer {	//serves as list header, similar to listimp
	link head;		//head of the list
	link tail;		//end of the list
	int size;		//size of the list
};

/* Creates a new textbuffer list header
 * list header contains basic information of the created list
 * Everything in the list header is initiallized
 */
TB createTextBuffer (void){
	TB tb = malloc(sizeof(struct textbuffer));
	assert (tb != NULL);
	tb->head = NULL;
	tb->tail = NULL;
	tb->size = 0;
	return tb;
}

/* Creates a node to contain text
 * Function will count length of string
 * Passing of text will be required
 */
link createNode (char text[]){
	link node = NULL;
	char *str = text; 	//string holder, allowing manipulation without destroying original
	int size = 0;	//length of string
	int i = 0;			//generic counter
	
	for(i = 0; str[i] != '\0'; i++){	//loop that determines the length of string
		size++;
	}
	//printf("%d\n", size);	//debugging purpose: display length of string
	
	node = malloc(sizeof(struct node));	//allocated memory for node containing text
	node->strSize = size;				//length of string
	node->item = malloc(node->strSize * sizeof(char));	//allocated memory for text
	node->item = text;
	node->next = NULL;

	return node;
}

void printTextBuffer (TB tb1){
	TB printTb = tb1;
	link node = NULL;
	
	node = printTb->head;			//node points to the first node in text buffer
	while(node != NULL){
		printf("[%s]->", node->item);
		node = node->next;
	}
		
	printf("[X]\n");
	
}

void printArray (char array[]){
	printf("%s", array);
}
/* Allocate a new textbuffer whose contents is initialised with the text given
 * in the array.
 */
TB newTB (char text[]){
	//int i = 0;					//first generic counter
	int j = 0;					//second generic counter
	int k = 0;					//third generic counter
	int l = 0;					//determines the string length
	int strlen = 0;				//string length counter
	TB tb = NULL;
	char *str;					//contains text
	char *cpystr = NULL;				//copied string, used to pass to createNode
	link node = NULL;
	link tmp = NULL;			//points to current node, but named as tmp
	
	str = text;

	tb = createTextBuffer();	//creates a text buffer list header
	
	while(str[j] != '\0'){
		for(l = j; str[l] != '\n'; l++){
			strlen++;
		}
		cpystr = malloc(strlen * sizeof(char));
		while(str[j] != '\n'){
			cpystr[k] = str[j];
			//printf("%s", &cpystr[k]);//print string
			k++;
			j++;
		}
		node = createNode(cpystr);
		if(tb->head == NULL){
			tb->head = node;
		}
		else{
			tmp->next = node;
		}
		tmp = node;
		tb->tail = node;
		tb->size++;
		j++;					//update pointer of string
		k = 0;					//string counter is reseted
	}
    return tb;
}

/* Free the memory occupied by the given textbuffer.  It is an error to access
 * the buffer afterwards.
 */
void releaseTB (TB tb){
	link node = NULL;
	link tmp = NULL;
	node = tb->head;
	while(node != NULL){
		tmp = node;
		node = node->next;
		free(tmp);
	}
}

/* Allocate and return an array containing the text in the given textbuffer.
 */
char *dumpTB (TB tb){
	char *array;				//array used to return text buffer list
	int tbSize = linesTB(tb);	//size of tb
	int i = 0;					//first generic counter
	int j = 0;					//second generic counter
	link tmp = tb->head;

	if(tb->head == NULL){		//case when there is no textbuffer
		return NULL;	
	}
	array = (char *)malloc(tbSize * sizeof(char));

	while(tmp != NULL){
		for(i = 0; tmp->item[i] != '\0'; i++){
			array[j] = tmp->item[i];
			j++;
		}
		array[j] = '\n'	;			//adds a next line at the end of each word
		j++;	
		tmp = tmp->next;
	}
	array[j] = '\0';			//adds end of text at the end of array
    return array;
}

/* Return the number of lines of the given textbuffer.
 */
int linesTB (TB tb){
    return tb->size;
}

/* Swap the two given lines in the textbuffer.
 *
 * - The program is to abort() with an error message if line 'pos1' or line
 *   'pos2' is out of range.  The first line of a textbuffer is at position 0.
 */
void swapTB (TB tb, int pos1, int pos2){
	link tmpPos1 = tb->head;
	link tmpPos2 = tb->head;
	char *tmpItem;				//usd to compy, needs to be alloc
	int tmpLength = 0;			//used to cpy length of text in node
	int i = 0;

	
	if((pos1 < 0)||(pos2 < 0)||(pos1 > (linesTB(tb)-1))||(pos2 > (linesTB(tb)-1))){
		abort();
	}
	else{
		for(i = 0; i < pos1; i++){		//finds the location of swapped nodes;
			tmpPos1 = tmpPos1->next;
		}
		for(i = 0; i < pos2; i++){
			tmpPos2 = tmpPos2->next;
		}

		//printf("tmpPos1 = %s		tmpPos2 = %s\n\n", tmpPos1->item, tmpPos2->item);
		tmpLength = tmpPos1->strSize;
		tmpPos1->strSize = tmpPos2->strSize;
		tmpPos2->strSize = tmpLength;
		
		tmpItem = tmpPos1->item;
		tmpPos1->item = tmpPos2->item;
		tmpPos2->item = tmpItem;	
		//printf("tmpPos1 = %s		tmpPos2 = %s\n\n", tmpPos1->item, tmpPos2->item);
		
	}
}

/* Merge 'tb2' into 'tb1' at line 'pos'.
 * 
 * - Afterwards line 0 of 'tb2' will be line 'pos' of 'tb1'.
 * - The old line 'pos' of 'tb1' will follow after the last line of 'tb2'.
 * - After this operation 'tb2' can not be used anymore (as if we had used
 *   releaseTB() on it).
 * - The program is to abort() with an error message if 'pos' is out of range.
 */
void mergeTB (TB tb1, int pos, TB tb2){
	link tmp1 = tb1->head;
	link tmp2Head = tb2->head;
	link tmp2Tail = tb2->tail;
	link tmp = NULL;
	int i = 0;
	if((pos < 0)||(pos > linesTB(tb1))){
		printf("out of range\n");	//debugging
		abort();
	}
	else if(pos == 0){		//indicating that TB2 is at the front of TB1 
		//tmp = tmp1;			//tmp = tb1->head
		tmp2Tail->next = tmp1;	//tb2->tail->next = tb1->head
		tb1->head = tmp2Head;		//tb1->head = tb2->head, why does tmp1 = tmp2head not work
	}
	
	else if(pos !=0){
		for(i = 0; i <= (pos - 2); i++){
				tmp1 = tmp1->next; //find position
		}
		tmp = tmp1;		//holds current node of next; tmp = tb1->head
		tmp1 = tmp1->next;		//goes to next for tmp2head to link to
		tmp2Tail->next = tmp1;	//tb2->tail->next = tmp1->next;
		tmp->next = tmp2Head;	//tmp1->next = tb2->head;
	}
	tb1->size = tb1->size + tb2->size;	
	tb2->size = 0;
	free(tb2);
}

/* Copy 'tb2' into 'tb1' at line 'pos'.
 * 
 * - Afterwards line 0 of 'tb2' will be line 'pos' of 'tb1'.
 * - The old line 'pos' of 'tb1' will follow after the last line of 'tb2'.
 * - After this operation 'tb2' is unmodified and remains usable independent
 *   of 'tb1'. 
 * - The program is to abort() with an error message if 'pos' is out of range.
 * - isn't this the same as mergeTB?
 * - a combination of pasteTB and mergeTB
 * - cannot releaseTB on tb2
 * - tb2 must be still useable after this function is completed
 */
void pasteTB (TB tb1, int pos, TB tb2){
	TB tmp = NULL;		//a temporary text buffer to hold everything in tb2
	link tmpNode;		//accomidates the temporary text buffer
	link Node1 = tb2->head;			//pointer of tb2
	link Node2 = NULL;	//used to serve as node pointer for tmp
	int Spos = 0;		//secondary pos. i.e. pos passed down to margeTB

	Spos = pos;			//Location of paste is now pasted into merge
	if((pos < 0)||(pos > linesTB(tb1))){
		printf("out of range\n");	//debugging
		abort();
	}
	

	else{
		tmp = createTextBuffer();
		
		for(Node1 = tb2->head; Node1 != NULL; Node1 = Node1->next){
			tmpNode = createNode(Node1->item);		//copied from createNode with name changes to suit purpose
				if(tmp->head == NULL){
					tmp->head = tmpNode;
				}
				else{
					Node2->next = tmpNode;
				}
			Node2 = tmpNode;
			tmp->tail = tmpNode;
		}
		tmp->size = tb2->size;

		mergeTB(tb1, Spos, tmp);
	}	//allows tb2 to be still useable without modifying it
}

/* Cut the lines between and including 'from' and 'to' out of the textbuffer
 * 'tb'.
 *
 * - The result is a new textbuffer (much as one created with newTB()).
 * - The cut lines will be deleted from 'tb'.
 * - The program is to abort() with an error message if 'from' or 'to' is out
 *   of range. 
 * - Two methods of doing it, manually free the cutted nodes, or pass tb to deleteTB
 */
TB cutTB (TB tb, int from, int to){
	TB cutTB = NULL;
	link tmpNode;
	//link tmp;
	link Node1 = tb->head;
	link Node2 = NULL;
	link prevNode = tb->head;
	link delNode1 = tb->head;
	link delNode2 = NULL;
	int i = 0;
	
	if((from < 0)||(to > linesTB(tb))){
		printf("out of range\n");	//debugging
		abort();
	}
	else if(from > to){
		return NULL;			//can't do anything
	}
	
	else{
		for(i = 0; i < from; i++){
			Node1 = Node1->next;
		}
		cutTB = createTextBuffer();
		for(i = from; i <= to; i++){//proceeds to cut tb
			tmpNode = createNode(Node1->item); //how is opereates is similar to pasteTB
			if(cutTB->head == NULL){
				cutTB->head = tmpNode;
			}
			else{
				Node2->next = tmpNode;
			}
			cutTB->tail = tmpNode;
			Node2 = tmpNode;
			cutTB->size++;
			Node1 = Node1->next;
		}
	}
	//the following is deleting portions of tb accordingly
	//will be copying this to deleteTB
	//printf("tb->size = %d	from = %d		to = %d\n", tb->size, from , to);
	if((from == 0) && (to == (tb->size))){	//this will delete the whole text buffer
		releaseTB(tb);
		tb->size = 0;
	}

	else if((from == 0) && (to < (tb->size))){	//deleting from the first node
		for(i = 0; i < from; i++){		//finds the deleting node
			delNode1 = delNode1->next;
		}
		for(i = from; i<=to; i++){
			delNode2 = delNode1;
			delNode1 = delNode1->next;
			free(delNode2);
			tb->size--;
		}
		tb->head = delNode1;
	}
	else if((from > 0) && (to < (tb->size))){		//deleting somewhere between
		delNode1 = tb->head;
		prevNode = tb->head;
		for(i = 0; i < (from-1); i++){
			prevNode = prevNode->next;
		}
		for(i = 0; i < from; i++){
		delNode1 = delNode1->next;
		}
		for(i = 0; (i + from - 1) < to; i++){
			delNode2 = delNode1;
			delNode1 = delNode1->next;
			free(delNode2);
			tb->size--;
		}
		prevNode->next = delNode1;	
	}
	else if((from > 0) && (to == (tb->size))){	//deleting to tail
		delNode1 = tb->head;
		for(i = 0; i < (from - 1); i++){		//copied from above
			prevNode = prevNode->next;
		}
		for(i = 0; (i + from -1) < to; i++){
			delNode2 = delNode1;
			delNode1 = delNode1->next;
			free(delNode2);
			tb->size--;
		}
		prevNode->next = NULL;	
	}
	
    return cutTB;
}

/* Copy the lines between and including 'from' and 'to' of the textbuffer
 * 'tb'.
 *
 * - The result is a new textbuffer (much as one created with newTB()).
 * - The textbuffer 'tb' will remain unmodified.
 * - The program is to abort() with an error message if 'from' or 'to' is out
 *   of range. 
 */
TB copyTB (TB tb, int from, int to){	//very similar to cut tb
	TB copyTB = NULL;
	link tmpNode;
	link Node1 = tb->head;
	link Node2 = NULL;
	int i;
	
	if((from < 0)||(to > linesTB(tb))){
		printf("out of range\n");	//debugging
		abort();
	}

	for(i = 0; i < from ; i++){	//find copy section
		Node1 = Node1->next;
	}
	for(i = to; i <= from; i++){	//pretty much copy paste cut tb
		tmpNode = createNode(Node1->item);
		if(copyTB->head == NULL){
			copyTB->head = tmpNode;
		}
		else{
			Node2->next = tmpNode;
		}
		copyTB->tail = tmpNode;
		Node2 = tmpNode;
		copyTB->size++;
		Node1 = Node1->next;
	}
    return copyTB;
}

/* Remove the lines between and including 'from' and 'to' from the textbuffer
 * 'tb'.
 *
 * - The program is to abort() with an error message if 'from' or 'to' is out
 *   of range. 
 */
void deleteTB (TB tb, int from, int to){
	if((from < 0)||(to > linesTB(tb))){
		printf("out of range\n");	//debugging
		abort();
	}

}


/* Search every line of tb for each occurrence of str1 and replaces them 
 * with str2
 */
void replaceText (TB tb, char* str1, char* str2) {

}

/* Bonus Challenges
 */

char* diffTB (TB tb1, TB tb2) {
    return NULL;
}

void undoTB (TB tb) {

}

void redoTB (TB tb) {

}
 
