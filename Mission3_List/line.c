#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef struct line{
    int x1,y1;
    int x2,y2;
    int length;
}line;

int n;
line a[MAX+5];

int cmp1(const void *c,const void *b){
    line *aa=(line *)c;
    line *bb=(line *)b;
    if(aa->x1>bb->x1) return 1;
    if(aa->x1<bb->x1) return -1;
    if(aa->y1>bb->y1) return 1;
    if(aa->y1<bb->y1) return -1;
}
int cmp2(const void *c,const void *b){
    line *aa=(line *)c;
    line *bb=(line *)b;
    if(aa->length>bb->length) return -1;
    return 1;
}

int main(){
    int i,j;
    scanf("%d",&n);
    for(i=0;i<n;i++){
        scanf("\n%d%d%d%d",&(a[i].x1),&(a[i].y1),&(a[i].x2),&(a[i].y2));
        a[i].length=1;
    }
    qsort(a,n,sizeof(a[0]),cmp1);
    for(i=0;i<n;i++){
        for(j=i+1;j<n;j++){
            if(j==i) continue;
            if(a[i].x1==0&&a[i].x2==0)
                continue;
            if(a[i].x2==a[j].x1&&a[i].y2==a[j].y1){
                a[i].x2=a[j].x2;
                a[i].y2=a[j].y2;
                a[i].length+=a[j].length;
                memset(&a[j],0,sizeof(a[j]));
            }
        }
    }
    qsort(a,n,sizeof(a[0]),cmp2);
    printf("%d %d %d",a[0].length,a[0].x1,a[0].y1);
    return 0;
}