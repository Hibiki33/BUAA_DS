#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 5000
#define N 1800

int step[MAX+5][N+5];

int main(){
	int i,j,flag=1;
	int n;
	scanf("%d",&n);
	if(n>=0&&n<=2){
		printf("%d",n);
		return 0;
	}
	step[0][1]=0;
	step[1][1]=1;
	step[2][1]=2;
	for(i=3;i<=MAX+1;i++){
		for(j=1;j<N;j++)
			step[i][j]=step[i-1][j]+step[i-2][j];
		for(j=1;j<N;j++)
			while(step[i][j]>9){
				step[i][j+1]++;
				step[i][j]-=10;
			}
	}
	for(i=N-1;i>1;i--){
		if(flag&&step[n][i]==0)
			continue;
		else if(flag&&step[n][i]!=0)
			flag=0;
		printf("%d",step[n][i]);
	}
	printf("%d",step[n][1]);
	return 0;
}