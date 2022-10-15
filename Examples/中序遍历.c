#include <stdio.h>
#include <stdlib.h>

struct TreeNode{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int *inorderTraversal(struct TreeNode *root,int *returnSize){
    int *ans=(int*)malloc(sizeof(int)*100);
    struct TreeNode *stack[100];
    int top=-1,pa=0;
    struct TreeNode *p=root;
    while(top!=-1||p){
        while(p!=NULL){
            stack[++top]=p;
            p=p->left;
        }
        p=stack[top--];
        ans[pa++]=p->val;
        p=p->right;
    }
    *returnSize=pa;
    return ans;
}

int main(){


    return 0;
}