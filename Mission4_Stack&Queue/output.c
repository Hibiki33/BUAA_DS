#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char s[105],ct[50];
int m=0,n=0;
int flag=0;

int main(){
    int i=1,j=0,k=0;
    fgets(ct,50,stdin);
    scanf("\n");
//    gets(s);
//    scanf("%s",s);
    fgets(s,100,stdin);
    int len=strlen(s);
    if(s[len-1]=='\n'){
        s[len-1]=0;
        len--;
    }
//    printf("%d",len);
//    puts(ct);
//    puts(s);
    if(ct[i]=='['){
        while(ct[i]!=']')i++;
        i++;
    }
    if(ct[i]=='-'){
        flag=-1;
        i++;  
    }
    else flag=1;
    while(isdigit(ct[i])){
        m=m*10+ct[i]-'0';
        i++;
    }
    if(ct[i]==':')i++;
    while(isdigit(ct[i])){
        n=n*10+ct[i]-'0';
        i++;
    }
//    printf("%d %d %d",flag,m,n);
    if(m>len){
        if(n<=len){
            printf("%s",s);
        }
        else{
            if(flag==1){
                printf("%s",s);
                while(j<n-len){
                    printf("#");
                    j++;    
                }
            }
            else if(flag==-1){
                while(j<n-len){
                    printf("#");
                    j++;    
                }
                printf("%s",s);
            }
        }
    }
    else if(m<=len){
        s[m]='\0';
        len=m;
        if(n<=len){
            printf("%s",s);
        }
        else{
            if(flag==1){
                printf("%s",s);
                while(j<n-len){
                    printf("#");
                    j++;    
                }
            }
            else if(flag==-1){
                while(j<n-len){
                    printf("#");
                    j++;    
                }
                printf("%s",s);
            }
        }
    }
    return 0;
}