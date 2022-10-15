#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXWORD 40

typedef struct node{
    char word[MAXWORD];
    int freqency;
    struct node *next;
}node,*linklist;

linklist wordlist=NULL;

void insertWord(linklist p,char *w){
    linklist q;
    q=(linklist)malloc(sizeof(node));
    strcpy(q->word,w);
    q->freqency=1;
    q->next=NULL;              
    if(wordlist==NULL)
        wordlist=q;
    else if(p==NULL){
        q->next=wordlist;
        wordlist=q;
    }
    else{
        q->next=p->next;
        p->next=q;
    }
    return;
}

void searchword(char *w){
    linklist p,q=NULL;
    for(p=wordlist;p!=NULL;q=p,p=p->next){
        if(strcmp(w,p->word)<0) 
            break;
        else if(strcmp(w,p->word)==0){
            p->freqency++;
            return;
        }
    }
    insertWord(q,w);
    return;
}

int main(){
    int i=0;
    linklist p;
    char word[MAXWORD],tmp;
    memset(word,0,sizeof(word));
    FILE *in=fopen("article.txt","r");
    while((tmp=fgetc(in))!=EOF){
        if(isalpha(tmp)){
            tmp=tolower(tmp);
            word[i++]=tmp;
        }
        else if((!isalpha(tmp))&&i){
            word[i]='\0';
            searchword(word);
            i=0;
        }
    }
    for(p=wordlist;p!=NULL;p=p->next)
        printf("%s %d\n",p->word,p->freqency);
    fclose(in);
    return 0;
}