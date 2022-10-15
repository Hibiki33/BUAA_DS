#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100005

int n, numsSize;
int pushed[MAX];
int poped[MAX];
int stack[MAX], top = -1;

int main() {
    scanf("%d", &n);
    for (int t = 0; t < n; t++) {
        int cnt = 0;
        scanf("%d", &numsSize);
        memset(stack, 0, numsSize);
        for (int i = 0; i < numsSize; i++) {
            scanf("%d", pushed + i);
        }
        for (int i = 0; i < numsSize; i++) {
            scanf("%d", poped + i);
        }
        for (int i = 0; i < numsSize; i++) {
            stack[++top] = pushed[i];
            while(~top && stack[top] == poped[cnt]) {
                top--;
                cnt++;
            }
        }
        if (cnt == numsSize) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
        top = -1;
    }
    return 0;
}