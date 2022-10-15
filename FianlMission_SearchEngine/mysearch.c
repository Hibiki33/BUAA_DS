/**
 * Data Structures Great Assignment
 * Search Engine
 * Created by Wjj
 */

#pragma GCC optimize ("O3")                                     //手动开启O3优化
#pragma pack (16)                                               //存储以16字节为单位
#pragma once                                                    //头文件只打开一次
#include <stdio.h>
#include <stdlib.h>
#include <math.h> /*优化1：能否直接实现log10从而减少打开头文件的时间*/

struct Page {
    char page_ID[20];                                           //网页标识号
    int page_num;                                               //网页对应编号
    int wordsum;                                                //该网页总词数
    int keyword[20];                                            //关键词在该文档中出现次数
    double sim;                                                 //相关度
} page[16005];                                                  

struct Key {
    int DN;                                                     //出现该单词的文档数
    double IDF;                                                 //逆文档频率
} key[20];                                                      //k对应argv[]编号

int NUM = 0;                                                    
int trie[1200000][26];                                          //字典树 (1128344)
int words[1200000][2];                                          //0列单词表 1列关键词映射
int pos = 1, pagecnt;                                           //字典树编号 网页编号
int p, i, j, temp, sgn;
char word_dictionary[55], word_stopwords[15];                   //字典单词 停用词单词
char article[100000000];                                        //储存网页集合
int article_len;                                                //网页总长度

int cmp(const void *a, const void *b);

int main(int argc, char *argv[]) {
    FILE *fp_article = fopen("article.txt", "r");
//读入字典单词生成字典树
    freopen("dictionary.txt", "r", stdin);
    while (~scanf("%s", word_dictionary)) {     
        for (i = 0, p = 0; word_dictionary[i]; i++) {
            temp = word_dictionary[i] - 'a';
            if (!trie[p][temp]) {
                trie[p][temp] = pos++;
            }
            p = trie[p][temp];
        }
        words[p][0] = 1;
    } /*优化2：用fread统一读是否比fscanf分行读更快*/
    fclose(stdin);
//读入停用词从单词表中删去
    freopen("stopwords.txt", "r", stdin);
    while (~scanf("%s", word_stopwords)) {       
        for (i = 0, p = 0; word_stopwords[i]; i++) {
            p = trie[p][word_stopwords[i] - 'a'];
            if (!p) {
                break;
            }
        }   
        words[p][0] = 0;
    } /*优化3：同优化2*/
    fclose(stdin);
//从命令行参数计算NUM值    
    for (i = 0; argv[1][i]; i++) {                              
        NUM = NUM * 10 + argv[1][i] - '0'; 
    } 
//建立字典树编号到关键词序号的映射
    for (i = 2; i < argc; i++) {                                
        for (j = 0, p = 0; argv[i][j]; j++) {
            p = trie[p][argv[i][j] - 'a'];
            if (!p) {                                           //一旦为0直接退出
                break;
            }
        }                                                       //暂时不处理 关键词是停用词
        words[p][1] = i;                                        //编号0没有对应单词 不影响
    } /*优化4：能否减少比较的次数*/
//处理网页集合
    article_len =  fread(article, sizeof(char), 100000000, fp_article);
    fclose(fp_article);
    for (i = 0, p = 0; i < article_len; i++) {
        if (!sgn) {
            for (j = 0; article[i] != '\n' && article[i] != '\r'; i++, j++) {         
                page[pagecnt].page_ID[j] = article[i];          //获得第一行网页标识号
            }
            if (page[pagecnt].page_ID[0] != '\0') {
                sgn = 1;
            }  
            continue;
        }
        if ((article[i] >= 'a' && article[i] <='z') || (article[i] >= 'A' && article[i] <= 'Z')) {
                temp = (article[i] <= 'Z') ? article[i] - 'A' : article[i] - 'a';
                p = trie[p][temp];                              //isalpah() tolower()                                       
        } else {
            if (words[p][0]) {                                  //如果符合条件
                page[pagecnt].wordsum++;                        //网页总词数增加
                if (words[p][1]) {                              //如果是关键词
                    page[pagecnt].keyword[words[p][1]]++;       //当前网页该关键词数增加
                }
            }
            p = 0;
            if (article[i] == '\f') {                           //开始下一页
                for (j = 2; j < argc; j++) {
                    if (page[pagecnt].keyword[j]) {
                        key[j].DN++;
                    }
                }
                page[pagecnt].page_num = pagecnt + 1;
                pagecnt++;
                sgn = 0;
            }
        }
        if (!p) {                                               //若当前长度下该词不存在 跳过该词
            while ((article[i] >= 'a' && article[i] <='z') || (article[i] >= 'A' && article[i] <= 'Z')) {
                i++;
            }
        }  
    }
    for (j = 2; j < argc; j++) {                                //最后一次翻页手动进行
        if (page[pagecnt].keyword[j]) {
            key[j].DN++;
        }
    }
    page[pagecnt].page_num = pagecnt + 1;
    pagecnt++;
//计算每个单词的逆文档频率
    for (i = 2; i < argc; i++) {
        if (key[i].DN) {
            key[i].IDF = log10(((double)pagecnt) / ((double)key[i].DN));
        }
    } 
//计算每个文档的相关度
    for (i = 0; i < pagecnt; i++) {
        for (j = 2; j < argc; j++) {
            page[i].sim += ((double)page[i].keyword[j]) / ((double)page[i].wordsum) * 100 * key[j].IDF;
        }
    }
//排序并输出结果
    qsort(page, pagecnt, sizeof(page[0]), cmp);
    for (i = 0; i < 5; i++) {
        if (page[i].sim > 1e-6) {
            printf("%.6f %d %s\r\n", page[i].sim, page[i].page_num, page[i].page_ID);
        } else {
            break;
        }
    }
    freopen("results.txt", "w", stdout);
    for (i = 0; i < NUM; i++) {
        if (page[i].sim > 1e-6) {
            printf("%.6f %d %s\r\n", page[i].sim, page[i].page_num, page[i].page_ID);
        } else {
            break;
        }
    }
    fclose(stdout);
    return 0;
}

int cmp(const void *a, const void *b) {
    struct Page *aa = (struct Page *)a, *bb = (struct Page *)b;
    if ((*aa).sim - (*bb).sim < 1e-6 && (*bb).sim - (*aa).sim < 1e-6) {
        return (*aa).page_num - (*bb).page_num;
    } else {
        if ((*aa).sim > (*bb).sim) {
            return -1;
        } else {
            return 1;
        }
    }
}
