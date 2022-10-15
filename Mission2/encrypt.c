#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

char a[30][2],input[55],contain[1000];
char alptab[30]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
char tmp;

int main(){
    int i=0,j=0,k=0,flag;
    FILE *fp1=fopen("encrypt.txt","r");
    FILE *fp2=fopen("output.txt","w");
    for(i=0;i<26;i++)
        a[i][0]=alptab[i];

    gets(input);
    for(i=0;i<strlen(input);i++)
        if(alptab[input[i]-'a']!=0){
            a[j++][1]=input[i];
            alptab[input[i]-'a']=0;
        }
    for(k=25;k>=0;k--)
        if(alptab[k]!=0)
            a[j++][1]=alptab[k];

    i=0;tmp=fgetc(fp1);
    while(tmp!=EOF){
        contain[i++]=tmp;
        tmp=fgetc(fp1);
    }
    contain[i]='\0';

    for(i=0;i<strlen(contain);i++){
        if(iswalpha(contain[i]))
            fputc(a[contain[i]-'a'][1],fp2);
        else
            fputc(contain[i],fp2);
    }

    fclose(fp1);
    fclose(fp2);
    return 0;
}