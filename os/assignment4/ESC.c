#include<stdio.h>
#include<stdlib.h>
#include "circularQueue.h"

#define MAX_STRING 500


void ESC(int pageStreamESC[][3], int pageframe)
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
	
	printf("------------------------ESC------------------------\n");
	fprintf(fp,"------------------------ESC------------------------\n");
	
	for(int i=0; i<MAX_STRING; i++)
	{
		int pagefault=0;//현재 스트림에서 pageFault 발생 여부 저장
		if(hit=pageSearch(q,pageStreamESC[i][0],max))//hit이면
		{
			q.page[hit].R=1;
			if(pageStreamESC[i][2]==1)//W bit 1이면
				q.page[hit].M=1;
			else
				q.page[hit].M=0;
		}
		else//페이지 폴트 발생하면
		{	
			pageFaultCount++;
			pagefault++;
			//새로운 페이지 초기화
			Page page;
			page.pageNum=pageStreamESC[i][0];
			page.R=1;//기본적으로 스트림에서 참조되었기 때문에 R bit는 1임.
			if(pageStreamESC[i][2]==1)//W bit 1이면
				page.M=1;
			else
				page.M=0;

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
				//ESC 알고리즘으로 페이지 교체 수행
				//페이지의 R|M이 0|0이면 1순위 교체
				while(1)
				{
					if(q.page[pointer].R==0 && q.page[pointer].M==0)
					{
						q.page[pointer]=page;
						pointer=(pointer+1)%max;
						if(pointer==0)
							pointer++;
						break;
					}
					else if(q.page[pointer].R==0 && q.page[pointer].M==1)
					{
						//R|M 이 0|1인 경우 2순위
						//M bit를 0으로 바꾸고 한번 더 기회를 준다
						q.page[pointer].M=0;
						pointer=(pointer+1)%max;
						if(pointer==0)
							pointer++;
					}
					else if(q.page[pointer].R==1 && q.page[pointer].M==0)
					{
						//R|M 이 1|0인 경우 3순위
						//R bit를 0으로 바꾸고 기회를 준다
						q.page[pointer].R=0;
						pointer=(pointer+1)%max;
						if(pointer==0)
							pointer++;
					}
					else if(q.page[pointer].R==1 && q.page[pointer].M==1)
					{
						//R|M이 1|1인 경우 4순위
						//R bit를 0으로 바꾸고 기회를 준다
						q.page[pointer].R=0;
						pointer=(pointer+1)%max;
						if(pointer==0)
							pointer++;
					}
				}	
			}
		}	
		printQueueESC(q,max,fp);
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



