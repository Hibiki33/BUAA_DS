#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct node{
    char word[15];
    int freq;
    struct node *left,*right;
}node,*bitree;

bitree root=NULL;

int find(char *c,bitree p){
    if(p==NULL)return 0;
    if(strcmp(p->word,c)>0)
        return find(c,p->left);
    else if(strcmp(p->word,c)<0)
        return find(c,p->right);
    else if(strcmp(p->word,c)==0){
        p->freq++;
    }
    return 1;
}

bitree insert(char *c,bitree p){
    if(p==NULL){
        p=(bitree)malloc(sizeof(node));
        p->freq=1;
        strcpy(p->word,c);
        p->left=p->right=NULL;
    }
    else if(strcmp(p->word,c)>0)
        p->left=insert(c,p->left);
    else if(strcmp(p->word,c)<0)
        p->right=insert(c,p->right);
    return p;
}

void inorderTraversal(bitree r){
    bitree stack[100];
    int top=-1;
    bitree p=r;
    while(top!=-1||p){
        while(p!=NULL){
            stack[++top]=p;
            p=p->left;
        }
        p=stack[top--];
        printf("%s %d\n",p->word,p->freq);
        p=p->right;
    } 
}

int main(){
    char cc,tmp[15];
    int ptmp=0;
    FILE *in=fopen("article.txt","r");
    cc=fgetc(in);
    while(cc!=EOF){
        if(isalpha(cc)){
            cc=tolower(cc);
            tmp[ptmp++]=cc;
        }
        else{
            if(ptmp>0){
                tmp[ptmp]='\0';
                if(!find(tmp,root))
                    root=insert(tmp,root);
                ptmp=0;
                memset(tmp,0,sizeof(char)*15);
            }
        }
        cc=fgetc(in);
    }
    if(root){
        printf("%s",root->word);
        if(root->right){
            printf(" ");
            printf("%s",root->right->word);
            if(root->right->right){
                printf(" ");
                printf("%s",root->right->right->word);   
            }
        }
        printf("\n");
    }
    inorderTraversal(root);
    return 0;
}