#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct{
    char ch;
    int line;
}stack[205];

int p=-1,pa=0,linecnt=0;
char s[205],ans[505],s0[205];
int flagduo=1;

char pop(){return stack[p--].ch;}
void push(char x,int l){stack[++p].ch=x;stack[p].line=l;}

void work(){
    int i=0,j=0;
    for(i=0;i<strlen(s0);i++){
        if(s0[i]=='*'&&s0[i+1]=='/'){
            flagduo=1;
            i+=2;    
        }
        if(flagduo==1){
            if(s0[i]=='/'&&s0[i+1]=='/')break;
            else if(s0[i]=='"'){
                for(i++;s0[i]!='"';i++);
                continue; 
            }
            else if(s0[i]==39){
                for(i++;s0[i]!=39;i++);
                continue; 
            } 
            else if(s0[i]=='/'&&s0[i+1]=='*'){
                flagduo=0;
                continue;    
            }
            else
                s[j++]=s0[i];
        }  
    }
    s[j]='\0';
}

int main(){
    int i,tmp;
    char tmpchar;
    FILE *in=fopen("example.c","r");
    while(fgets(s0,200,in)!=NULL){
        linecnt++;
        work(); 
        for(i=0;i<strlen(s);i++){
            switch(s[i]){
            case '(':
                push(s[i],linecnt);
                ans[pa++]=s[i];
                break;
            case '{':
                tmp=stack[p].line;
                tmpchar=stack[p].ch;
                if(tmpchar=='('){
                    printf("without maching '%c' at line %d",tmpchar,tmp);
                    return 0;
                }
                else{
                    push(s[i],linecnt);
                    ans[pa++]=s[i];
                    break;
                }
            case ')':
                ans[pa++]=s[i];
                if(pop()!='('){
                    printf("without maching '%c' at line %d",s[i],linecnt);
                    return 0;
                }
                break;
            case '}':
                ans[pa++]=s[i];
                if(pop()!='{'){
                    printf("without maching '%c' at line %d",s[i],linecnt);
                    return 0;
                }
                break;
            default:break;
            }
        }
    }
    if(p==0){
        printf("without maching '%c' at line %d",stack[0].ch,stack[0].line);
        return 0;
    }
    ans[pa]='\0';
    puts(ans);
    fclose(in);
    return 0;
}