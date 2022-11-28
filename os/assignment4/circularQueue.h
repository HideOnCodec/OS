typedef struct page
{
	int pageNum;
	int R;//Reference bit
	int M;//Modifiy bit
}Page;

typedef struct circleQueue {
	int rear;
	int front;
	Page *page;
}Queue;

void enqueue(Queue *q, Page page,int pageframe);
int dequeue(Queue *q,int max);
void initQueue(Queue *q,int max);
int isFull(Queue *q,int max);
int isEmpty(Queue *q);
int pageSearch(Queue q,int pageStringNum,int max);
void printQueueSC(Queue q,int max,FILE *fp);
void printQueueESC(Queue q,int max,FILE *fp);

