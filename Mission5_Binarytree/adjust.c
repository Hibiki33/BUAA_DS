#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int pos;
    struct node *child[3];
}node,*specific;

typedef struct gate{
    int pos;
    int nums;
}gate;

specific hashtable[205];
specific root=NULL,p=NULL;
int parent,tmp,cnt=0;
gate g[100];
int ans[100][2],pa=0;

int cmp(const void *a,const void *b){
    gate *aa=(gate *)a;
    gate *bb=(gate *)b;
    if((*bb).nums!=(*aa).nums)
        return (*bb).nums-(*aa).nums;
    else return (*aa).pos-(*bb).pos;
}

void leveltraversal(){
    specific queue[105];
    int front=0,rear=-1;
    queue[++rear]=root;
    while(front<=rear){
        if(queue[front]->child[0])
            queue[++rear]=queue[front]->child[0];
        if(queue[front]->child[1])
            queue[++rear]=queue[front]->child[1];
        if(queue[front]->child[2])
            queue[++rear]=queue[front]->child[2];
        if(queue[front]->pos<100)
            ans[pa++][1]=queue[front]->pos;
        front++;
    }
}

int main(){
    root=(specific)malloc(sizeof(node));
    root->pos=100;
    root->child[0]=root->child[1]=root->child[2]=NULL;
    hashtable[100]=root;
    scanf("%d",&parent);
    while(~parent){
        scanf("%d",&tmp);
        int i=0;
        while(~tmp){
            if(tmp!=-1&&tmp<100)cnt++;
            p=(specific)malloc(sizeof(node));
            p->pos=tmp;
            p->child[0]=p->child[1]=p->child[2]=NULL;
            hashtable[parent]->child[i++]=p;//
            hashtable[tmp]=p;
            scanf("%d",&tmp);
        }
        scanf("%d",&parent);
    }
    int j; 
    for(j=0;j<cnt;j++)
        scanf("%d%d",&g[j].pos,&g[j].nums);
    qsort(g,cnt,sizeof(g[0]),cmp);
    for(j=0;j<cnt;j++){
        ans[j][0]=g[j].pos;
//        printf("%d\n",ans[j][0]);
    }
    leveltraversal();
    for(j=0;j<cnt;j++)
        printf("%d->%d\n",ans[j][0],ans[j][1]);
    return 0;
}
