#include "header.h"

Node* createNode(int pageStringNum)
{
	Node *newNode=(Node *)malloc(sizeof(Node));
	newNode->pageNum=pageStringNum;
	newNode->nextUsing=-1;
	newNode->counter=1;
	newNode->next=NULL;
	return newNode;
}

Data addNodeHead(Node *head,Node *tail,Node* newNode)//새로운 페이지를 head가 가리키도록 추가하는 함수
{
	if(head==NULL)//head 노드가 가리키는 노드가 없으면
	{
		//새로운 노드를 가리키게 함
		head=newNode;
		tail=newNode;
	}
	else
	{
		newNode->next=head;//head가 가리키던 노드를 새로운 노드가 가리킨다.
		head=newNode;//head는 새로운 노드를 가리킨다.
	}
	
	Data data;
	data.head=head;
	data.tail=tail;
	
	return data;
}

Data addNodeTail(Node *head,Node *tail,Node *newNode)//새로운 페이지를 tail이 가리키도록 추가하는 함수
{	
	if(head==NULL)//head 노드가 가리키는 노드가 없으면
		head=newNode;//새로운 노드를 가리키게 함
	else
		tail->next=newNode;//tail이 가리키는 노드가 새로 추가된 노드를 가리킴. 즉 새로운 페이지를 가리킴

	tail=newNode;
	
	Data data;
	data.head=head;
	data.tail=tail;
	
	return data;
}

Data deleteNodeTail(Node* head,Node *tail)//tail이 가리키는 페이지 삭제 함수
{
	if(head!=NULL)
	{
		//연결리스트의 마지막 노드를 삭제하는 함수
		Node *current=head;
		while(current!=NULL)//연결리스트를 head부터 탐색
		{
			if(current->next==tail)//현재 노드의 다음 노드가 마지막 노드라면 break
				break;
			current=current->next;
		}
		//tail이 prev를 가리켜서 가장 마지막에 연결된 노드가 삭제됨
		tail=current;//tail이 마지막 노드의 이전 노드인 current를 가르킴
		tail->next=NULL;
	}
	Data data;
	data.head=head;
	data.tail=tail;

	return data;
}

Node* deleteNodeHead(Node* head)//head가 가리키는 페이지 삭제 함수
{
	if(head!=NULL)
		head=head->next;//head가 가리키던 노드를 삭제
	return head;
}

Node* pageFault(Node *head, int pageStringNum)//페이지 폴트인지 검사하는 함수
{
	Node *current=head;
	while(current!=NULL)//head 노드부터 연결리스트를 탐색함
	{
		if(current->pageNum==pageStringNum)//페이지스트링번호와 같은 페이지가 있으면
			return current;//해당 페이지 노드를 리턴함
		current=current->next;
	}
	return NULL;//페이지스트링번호와 같은 페이지가 없으면 NULL 리턴함
}

void printList(Node *head,FILE *fp)//페이지 프레임을 구현한 연결리스트 출력
{
	Node *cur=head;
	while(cur!=NULL)
	{
		printf("%d->", cur->pageNum);
		fprintf(fp,"%d->",cur->pageNum);
		cur=cur->next;
	}
	printf("NULL ");
	fprintf(fp,"NULL ");
}

void freeAll(Node *head)//연결리스트 노드 해제 함수
{
     Node *current = head;
     while (current!=NULL)
     {
         Node *next = current->next;
         // 다음 원소를 저장후에
         free(current);
         // 현재 가리키는 원소를 할당 해제
         current = next;
         // cur 포인터를 다음 Node를 가리킨후 다시 확인
     }
}
