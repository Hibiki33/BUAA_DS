#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    long long num;
    char name[25];
    int freq;
}people;
people list[105];
int cmp(const void *a,const void *b){
    people *aa=(people *)a;
    people *bb=(people *)b;
    int t=strcmp(aa->name,bb->name);//strcmp()返回值不止-1,1,0
    if(t) return t;
    if((*aa).freq>(*bb).freq)
        return 1;
    if((*aa).freq<(*bb).freq)
        return -1;   
}

int search(people list[],int cnt,char *a,long long b){
    int i;
    for(i=0;i<cnt;i++)
        if(strcmp(list[i].name,a)==0&&b==list[i].num)
            return 1;
    return 0;
}
int same(people list[],int cnt,char a[]){
    int i;
    for(i=0;i<cnt;i++)
        if(strcmp(list[i].name,a)==0)
            return 1;
    return 0;
}

int main(){
    int i,j,cnt=0,n,sgn=0;
    char a[25];long long b;
    scanf("%d",&n);
    for(i=0;i<n;i++){
        scanf("\n%s%lld",a,&b);
        if(search(list,cnt,a,b))
            continue;
        if(same(list,cnt,a)){
            for(sgn=0,j=0;j<cnt;j++){
                if(strcmp(list[j].name,a)==0)
                  sgn++;
            }
            list[cnt].freq=sgn;
        }
        strcpy(list[cnt].name,a);
        list[cnt++].num=b;
    }
    qsort(list,cnt,sizeof(list[0]),cmp);
    qsort(list,cnt,sizeof(list[0]),cmp);
    for(i=0;i<cnt;i++){
        if(list[i].freq==0)
            printf("%s %lld\n",list[i].name,list[i].num);
        else
            printf("%s_%d %lld\n",list[i].name,list[i].freq,list[i].num);
    }
    return 0;
}