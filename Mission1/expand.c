#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>

#define true 1
#define false 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX 10000

typedef int Status;
typedef int ElemType;

char s[MAX];

void func(char a,char b){
	char j;
	printf("%c",a);
	if(a<b-1)
		for(j=a+1;j<=b-1;j++)
			printf("%c",j);
	else
		printf("-");
} 

int main(){
	int i;
	gets(s);
	for(i=0;i<strlen(s)-2;i++){
		if(s[i+1]!='-')
			printf("%c",s[i]);
		else{
			if(isdigit(s[i])){
				if(isdigit(s[i+2])){
					func(s[i],s[i+2]);
					i++;
				}
				else
					printf("%c",s[i]);	
			}
			else if(islower(s[i])){
				if(islower(s[i+2])){
					func(s[i],s[i+2]);
					i++;
				}
				else
					printf("%c",s[i]);
			}
			else if(isupper(s[i])){
				if(isupper(s[i+2])){
					func(s[i],s[i+2]);
					i++;
				}
				else
					printf("%c",s[i]);
			}
		}	
	}
	for(;i<strlen(s);i++)
		printf("%c",s[i]);
	return 0;
}

