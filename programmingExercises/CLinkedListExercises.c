#include <stdio.h>
#include <stdlib.h>

// Definitions
typedef struct Node{
	int value;
	struct Node *next;
}Node;

void printList(Node *linkedList);
void addNodeAtEnd(int value, Node *linkedList);
void addNodeFirst(int value, Node *linkedList);
void deleteNode(int deleteValue, Node *linkedList);
void invertList(Node *linkedList);
void isCircularLinkedList(Node *linkedList);
void getTheNthElement(int element, Node *linkedList);

Node *z;

// Oracle
// Invert a linked list in place, no more memory is allowed
void invertList(Node *linkedList){
	if(linkedList->next == z){
		return;
	}

	Node *beginning = linkedList->next;
	Node *current = beginning->next;
	Node *aux;
	
	if(current != z){ // The list has at leas one node
		if(beginning->next != z){ // The list has more than one node
			beginning->next = z;
			while(current != z){
				aux = current->next;
				current->next = beginning;
				beginning = current;
				current = aux;
			}
			linkedList->next = beginning;
		}
	}
}

// Apian, Amdocs
// Checks if a linked list has a loop
void isCircularLinkedList(Node *linkedList){
	if(linkedList->next == z){
		printf("Lista vacia\n");
		return;
	}
	Node *a = linkedList->next;
	Node *b = linkedList->next->next;
	while(a!=z && b!=z){
		if(a == b){
			printf("Es una lista lista ligada con ciclo\n");
			return;
		}
		a = a->next;
		b = b->next->next;
	}
	printf("Es una lista ligada sencilla sin ningun ciclo\n`");
}

// Microsoft
// Given a linked list and a number, return the value of the nth to finish, in just one read of the linked list.
// Ej. NULL -> 4 -> 3  -> 7 -> 8 -> 9 -> 15 -> 21 -> 1 ->  2 -> NULL and 3 return 21
void getTheNthElement(int element, Node *linkedList){
	if(linkedList->next == z){
		printf("The list is empty\n");
		return;
	}
	int i;
	Node *simple = linkedList->next;
	Node *advanced = linkedList->next;
	for(i=0; i<element; i++){
		advanced = advanced->next;
	}
	while(advanced != z){
		advanced = advanced->next;
		simple = simple->next;
	}
	printf("The values of the Nth element is : %d\n", simple->value);
}

void addNodeAtEnd(int value, Node *linkedList){
	Node *newNode = (Node *)malloc(sizeof(Node));
	newNode->value = value;
	newNode->next = z;
	Node *aux = linkedList;
	for(; aux->next!=z; aux=aux->next){}
	aux->next = newNode;
}

void addNodeFirst(int value, Node *linkedList){
	Node *newNode = (Node *)malloc(sizeof(Node));
	newNode->value = value;
	newNode->next = linkedList->next;
	linkedList->next = newNode;
}

void deleteNode(int deleteValue, Node *linkedList){
	Node *aux = linkedList;
	Node *freeNode;
	for(; aux->next!= z; aux=aux->next){
		if(aux->next->value == deleteValue){
			freeNode = aux->next;
			free(freeNode);
			aux->next = aux->next->next;
			return;
		}
	}
}

void printList(Node *linkedList){
	Node *current =  linkedList->next;
	for(; current!= z; current=current->next){
		printf(" %d ->", current->value);
	}
	printf("\n");
}

int main(){
	// Guard node
	z = (Node *) malloc(sizeof(Node));
	z->next = z;

	// Empty list
	Node *linkedList =  (Node *) malloc(sizeof(Node));
	linkedList->next = z;
	
	//printList(linkedList);
	addNodeAtEnd(1, linkedList);
	//printList(linkedList);
	addNodeAtEnd(2, linkedList);
	//printList(linkedList);
	addNodeAtEnd(3, linkedList);
	//printList(linkedList);
	addNodeAtEnd(4, linkedList);
	printList(linkedList);
	invertList(linkedList);
	printList(linkedList);

	Node *circularLinkedList=  (Node *) malloc(sizeof(Node));
	circularLinkedList->next = z;
	addNodeAtEnd(1, circularLinkedList);
	addNodeAtEnd(2, circularLinkedList);
	addNodeAtEnd(3, circularLinkedList);
	addNodeAtEnd(4, circularLinkedList);
	circularLinkedList->next->next->next->next->next = circularLinkedList;
	isCircularLinkedList(linkedList);
	isCircularLinkedList(circularLinkedList);

	int i;
	for(i=5; i<15; i++){
		addNodeAtEnd(i, linkedList);
	}
	printList(linkedList);
	getTheNthElement(3, linkedList);
}
