#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10000

int Strstr_KMP(char *s,char *t,int *next,int pos){
	//求子串在主串第pos个字符后的位置
	int i=pos,j=1;
//	printf("%d %d %d\n",strlen(s),strlen(t),*(next+3));
	while(i<=strlen(s+1)&&j<=strlen(t+1)){
		if((!j)||*(s+i)==*(t+j)){
			++i;++j;
		}
		else 
			j=*(next+j);
	}
	if(j>strlen(t))
		return i-strlen(t+1); 
	else
		return 0;
}

void get_Next(char *t,int *next){
	int i=1,j=0;
	next[1]=0;
	while(i<strlen(t+1)){
		if((!j)||*(t+i)==*(t+j)){
			++i;++j;
			if(*(t+i)!=*(t+j))
				*(next+i)=j;
			else 
				*(next+i)=*(next+j);
		}
		else
			j=*(next+j);
	}
}

int main(){
	char s[MAX+5];
	char substring[MAX+5];
	int pos,ans,next[MAX+5];
	gets(s+1);
	gets(substring+1);
	scanf("%d",&pos);
	get_Next(substring,next);
	ans=Strstr_KMP(s,substring,next,pos);
	printf("%d",ans);
	return 0;
}