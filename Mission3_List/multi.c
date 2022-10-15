#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct polymial{
    int coef;
    int expn;
    struct polymial *next;
}polymial,*linklist;

linklist poly1=NULL,poly2=NULL,polyans=NULL;

void insert(linklist p,int c,int e){
    linklist q;
    q=(linklist)malloc(sizeof(polymial));
    q->coef=c;
    q->expn=e;
    q->next=NULL;              
    if(polyans==NULL)
        polyans=q;
    else if(p==NULL){
        q->next=polyans;
        polyans=q;
    }
    else{
        q->next=p->next;
        p->next=q;
    }
    return;
}

void search(int c,int e){
    linklist p,q=NULL;
    for(p=polyans;p!=NULL;q=p,p=p->next){
        if(e>p->expn) 
            break;
        else if(e==p->expn){
            p->coef+=c;
            return;
        }
    }
    insert(q,c,e);
    return;
}


void multi(){
    linklist p1,p2;
    int r1,r2;
    for(p1=poly1;p1!=NULL;p1=p1->next){
        for(p2=poly2;p2!=NULL;p2=p2->next){
            r1=p1->coef*p2->coef;
            r2=p1->expn+p2->expn;
            search(r1,r2);
        }
    }
    return;
}

int main(){
    linklist pp;
    int tmp1,tmp2;
    linklist p,q;
    char ch;
    do{
        scanf("%d%d%c",&tmp1,&tmp2,&ch);
        q=(linklist)malloc(sizeof(polymial));
        q->coef=tmp1;
        q->expn=tmp2;
        q->next=NULL;
	    if(poly1==NULL)
            poly1=p=q;
        else
            p->next=q;      
	    p=q;
    }while(ch!='\n');
    do{
        scanf("%d%d%c",&tmp1,&tmp2,&ch);
        q=(linklist)malloc(sizeof(polymial));
        q->coef=tmp1;
        q->expn=tmp2;
        q->next=NULL;
	    if(poly2==NULL)
            poly2=p=q;
        else
            p->next=q;      
	    p=q;
    }while(ch!='\n');
    multi();
    for(pp=polyans;pp!=NULL;pp=pp->next)
        printf("%d %d ",pp->coef,pp->expn);
    return 0;
}
