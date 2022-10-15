//�ļ�ѹ��-Huffmanʵ��
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 32

struct tnode {					//Huffman���ṹ
	char c;		
	int weight;					//���ڵ�Ȩ�أ�Ҷ�ڵ�Ϊ�ַ������ĳ��ִ���
	struct tnode *left,*right;
} ; 
int Ccount[128]={0};			//���ÿ���ַ��ĳ��ִ�������Ccount[i]��ʾASCIIֵΪi���ַ����ִ��� 
struct tnode *Root=NULL; 		//Huffman���ĸ��ڵ�
char HCode[128][MAXSIZE]={{0}}; //�ַ���Huffman���룬��HCode['a']Ϊ�ַ�a��Huffman���루�ַ�����ʽ�� 
int Step=0;						//ʵ�鲽�� 
FILE *Src, *Obj;
	
void statCount();				//����1��ͳ���ļ����ַ�Ƶ��
void createHTree();				//����2������һ��Huffman�������ڵ�ΪRoot 
void makeHCode();				//����3������Huffman������Huffman����
void atoHZIP(); 				//����4������Huffman���뽫ָ��ASCII���ı��ļ�ת����Huffman���ļ�

void print1();					//�������1�Ľ��
void print2(struct tnode *p);	//�������2�Ľ�� 
void print3();					//�������3�Ľ��
void print4();					//�������4�Ľ��

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
	scanf("%d",&Step);					//���뵱ǰʵ�鲽�� 
	
	statCount();						//ʵ�鲽��1��ͳ���ļ����ַ����ִ�����Ƶ�ʣ�
	(Step==1) ? print1(): 1; 			//���ʵ�鲽��1���	
	createHTree();						//ʵ�鲽��2�������ַ�Ƶ��������Ӧ��Huffman��
	(Step==2) ? print2(Root): 2; 		//���ʵ�鲽��2���	
	makeHCode();				   		//ʵ�鲽��3������RootΪ���ĸ���Huffman��������ӦHuffman����
	(Step==3) ? print3(): 3; 			//���ʵ�鲽��3���
	(Step>=4) ? atoHZIP(),print4(): 4; 	//ʵ�鲽��4����Huffman��������ѹ���ļ��������ʵ�鲽��4���	

	fclose(Src);
	fclose(Obj);

    return 0;
} 

//��ʵ�鲽��1����ʼ 

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

//��ʵ�鲽��1������

//��ʵ�鲽��2����ʼ

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

//��ʵ�鲽��2������

//��ʵ�鲽��3����ʼ

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

//��ʵ�鲽��3������

//��ʵ�鲽��4����ʼ

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

//��ʵ�鲽��4������

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
	
	printf("\nԭ�ļ���С��%ldB\n",in_size);
	printf("ѹ�����ļ���С��%ldB\n",out_size);
	printf("ѹ���ʣ�%.2f%%\n",(float)(in_size-out_size)*100/in_size);
}
