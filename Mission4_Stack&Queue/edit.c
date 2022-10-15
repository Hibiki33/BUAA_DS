#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stack{
    int tag;
    int pos;
    char str[600];
}stack;

stack order[500];
char s[600];
int n,p=-1;

void insert(int pos,char *str1){
    int i;
    for(i=strlen(s);i>=pos;i--)
        s[i+strlen(str1)]=s[i];
    for(i=0;i<strlen(str1);i++)
        s[i+pos]=str1[i];
}

void delete(int pos,int n1,char *str2){
    int i,a=strlen(s);
    for(i=0;i<n1;i++)
        str2[i]=s[i+pos];
    for(i=pos;i+n1<a;i++)
        s[i]=s[i+n1];
    s[i]='\0';
    for(i++;i<a;i++)
        s[i]=0;
}

int main(){
    int i,j;
    int tag0,pos0,n0;
    char str0[600],tmp[600];
    fgets(s,515,stdin);
    scanf("%d",&n);
    for(i=0;i<n;i++){
        scanf("\n%d%d%s",&tag0,&pos0,str0);
        p++;
        order[p].tag=tag0;
        order[p].pos=pos0;
        strcpy(order[p].str,str0);
    }
    scanf("\n%d",&tag0);
    while(tag0!=-1){
        switch(tag0){
        case 1:
            scanf("%d%s",&pos0,str0);
            insert(pos0,str0);
            p++;
            order[p].tag=tag0;
            order[p].pos=pos0;
            strcpy(order[p].str,str0);
            break;
        case 2:
            scanf("%d%d",&pos0,&n0);
            p++;
            delete(pos0,n0,order[p].str);
            order[p].tag=tag0;
            order[p].pos=pos0;
            break;
        case 3:
            if(order[p].tag==1){
                delete(order[p].pos,strlen(order[p].str),tmp);
                p--;
            }
            else{
                insert(order[p].pos,order[p].str);
                p--;
            }
            break;
        }
        scanf("\n%d",&tag0);
    }
    puts(s);
    return 0;
}