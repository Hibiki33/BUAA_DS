typedef struct{
    int stk[100];
    int top;
}stack;

stack *stackcreate(){
    stack *res=(stack *)malloc(sizeof(stack));
    res->top=-1;
    return res;
}
void stackpush(stack *obj,int x){obj->stk[++obj->top]=x;}
void stackpop(stack *obj){obj->top--;}
int stacktop(stack *obj){return obj->stk[obj->top];}
bool stackempty(stack *obj){return obj->top==-1;}
void stackfree(stack *obj){free(obj->stk);}

typedef struct{
    stack *in;
    stack *out;
}MyQueue;

void in2out(MyQueue *obj){
    while(!stackempty(obj->in)){
        stackpush(obj->out,stacktop(obj->in));
        stackpop(obj->in);
    }
}

MyQueue *myQueueCreate(){
    MyQueue *res=(MyQueue *)malloc(sizeof(MyQueue));
    res->in=stackcreate();
    res->out=stackcreate();
    return res;
}

void myQueuePush(MyQueue *obj,int x){
    stackpush(obj->in,x);
}

int myQueuePop(MyQueue *obj){
    if(stackempty(obj->out))in2out(obj);
    int x=stacktop(obj->out);
    stackpop(obj->out);
    return x;
}

int myQueuePeek(MyQueue *obj){
    if(stackempty(obj->out))in2out(obj);
    return stacktop(obj->out);
}

bool myQueueEmpty(MyQueue *obj){
    return stackempty(obj->in)&stackempty(obj->out);
}

void myQueueFree(MyQueue *obj){
    stackfree(obj->in);
    stackfree(obj->out);
}