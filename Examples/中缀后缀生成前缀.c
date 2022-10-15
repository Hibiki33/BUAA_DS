#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 12

typedef struct node{
    char data;
    struct node *lchild,*rchild;
}node,*bitree;

bitree preorder=NULL;
char inorder[MAX+5],postorder[MAX+5];
//int pfront,prear;

int search(char a,int i){
    while(inorder[i++]!=a);
    return i-1;
}

bitree creatbitree(int front,int rear,int root){
//    printf("%d %d \n",front,rear);
    bitree p=(bitree)malloc(sizeof(node));
    if(front==rear){
        p->data=inorder[front];
        p->lchild=p->rchild=NULL;
        printf("%c",p->data);
        return p;
    }
    int mid=search(postorder[root],front);
//    int mid=search(0,front);
//    printf("%d\n",mid);
    p->data=inorder[mid];
    printf("%c",p->data);
    if(postorder[root]!=inorder[front])
        p->lchild=creatbitree(front,mid-1,root-(rear-mid)-1);
    else p->lchild=NULL;
    if(postorder[root]!=inorder[rear])
        p->rchild=creatbitree(mid+1,rear,root-1);
    else p->rchild=NULL;
    return p;
}

//void preordertraverse(){
//}

int main(){
//    fgets(inorder,MAX+5,stdin);
//    fgets(postorder,MAX+5,stdin);
    scanf("%s",inorder);
    scanf("%s",postorder);
    preorder=creatbitree(0,strlen(inorder)-1,strlen(postorder)-1);
//    printf("%c",preorder->rchild->rchild);
//    preordertraverse();
    return 0;
}