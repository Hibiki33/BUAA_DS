#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char a[10000],b[10000],contain[10000];
int i,j,k,la=0,lb=0,lc=0,sgn=0;
char charac;

int main(){
    gets(a);
    gets(b);
    FILE *in=fopen("filein.txt","r");
    FILE *out=fopen("fileout.txt","w");
    la=strlen(a);  
    for(i=0;i<la;i++)
        a[i]=tolower(a[i]);
    lb=strlen(b);
    for(i=0;i<lb;i++)
        b[i]=tolower(b[i]);
    charac=fgetc(in);
    i=0;
    while(charac!=EOF){
        contain[i++]=charac;
        charac=fgetc(in);
    }
    contain[i]='\0';
    for(i=0;i<strlen(contain);i++){
        sgn=1;
        if(tolower(contain[i])==tolower(a[0])){
            for(j=1;j<la;j++)
                if(tolower(contain[i+j])!=tolower(a[j]))
                    sgn=0;
            if(sgn){
                for(k=0;k<lb;k++)
                    fputc(b[k],out);
                i+=la-1;
            }
            else 
                fputc(contain[i],out);          
        }
        else 
            fputc(contain[i],out);
    }
    fclose(in);
    fclose(out);
    return 0;
}