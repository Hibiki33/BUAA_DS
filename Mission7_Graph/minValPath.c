#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef struct ArcNode {
    int arcnum;
    int adjvex;
    int arcval;
    struct ArcNode *next;
} ArcNode;
typedef struct VertexNode {
    ArcNode *firstnode;
} VertexNode;

VertexNode Graph[MAX + 5];
int VertexNum, EdgeNum, visited[MAX + 5], ans[MAX + 5], k;

struct Arc{
    int arcnum;
    int arcval;
} closedge[MAX + 5];

int chooseMinArc() {
    int k = 0;
    for (int j = 1; j < VertexNum; j++) {
        if (closedge[j].arcnum && (!k || closedge[k].arcval > closedge[j].arcval)) {
            k = j;
        }
    }
    return k;
}

void InsertArc(int h, int num, int t, int val) {
    ArcNode *p = (ArcNode *)malloc(sizeof(ArcNode));
    p->arcnum = num;
    p->adjvex = t;
    p->arcval = val;
    p->next = NULL;
    if (!Graph[h].firstnode) {
        Graph[h].firstnode = p;
    } else {
        ArcNode *q = NULL;
        for (q = Graph[h].firstnode; q->next; q = q->next);
        q->next = p;
    }
}

int cmp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

int main() {
    int num, a, b, val, pa = 0, sum = 0;
    scanf("%d %d", &VertexNum, &EdgeNum);
    for (int i = 0; i < EdgeNum; i++) {
        scanf("%d %d %d %d", &num, &a, &b, &val);
        InsertArc(a, num, b, val);
        InsertArc(b, num, a, val);
    }
    for (ArcNode *p = Graph[0].firstnode; p; p = p->next) {
        closedge[p->adjvex].arcnum = p->arcnum;
        closedge[p->adjvex].arcval = p->arcval;
    }
    visited[0] = 1;
    for (int i = 1; i < VertexNum; i++) {
        int k = chooseMinArc();
        visited[k] = 1;
        ans[pa++] = closedge[k].arcnum;
        sum += closedge[k].arcval;
        closedge[k].arcnum = 0;
        closedge[k].arcval = 0;
        for (ArcNode *p = Graph[k].firstnode; p; p = p->next) {
            if (!visited[p->adjvex] && (p->arcval < closedge[p->adjvex].arcval || !closedge[p->adjvex].arcnum)) {
                closedge[p->adjvex].arcnum = p->arcnum;
                closedge[p->adjvex].arcval = p->arcval;
            }
        }
    }
    printf("%d\n",sum);
    qsort(ans, pa, sizeof(int), cmp);
    for (int i = 0; i < pa; i++) {
        printf("%d ", ans[i]);
    }
    return 0;
}