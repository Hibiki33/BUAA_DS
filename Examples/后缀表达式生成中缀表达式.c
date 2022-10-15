#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#define LENGTH 10007
#define SUM 512
 
/*表达式树的定义及函数*/
struct node {
	char num[LENGTH];
	struct node *lchild;
	struct node *rchild;
};
typedef struct node Node;
typedef struct node* BTNodeptr;
 
void freeT(BTNodeptr p);	//释放表达式树
void travel(BTNodeptr p);	//中序遍历，输出中缀表达式以及添加括号
BTNodeptr buildT(char s[]);	//建立表达式树
 
/*存放表达式树的指针的栈*/
BTNodeptr tree[SUM];	
int top = 0;
void push(BTNodeptr p) { tree[++top] = p; }
BTNodeptr pop() { return tree[top--]; }
 
/*判断符号优先级*/
bool judge(char s[]);
bool judgeLeft(char s1[], char s2[]);
bool judgeRight(char s1[], char s2[]);
 
int main()
{
	char s[LENGTH];
	BTNodeptr root = NULL;
 
	fgets(s, LENGTH, stdin);    //不用gets是因为fgets更安全
	root = buildT(s);
	travel(root);
	freeT(root);                //虽然大一很菜很菜，不过记得free这个好习惯还是从大一就有了
                                    //PS：其实是因为没听懂担心内存泄露
 
	return 0;
}
 
 
void freeT(BTNodeptr p)
{
	if (p != NULL) {
		freeT(p->lchild);
		freeT(p->rchild);
		free(p);
		p = NULL;
	}
}
 
/*表达式树特点：若p有左右节点，则p必定为符号位*/
void travel(BTNodeptr p)
{
	if (p != NULL)
	{
		/*若p的左子树上是符号，并且小于p上的符号优先级，则添加括号*/
		if (p->lchild && judgeLeft(p->num,p->lchild->num))
		{
			printf("(");
			travel(p->lchild);
			printf(")");
		}
		else
			travel(p->lchild);
 
		printf("%s", p->num);
 
		/*若p的右子树上是符号，并且不大于p上的符号优先级，则判断后添加括号*/
		if (p->rchild && judgeRight(p->num, p->rchild->num))
		{
			printf("(");
			travel(p->rchild);
			printf(")");
		}
		else
			travel(p->rchild);
	}
}
 
 
BTNodeptr buildT(char s[])
{
	int i;
	BTNodeptr p;
	int a = 0;
	char temp[LENGTH];
 
	for (i = 0; s[i] != '\0'; i++)
	{
		/*读取到数字，储存*/
		if ((s[i] >= '0' && s[i] <= '9') || s[i] == '.')
			temp[a++] = s[i];
		/*读取到空格，将数字存储*/
		else if (s[i] == ' ' && a != 0)
		{
			temp[a] = '\0';
			p = (BTNodeptr)malloc(sizeof(Node));
			strcpy(p->num, temp);
			p->lchild = NULL;
			p->rchild = NULL;
			push(p);
			a = 0;
		}
		/*若为运算符，从栈中弹出T1和T2作为右节点和左节点*/
		else if(s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {
			p = (BTNodeptr)malloc(sizeof(Node));
			p->num[0] = s[i];
			p->num[1] = '\0';
			BTNodeptr pright = pop();
			BTNodeptr pleft = pop();
			p->lchild = pleft;
			p->rchild = pright;
			push(p);
		}
	}
	return p;
}
 
/*判断s是否为符号*/
bool judge(char s[])
{
	return (s[0] == '+' || s[0] == '-' || s[0] == '/' || s[0] == '*');
} 
 
 
/*判断父节点s1的优先级是否比左节点s2高 */
bool judgeLeft(char s1[], char s2[])
{
	if ((s1[0] == '*' || s1[0] == '/') && (s2[0] == '+' || s2[0] == '-'))
		return true;
	return false;
}
 
/*判断父节点s2的优先级是否大于右节点s2，若相等还需判断父节点是否为'/'或'-' */
bool judgeRight(char s1[], char s2[])
{
	if (s1[0] == '/' && judge(s2))
		return true;
	if ((s1[0] == '*' || s1[0] == '-') && (s2[0] == '+' || s2[0] == '-'))
		return true;
	return false;
}