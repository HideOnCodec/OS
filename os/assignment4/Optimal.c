#include "header.h"

void PageReplacement(Node* head,int nowposition,int pageStream[]);

void Optimal(int pageStream[], int pageframe)
{
	FILE *fp;
	fp=fopen("SimulationResult.txt","a");
	
	Node *head=NULL;
	Node *tail=NULL;
	int pageFaultCount=0;//페이지 폴트 횟수
	int pageFrameCount=0;//페이지 프레임에 차있는 페이지 갯수

	Data data;
	printf("------------------------Optimal------------------------\n");
	fprintf(fp,"------------------------Optimal------------------------\n");
	
	for(int i=0; i<MAX_STRING; i++)
	{
		int pagefault=0; //현재 스트림에서 페이지 폴트 발생 여부 저장
		if(pageFault(head,pageStream[i])==NULL)//pageFault 발생
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
				//가장 오랫동안 안 쓰일 page를 찾아서 교체
				PageReplacement(head,i,pageStream);
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

void PageReplacement(Node* head,int nowPosition,int pageStream[])
{
	Node *cur=head;
	int cnt=0; //더 이상 사용되지 않는 페이지 개수
	int max=-1;
	while(cur!=NULL)
	{	
		for(int i=nowPosition+1; i<MAX_STRING; i++)
		{
			if(pageStream[i]==cur->pageNum)
			{
				 cur->nextUsing=i;//해당 페이지가 사용되는 위치를 반환
				 break;
			}
		}
		if(cur->nextUsing==-1)//다음에 사용될 위치를 찾지 못했다면
		{
			cnt++;
			cur->nextUsing=1000;//더 이상 해당 페이지가 사용되지 않기때문에 1000 반환
		}
		if(max<cur->nextUsing)//다음에 사용될 위치가 제일 나중이면
			max=cur->nextUsing;//max에 위치 저장
		cur=cur->next;
	}
	cur=head;
	if(max!=1000)
	{
		while(cur!=NULL)
		{
			if(cur->nextUsing==max)//가장 나중에 쓰일 페이지라면
			{
				//이 페이지를 교체함
				//새로운 페이지로 기존 페이지 노드를 초기화함
				cur->pageNum=pageStream[nowPosition];
				cur->nextUsing=-1;
				break;
			}
			cur=cur->next;
		}

	}
	else
	{
		if(cnt)//더 이상 사용되지 않는 페이지가 존재할 경우
		{
			while(cur!=NULL)
			{
				if(cur->nextUsing==1000)
				{
					//더 이상 사용되지 않는 페이지가 여러 개일 경우 가장 먼저 나오는 페이지를 선택함(FIFO)
					cur->pageNum=pageStream[nowPosition];
					cur->nextUsing=-1;
					break;
				}
				cur=cur->next;
			}
		}
	}

}

