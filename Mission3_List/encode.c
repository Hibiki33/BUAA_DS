#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node{
    char data;
    struct node *next;
}node,*linklist;

linklist origin=NULL,new=NULL,code=NULL;
char contain[100000],c;
char encode[128];

linklist deleteNode(linklist list,char elem){
    linklist p,q;               /*p指向要删除的结点，q为p的前一个结点*/
    for(p=list;p!=NULL;q=p,p=p->next) 
        if(p->data==elem)       /*找到要删除的链结点*/
            break;
    if(p==list){                /*删除头结点*/
        list=list->next;
        free(p);                  
    } 
    if(q->next!=NULL){          /*删除p指向的结点*/
        q->next=p->next;
        free(p);
    }
    return list;
}
/*
char search(char x){
    linklist p;
    for(p=code;1;p=p->next)
        if(p->data==x)
            break;
    return p->next->data;
}
*/
int main(){
    int i,j;
    char s[100],l[100];
    linklist p,q,r1,r2;
    for(i=32;i<=126;i++){
        q=(linklist)malloc(sizeof(node));
        q->data=i;
        q->next=NULL;
	    if(origin==NULL)
            origin=p=q;
        else
            p->next=q;      
	    p=q;
    }
//    for(p=origin;p!=NULL;p=p->next)
//        printf("%c",p->data);
    gets(l);
    int k=0,sgn=1;
    for(i=0;i<strlen(l);i++){
    	sgn=1;
    	for(j=0;j<k;j++){
    		if(l[i]==s[j]){
				sgn=0;
    			break;
    		}
		}
		if(sgn)
        	s[k++]=l[i];
	}
	s[k]='\0';
//	for(i=0;s[i]!='\0';i++)
//		printf("%c",s[i]); 
    for(i=0;i<strlen(s);i++){
        for(p=origin;1;q=p,p=p->next){
            if(p->data!=s[i])continue;
            if(p->data==s[i]){
                
                p->data=0;

                r2=(linklist)malloc(sizeof(node));
                r2->data=s[i];
                r2->next=NULL;
	            if(new==NULL)
                    new=r1=r2;
                else
                    r1->next=r2;      
	            r1=r2;
                break;
            }
        }
    }
//    for(p=new;p!=NULL;p=p->next)
//        printf("%c",p->data);
    for(r2=new;r2!=NULL;r1=r2,r2=r2->next);
    for(p=origin;p!=NULL;p=p->next){
        if(p->data!=0){      
            r2=(linklist)malloc(sizeof(node));
            r2->data=p->data;
            r2->next=NULL;
            r1->next=r2;      
            r1=r2;
        }            
    }
//    for(p=new;p!=NULL;p=p->next)
//        printf("%c",p->data);
    for(q=new;q!=NULL;p=q,q=q->next);
    p->next=new;
//    for(p=new->next;p!=new;p=p->next)
//        printf("%c",p->data);
  
    linklist m,n,a,b;
    int cnt;
    char tmp;
    for(n=p,cnt=0;cnt<126-32+1;cnt++){
        m=n->next;
        tmp=m->data;
//        printf("%d",tmp);

        n->next=m->next;
        free(m);
        if(n!=NULL)
    	    for(i=1;i<tmp;n=n->next,i++);

        b=(linklist)malloc(sizeof(node));
        b->data=tmp;
        b->next=NULL;
	    if(code==NULL)
            code=a=b;
        else
            a->next=b;      
	    a=b;
    }
//    for(n=code;n!=NULL;n=n->next)
//       printf("%c",n->data);
//    a->next=code;
//    for(n=code;n!=a;n=n->next)
//        printf("%c",n->data);
    for(p=code;p!=NULL;p=p->next){
        if(p==a)
            encode[p->data]=code->data;
        else 
            encode[p->data]=p->next->data;
    }

    FILE *in=fopen("in.txt","r");
    FILE *out=fopen("in_crpyt.txt","w");

    c=fgetc(in);
    i=0;
    while(c!=EOF){
        contain[i++]=c;
        c=fgetc(in);
    }
    contain[i]='\0';
    for(i=0;i<strlen(contain);i++){
        if(contain[i]>=32&&contain[i]<=126)
            fputc(encode[contain[i]],out);
        else 
            fputc(contain[i],out);
    }

    fclose(in);
    fclose(out);
    return 0;
}
