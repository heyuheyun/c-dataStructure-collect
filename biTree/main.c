#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//树的结点定义
struct node
{
    int e;
    struct node *lc;
    struct node *rc;
};
typedef struct node *ptr;
typedef ptr tree;
int authority = 1, count = 0;

tree initbitree(void);
void destorybitree(tree t);
int bitreeDepth(tree t);
int root(tree t);
int value(tree t, int x);
void assign(tree t, int x, int e);
int parent(tree t, int x);
int lc(tree t, int x);
int rc(tree t, int x);
int ls(tree t, int x);
int rs(tree t, int x);
void insertchild(tree t, int x, int lr, tree c);
void deleteChild(tree t, int x, int lr);
void preorderTraverse(tree t, void(visit)(int));
void inorderTraverse(tree t, void(visit)(int));
void postorderTraverse(tree t, void(visit)(int));
void leveorderTraverse(tree t, void(visit)(int));
void printfbitree(tree t);
void creatbiTree_pre(tree *t);
void printelem(int e);

int main()
{
    printf("树结点的值为数值类型,所有输入用空格隔开,程序没有进行错误输入处理，因此任何不符合要求的输入都可能导致程序错误-_-\n");
    printf("关于值的位置:根结点位置为1,根左孩子位置2、右孩子位置3,以此类推.另外树结点的值超过2位数时,打印树的预览缩进会有小差异\n");
    int a, a2;
    tree t = NULL, t2 = NULL;
    while (1)
    {
        printf("***********************************************************************************************************\n");
        if (t)
            printfbitree(t);
        printf("请选择:1.创建  2.销毁  3.求深  4.求根  5.求值或指定值  6.求亲  7.求左右孩子兄弟  8.插入  9.删除  0.遍历  \n");
        scanf("%d", &a);
        switch (a)
        {
            case 1:
                t = initbitree();
                printf("按先序遍历输入数据\n(把指向NULL的指针视为指向数据0,如1,2,3,0,0,0,4,0,0):");
                creatbiTree_pre(&t);
                break;
            case 2:
                destorybitree(t);
                t = NULL;
                break;
            case 3:
                printf("深：%d", bitreeDepth(t));
                break;
            case 4:
                printf("根: %d", root(t));
                break;
            case 5:
                printf("1.求值  2.指定位置赋值  \n");
                scanf("%d", &a);
                if (a == 1)
                {
                    printf("请输入值的位置：");
                    scanf("%d", &a);
                    printf("值：%d", value(t, a));
                }
                else
                {
                    printf("指定值的位置和值:");
                    scanf("%d %d", &a, &a2);
                    assign(t, a, a2);
                }
                break;
            case 6:
                printf("请输入元素位置：");
                scanf("%d", &a);
                printf("亲的值：%d", parent(t, a));
                break;
            case 7:
                printf("1.左孩子  2.右孩子  3.左兄弟  4.右兄弟\n");
                scanf("%d", &a);
                if (a == 1)
                {
                    printf("位置：");
                    scanf("%d", &a);
                    printf("左孩子值：%d", lc(t, a));
                    break;
                }
                if (a == 2)
                {
                    printf("位置：");
                    scanf("%d", &a);
                    printf("右孩子值：%d", rc(t, a));
                    break;
                }
                if (a == 3)
                {
                    printf("位置：");
                    scanf("%d", &a);
                    printf("左兄弟值：%d", ls(t, a));
                    break;
                }
                if (a == 4)
                {
                    printf("位置：");
                    scanf("%d", &a);
                    printf("右兄弟值：%d", rs(t, a));
                }
                break;
            case 8:
                t2 = initbitree();
                printf("请输入一颗无右子树的树:");
                creatbiTree_pre(&t2);
                printfbitree(t2);
                printf("插的位置和左右(输入1代表左,2右,空格隔开):");
                scanf("%d %d", &a, &a2);
                insertchild(t, a, a2, t2);
                break;
            case 9:
                printf("删的位置和左右(输入1代表左,2右):");
                scanf("%d %d", &a, &a2);
                deleteChild(t, a, a2);
                break;
            case 0:
                printf("1.层次  2.先序  3.中序  4.后序\n");
                scanf("%d", &a);
                if (a == 1)
                    leveorderTraverse(t, printelem);
                if (a == 2)
                    preorderTraverse(t, printelem);
                if (a == 3)
                    inorderTraverse(t, printelem);
                if (a == 4)
                    postorderTraverse(t, printelem);
        }
        printf("\n");
        
        printf("***********************************************************************************************************\n\n\n\n");
    }
    return 0;
}

//打印元素的值
void printelem(int e)
{
    printf("%d ", e);
    return;
}

//初始化二叉树
tree initbitree(void)
{
    tree t = NULL;
    return t;
}

//销毁二叉树
void destorybitree(tree t)
{
    if (t)
    {
        destorybitree(t->lc);
        destorybitree(t->rc);
        free(t);
        return;
    }
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

//求根
int root(tree t)
{
    if (t)
        return t->e;
    printf("null!");
    return 0;
}

//求指定位置的值
int value(tree t, int x)
{
    int i = 0, tmp, a = x;
    for (; a > 1; i++)
        a /= 2;
    for (; i > 0; i--)
    {
        tmp = x - (a * pow(2, i)); //求输入位置离当前子树的当前行首元素的距离
        if (tmp >= pow(2, i) / 2)  //根据距离判断元素位于左子树还是右子树
        {
            t = t->rc;
            a = a * 2 + 1;
        }
        else
        {
            t = t->lc;
            a *= 2;
        }
    }
    return t->e;
}

//指定位置赋值
void assign(tree t, int x, int e)
{
    int i = 0, tmp, a = x;
    for (; a > 1; i++)
        a /= 2;
    for (; i > 0; i--)
    {
        tmp = x - (a * pow(2, i));
        if (tmp >= pow(2, i) / 2)
        {
            t = t->rc;
            a = a * 2 + 1;
        }
        else
        {
            t = t->lc;
            a *= 2;
        }
    }
    t->e = e;
    return;
}

//求亲
int parent(tree t, int x)
{
    int i = 0, tmp, a = x;
    for (; a > 1; i++)
        a /= 2;
    for (; i > 1; i--)
    {
        tmp = x - (a * pow(2, i));
        if (tmp >= pow(2, i) / 2)
        {
            t = t->rc;
            a = a * 2 + 1;
        }
        else
        {
            t = t->lc;
            a *= 2;
        }
    }
    return t->e;
}

//求左孩子
int lc(tree t, int x)
{
    int i = 0, tmp, a = x;
    for (; a > 1; i++)
        a /= 2;
    for (; i > 0; i--)
    {
        tmp = x - (a * pow(2, i));
        if (tmp >= pow(2, i) / 2)
        {
            t = t->rc;
            a = a * 2 + 1;
        }
        else
        {
            t = t->lc;
            a *= 2;
        }
    }
    return t->lc->e;
}

//求右孩子
int rc(tree t, int x)
{
    int i = 0, tmp, a = x;
    for (; a > 1; i++)
        a /= 2;
    for (; i > 0; i--)
    {
        tmp = x - (a * pow(2, i));
        if (tmp >= pow(2, i) / 2)
        {
            t = t->rc;
            a = a * 2 + 1;
        }
        else
        {
            t = t->lc;
            a *= 2;
        }
    }
    return t->rc->e;
}

//求左兄弟
int ls(tree t, int x)
{
    int i = 0, tmp, a = x;
    for (; a > 1; i++)
        a /= 2;
    for (; i > 1; i--)
    {
        tmp = x - (a * pow(2, i));
        if (tmp >= pow(2, i) / 2)
        {
            t = t->rc;
            a = a * 2 + 1;
        }
        else
        {
            t = t->lc;
            a *= 2;
        }
    }
    return t->lc->e;
}

//求右兄弟
int rs(tree t, int x)
{
    int i = 0, tmp, a = x;
    for (; a > 1; i++)
        a /= 2;
    for (; i > 1; i--)
    {
        tmp = x - (a * pow(2, i));
        if (tmp >= pow(2, i) / 2)
        {
            t = t->rc;
            a = a * 2 + 1;
        }
        else
        {
            t = t->lc;
            a *= 2;
        }
    }
    return t->rc->e;
}

//插入子树
void insertchild(tree t, int x, int lr, tree c)
{
    int i = 0, tmp, a = x;
    for (; a > 1; i++)
        a /= 2;
    for (; i > 1; i--)
    {
        tmp = x - (a * pow(2, i));
        if (tmp >= pow(2, i) / 2)
        {
            t = t->rc;
            a = a * 2 + 1;
        }
        else
        {
            t = t->lc;
            a *= 2;
        }
    }
    tree tmpt;
    if (lr)
        tmpt = t->rc;
    else
        tmpt = t->lc;
    if (lr)
        t->rc = c;
    else
        t->lc = c;
    c->rc = tmpt;
    return;
}

//删除子树
void deleteChild(tree t, int x, int lr)
{
    int i = 0, tmp, a = x;
    for (; a > 1; i++)
        a /= 2;
    for (; i > 1; i--)
    {
        tmp = x - (a * pow(2, i));
        if (tmp >= pow(2, i) / 2)
        {
            t = t->rc;
            a = a * 2 + 1;
        }
        else
        {
            t = t->lc;
            a *= 2;
        }
    }
    if (lr)
    {
        destorybitree(t->rc);
        t->rc = NULL;
    }
    else
    {
        destorybitree(t->lc);
        t->lc = NULL;
    }
    return;
}

//先序遍历
void preorderTraverse(tree t, void(visit)(int))
{
    if (t)
    {
        visit(t->e);
        preorderTraverse(t->lc, printelem);
        preorderTraverse(t->rc, printelem);
    }
    return;
}

//中序遍历
void inorderTraverse(tree t, void(visit)(int))
{
    if (t)
    {
        inorderTraverse(t->lc, printelem);
        visit(t->e);
        inorderTraverse(t->rc, printelem);
    }
    return;
}

//后序遍历
void postorderTraverse(tree t, void(visit)(int))
{
    if (t)
    {
        postorderTraverse(t->lc, printelem);
        postorderTraverse(t->rc, printelem);
        visit(t->e);
    }
    return;
}

//层次遍历
void leveorderTraverse(tree t, void(visit)(int))
{
    if (!t)
        return;
    authority -= 1;
    if (!authority)
        visit(t->e);
    while (1)
    {
        if (authority)
        {
            leveorderTraverse(t->lc, printelem);
            leveorderTraverse(t->rc, printelem);
        }
        if (authority < count)
        {
            authority += 1;
            return; //只有递归的函数才在这返回
        }
        authority += 1; //递归的函数无法到这里
        count = authority;
        printf("   ");
        if (authority >= bitreeDepth(t))
        {
            authority = 1;
            count = 0;
            return;
        }
    }
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
            printf("--"); //如果当前位置没有数据则打印空格
        else             
            //printf("*");
            printf("%2d",tmpcell->e);
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

//通过先序遍历创建二叉树
void creatbiTree_pre(tree *t)
{
    *t = malloc(sizeof(struct node));
    scanf("%d", &(*t)->e);
    getchar();
    (*t)->lc = NULL;
    (*t)->rc = NULL;
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
