#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int data;
	struct node *next;
}node,*stack;

stack first;

int main(){
	first=(stack)malloc(sizeof(node));
	first->data=0;
	first->next=NULL;
	int tmp,figure;
	stack p=first->next,q;
	scanf("%d",&tmp);
	while(tmp!=-1){
		switch(tmp){
		case 1:
			scanf("%d",&figure);
			if(first->data<100){
				q=(stack)malloc(sizeof(node));
				q->data=figure;
				q->next=p;
				first->next=q;
				first->data++;
				p=q;
			}
			else 
				printf("error ");
			break;
		case 0:
			if(first->data==0)
				printf("error ");
			else{
				p=p->next;
				first->next=p;
				printf("%d ",q->data);
				q=p;
				first->data--;
			}
		default:
			break;
		}
		scanf("%d",&tmp);
	}
	return 0;
}