#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char s1[1000000], s2[1000000];


int main() {
    FILE *fp1 = fopen("results.txt", "r");
    FILE *fp2 = fopen("results(example).txt", "r");
    fread(s1, sizeof(char), 1000000, fp1);
    fread(s2, sizeof(char), 1000000, fp2);
    int a = strcmp(s1, s2);
    printf("%d", a);
}