#include <stdio.h>
#include <string.h>

int t[25][25];

int func(int i,int j){
	int p1,p2,flag;
    if(t[i][j]==0)return 0;
    for(p1=i,p2=j,flag=1;p1<=i+3;p1++){
    	if(t[i][j]!=t[p1][p2]){
    		flag=0;break;
		}
	}
	if(flag&&(!t[i-1][j]||!t[i+4][j]))
		return t[i][j];
	for(p1=i,p2=j,flag=1;p2<=j+3;p2++){
    	if(t[i][j]!=t[p1][p2]){
    		flag=0;break;
		}
	}
	if(flag&&(!t[i][j-1]||!t[i][j+4]))
		return t[i][j];
	for(p1=i,p2=j,flag=1;p1<=i+3;p1++,p2++){
    	if(t[i][j]!=t[p1][p2]){
    		flag=0;break;
		}
	}
	if(flag&&(!t[i-1][j-1]||!t[i+4][j+4]))
		return t[i][j];
	for(p1=i,p2=j,flag=1;p1<=i+3;p1++,p2--){
    	if(t[i][j]!=t[p1][p2]){
    		flag=0;break;
		}
	}
	if(flag&&(!t[i-1][j+1]||!t[i+4][j-4]))
		return t[i][j];
	return 0;
}

int main(){
    int i,j,a;
    for(i=1;i<=19;i++){
        for(j=1;j<=19;j++)
            scanf("%d",&t[i][j]);
    }
    for(i=1;i<=19;i++){
        for(j=1;j<=19;j++){
            if(func(i,j)){
				a=func(i,j);
                printf("%d:%d,%d",a,i,j);
                return 0;
            }
        }
    } 
    printf("No\n");
    return 0;
}
