#include <stdio.h>
#include <ctype.h>

int iseven(int x){
	if(x%2)return 0;
	return 1;
}

int quickpow(int x,int n){
	if(!n)return 1;
	if(iseven(n))
		return quickpow(x*x,n/2);
	else 
		return quickpow(x*x,n/2)*x;
}//x=x^(n/2)*x^(n/2)=(x*x)^(n/2) or x=x^(n/2)*x^(n/2)*x=(x*x)^(n/2)*x

int main(){
	int x,n;
	int ans;
	scanf("%d%d",&x,&n);
	ans=quickpow(x,n);
	printf("%d",ans);
	atoi()
	return 0;
}