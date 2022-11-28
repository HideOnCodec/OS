#include "types.h"
#include "user.h"
#include "stat.h"

#define PNUM 5 // 프로세스 수
#define PRINT_CYCLE 10000000 // fork()로 생성된 프로세스 중 실행 중인 프로세스 정보를 출력하는 주기
#define TOTAL_COUNTER 500000000// fork()로 생성된 프로세스가 생성된 이후부터 소모할 수 있는 시간
void sdebug_func(void)
{
	int n,pid;
	
	printf(1,"start sdebug command\n");
	
	for(n=0; n<PNUM; n++)
	{
		pid=fork();//자식 프로세스 생성
		
		if(pid<0)
		{	//에러 출력
			printf(1,"fork failed\n");
			break;
		}
		if(pid==0)
		{	//자식 프로세스인 경우
			int weight=weightset(n+1);//1부터 가중치 설정
			uint startTime=uptime();//프로세스 생성 후 tick
			
			long long counter=0; //TOTAL_COUNTER와 비교하는 counter 변수
			long long print_counter=0;//출력주기와 비교하는 print_counter 변수
			int first=1;
			while(counter<=TOTAL_COUNTER) //TOTAL_COUNTER에 도달하면 프로세스 종료
			{
				counter++; //counter 값  증가
				print_counter++;//print_counter 값 증가

				if(print_counter==PRINT_CYCLE){//PRINT_CYCLE에 도달하면 프로세스 정보 출력
					uint endTime=uptime(); //프로세스 정보를 출력할 때의 tick
					if(first){//처음 PRINT_CYCLE에 도달했으면 프로세스 정보를 출력함
					printf(1,"PID: %d, WEIGHT: %d, ",getpid(),weight);
					printf(1,"TIMES: %d ms\n",(endTime-startTime)*10); //프로세스 생성부터 정보 출력까지 소요된 시간 계산
					first=0;//
					}
					print_counter=0; //출력 counter 다시 초기화
				}
			}
			printf(1,"PID: %d terminated\n",getpid());
			exit();//프로세스 종료
		}

	}
	//sdebug는 자식프로세스가 모두 끝날때까지 기다림
    for(; n > 0; n--){
    	if(wait() < 0){//음수가 나오면 에러
      		printf(1, "wait stopped early\n");
      		exit();
    	}
  	}
   	if(wait() != -1){
    	printf(1, "wait got too many\n");
    	exit();
  	}
	printf(1,"end sdebug command\n");
	
	return ;
}

int main(void)
{
	sdebug_func();
	exit();
}
