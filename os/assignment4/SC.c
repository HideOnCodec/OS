#include<stdio.h>
#include<stdlib.h>
#include "circularQueue.h"

#define MAX_STRING 500

void SC(int pageStream[], int pageframe)
{
	FILE *fp;
	fp=fopen("SimulationResult.txt","a");
	
	int pageFaultCount=0;
	int pageFrameCount=0;
	int hit;
	int pointer;
	int max=pageframe+1;
	Queue q;
	initQueue(&q, max);
	
	printf("------------------------SC------------------------\n");
	fprintf(fp,"------------------------SC------------------------\n");
	
	for(int i=0; i<MAX_STRING; i++)
	{
		int pagefault=0; //현재 스트림에서 pageFault 발생 여부 저장
		if(hit=pageSearch(q,pageStream[i],max))//hit이면
			q.page[hit].R=1;
		else//페이지 폴트 발생하면
		{	
			pagefault++;
			pageFaultCount++;
			//새로운 페이지 초기화
			Page page;
			page.pageNum=pageStream[i];
			page.R=1;			
			if(pageFrameCount<pageframe)//비어있는 페이지 프레임이 존재하면
			{
				enqueue(&q,page,max);
				pageFrameCount++;
				pointer=(q.rear+1)%max;
				if(pointer==0)
					pointer++;
			}
			else//페이지 프레임이 꽉 찼으면
			{
				//SC 알고리즘으로 페이지 교체 수행
				while(1)
				{
					if(q.page[pointer].R==0)//페이지의 R비트가 0이면 교체
					{
						q.page[pointer]=page;
						pointer=(pointer+1)%max;
						if(pointer==0)
							pointer++;
						break;
					}
					else if(q.page[pointer].R==1)//페이지의 R비트가 1이면
					{
						//SC는 R비트가 1일 경우 2차 기회를 줌
						//R비트를 0으로 초기화하고 넘어가서 계속 탐색함
						q.page[pointer].R=0;
						pointer=(pointer+1)%max;
						if(pointer==0)
							pointer++;	
					}
				
				}	
			}
		}	
		printQueueSC(q,max,fp);
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
	printf("pageFault: %d\n",pageFaultCount);
	fprintf(fp,"pageFault: %d\n",pageFaultCount);
	fclose(fp);
}
