#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 26
typedef int Status;

typedef struct node{
    char data;
    struct node *lchild,*rchild;
}node,*bitree;

bitree postorder=NULL;
char preorder[MAX+5],inorder[MAX+5];

int search(char a,int i){
    while(inorder[i++]!=a);
    return i-1;
}

bitree creatbitree(int front,int rear,int root){
	bitree p=(bitree)malloc(sizeof(node));
	if(front==rear){
        p->data=inorder[front];
        p->lchild=p->rchild=NULL;
        return p;
    }
	int mid=search(preorder[root],front);
	p->data=inorder[mid];
	if(preorder[root]!=inorder[front])
        p->lchild=creatbitree(front,mid-1,root+1);
    else p->lchild=NULL;
    if(preorder[root]!=inorder[rear])
        p->rchild=creatbitree(mid+1,rear,root+mid-front+1);
    else p->rchild=NULL;
    return p;
}

Status visitnode(bitree tnode){
//	if(!tnode->data)return 0;
	printf("%c",tnode->data);
	return 1;
}

Status postordertraverse(bitree tnode){
	if(tnode){
		if(postordertraverse(tnode->lchild))
		if(postordertraverse(tnode->rchild))
		if(visitnode(tnode))
			return 1;
		return 0;
	}
	else return 1;
}

int main(){
//  fgets(inorder,MAX+5,stdin);
//  fgets(postorder,MAX+5,stdin);
//  The function "fgets()" will get in the "\n"
	scanf("%s",inorder);
	scanf("%s",preorder);

	for (int i = strlen(preorder) - 1; preorder[i] == ' '; i--) {
		preorder[i] =0;
	}

	postorder=creatbitree(0,strlen(inorder),0);
	if(postordertraverse(postorder));
	return 0;
}