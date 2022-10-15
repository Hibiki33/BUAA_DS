#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define false 0
#define true 1
typedef int bool;
char s[]={')','(',')','(',')',')'};
//******************************************
int max(int a,int b){return a>b?a:b;}
int longestValidParentheses(char *s){
    int i,size=strlen(s),res=0;
    int stack[30005],top=0;
    stack[top]=-1;
    for(i=0;i<size;i++){
        if(s[i]=='(')
            stack[++top]=i;
        else{
            stack[top--]=0;
            if(top==-1)
                stack[++top]=i;
            else
                res=max(i-stack[top],res);
        }
    }
    return res;
}
//*******************************************
int main(){
    printf("%d",longestValidParentheses(s));
    return 0;
}