#pragma GCC optimize ("O3")
#pragma pack (16)
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>


struct Page {
    int 

} page[1005];

char s[4700000], stop[5000];
int pos = 1, p = 0, i;
int trie[1200000][26];
int flag = 1, temp;


int main(int argc, char *argv[]) {
    FILE *fp_dictionary = fopen("dictionary.txt", "r");
    FILE *fp_stopwords = fopen("stopwords.txt", "r");
    FILE *fp_article = fopen("article.txt", "r");
    fread(s, sizeof(char), 4700000, fp_dictionary);
    for (i = 0; s[i]; i++) {
/*        if ((s[i] >= 'a' && s[i] <='z') || (s[i] >= 'A' && s[i] <= 'Z')) {
            temp = (s[i] <= 'A') ? s[i] - 'A' : s[i] - 'a';*/
        if (s[i] >= 'a' && s[i] <='z') {
            temp = s[i] - 'a';
            if (!trie[p][temp]) {
                trie[p][temp] = pos++;
            }
            p = trie[p][temp];
        } else {
            p = 0;
        }
    }
    printf("POS 1 SUCCESS");
    fread(stop, sizeof(char), 5000, fp_dictionary);
    for(i = 0; stop[i]; i++) {
        if (stop[i] >= 'a' && s[i] <='z') {
            temp = s[i] - 'a';


        } else {
            
            p = 0;
        }
    }
    
for (i = 0; i < article_len;) {                      //按页操作 假循环
//        if (article[i] == '\n') {         
//            break; /*优化5：不知道为什么article[i]!=0失效了 暂时用首个字符读到\n退出*/                                           
//        } 
        for (j = 0; article[i] != '\n'; i++, j++) {             //获得第一行网页标识号
            page[pagecnt].page_ID[j] = article[i];
        }
        for (i++, p = 0; article[i] != '\f'; i++) {
            if ((article[i] >= 'a' && article[i] <='z') || (article[i] >= 'A' && article[i] <= 'Z')) {
                temp = (article[i] <= 'Z') ? article[i] - 'A' : article[i] - 'a';
                p = trie[p][temp];                              //isalpah() tolower()                                       
            } else {
                if (words[p][0]) {                              //如果符合条件
                    page[pagecnt].wordsum++;                    //网页总词数增加
                    if (words[p][1]) {                          //如果是关键词
                        page[pagecnt].keyword[words[p][1]]++;   //当前网页该关键词数增加
                    }
                }
                p = 0;
            }                                                   //TF(关键词频)无需提前求出
            if (!p) {                                           //若当前长度下该词不存在 跳过该词
                while ((article[i] >= 'a' && article[i] <='z') || (article[i] >= 'A' && article[i] <= 'Z')) {
                    i++;
                }
            }                                         
        } /*优化6：能否减少判断的次数*/
        for (j = 2; j < argc; j++) {
            if (page[pagecnt].keyword[j]) {
                key[j].DN++;
            }
        }
        page[pagecnt].page_num = pagecnt + 1;
        pagecnt++;
        while (article[i] == '\f' || article[i] == '\n' || article[i] == '\f') {
            i++;
        }
    }




    return 0;
}
