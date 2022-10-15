#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stack{
    char data[25];
}s[205];
struct answer{
    char name[25];
    int freq;
    char contain[12][25];
}ans[105];

int top=-1,pa=-1;

void search(){
    int i;
    for(i=0;i<=pa;i++)
        if(strcmp(s[top].data,ans[i].name)==0)
            break;
    if(i>pa)
        strcpy(ans[++pa].name,s[top].data);
}

void count(){
    int i,j;
    for(i=0;i<=pa;i++)
        if(strcmp(s[top-1].data,ans[i].name)==0)
            break;
    for(j=0;j<ans[i].freq;j++)
        if(strcmp(ans[i].contain[j],s[top].data)==0)
            break;
    if(j==ans[i].freq){
        strcpy(ans[i].contain[ans[i].freq],s[top].data);
        ans[i].freq++;
    }
}

int main(){
    int oper,i,j;
//    char func;
    scanf("%d%s",&oper,s[++top].data);
    strcpy(ans[++pa].name,s[top].data);
    while(top!=-1){
        scanf("%d",&oper);
        if(oper==8){
            scanf("%s",s[++top].data);
            search();
            count();
        }
        else top--;
    }
    for(i=0;i<=pa;i++){
        if(ans[i].freq){
            printf("%s:",ans[i].name);
            for(j=0;j<ans[i].freq;j++){
                if(j<ans[i].freq-1)
                    printf("%s,",ans[i].contain[j]);
                else 
                    printf("%s",ans[i].contain[j]);
            }
            printf("\n");
        }
    }
    return 0;
}
