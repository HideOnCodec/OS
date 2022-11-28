#include<stdio.h>
#include<stdlib.h>
#include "circularQueue.h"

void initQueue(Queue *q,int max)//큐 생성 
{
	q->front = 0;
	q->rear = 0;
	q->page = (Page*)malloc(sizeof(Page)*(max));
}

void enqueue(Queue *q, Page page,int max)//큐에 페이지 추가
{
	if (!isFull(q,max)) 
	{
		q->rear = (q->rear + 1) % (max);
		q->page[q->rear] = page;	
	}
	else
		printf("full\n");
		
}

int dequeue(Queue *q,int max)//큐 페이지 삭제
{
	if (!isEmpty(q)) 
	{
		q->front = (q->front + 1) % (max);
		return q->front;
	}
	else
		printf("empty\n");
	return 0;
}

int isEmpty(Queue *q)//큐가 비어있는지 여부 판단 
{
	if (q->front == q->rear) 
		return 1;
	else 
		return 0;
}

int isFull(Queue *q,int max)//큐가 모두 찼는지 판단
{
	if (((q->rear + 1) %max ) == q->front) 
		return 1;
	else 
		return 0;
}

int pageSearch(Queue q,int pageStringNum,int max)//해당 페이지가 존재하는지 검사
{	
	int i=q.front;
	do 
	{
		i = (i + 1) % max;
		if(q.page[i].pageNum==pageStringNum)
			return i;
		if (i == q.rear) 
			break;
	} while (i != q.front);
		
	return 0;
}

void printQueueSC(Queue q,int max,FILE *fp)//SC 알고리즘을 위한 큐 출력 함수(R bit)
{
	int i = q.front;
	if (!isEmpty(&q)) 
	{
		do 
		{
			i = (i + 1) % max;
			printf("%d|%d ", q.page[i].pageNum,q.page[i].R);
			fprintf(fp,"%d|%d ", q.page[i].pageNum,q.page[i].R);
			if (i == q.rear) 
				break;
		} while (i != q.front);
	}
}

void printQueueESC(Queue q,int max,FILE *fp)//ESC 알고리즘을 위한 큐 출력 함수(R bit,M bit)
{
	int i = q.front;
	if (!isEmpty(&q)) 
	{
		do 
		{
			i = (i + 1) % max;
			printf("%d(%d,%d) ", q.page[i].pageNum,q.page[i].R,q.page[i].M);
			fprintf(fp,"%d(%d,%d) ", q.page[i].pageNum,q.page[i].R,q.page[i].M);
			if (i == q.rear) 
				break;
		} while (i != q.front);
	}
}
