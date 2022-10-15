#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 400
#define BUFSIZE 10000000
#define NAMESIZE 20

struct Graph {
    int val;
    int lineID;
} Map[MAX + 5][MAX + 5];

struct Station {
    char name[NAMESIZE];
    int change;
} station[MAX];

char Begin[NAMESIZE], End[NAMESIZE];
int LineNum = 0, StationSumNum = 0;
int PathStack[MAX], top = -1;
int PriStation[MAX], dist[MAX];

int SearchStation(char *name);
void InitGraph(FILE *fp);
void dijkstra(int bi, int ei);
void creatStack(int bi, int ei);
void printLine(int bi, int ei);

int main() {
    int beginID, endID;
    FILE *fp = fopen("bgstations.txt", "r");
    scanf("%s\n%s", Begin, End);
    InitGraph(fp);
    beginID = SearchStation(Begin);
    endID = SearchStation(End);
    dijkstra(beginID, endID);
    creatStack(beginID, endID);
/*    for (int i = 0; i <= top; i++) {
        printf("%s\n", station[i].name);
    }*/
    printLine(beginID, endID);
    return 0;
}

int SearchStation(char *name) {
    for (int i = 0; i < StationSumNum; i++) {
        if (!strcmp(name, station[i].name)) {
            return i;
        }
    }
    return -1;
}

void InitGraph(FILE *fp) {
    int LineID, StationNum, StationChange;
    char StationName[NAMESIZE];
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            Map[i][j].val = Map[j][i].val = BUFSIZE;
            Map[i][j].lineID = Map[j][i].lineID = 0;
        }
    }
    fscanf(fp, "\n%d", &LineNum);
    for (int i = 0; i < LineNum; i++) {
        fscanf(fp, "\n%d %d", &LineID, &StationNum);
        int lastStaionID = -1;
        for (int j = 0; j < StationNum; j++) {
            fscanf(fp, "\n%s %d", StationName, &StationChange);
            int tmpID = SearchStation(StationName);
            if (tmpID == -1) {
                station[StationSumNum].change = StationChange;
                strcpy(station[StationSumNum].name, StationName);
                if (~lastStaionID) {
                    Map[StationSumNum][lastStaionID].lineID = Map[lastStaionID][StationSumNum].lineID = LineID;
                    Map[StationSumNum][lastStaionID].val = Map[lastStaionID][StationSumNum].val = 1;
                }
                lastStaionID = StationSumNum;
                StationSumNum++;
            } else {
                if (~lastStaionID) {
                    Map[tmpID][lastStaionID].lineID = Map[lastStaionID][tmpID].lineID = LineID;
                    Map[tmpID][lastStaionID].val = Map[lastStaionID][tmpID].val = 1;
                }
                lastStaionID = tmpID;
            }
        }
    }
}

void dijkstra(int bi, int ei) {
    int finished[MAX], res;
    memset(finished, 0, sizeof(int) * MAX);
    for (int i = 0; i < StationSumNum; i++) {
        PriStation[i] = bi;
        dist[i] = Map[bi][i].val;
    }
    finished[bi] = 1;
    dist[bi] = 0;
    for (int i = 0; i < StationSumNum - 1; i++) {
        int min = BUFSIZE;
        for (int j = 0; j < StationSumNum; j++) {
            if (!finished[j] && dist[j] < min) {
                min = dist[j];
                res = j;
            }
        }
        finished[res] = 1;
        if (res == ei) {
            return ;
        }  
        for (int j = 0; j < StationSumNum; j++) {
            int tmp = min + Map[res][j].val;
            tmp = tmp > BUFSIZE ? BUFSIZE : tmp; 
            if (!finished[j] && (tmp < dist[j]) && Map[res][j].lineID) {
                dist[j] = tmp;
                PriStation[j] = res;
            }
        }
    }
}

void creatStack(int bi, int ei) {
    for (int now = ei; now != bi; now = PriStation[now]) {
        PathStack[++top] = now;
    }
    PathStack[++top] = bi;
}

void printLine(int bi, int ei) {
    int cnt = 1, e = PathStack[top - 1], b = e;
    printf("%s-%d", station[bi].name, Map[bi][e].lineID);
    int LineID = Map[bi][e].lineID;
    for (int i = top - 2; i >=0; i--) {
        e = PathStack[i];
        if (LineID != Map[b][e].lineID) {
            LineID = Map[b][e].lineID;
            printf("(%d)-%s-%d", cnt, station[b].name, LineID);
            cnt = 0;
        }
        cnt++;
        b = e;
    }
    printf("(%d)-%s", cnt, station[ei].name);
}
