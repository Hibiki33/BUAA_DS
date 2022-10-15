#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 1000

double num[MAX+5];
char cal[MAX+5];
int pn=0,pc=0;
char c;

char scan(){
	char tmp;	
	do{
		tmp=getchar();
	}while(tmp==' ');
	if(isdigit(tmp)){
		num[pn]=tmp-'0';
		tmp=getchar();
		while(isdigit(tmp)){
			num[pn]=num[pn]*10+tmp-'0';
			tmp=getchar();
		}
		pn++;
	}
	while(tmp==' ')
		tmp=getchar();
	return tmp;
}

int compare(char a,char b){
	switch(a){
	case '+':
	case '-':
		switch(b){
		case '+':
		case '-':
		case '=':
		case ')': return 1;
		default:  return -1;
		}
	case '*':
	case '/':
		switch(b){
		case '(': return -1;
		default:  return 1;	
		}
	case '(':
		switch(b){
		case ')': return 0;
		default:  return -1;
		}
	case ')':     return 1;
	case '=':     return -1;
	}
}

double operate(double a,double b,char x){
	switch(x){
	case '+': return a+b;
	case '-': return a-b;
	case '*': return a*b;
	case '/': return a/b;
	}
}

int main(){
	cal[pc++]='=';
	c=scan();
//	printf("%d\n",num[0]);
	while(c!='='||cal[pc-1]!='=')
		switch(compare(cal[pc-1],c)){
		case -1:
			cal[pc++]=c;
			c=scan();
			break;
		case 1:
			num[pn-2]=operate(num[pn-2],num[pn-1],cal[pc-1]);
			num[--pn]=0;
			cal[--pc]=0;
			break;
		case 0:
			cal[--pc]=0;
			c=scan();
			break;
		}
	printf("%.2f",num[pn-1]);
	return 0;
}