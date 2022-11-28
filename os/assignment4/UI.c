#include "header.h"

void execute();
void userCreateStream();
void userCreateStreamESC();

int pageframe;
char num[3];
int selectCount;
int pageStream[MAX_STRING];
int pageStreamESC[MAX_STRING][3];

int main()
{	
	srand((unsigned int)time(NULL));
	FILE *fp = fopen("SimulationResult.txt","w");
	
	int ESC=0;
	while(1)
	{
		printf("------------------------UI------------------------\n");
		printf("A.	Page Replacement 알고리즘 시뮬레이터를 선택하시오 (최대 3개)\n");
		printf(" (1) Optimal  (2) FIFO  (3) LIFO  (4) LRU  (5) LFU  (6) SC  (7) ESC  (8) ALL\n");
		
		fprintf(fp,"------------------------UI------------------------\n");
		fprintf(fp,"A.	Page Replacement 알고리즘 시뮬레이터를 선택하시오 (최대 3개)\n");
		fprintf(fp," (1) Optimal  (2) FIFO  (3) LIFO  (4) LRU  (5) LFU  (6) SC  (7) ESC  (8) ALL\n");
		
		char c;
		int fail=0;
		selectCount=0;
		while((c=getchar())!='\n' && selectCount<3)
		{
			if(c!=' ')
				num[selectCount++]=c;
			if(!('1'<=c && c<='8'||c==' '))
				fail++;
			if(c=='7' || c=='8')
				ESC++;
			fprintf(fp,"%c ",c);	
		}
		fprintf(fp,"\n");
		if(fail==0)
			break;
		else{
			printf("1~8 사이의 정수를 입력하세요.\n");
			fprintf(fp,"1~8 사이의 정수를 입력하세요.\n");
		}
	}
	
	while(1)
	{
		printf("B. 페이지 프레임의 개수를 입력하시오.(3~10)\n");
		fprintf(fp,"B. 페이지 프레임의 개수를 입력하시오.(3~10)\n");

		scanf("%d",&pageframe);
		fprintf(fp,"%d\n",pageframe);

		if(pageframe<3 || pageframe>10)
		{
			printf("3~10 사이의 정수를 입력하세요.\n");
			fprintf(fp,"3~10 사이의 정수를 입력하세요.\n");
		}
		else
			break;
	}
	while(1)
	{
		printf("C. 데이터를 입력 방식을 선택하시오. (1,2)\n");
		printf("(1) 랜덤하게 생성\n");
		printf("(2) 사용자 생성 파일 오픈\n");
		
		fprintf(fp,"C. 데이터를 입력 방식을 선택하시오. (1,2)\n");
		fprintf(fp,"(1) 랜덤하게 생성\n");
		fprintf(fp,"(2) 사용자 생성 파일 오픈\n");
		int n;
		scanf("%d",&n);
		fprintf(fp,"%d\n",n);
		if(n==1 || n==2)
		{
			if(n==1) //(1)을 선택할 경우 프로그램에서 랜덤하게 생성해서 바로 출력
			{
				for(int i=0; i<MAX_STRING; i++)
					pageStream[i]=rand()%30+1;
			}
			else if(n==2)//(2)을 선택할 경우 페이지 스트림이 입력된 파일을 open해서 읽음
			{
				userCreateStream();
				FILE *fp;
				fp=fopen("samplestream.txt","r");
				
				if(fp==NULL)
				{
					printf("file open error\n");
					exit(1);
				}
				for(int i=0; i<MAX_STRING; i++)
					fscanf(fp,"%d ",&pageStream[i]);
				
				fclose(fp);
			}
			printf("페이지 스트링 출력: ");
			for(int i=0; i<MAX_STRING; i++)
				printf("%d ",pageStream[i]);
			printf("\n");
			
			fprintf(fp,"페이지 스트링 출력: ");
			for(int i=0; i<MAX_STRING; i++)
				fprintf(fp,"%d ",pageStream[i]);
			fprintf(fp,"\n");
			
			break;
		}
		else
		{
			printf("1 또는 2를 입력하세요.\n");
			fprintf(fp,"1 또는 2를 입력하세요.\n");
		}
	}

	if(ESC) // 7번 혹은 8번을 선택하면 ESC R/W비트 생성 방식을 선택받음
	{
		for(int i=0; i<MAX_STRING; i++)
			pageStreamESC[i][0]=pageStream[i];//페이지 번호 복사
		while(1)
		{
			printf("ESC R/W 데이터 생성 방식을 선택하시오. (1,2)\n");
			printf("(1) 랜덤하게 생성\n");
			printf("(2) 사용자 생성 파일 오픈\n");
			
			fprintf(fp,"ESC R/W 데이터 생성 방식을 선택하시오. (1,2)\n");
			fprintf(fp,"(1) 랜덤하게 생성\n");
			fprintf(fp,"(2) 사용자 생성 파일 오픈\n");
			
			int n;
			scanf("%d",&n);
			fprintf(fp,"%d\n",n);
			
			if(n==1 || n==2)
			{
				if(n==1) //(1)을 선택할 경우 프로그램에서 랜덤하게 생성해서 바로 출력
				{
					for(int i=0; i<MAX_STRING; i++)
					{
						pageStreamESC[i][1]=rand()%2;
						pageStreamESC[i][2]=rand()%2;
					}
				}
				else if(n==2)//(2)을 선택할 경우 페이지 스트링이 입력된 파일을 open해서 읽음
				{
					userCreateStreamESC();
					FILE *fp;
					fp=fopen("samplestreamESC.txt","r");
					
					if(fp==NULL)
					{
						printf("file open error\n");
						exit(1);
					}
					for(int i=0; i<MAX_STRING; i++)
						fscanf(fp,"%d %d %d\n",&pageStreamESC[i][0],&pageStreamESC[i][1],&pageStreamESC[i][2]);
					
					fclose(fp);
				}
				printf("페이지 스트림 출력(번호,R,W): ");
				for(int i=0; i<MAX_STRING; i++)
					printf("(%d, %d, %d) ",pageStreamESC[i][0],pageStreamESC[i][1],pageStreamESC[i][2]);
				printf("\n");
				
				fprintf(fp,"페이지 스트림 출력(번호,R,W): ");
				for(int i=0; i<MAX_STRING; i++)
					fprintf(fp,"(%d, %d, %d) ",pageStreamESC[i][0],pageStreamESC[i][1],pageStreamESC[i][2]);
				fprintf(fp,"\n");
				break;
			}
			else
			{
				printf("1 또는 2를 입력하세요.\n");
				fprintf(fp,"1 또는 2를 입력하세요.\n");
			}
		}	
	}
	fclose(fp);
	execute();

	printf("D. 종료\n");
	return 0;
}

void userCreateStream()//(2)사용자 생성 파일에 랜덤으로 생성된 페이지 스트림을 저장
{
	FILE *fp;
	fp=fopen("samplestream.txt","wt+");
	
	if(fp==NULL)
	{
		printf("file open error\n");
		exit(1);
	}
	
	srand((unsigned int)time(NULL));
	for(int i=0; i<MAX_STRING; i++)
	{
		pageStream[i]=rand()%30+1;
		fprintf(fp,"%d ",pageStream[i]);
	}
	fclose(fp);
}

void userCreateStreamESC()//ESC 선택할 경우 (2)사용자 생성 파일에 랜덤으로 페이지 스트림 저장
{
	//페이지 번호, 페이지 R bit, 페이지 W bit \n 형식으로 파일에 저장
	FILE *fp;
	fp=fopen("samplestreamESC.txt","w");
	
	if(fp==NULL)
	{
		printf("file open error\n");
		exit(1);
	}

	for(int i=0; i<MAX_STRING; i++)
	{
		pageStreamESC[i][1]=rand()%2;
		pageStreamESC[i][2]=rand()%2;
		fprintf(fp,"%d %d %d\n",pageStreamESC[i][0],pageStreamESC[i][1],pageStreamESC[i][2]);
	}
	fclose(fp);
}

void execute()
{
	for(int i=0; i<selectCount; i++)
	{

		switch(num[i])
		{
			case '1': 
					Optimal(pageStream,pageframe);
					break;
			case '2':
					Optimal(pageStream,pageframe);
					FIFO(pageStream,pageframe);
					break;
			case '3':
					Optimal(pageStream,pageframe);
					LIFO(pageStream,pageframe);
					break;
			case '4':
					Optimal(pageStream,pageframe);
					LRU(pageStream,pageframe);
					break;
			case '5':
					Optimal(pageStream,pageframe);
					LFU(pageStream,pageframe);
					break;
			case '6':
					Optimal(pageStream,pageframe);
					SC(pageStream,pageframe);
					break;
			case '7':
					Optimal(pageStream,pageframe);
					ESC(pageStreamESC,pageframe);
					break;
			case '8': 
					Optimal(pageStream,pageframe);
					FIFO(pageStream,pageframe);
					LIFO(pageStream,pageframe);
					LRU(pageStream,pageframe);
					LFU(pageStream,pageframe);
					SC(pageStream,pageframe);
					ESC(pageStreamESC,pageframe);
					break;
					
			default: break;
		}
	}

}


