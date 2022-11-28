#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAX_STRING 500

typedef struct node
{
	int pageNum;
	int nextUsing;
	int counter;
	struct node *next;
}Node;

typedef struct data
{
	Node *head;
	Node *tail;
}Data;

void Optimal(int pageStream[], int pageframe);
void FIFO(int pageStream[],int pageframe);
void LIFO(int pageStream[],int pageframe);
void LRU(int pageStream[],int pageframe);
void LFU(int pageStream[],int pageframe);
void SC(int pageStream[],int pageframe);
void ESC(int pageStreamESC[][3],int pageframe);

Node* createNode(int pageStringNum);
Data addNodeHead(Node *head,Node *tail,Node *newNode);
Data addNodeTail(Node *head,Node *tail,Node *newNode);
Data deleteNodeTail(Node *head,Node *tail);
Node* deleteNodeHead(Node *head);
Node* pageFault(Node *head,int pageStringNum);
void printList(Node *head,FILE *fp);
void freeAll(Node *head);

