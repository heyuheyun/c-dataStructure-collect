#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//���Ľ�㶨��
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
    printf("������ֵΪ��ֵ����,���������ÿո����,����û�н��д������봦������κβ�����Ҫ������붼���ܵ��³������-_-\n");
    printf("����ֵ��λ��:�����λ��Ϊ1,������λ��2���Һ���λ��3,�Դ�����.����������ֵ����2λ��ʱ,��ӡ����Ԥ����������С����\n");
    int a, a2;
    tree t = NULL, t2 = NULL;
    while (1)
    {
        printf("***********************************************************************************************************\n");
        if (t)
            printfbitree(t);
        printf("��ѡ��:1.����  2.����  3.����  4.���  5.��ֵ��ָ��ֵ  6.����  7.�����Һ����ֵ�  8.����  9.ɾ��  0.����  \n");
        scanf("%d", &a);
        switch (a)
        {
            case 1:
                t = initbitree();
                printf("�����������������\n(��ָ��NULL��ָ����Ϊָ������0,��1,2,3,0,0,0,4,0,0):");
                creatbiTree_pre(&t);
                break;
            case 2:
                destorybitree(t);
                t = NULL;
                break;
            case 3:
                printf("�%d", bitreeDepth(t));
                break;
            case 4:
                printf("��: %d", root(t));
                break;
            case 5:
                printf("1.��ֵ  2.ָ��λ�ø�ֵ  \n");
                scanf("%d", &a);
                if (a == 1)
                {
                    printf("������ֵ��λ�ã�");
                    scanf("%d", &a);
                    printf("ֵ��%d", value(t, a));
                }
                else
                {
                    printf("ָ��ֵ��λ�ú�ֵ:");
                    scanf("%d %d", &a, &a2);
                    assign(t, a, a2);
                }
                break;
            case 6:
                printf("������Ԫ��λ�ã�");
                scanf("%d", &a);
                printf("�׵�ֵ��%d", parent(t, a));
                break;
            case 7:
                printf("1.����  2.�Һ���  3.���ֵ�  4.���ֵ�\n");
                scanf("%d", &a);
                if (a == 1)
                {
                    printf("λ�ã�");
                    scanf("%d", &a);
                    printf("����ֵ��%d", lc(t, a));
                    break;
                }
                if (a == 2)
                {
                    printf("λ�ã�");
                    scanf("%d", &a);
                    printf("�Һ���ֵ��%d", rc(t, a));
                    break;
                }
                if (a == 3)
                {
                    printf("λ�ã�");
                    scanf("%d", &a);
                    printf("���ֵ�ֵ��%d", ls(t, a));
                    break;
                }
                if (a == 4)
                {
                    printf("λ�ã�");
                    scanf("%d", &a);
                    printf("���ֵ�ֵ��%d", rs(t, a));
                }
                break;
            case 8:
                t2 = initbitree();
                printf("������һ��������������:");
                creatbiTree_pre(&t2);
                printfbitree(t2);
                printf("���λ�ú�����(����1������,2��,�ո����):");
                scanf("%d %d", &a, &a2);
                insertchild(t, a, a2, t2);
                break;
            case 9:
                printf("ɾ��λ�ú�����(����1������,2��):");
                scanf("%d %d", &a, &a2);
                deleteChild(t, a, a2);
                break;
            case 0:
                printf("1.���  2.����  3.����  4.����\n");
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

//��ӡԪ�ص�ֵ
void printelem(int e)
{
    printf("%d ", e);
    return;
}

//��ʼ��������
tree initbitree(void)
{
    tree t = NULL;
    return t;
}

//���ٶ�����
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

//����������
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

//���
int root(tree t)
{
    if (t)
        return t->e;
    printf("null!");
    return 0;
}

//��ָ��λ�õ�ֵ
int value(tree t, int x)
{
    int i = 0, tmp, a = x;
    for (; a > 1; i++)
        a /= 2;
    for (; i > 0; i--)
    {
        tmp = x - (a * pow(2, i)); //������λ���뵱ǰ�����ĵ�ǰ����Ԫ�صľ���
        if (tmp >= pow(2, i) / 2)  //���ݾ����ж�Ԫ��λ������������������
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

//ָ��λ�ø�ֵ
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

//����
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

//������
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

//���Һ���
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

//�����ֵ�
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

//�����ֵ�
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

//��������
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

//ɾ������
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

//�������
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

//�������
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

//�������
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

//��α���
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
            return; //ֻ�еݹ�ĺ��������ⷵ��
        }
        authority += 1; //�ݹ�ĺ����޷�������
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

//��ӡ������
void printfbitree(tree t)
{
    int j, i, r = 1, i2, depth, ss = 3, sum;
    tree tmpcell;
    depth = bitreeDepth(t);
    sum = pow(2, depth) - 1; //Ҫ��ӡ��Ԫ���ܸ���
    int a[depth];
    for (j = 0; j < depth; j++) // a[]�ĳ�ʼ��
    {
        a[j] = -1;
    }
    for (i = 1; i < (depth - 1); i++) //ȷ��Ҫ��ӡ�Ŀո���
    {
        ss = ss * 2 + 1;
    }
    for (i = 1; i <= sum; i++)
    {
        tmpcell = t;
        j = i;
        for (i2 = 1; i2 < r; i2++) //��a[]��¼��ǰ�ڵ��·��
        {
            a[i2] = j % 2;
            j /= 2;
        }
        for (i2--; a[i2] != -1; i2--) //����·���ҵ���Ҫ��ӡ�Ľڵ�
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
            printf("--"); //�����ǰλ��û���������ӡ�ո�
        else             
            //printf("*");
            printf("%2d",tmpcell->e);
        for (j = 0; j <= ss; j++)
        {
            printf("  ");
        }
        if (i >= pow(2, r) - 1) //�ж��Ƿ������һ��
        {
            printf("\n");
            r += 1;
            ss /= 2;
        }
    }
    return;
}

//ͨ�������������������
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
