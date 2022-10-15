#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NHASH 3001
#define MULT  37

char Dictionary[3500][20];
int dic = 0;
struct {
    int pos;
    int num;
} Index[26];

typedef struct node {
    char key[20];
    struct node *next;
} node, *LinkList;

typedef struct {
    LinkList data;
} MyHashMap;
MyHashMap *map;

void InitAll(FILE *fp);
void SequenceSearch(char *target);
void BinarySearch(char *target);
void IndexSearch(char *target);
void bisearch(char *target, int low, int high);
void HashSearch(char *target);

void listpush(LinkList head, char *key);
void listdelete(LinkList head, char *key);
int listfind(LinkList head, char *key, int *cnt);

unsigned int hash(char *str);
MyHashMap* myHashMapCreate();
void myHashMapPut(MyHashMap *obj, char *key);

int main() {
    FILE *fp = fopen("dictionary3000.txt", "r");
    InitAll(fp);
    char target[20];
    int order;
    scanf("%s %d", target, &order);
    switch(order) {
    case 1: SequenceSearch(target); break;
    case 2: BinarySearch(target);   break;
    case 3: IndexSearch(target);    break;
    case 4: HashSearch(target);     break;
    default: break;
    }
    fclose(fp);
    return 0;
}

void InitAll(FILE *fp) {
    char tmp[20];
    map = myHashMapCreate();
    for(int i = 0; i < 26; ++i) {
        Index[i].pos = 0;
        Index[i].num = 0;
    }
    while(~ fscanf(fp, "%s", tmp)) {
        if(!Index[tmp[0] - 'a'].pos) {
            Index[tmp[0] - 'a'].pos = dic;
        }
        Index[tmp[0] - 'a'].num++;
        strcpy(Dictionary[dic++], tmp);
        myHashMapPut(map, tmp);
    }
}

void SequenceSearch(char *target) {
    for(int i = 0; i < dic; ++i) {
        if(strcmp(target, Dictionary[i]) == 0) {
            printf("1 %d", i + 1);
            return;
        }
        else if(strcmp(target, Dictionary[i]) < 0) {
            printf("0 %d", i + 1);
            return;
        }
    }
    printf("0 %d", dic);
}

void BinarySearch(char *target) {
    bisearch(target, 0, dic - 1);
}

void IndexSearch(char *target) {
    int low = Index[target[0] - 'a'].pos;
    int high = Index[target[0] - 'a'].pos + Index[target[0] - 'a'].num - 1;
    bisearch(target, low, high);
}

void bisearch(char *target, int low, int high) {
    int cnt = 0, mid;
    while(low <= high) {
        cnt++;
        mid = (low + high) / 2;
        if(strcmp(target, Dictionary[mid]) == 0) {
            printf("1 %d", cnt);
            return;
        }
        else if(strcmp(target, Dictionary[mid]) > 0) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    printf("0 %d", cnt);
}

void HashSearch(char *target) {
    int h = hash(target), cnt = 0;
    int res = listfind(&(map->data[h]), target, &cnt);
    printf("%d %d", res, cnt);
}

unsigned int hash(char *str) {
    unsigned int h = 0;
    char *p;
    for(p=str; *p != '\0'; p++) {
        h = MULT * h + *p;
    }
    return h % NHASH;
}

void listpush(LinkList head, char *key) {
    LinkList p = (LinkList)malloc(sizeof(node));
    strcpy(p->key, key);
    p->next = head->next;
    head->next = p;
}

int listfind(LinkList head, char *key, int *cnt) {
    for(LinkList p = head; p->next; p = p->next) {
        (*cnt)++;
        if(strcmp(p->next->key, key) == 0) {
            return 1;    
        }
    }
    return 0;
}

MyHashMap *myHashMapCreate() {
    MyHashMap *res = (MyHashMap *)malloc(sizeof(MyHashMap));
    res->data = (LinkList)malloc(sizeof(node) * NHASH);
    for(int i = 0; i < NHASH; i++){
        memset(res->data[i].key , 0, sizeof(char) * 20);
        res->data[i].next = NULL;
    }
    return res;
}

void myHashMapPut(MyHashMap *obj, char *key) {
    int h = hash(key);
    listpush(&(obj->data[h]), key);
}
