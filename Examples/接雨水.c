#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define false 0
#define true 1
typedef int bool;
int height[]={4,2,0,3,2,5};
//******************************************
int stack[20005],top=-1;
int pos0,height0;

void push(int p){stack[++top]=p;}
int pop(){return stack[top--];}
int min(int a,int b){return a<b?a:b;}

int trap(int *height,int heightSize){
	int i,res=0,tmp;
	for(i=0;i<heightSize;i++){
		while(top!=-1&&height[stack[top]]<height[i]){
			tmp=pop();
			if(top==-1)break;
			res+=(i-stack[top]-1)*(min(height[i],height[stack[top]])-height[tmp]);
		}
		push(i);
	}
	return res;
}
//*******************************************
int main(){
    printf("%d",trap(height,6));
    return 0;
}