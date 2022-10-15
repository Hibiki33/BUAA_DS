#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int time;
    int id;
	struct node *next;
}node,*queue;
typedef struct{
	queue front;
	queue rear;
}linkqueue;

linkqueue Q;
int time0,id0,idcnt=1;
int op,n,tmp,sum=0;

void chooseOP1(int n){
	if(n<21)op=3; 
	else if(n>=21&&n<28)op=4;
	else op=5;
}
void chooseOP2(int n){
	if(n<28)op=3; 
	else if(n>=28&&n<35)op=4;
	else op=5;
}

void enqueue(){
	queue p;
	p=(queue)malloc(sizeof(node));
	p->id=idcnt++;p->time=0;
	p->next=NULL;
	Q.rear->next=p;
	Q.rear=p;
}

void dequeue(){
	queue p=Q.front->next;
	if(Q.rear==p)
		Q.rear=Q.front;
	time0=p->time;
    id0=p->id;
	Q.front->next=p->next;
	free(p);
}

int main(){
	Q.front=(queue)malloc(sizeof(node));
	Q.front->next=NULL;
	Q.rear=Q.front;
	int i;
	queue p;
	scanf("%d",&n);
	while(n--){
		scanf("\n%d",&tmp);
//		printf("%d\n",tmp);
		sum+=tmp;
		chooseOP1(sum);
//		printf("%d",op);
		for(i=0;i<tmp;i++)
			enqueue();
		for(i=0;i<op&&Q.front!=Q.rear;i++){
			dequeue();
			printf("%d : %d\n",id0,time0);
		}
		for(p=Q.front->next;p!=NULL;p=p->next)
			p->time++;
		sum-=op;
		if(sum<0)sum=0;
	}
	while(Q.front!=Q.rear){
		chooseOP2(sum);
		for(i=0;i<op&&Q.front!=Q.rear;i++){
			dequeue();
			printf("%d : %d\n",id0,time0);
		}
		for(p=Q.front->next;p!=NULL;p=p->next)
			p->time++;
		sum-=op;
	}
    return 0;
}