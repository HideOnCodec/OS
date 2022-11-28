#include "header.h"

void LIFO(int pageStream[], int pageframe)
{
	FILE *fp;
	fp=fopen("SimulationResult.txt","a");
	
	Node *head=NULL;
	Node *tail=NULL;
	int pageFaultCount=0;//페이지 폴트 횟수
	int pageFrameCount=0;//페이지 프레임에 차있는 페이지 갯수
	Data data;

	printf("------------------------LIFO------------------------\n");
	fprintf(fp,"------------------------LIFO------------------------\n");
	
	for(int i=0; i<MAX_STRING; i++)
	{
		int pagefault=0;//현재 스트림에서 pageFault 발생 여부 저장
		if(pageFault(head,pageStream[i])==NULL)//pageFault가 발생
		{
			pageFaultCount++;
			pagefault++;
			if(pageFrameCount<pageframe)//비어있는 pageframe이 있으면
			{
				data=addNodeTail(head,tail,createNode(pageStream[i])); //page 추가
				head=data.head;
				tail=data.tail;
				pageFrameCount++;
			}
			else//pageFrame이 모두 차있으면
			{
				//tail이 가리키는 페이지를 교체해야함
				//tail이 가리키는 노드 삭제
				//즉 가장 최근에 들어온 페이지 삭제
				data=deleteNodeTail(head,tail);
				head=data.head;
				tail=data.tail;
				pageFrameCount--;
				//새로운 노드 tail에 연결하여 추가
				data=addNodeTail(head,tail,createNode(pageStream[i]));
				head=data.head;
				tail=data.tail;
				pageFrameCount++;
			}
		}
		printList(head,fp);
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
	freeAll(head);
	printf("pageFault: %d\n",pageFaultCount);
	fprintf(fp,"pageFault: %d\n",pageFaultCount);
	fclose(fp);
	
}

