#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

int Graph[MAX + 5][MAX + 5];
int VertexNum, EdgeNum;
int visited[MAX + 5];

int max(int a, int b) {
    return a > b ? a : b;
}
int min(int a, int b) {
    return a < b ? a : b;
}

void dfs(int v) {
    visited[v] = 1;
    printf("%d ", v);
    for (int i = 0; i < VertexNum; i++) {
        if (i == v) {
            continue;
        }
        if (!visited[i] && Graph[v][i]) {
            dfs(i);
        }
    }
}

void bfs() {
    int queue[VertexNum + 5];
    memset(queue, 0, sizeof(int) * VertexNum);
    int front = 0, rear = -1;
    queue[++rear] = 0;
    visited[0] = 1;
    while (front <= rear) {
        for (int i = 0; i < VertexNum; ++i) {
            if (i == queue[front]) {
                continue;
            }   
            if (!visited[i] && Graph[queue[front]][i]) {
                queue[++rear] = i;
                visited[i] = 1;
            }
        }
        printf("%d ", queue[front]);
        front++;
    }
}

int main() {
    int a, b, delval;
    scanf("%d %d", &VertexNum, &EdgeNum);
    for (int i = 0; i < EdgeNum; ++i) {
        scanf("%d %d", &a, &b);
        Graph[min(a, b)][max(a, b)] = 1;
        Graph[max(a, b)][min(a, b)] = 1;
    }
    scanf("%d", &delval);
    memset(visited, 0 ,sizeof(int) * VertexNum);
    dfs(0);printf("\n");
    memset(visited, 0 ,sizeof(int) * VertexNum);
    bfs();printf("\n");
    for (int i = 0; i < VertexNum; ++i) {
        Graph[i][delval] = 0;
    }
    for (int i = 0; i < VertexNum; ++i) {
        Graph[delval][i] = 0;
    }
    memset(visited, 0 ,sizeof(int) * VertexNum);
    dfs(0);printf("\n");
    memset(visited, 0 ,sizeof(int) * VertexNum);
    bfs();
    return 0;
}