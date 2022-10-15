#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    char name[50];
    char author[20];
    char pub[30];
    char date[10];
}BOOK;
BOOK book[505];

int cmp(const void *a,const void *b){
    BOOK *aa=(BOOK *)a;
    BOOK *bb=(BOOK *)b;
    return strcmp(aa->name,bb->name); 
}

int main(){
    int i=0,j,k,m,len,cnt;
    FILE *fp1=fopen("books.txt","r");
    FILE *fp2=fopen("ordered.txt","w");
    char tmp[150];
    while(fgets(tmp,150,fp1)!=NULL){
        for(j=0,k=0;tmp[j]!=' ';j++,k++)
            book[i].name[k]=tmp[j];
        for(j++,k=0;tmp[j]!=' ';j++,k++)
            book[i].author[k]=tmp[j];
        for(j++,k=0;tmp[j]!=' ';j++,k++)
            book[i].pub[k]=tmp[j];
        for(j++,k=0;j<strlen(tmp);j++,k++) 
            book[i].date[k]=tmp[j];  
        i++;
    }
    len=i;
    qsort(book,len,sizeof(book[0]),cmp);   
    
    while(1){
    	int order;
    	char str[150];
        scanf("\n%d\n",&order);
        if(!order)break;
        gets(str);
        cnt=0;
        switch(order){
        case 1:
            for(j=0,k=0;str[j]!=' ';j++,k++)
                book[len].name[k]=str[j];
            for(j++,k=0;str[j]!=' ';j++,k++)
                book[len].author[k]=str[j];
            for(j++,k=0;str[j]!=' ';j++,k++)
                book[len].pub[k]=str[j];
            for(j++,k=0;j<strlen(str);j++,k++) 
                book[len].date[k]=str[j];  
            len++;
            qsort(book,len,sizeof(book[0]),cmp);  
            break;
        case 2:
            for(i=0;i<len;i++)
                if(strstr(book[i].name,str)!=NULL)
                    printf("%-50s%-20s%-30s%-10s\n",book[i].name,book[i].author,book[i].pub,book[i].date);
            break;
        case 3:
            for(i=0;i<len;i++)
                if(strstr(book[i].name,str)!=NULL){
                    book[i].name[0]='z'+1;
                    cnt++;
                }
            qsort(book,len,sizeof(book[0]),cmp);
            len-=cnt;
            break;
        default:break;
        }
        m++;
    }
    for(i=0;i<len;i++){
        fprintf(fp2,"%-50s%-20s%-30s%-10s\n",book[i].name,book[i].author,book[i].pub,book[i].date);
    }

    fclose(fp1);
    fclose(fp2);
    return 0;
}
