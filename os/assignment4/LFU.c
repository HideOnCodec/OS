#include "header.h"

Data replacementMinCounter(Node* front, Node* rear,int pageStringNum)//카운터 값이 가장 작은 페이지 교체
{	
	Node* minPage=NULL;//카운터 값이 가장 작은 페이지
	int min=1000;//counter의 min값을 1000으로 초기화
	Data data;
	
	Node* current=front;//front부터 연결리스트 탐색
	Node* prev;//이전 노드 저장
	Node* prev2;//카운터 값이 가장 작은 페이지의 이전 노드 저장
	while(current!=NULL)
	{
		if(current->counter<min)//현재 페이지의 counter값이 min보다 작을 경우
		{
			//counter 최솟값을 갖는 페이지가 여러 개여도 자연스럽게 FIFO로 선택하게됨
			prev2=prev;
			min=current->counter;//min값 갱신
			minPage=current;//카운터 값이 가장 작은 페이지를 current페이지로 갱신
		}
		prev=current;
		current=current->next;
	}

	//카운터 값이 가장 작은 페이지와 새로운 페이지 교체
	//먼저 가장 적게 참조된 페이지를 삭제함
	if(minPage==front)//front가 가리키는 노드이면
		front=deleteNodeHead(front);//front가 가리키는 노드 삭제
	else if(minPage==rear)//rear가 가리키는 노드이면
	{
		data=deleteNodeTail(front,rear);//rear가 가리키는 노드 삭제
		front=data.head;
		rear=data.tail;
	}
	else//중간에 낀 노드이면
		prev2->next=minPage->next;//이전 노드를 다음 노드와 연결시켜 현재 노드를 삭제
				
	//새로운 페이지를 rear가 가리키도록 추가함
	data=addNodeTail(front,rear,createNode(pageStringNum));
	return data;
}
void LFU(int pageStream[],int pageframe)
{
	FILE *fp;
	fp=fopen("SimulationResult.txt","a");
	
	Node *front=NULL;//가장 오래된 페이지를 가리킴
	Node *rear=NULL;//가장 최근에 들어온 페이지를 가리킴
	
	int pageFaultCount=0;
	int pageFrameCount=0;
	Data data;

	printf("------------------------LFU------------------------\n");
	fprintf(fp,"------------------------LFU------------------------\n");
	
	for(int i=0; i<MAX_STRING; i++)
	{
		int pagefault=0; //현재 스트림에서 pageFault 발생 여부 저장
		int hit=0;//hit 여부를 저장하는 변수
		Node *current=front; //연결리스트를 front부터 탐색
		Node *prev; //이전 노드 저장
		while(current != NULL)
		{
			if(current->pageNum==pageStream[i])//현재 페이지 노드의 pageNum와 pageString 번호가 일치하면 hit
			{
				current->counter++;//hit된 페이지의 counter 증가
				hit++;
			}
			prev=current;
			current=current->next;
		}
		if(hit==0)//페이지 폴트일 경우
		{
			pageFaultCount++;
			pagefault++;
			if(pageFrameCount<pageframe)//페이지 프레임에 공간이 있을 경우
			{
				//페이지 추가
				//counter 최솟값을 갖는 페이지가 여러 개일 경우 FIFO 채택
				//따라서 페이지 추가 시 FIFO를 따른다. rear노드에 추가함
				data=addNodeTail(front,rear,createNode(pageStream[i]));
				front=data.head;
				rear=data.tail;
				pageFrameCount++;
			}
			else//페이지 프레임에 공간이 없을 경우
			{ 
				//counter가 가장 작은 페이지와 교체가 일어남
				data=replacementMinCounter(front,rear,pageStream[i]);
				front=data.head;
				rear=data.tail;
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
