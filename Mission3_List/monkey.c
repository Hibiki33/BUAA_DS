#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node *next;
}node,*linklist;

linklist first=NULL,p1,p2,p,pt;
int m,n,q;

int main(){
    int i,j,cnt=0;
    scanf("%d%d%d",&n,&m,&q);
    for(i=1;i<=n;i++){
        p2=(linklist)malloc(sizeof(node));
        p2->data=i; 
        p2->next=NULL;
        if(first==NULL)
            first=p1=p2;
        else{
            p1->next=p2;
            p1=p1->next;
        }
    }
    p1->next=first;
    for(i=0,p=p1;i<q-1;i++){
        p=p->next;
//        printf("%d\n",p->data);
    }
    while(cnt<n-1){
        for(j=0;j<m-1;j++)
            p=p->next;
//        printf("%d\n",p->data);  
        pt=p->next;
        p->next=p->next->next;
        free(pt);
//        p=p->next;
        cnt++;
    }
    printf("%d",p->data);
    return 0;
}
