#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define false 0
#define true 1
typedef int bool;

typedef struct node{
    int num;
    int height;
    int cnt;
    struct node *left,*right;
}node,*bitree;

bitree searchtree=NULL;
int nums,numsSize;
int sumcnt = 0;

bitree insert(int x,bitree p,int h){
    if(p==NULL){
        p=(bitree)malloc(sizeof(node));
//        printf("%d %d\n",x,h);
        p->cnt = 1;
        p->num=x;
        p->height=h;
        p->left=p->right=NULL;
    } else {
        sumcnt++;
        if(x<p->num)
            p->left=insert(x,p->left,h+1);
        else if(x>p->num)
            p->right=insert(x,p->right,h+1);
        else if (x == p->num) {
            p->cnt++;
        } 
    }
    return p;
}
/*
void inorderTraversal(bitree root){
    bitree stack[100];
    int top=-1,pa=0;
    bitree p=root;
    while(top!=-1||p){
        while(p!=NULL){
            stack[++top]=p;
            p=p->left;
        }
        p=stack[top--];
        if(p->right==NULL&&p->left==NULL)
            printf("%d %d\n",p->num,p->height);
        p=p->right;
    }
   
}
*/
bitree nodes[1000];
int pn = 0;

void preorder(bitree p) {
    if (p) {
        nodes[pn++] = p;

       // printf("%d %d\n", p->num, p->cnt);

        preorder(p->left);
        preorder(p->right);
    }
}

int canfind(bitree p, bitree t) {
    if (p == t) return 1;
    if (!p) return 0;
    else {
        return canfind(p->left, t) || canfind(p->right, t);
    }
}

void find(bitree p, bitree t) {
    if (p) {
        if (canfind(p, t)) {
            printf("%d ", p->num);
            find(p->left, t);
            find(p->right, t);
        }
    }
}

int main(){
    int i;
    scanf("%d\n",&numsSize);
    scanf("%d",&nums);
    searchtree=(bitree)malloc(sizeof(node));
    searchtree->height=1;
    searchtree->num=nums;
    searchtree->left=searchtree->right=NULL;
    searchtree->cnt = 1;
    for(i=1;i<numsSize;i++){
        scanf("%d",&nums);
        insert(nums,searchtree,1);
    }
//    inorderTraversal(searchtree);
    printf("%d\n", sumcnt);
    nodes[pn++] = searchtree;
    preorder(searchtree);

    int max = 0;
    for (i = 0; i < pn; i++) {
        max = max > nodes[i]->cnt ? max : nodes[i]->cnt;
    }
    for (i = 0; i < pn; i++) {
        if (nodes[i]->cnt == max) break;
    }
    find(searchtree, nodes[i]);

    return 0;
}