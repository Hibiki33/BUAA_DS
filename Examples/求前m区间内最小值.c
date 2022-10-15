#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 2000005

int n, m;
int front = 0, rear = -1, dequeue[MAX];
int nums[MAX], i = 0;

int main() {
    scanf("%d %d", &n, &m);
    scanf("%d", nums + i);
    dequeue[++rear] = i;
    printf("0\n");
    for (i = 1; i < n; i++) {
        printf("%d\n", nums[dequeue[front]]);
        scanf("%d", nums + i);
        if (i - m == dequeue[front]) {
            front++;
        }
        while (rear >= front && nums[i] < nums[dequeue[rear]]) {
            rear--;
        }
        dequeue[++rear] = i;    
        /*
        if (front == rear) {
            queue[++rear] = i;
        }
        else if (nums[i] <= nums[queue[rear]]) {
            queue[++rear] = i;
        }
        if (i - m == queue[front] || nums[queue[front]] >= nums[queue[rear]]) {
            front = rear;
        }
        */
        //printf("%d\n", queue[front]);
    }
    return 0;
}