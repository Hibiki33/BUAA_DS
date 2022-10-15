#include <stdio.h>
#include <string.h>

/*
int n;
int a[15]={1,2,3,4,5,6,7,8,9,10};
int flag[15],ans[15];

void func(int a[],int flag[],int i,int ans[]){
	int j,k;
	if(i==n){
		for(k=0;k<n;k++)
			printf("%d ",ans[k]);
		printf("\n");
	}
	else{
		for(j=0;j<n;j++){
			if(flag[j]==0){
				ans[i]=a[j];
				flag[j]=1;
				func(a,flag,i+1,ans);
				flag[j]=0;
			}
		}
	}
}

int main(){
	scanf("%d",&n);
	func(a,flag,0,ans);
	return 0;
}
*/
int n;
int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

void chan(int a[], int low, int high) {
	int i = low, j = high, tmp;
	for (; i < j; i++, j--) {
		tmp = a[j];
		a[j] = a[i];
		a[i] = tmp;
	}
}

void pri(int a[], int n) {
	int i;
	for (i = 0; i < n; i++)
		printf("  %d  ", a[i]);
	printf("\n");
}
void func(int a[], int n) {
	int tmp, low, high, i, rmin = 11, aa;
	for (i = n - 1; a[i - 1] > a[i] && i > 0; i--) {}
	if (!i)
		return;
	for (tmp = i, low = i; tmp < n; tmp++) {
		if (a[tmp] < rmin && a[tmp] > a[low - 1]) {
			rmin = a[tmp];
			high = tmp;
		}
	}
	aa = a[high];
	a[high] = a[low - 1];
	a[low - 1] = aa;
	chan(a, low, n - 1);
	pri(a, n);
	func(a, n);
}

int main() {
	scanf("%d", &n);
	pri(a, n);
	func(a, n);
	return 0;
}
