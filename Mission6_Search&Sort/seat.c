#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
    int id;
    char name[25];
    int seat;
} list[105];

int cmp1(const void *a, const void *b) {
    struct student *aa = (struct student *)a;
    struct student *bb = (struct student *)b;
    if((*aa).seat < (*bb).seat) return -1;
    if((*aa).seat > (*bb).seat) return  1;
    return (*aa).id - (*bb).id;
}

int cmp2(const void *a, const void *b) {
    return (*(struct student *)a).id - (*(struct student *)b).id;
}

int main() {
    int num, hashtable[105];
    scanf("%d", &num);
    memset(hashtable, 0, sizeof(int) * 105);
    FILE *fp1 = fopen("in.txt", "r");
    FILE *fp2 = fopen("out.txt", "w");
    for(int i = 0; i < num; ++i) {
        fscanf(fp1, "%d %s %d\n", &list[i].id, list[i].name, &list[i].seat);
        hashtable[list[i].seat]++;
    }
    qsort(list, num, sizeof(list[0]), cmp1);
    int q = 105;
    int tmp = num - 1;
    for(int i = 1; i <= q; ++i) {
        q = num < list[tmp].seat ? num : list[tmp].seat;
        if(!hashtable[i]) {
            list[tmp--].seat = i;
        }
    }
    qsort(list, num, sizeof(list[0]), cmp1);
    int m = list[num-1].seat;
    for(int i = 1; i < num; ++ i) {
        if(list[i].seat == list[i-1].seat) {
            list[i].seat = (++m);
        }
    }
    qsort(list, num, sizeof(list[0]), cmp2);
    for(int i = 0; i < num; ++i) {
        fprintf(fp2, "%d %s %d\n", list[i].id, list[i].name, list[i].seat);
    }
    fclose(fp1);
    fclose(fp2);
    return 0;
}