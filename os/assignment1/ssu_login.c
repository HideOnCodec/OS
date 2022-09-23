#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

char userID[16][32];
char pwdID[16][32];

char Username[32];
char Password[32];
char id[32];

void scanf(){
	char c;
	int n;
	int i=0;
	while((n=read(0,&c,1))>0){
		if(c=='\n'){
			id[i]='\0';
			break;
		}
		id[i++]=c;
	}
}

void get_user_list(){
	int fd,n;
	fd= open("list.txt",O_RDONLY);

	char c;
	int flag;//userID와 pwdID 구분
	
	for(int i=0; i<10; i++){
		// list.txt에서 Username, Password 정보를 userID, pwdID에 저장
		int index=0;
		flag=1; 
		while((n=read(fd,&c,1))>0){
			if(c==' '){
				userID[i][index]='\0';
				flag=0;
				index=0;
				continue;
			}
			if(c=='\n'){
				pwdID[i][index]='\0';
				break;
			}

			if(flag)
				userID[i][index++]=c;
			else
				pwdID[i][index++]=c;
		}
	}
	close(fd);
}

int check_idpw(){
	//입력받은 Username, Password와 list.txt 비교
	for(int i=0; i<16; i++){
		if(strcmp(Username,userID[i])==0 && strcmp(Password,pwdID[i])==0)
				return 1;
	}
	return 0;
}

int main(int argc, char *argv[])
{
	
	int pid,wpid;
	get_user_list();

	while(1)
	{
		printf(1,"Username: ");
		scanf();
		for(int i=0; i<32; i++)
			Username[i]=id[i];

		printf(1,"Password: ");
		scanf();
		for(int i=0; i<32; i++)
			Password[i]=id[i];
		
		if(check_idpw())
		{
			for(;;){
				pid=fork();

				if(pid<0){
					printf(1,"login : fork failed\n");
					exit();
				}
				if(pid==0){
					exec("sh",argv);
					printf(1,"login : exec login failed");
					exit();
				}
				while((wpid=wait()) >= 0 && wpid != pid)
					printf(1, "zombie!\n");
			}
			
		}
	}
}
		

