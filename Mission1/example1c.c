#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 100000

int shuzi[MAX],sum,flag=1;
char fuhao[MAX],s[MAX];

int main(){
	int i=0,j=0,k,m;
	gets(s);
	for(k=0;k<strlen(s);k++){
		if(isdigit(s[k])){
			shuzi[i]=shuzi[i]*10+s[k]-'0';
			if(!isdigit(s[k+1]))i++;
		}
		else if(s[k]=='*'||s[k]=='/'||s[k]=='+'||s[k]=='-'){
			fuhao[j++]=s[k];
		}
	}
	for(m=0;m<j;m++){
		if(fuhao[m]=='+')flag=1;
		else if(fuhao[m]=='-')flag=0;
        else if(fuhao[m]=='*'){
        	shuzi[m+1]*=shuzi[m];
        	shuzi[m]=0;
        	if(flag)
        		fuhao[m]='+';
        	else 
        		fuhao[m]='-';
		}
		else if(fuhao[m]=='/'){
			shuzi[m+1]=shuzi[m]/shuzi[m+1];
        	shuzi[m]=0;
        	if(flag)
        		fuhao[m]='+';
        	else 
        		fuhao[m]='-';
		}
    }
    sum+=shuzi[0];
    for(m=0;m<j;m++){
    	if(fuhao[m]=='+')
    		sum+=shuzi[m+1];
    	else if(fuhao[m]=='-')
    		sum-=shuzi[m+1];
	}
    printf("%d",sum);
	return 0;
}

