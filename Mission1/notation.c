#include <stdio.h>
#include <string.h>
#define MAX 10000

char s[MAX],zhengshu[MAX],xiaoshu[MAX]; 

int main(){
	int cnt1=0,cnt2=0,i=0,j,tmp;
	gets(s);
	while(s[i]!='.')
		zhengshu[cnt1++]=s[i++];
	for(cnt2=0,i+=1;s[i]!='\0';cnt2++)
		xiaoshu[cnt2]=s[i++];
	if(cnt1>1){
		printf("%c.",zhengshu[0]);
		for(j=1;j<cnt1;j++)
			printf("%c",zhengshu[j]);
		for(j=0;j<cnt2;j++)
			printf("%c",xiaoshu[j]);
		printf("e%d",cnt1-1);
	}
	else if(cnt1==1&&zhengshu[0]!='0'){
		printf("%c.",zhengshu[0]);
		for(j=0;j<cnt2;j++)
			printf("%c",xiaoshu[j]);
		printf("e0");
	}	
	else{
		for(j=0;j<cnt2;j++)
			if(xiaoshu[j]!='0')break;
		printf("%c",xiaoshu[j]);
		tmp=j+1;
		if(j+1<cnt2){
			printf(".");
			for(j++;j<cnt2;j++)
				printf("%c",xiaoshu[j]);
			printf("e-%d",tmp);
		}
		else
			printf("e-%d",tmp);
	}
	return 0;
}

