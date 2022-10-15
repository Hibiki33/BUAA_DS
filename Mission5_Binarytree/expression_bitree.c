#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int nums=0,pc=-1;
char cal[100];
struct Elem{
    int tag;
    union{
        int ival;
        char cval;
    };
}e[100];
int pe=-1;
typedef struct Tnode{
    int pos;
    struct Tnode *left,*right;
}Tnode,*bitree;
bitree stack[100];
int ps=-1;
char scan(){
	char tmp;	
	do{
		tmp=getchar();
	}while(tmp==' ');
	if(isdigit(tmp)){
		nums=tmp-'0';
		tmp=getchar();
		while(isdigit(tmp)){
			nums=nums*10+tmp-'0';
			tmp=getchar();
		}
		e[++pe].tag=1;
        e[pe].ival=nums;
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
int operate(int a,int b,char x){
	switch(x){
	case '+': return a+b;
	case '-': return a-b;
	case '*': return a*b;
	case '/': return a/b;
	}
}
int result(bitree x){
    if(e[x->pos].tag)
        return e[x->pos].ival;
    return operate(result(x->left),result(x->right),e[x->pos].cval);
}
int main(){
    char c;
    c=scan();
    while(c!='='){
        while(pc!=-1&&compare(cal[pc],c)>0){
            e[++pe].tag=0;
            e[pe].cval=cal[pc--];
        }
        if(compare(cal[pc],c)==0){
            pc--;
            c=scan();
            continue;    
        }
        cal[++pc]=c;
        c=scan();
    }
    while(pc!=-1){
        e[++pe].tag=0;
        e[pe].cval=cal[pc--];
    }
    bitree p,q;
    for(int i=0;i<=pe;i++){
        if(e[i].tag){
            p=(bitree)malloc(sizeof(Tnode));
            p->pos=i;
            p->left=p->right=NULL;
            stack[++ps]=p;
        }
        else{
            p=(bitree)malloc(sizeof(Tnode));
            p->pos=i;
            p->right=stack[ps--];
            p->left=stack[ps--];
            stack[++ps]=p;
        }
    }
    if(stack[0])
        printf("%c ",e[stack[0]->pos].cval);
    if(stack[0]->left){
        if(e[stack[0]->left->pos].tag)
            printf("%d ",e[stack[0]->left->pos].ival);
        else 
            printf("%c ",e[stack[0]->left->pos].cval);
    }
    if(stack[0]->right){
        if(e[stack[0]->right->pos].tag)
            printf("%d ",e[stack[0]->right->pos].ival);
        else 
            printf("%c ",e[stack[0]->right->pos].cval);
    }
    printf("\n");
    printf("%d",result(stack[0]));
	return 0;
}