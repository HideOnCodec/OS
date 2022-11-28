#include "header.h"


void LRU(int pageStream[], int pageframe)
{
	FILE *fp;
	fp=fopen("SimulationResult.txt","a");
	
	Node *front=NULL;//가장 최근에 참조된 페이지 노드를 가리킴
	Node *rear=NULL;//가장 오랫동안 참조되지 않은 페이지 노드를 가리킴
	int pageFaultCount=0;//페이지 폴트 횟수
	int pageFrameCount=0;//페이지 프레임에 차있는 페이지 갯수
	Data data;

	printf("------------------------LRU------------------------\n");
	fprintf(fp,"------------------------LRU------------------------\n");
	
	for(int i=0; i<MAX_STRING; i++)
	{
		int pagefault=0; //현재 스트림에서 pageFault 발생 여부 저장
		int hit=0;//hit 여부를 저장하는 변수
	    	Node *current=front;
		Node *prev=current;//이전 노드를 가리킴
		while(current != NULL)
		{
			//연결리스트를 front부터 탐색함
			if(current->pageNum==pageStream[i])//현재 페이지 노드의 pageNum와 pageString 번호가 일치하면
			{
				hit++;//hit이므로 hit 증가시킴
				//LRU는 hit된 페이지는 가장 최근에 참조된 페이지므로 해당 노드를 front가 가리키도록 위치를 바꿔야함
				Node *ptr=current;	
				if(current==front)//현재 페이지 노드가 front가 가리키는 노드이면
					front=deleteNodeHead(front);//front가 가리키는 노드 삭제
				else if(current==rear)//현재 페이지 노드가 rear가 가리키는 노드이면
				{
					data=deleteNodeTail(front,rear);//rear가 가리키는 노드 삭제
					front=data.head;
					rear=data.tail;
				}
				else//중간에 낀 노드이면
					prev->next=current->next;//이전 노드를 다음 노드와 연결시켜 현재 노드를 삭제
				
				//원래 있던 노드를 삭제하고 front가 가리키도록 다시 추가함
				data=addNodeHead(front,rear,ptr);
				front=data.head;
				rear=data.tail;
			}
			prev=current;//현재 노드는 다음 반복문의 이전 노드가 됨
			current=current->next;
		}
		if(hit==0)//hit==0, 즉 pagefault이면
		{
			pageFaultCount++;//pageFaultCount 증가
			pagefault++;
			if(pageFrameCount<pageframe)//비어있는 pageframe이 있으면
			{
				data=addNodeHead(front,rear,createNode(pageStream[i])); //front가 가리키도록 page 추가
				front=data.head;
				rear=data.tail;
				pageFrameCount++;//pageFrameCount 증가
			}
			else//pageFrame이 모두 차있으면
			{
				//가장 오랫동안 참조되지 않는 페이지 노드와 교체함
				//따라서 rear가 가리키는 노드를 삭제하고
				data=deleteNodeTail(front,rear);
				front=data.head;
				rear=data.tail;
				pageFrameCount--;
				//front에 새로운 페이지 노드를 추가함
				data=addNodeHead(front,rear,createNode(pageStream[i]));
				front=data.head;
				rear=data.tail;
				pageFrameCount++;
			}
		}
		printList(front,fp);
		if(pagefault)
		{
			printf("(pagefault)\n");
			fprintf(fp,"(pagefault)\n");
		}
		else
		{
			printf("\n");
			fprintf(fp,"\n");
		}
	}
	freeAll(front);
	printf("pageFault: %d\n",pageFaultCount);
	fprintf(fp,"pageFault: %d\n",pageFaultCount);
	fclose(fp);
}
