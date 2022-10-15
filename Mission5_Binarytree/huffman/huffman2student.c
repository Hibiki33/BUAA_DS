//文件压缩-Huffman实现
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 32

struct tnode {					//Huffman树结构
	char c;		
	int weight;					//树节点权重，叶节点为字符和它的出现次数
	struct tnode *left,*right;
} ; 
int Ccount[128]={0};			//存放每个字符的出现次数，如Ccount[i]表示ASCII值为i的字符出现次数 
struct tnode *Root=NULL; 		//Huffman树的根节点
char HCode[128][MAXSIZE]={{0}}; //字符的Huffman编码，如HCode['a']为字符a的Huffman编码（字符串形式） 
int Step=0;						//实验步骤 
FILE *Src, *Obj;
	
void statCount();				//步骤1：统计文件中字符频率
void createHTree();				//步骤2：创建一个Huffman树，根节点为Root 
void makeHCode();				//步骤3：根据Huffman树生成Huffman编码
void atoHZIP(); 				//步骤4：根据Huffman编码将指定ASCII码文本文件转换成Huffman码文件

void print1();					//输出步骤1的结果
void print2(struct tnode *p);	//输出步骤2的结果 
void print3();					//输出步骤3的结果
void print4();					//输出步骤4的结果

int main()
{
	if((Src=fopen("input.txt","r"))==NULL) {
		fprintf(stderr, "%s open failed!\n", "input.txt");
		return 1;
	}
	if((Obj=fopen("output.txt","w"))==NULL) {
		fprintf(stderr, "%s open failed!\n", "output.txt");
		return 1;
	}
	scanf("%d",&Step);					//输入当前实验步骤 
	
	statCount();						//实验步骤1：统计文件中字符出现次数（频率）
	(Step==1) ? print1(): 1; 			//输出实验步骤1结果	
	createHTree();						//实验步骤2：依据字符频率生成相应的Huffman树
	(Step==2) ? print2(Root): 2; 		//输出实验步骤2结果	
	makeHCode();				   		//实验步骤3：依据Root为树的根的Huffman树生成相应Huffman编码
	(Step==3) ? print3(): 3; 			//输出实验步骤3结果
	(Step>=4) ? atoHZIP(),print4(): 4; 	//实验步骤4：据Huffman编码生成压缩文件，并输出实验步骤4结果	

	fclose(Src);
	fclose(Obj);

    return 0;
} 

//【实验步骤1】开始 

void statCount()
{
	char cc=fgetc(Src);
	while(cc!=EOF){
		if(cc!='\n')
			Ccount[cc]++;
		cc=fgetc(Src); 
	}
	Ccount[0]++;
}

//【实验步骤1】结束

//【实验步骤2】开始

int cmp1(const void *a,const void *b){
	struct tnode **aa=(struct tnode **)a;
	struct tnode **bb=(struct tnode **)b;
	if((**bb).weight>(**aa).weight)return 1;
	if((**bb).weight<(**aa).weight)return -1;
	if((**bb).c>(**aa).c)return 1;
	if((**bb).c<(**aa).c)return -1;
}

void createHTree()
{
	struct tnode *F[128],*p=NULL;
	int nodecnt=0,i;
	for(i=0;i<128;i++){
		if(Ccount[i]>0){
			p=(struct tnode *)malloc(sizeof(struct tnode));
			p->c=i;p->weight=Ccount[i];
			p->left=p->right=NULL;
			F[nodecnt++]=p;
		}
	}
	qsort(F,nodecnt,sizeof(F[0]),cmp1);
	while(nodecnt>1){
		p=(struct tnode *)malloc(sizeof(struct tnode));
		p->left=F[nodecnt-1];p->right=F[nodecnt-2];
		p->weight=p->left->weight+p->right->weight;
		F[nodecnt-2]=p;
		nodecnt--;
		i=nodecnt;
		while(i>0&&F[i-1]->weight<=p->weight){
			F[i]=F[i-1];
			i--;
		}
		F[i]=p;
	}
	Root=F[0];
}

//【实验步骤2】结束

//【实验步骤3】开始

void preorder(struct tnode *p,char *path,int pos,char num){
	path[pos]=num;
	if(!p->left&&!p->right){
		path[pos+1]='\0';
		strcpy(HCode[p->c],path);
	}
	else{
		preorder(p->left,path,pos+1,'0');
		preorder(p->right,path,pos+1,'1');
	}
}

void makeHCode()
{
	char path[10];
	preorder(Root->left,path,0,'0');
	preorder(Root->right,path,0,'1');
} 

//【实验步骤3】结束

//【实验步骤4】开始

void atoHZIP()
{
	int l,i;
	Src=fopen("input.txt","r");
	char contain[10000];
	memset(contain,0,sizeof(char)*10000);
	char cc=fgetc(Src);
	while(cc!=EOF){
		if(cc!='\n')
			strcat(contain,HCode[cc]);
		else{
			l=strlen(contain);
			contain[l-1]='\n';
			contain[l]='\0';
		}
		cc=fgetc(Src);
	}
	strcat(contain,HCode[0]);
	l=strlen(contain);
	for(i=0;i<l;i+=8){
		int a=0,j;
		for(j=0;j<8;j++)
			a=a*2+(contain[i+j]-'0');
		char res1,res2;
		printf("%x",a);
		fprintf(Obj,"%c",a);
	}	
}

//【实验步骤4】结束

void print1()
{
	int i;
	printf("NUL:1\n");
	for(i=1; i<128; i++)
		if(Ccount[i] > 0)
			printf("%c:%d\n", i, Ccount[i]);
}

void print2(struct tnode *p)
{
	if(p != NULL){
		if((p->left==NULL)&&(p->right==NULL)) 
			switch(p->c){
				case 0: printf("NUL ");break;
				case ' ':  printf("SP ");break;
				case '\t': printf("TAB ");break;
				case '\n':  printf("CR ");break;
				default: printf("%c ",p->c); break;
			}
		print2(p->left);
		print2(p->right);
	}
}

void print3()
{
	int i;
	
	for(i=0; i<128; i++){
		if(HCode[i][0] != 0){
			switch(i){
				case 0: printf("NUL:");break;
				case ' ':  printf("SP:");break;
				case '\t': printf("TAB:");break;
				case '\n':  printf("CR:");break;
				default: printf("%c:",i); break;
			}
			printf("%s\n",HCode[i]);
		}
	}
} 

void print4()
{
	long int in_size, out_size;
	
	fseek(Src,0,SEEK_END);
	fseek(Obj,0,SEEK_END);
	in_size = ftell(Src);
	out_size = ftell(Obj);
	
	printf("\n原文件大小：%ldB\n",in_size);
	printf("压缩后文件大小：%ldB\n",out_size);
	printf("压缩率：%.2f%%\n",(float)(in_size-out_size)*100/in_size);
}
