#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char ans[205],s[1005],tmp;
int linecnt,pa=0;

typedef struct node{
	int line;
	char data;
	struct node *next;
}node,*stack;

stack top;

void pop(){
	char c;
	stack p=top->next;
	c=p->data;
	top->next=p->next;
//	free(p);
}

void push(char a,int cnt){
	stack p;
	p=(stack)malloc(sizeof(node));
	p->data=a;
	p->line=cnt;
	p->next=top->next;
	top->next=p;
}

int skip1(int i,FILE *in){
	int flag=1;
	while(!(s[i]=='/'&&s[i-1]=='*')&&s[i]!='\n')i++;
	if(s[i]=='\n'){
		while(flag!=0){
			fgets(s,1000,in);
			linecnt++;
			if(s[i]=='/'&&s[i-1]=='*')
				flag=0;
		}
	}
	return i;
}
int skip2(int i){
	while(s[i]!='"')i++;
	return i;
}

int main(){
	top=(stack)malloc(sizeof(node));
	top->next=NULL;
	int i,flag=1;
	FILE *in=fopen("example.c","r");
	while(fgets(s,1000,in)!=NULL){
		if(s[0]=='\n')
			continue;
		linecnt++;

		for(i=0;s[i]!='\0';i++){
			if(s[i]=='/'&&s[i+1]=='/')break;
			if(s[i]=='/'&&s[i+1]=='*')
				i=skip1(i,in);
			if(s[i]=='"')
				i=skip2(i+1);
//			if(s[i]==39)
//				i+=2;
			if(s[i]=='{'||s[i]=='('){
				push(s[i],linecnt);
				ans[pa++]=s[i];	
			}
			else if(s[i]=='}'){
				if(top->next->data=='{'){
					pop();
					ans[pa++]=s[i];
				}
				else{
					flag=0;
					break;
				}
			}
			else if(s[i]==')'){
				if(top->next->data=='('){
					pop();
					ans[pa++]=s[i];
				}
				else{
					flag=0;
					break;
				}
			}
		}
		if(!flag)
			break;
	}
	if(!flag)
		printf("without maching '%c' at line %d",s[i],linecnt);
	else if(top->next!=NULL)
		printf("without maching '%c' at line %d",top->next->data,top->next->line);
	else{
		ans[pa]='\0';
		puts(ans);
	}
	fclose(in);
	return 0;
}