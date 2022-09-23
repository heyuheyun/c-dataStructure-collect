#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//树的结点定义
struct node
{
    int e;
    int ltag;
    int rtag;
    struct node *lc;
    struct node *rc;
};
typedef struct node *ptr;
typedef ptr tree;

//栈
struct stack
{
    tree p;
    struct stack *next;
};
typedef struct stack stack;

//队列
struct queue
{
    tree p;
    struct queue *next;
};
typedef struct queue queue;
queue *rear = NULL;

void push(stack **s, tree t);
tree pop(stack **s);

void enqueue(queue **q, tree t);
tree dequeue(queue **q);

void creatbiTree_pre(tree *t);
void printfbitree(tree t);
int bitreeDepth(tree t);
void preorderTraverse(tree t);
void inorderTraverse(tree t);
void postorderTraverse(tree t);
void levelorderTraverse(tree t);
void creatPrethread(tree t);
void prethread(tree t, tree *pre);
void threadPreorder(tree t);
void destoryThread(tree t);
void inthread(tree t, tree *pre);
void creatinthread(tree t);
void threadInorder(tree t);

int main()
{
    tree t = NULL;
    printf("按先序遍历输入数据\n(把每一个指向NULL的指针视为指向数据0,比如输入1,2,3,0,0,0,4,0,0):");
    creatbiTree_pre(&t);
    printfbitree(t);
    printf("\n非递归先序遍历测试\n");
    preorderTraverse(t);
    printf("\n非递归中序遍历测试\n");
    inorderTraverse(t);
    printf("\n非递归后序遍历测试\n");
    postorderTraverse(t);
    printf("\n非递归层次遍历测试\n");
    levelorderTraverse(t);
    printf("\n先序线索化二叉树测试");
    creatPrethread(t);
    printf("\n线索化:先序遍历测试\n");
    threadPreorder(t);
    destoryThread(t);
    printf("\n中序线索化二叉树测试");
    creatinthread(t);
    printf("\n线索化:中序遍历测试\n");
    threadInorder(t);
    return 0;
}

//入栈
void push(stack **s, tree t)
{
    stack *tmp;
    tmp = (stack *)malloc(sizeof(stack));
    tmp->p = t;
    tmp->next = *s;
    *s = tmp;
    return;
}
//出栈
tree pop(stack **s)
{
    tree ttmp = (*s)->p;
    stack *stmp = *s;
    *s = (*s)->next;
    free(stmp);
    return ttmp;
}

//入队
void enqueue(queue **q, tree t)
{
    queue *tmp;
    tmp = (queue *)malloc(sizeof(queue));
    tmp->p = t;
    tmp->next = NULL;
    if ((*q) == NULL)
    {
        (*q) = tmp;
        rear = *q;
        return;
    }
    rear->next = tmp;
    rear = tmp;
    return;
}
//出队
tree dequeue(queue **q)
{
    tree ttmp;
    queue *qtmp;
    qtmp = *q;
    ttmp = (*q)->p;
    (*q) = qtmp->next;
    free(qtmp);
    return ttmp;
}

//打印二叉树
void printfbitree(tree t)
{
    int j, i, r = 1, i2, depth, ss = 3, sum;
    tree tmpcell;
    depth = bitreeDepth(t);
    sum = pow(2, depth) - 1; //要打印的元素总个数
    int a[depth];
    for (j = 0; j < depth; j++) // a[]的初始化
    {
        a[j] = -1;
    }
    for (i = 1; i < (depth - 1); i++) //确定要打印的空格数
    {
        ss = ss * 2 + 1;
    }
    for (i = 1; i <= sum; i++)
    {
        tmpcell = t;
        j = i;
        for (i2 = 1; i2 < r; i2++) //用a[]记录当前节点的路径
        {
            a[i2] = j % 2;
            j /= 2;
        }
        for (i2--; a[i2] != -1; i2--) //根据路径找到所要打印的节点
        {
            if (a[i2])
                tmpcell = tmpcell->rc;
            else
                tmpcell = tmpcell->lc;
            if (!tmpcell)
                break;
        }
        for (j = 1; j <= ss; j++)
        {
            printf("  ");
        }
        if (!tmpcell)
            printf("00"); //如果当前位置没有数据则打印空格
        else
            printf("%2d", tmpcell->e);
        // printf("*");
        for (j = 0; j <= ss; j++)
        {
            printf("  ");
        }
        if (i >= pow(2, r) - 1) //判断是否进入下一层
        {
            printf("\n");
            r += 1;
            ss /= 2;
        }
    }
    return;
}

//创建二叉树
void creatbiTree_pre(tree *t)
{
    *t = malloc(sizeof(struct node));
    scanf("%d", &(*t)->e);
    getchar();
    (*t)->lc = NULL;
    (*t)->rc = NULL;
    (*t)->ltag = 0;
    (*t)->rtag = 0;
    if (!(*t)->e)
    {
        free(*t);
        (*t) = NULL;
        return;
    }
    creatbiTree_pre(&((*t)->lc));
    creatbiTree_pre(&((*t)->rc));
    return;
}

//求二叉树深度
int bitreeDepth(tree t)
{
    if (t != NULL)
    {
        int i = 1, max = 1;
        max += bitreeDepth(t->lc);
        i += bitreeDepth(t->rc);
        if (i > max)
            max = i;
        return max;
    }
    return 0;
}

//先序遍历二叉树
void preorderTraverse(tree t)
{
    stack *s = NULL;
    tree tmp;
    if (t)
        push(&s, t);
    while (s)
    {
        tmp = pop(&s);
        if (tmp->rc)
            push(&s, tmp->rc);
        if (tmp->lc)
            push(&s, tmp->lc);
        printf("%d  ", tmp->e);
    }
    return;
}

//中序遍历二叉树
void inorderTraverse(tree t)
{
    stack *s = NULL;
    tree tmp = t;
    if (tmp)
        push(&s, tmp);
    while (tmp->lc)
    {
        tmp = tmp->lc;
        push(&s, tmp);
    }
    while (s)
    {
        tmp = pop(&s);
        printf("%d  ", tmp->e);
        if (tmp->rc)
        {
            tmp = tmp->rc;
            push(&s, tmp);
            while (tmp->lc)
            {
                tmp = tmp->lc;
                push(&s, tmp);
            }
        }
    }
}

//后序遍历二叉树
void postorderTraverse(tree t)
{
    stack *s = NULL, *s2 = NULL;
    tree tmp = t;
    if (t)
        push(&s, t);
    while (s)
    {
        tmp = pop(&s);
        if (tmp->lc)
            push(&s, tmp->lc);
        if (tmp->rc)
            push(&s, tmp->rc);
        push(&s2, tmp);
    }
    while (s2)
    {
        printf("%d  ", pop(&s2)->e);
    }
    return;
}

//层次遍历二叉树
void levelorderTraverse(tree t)
{
    tree tmp;
    queue *q = NULL;
    if (t)
        enqueue(&q, t);
    while (q)
    {
        tmp = dequeue(&q);
        if (tmp->lc)
            enqueue(&q, tmp->lc);
        if (tmp->rc)
            enqueue(&q, tmp->rc);
        printf("%d  ", tmp->e);
    }
    return;
}

//先序线索化二叉树
void creatPrethread(tree t)
{
    tree pre = NULL;
    prethread(t, &pre);
    pre->rc = NULL;
    pre->rtag = 1;
    return;
}
void prethread(tree t, tree *pre)
{
    if (t)
    {
        if ((*pre) != NULL && (*pre)->rc == NULL)
        {
            (*pre)->rc = t;
            (*pre)->rtag = 1;
        }
        if (t->lc == NULL)
        {
            t->lc = *pre;
            t->ltag = 1;
        }
        (*pre) = t;
        if (t->ltag == 0)
            prethread(t->lc, pre);
        if (t->rtag == 0)
            prethread(t->rc, pre);
    }
    return;
}

//线索化先序遍历
void threadPreorder(tree t)
{
    while (t)
    {
        printf("%d  ", t->e);
        if (t->rtag == 1)
            t = t->rc;
        else
            t = t->lc;
    }
    return;
}

//清除二叉树的线索
void destoryThread(tree t)
{
    stack *s = NULL;
    tree tmp;
    if (t)
        push(&s, t);
    while (s)
    {
        tmp = pop(&s);
        if (tmp->rc)
            push(&s, tmp->rc);
        if (tmp->lc)
            push(&s, tmp->lc);
        if (tmp->ltag == 1)
        {
            tmp->ltag = 0;
            tmp->lc = NULL;
        }
        if (tmp->rtag == 1)
        {
            tmp->rtag = 0;
            tmp->rc = NULL;
        }
    }
    return;
}

//中序线索化二叉树
void inthread(tree t, tree *pre)
{
    if (t)
    {
        inthread(t->lc, pre);
        if (t->lc == NULL)
        {
            t->ltag = 1;
            t->lc = *pre;
        }
        if ((*pre) && (*pre)->rc == NULL)
        {
            (*pre)->rtag = 1;
            (*pre)->rc = t;
        }
        (*pre) = t;
        inthread(t->rc, pre);
    }
    return;
}
void creatinthread(tree t)
{
    tree pre = NULL;
    inthread(t, &pre);
    pre->rtag = 1;
    pre->rc = NULL;
    return;
}

//线索化中序遍历
void threadInorder(tree t)
{
    while (t->lc)
        t = t->lc;
    while (t)
    {
        printf("%d  ", t->e);
        if (t->rtag == 1)
            t = t->rc;
        else
        {
            t = t->rc;
            while (t->lc && t->ltag == 0)
                t = t->lc;
        }
    }
    return;
}
