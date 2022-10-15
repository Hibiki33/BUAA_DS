#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000

typedef struct ArcNode {
    int adjvex;
    int arcval;
    struct ArcNode *next;
} ArcNode;

ArcNode Graph[MAX + 5];
int VertexNum, EdgeNum;
int visited[MAX + 5];

void InsertArc(int h, int t, int val) {
    ArcNode *p = (ArcNode *)malloc(sizeof(ArcNode));
    p->adjvex = t;
    p->arcval = val;
    p->next = NULL;
    ArcNode *q = NULL;
    for (q = &Graph[h]; q->next; q = q->next);
    q->next = p;
}

void dfs(int tex, int *path, int cnt) {
    visited[tex] =1;
    if (tex == VertexNum - 1) {
        for (int i = 0; i < cnt; ++i) {
            printf("%d ", path[i]);
        }
        printf("\n");
    } else {
        for (ArcNode *p = Graph[tex].next; p; p = p->next) {
            if (!visited[p->adjvex]) {
                path[cnt++] = p->arcval;
                dfs(p->adjvex, path, cnt);
                cnt--;
            }
        }
    }
    visited[tex] = 0;
}

int main() {
    int a, b, EdgeVal;
    scanf("%d %d", &VertexNum, &EdgeNum);
    for (int i = 0; i < EdgeNum; ++i) {
        scanf("%d %d %d", &EdgeVal, &a, &b);
        InsertArc(a, b, EdgeVal);
        InsertArc(b, a, EdgeVal);
    }
    int path[EdgeNum];
    for (ArcNode *p = Graph[0].next; p; p = p->next) {
        memset(path, 0, sizeof(int) * EdgeNum);
        memset(visited, 0, sizeof(int) * VertexNum);
        visited[0] = 1;
        path[0] = p->arcval;
        dfs(p->adjvex, path, 1);
    }
    return 0;
}