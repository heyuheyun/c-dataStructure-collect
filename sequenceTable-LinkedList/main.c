#include <stdio.h>
#include <stdlib.h>

struct node
{
    int element;
    struct node *next;
};
typedef struct node *ptr;
typedef ptr List;
typedef struct node node;

List initList(void);
int Length(List);
int Locateelem(List, int);
int getelem(List, int);
void Listinsert(List, int, int);
int Listdelete(List, int);
void printList(List);
int empty(List);
void destoryList(List);

int main()
{
    int a = 1, a2, i = 1;
    List L, temp;
    while (i)
    {
        printf("\n��ѡ��1.�����±� 2.��� 3.ֵ���� 4.λ���� 5.���� 6.ɾ�� 7.�������������Ԫ�� 8.�п� 9.���� 0.�뿪\n");
        scanf("%d", &a);
        if (a < 0 || a > 9)
            continue;
        switch (a)
        {
        case 1:
            L = initList();
            printf("���������ݣ�Ӣ�Ķ��Ÿ����������س���������");
            for (i = 1;; i++)
            {
                scanf("%d", &a);
                Listinsert(L, i, a);
                if (getchar() == '\n')
                    break;
            }
            break;
        case 2:
            printf("��ĳ��ȣ�%d\n", Length(L));
            break;
        case 3:
            printf("���ҵ�ֵ��");
            scanf("%d", &a);
            printf("%d�ڱ��е�%dλ��\n", a, Locateelem(L, a));
            break;
        case 4:
            printf("���ҵ�λ��");
            scanf("%d", &a);
            printf("%dλԪ��:%d\n", a, getelem(L, a));
            break;
        case 5:
            printf("����λ�������ֵ��");
            scanf("%d %d", &a, &a2);
            Listinsert(L, a, a2);
            break;
        case 6:
            printf("ɾ����λ��\n");
            scanf("%d", &a);
            Listdelete(L, a);
            break;
        // case 7:printList(L);break;
        case 8:
            if (empty(L))
                printf("empty\n");
            else
                printf("no empty\n");
            break;
        case 9:
            destoryList(L);
            break;
        case 0:
            i = 0;
        }
        if (L->next != NULL)
        {
            temp = L->next;
            do
            {
                printf("%d  ", temp->element);
                temp = temp->next;
            } while (temp != NULL);
        }
    }
    return 0;
}
List initList(void)
{
    List L;
    L = malloc(sizeof(node));
    if (L == NULL)
        printf("no space!");
    L->next = NULL;
    return L;
}
void Listinsert(List L, int x, int e)
{
    List temp, position;
    position = malloc(sizeof(node)); 
    position->element = e;
    if (x == 1)
    {
        if (L->next == NULL)
        {
            L->next = position;
            position->next = NULL;
            return;
        }
        position->next = L->next;
        L->next = position;
        return;
    }
    temp = L->next;
    x -= 1;
    int i = 1;
    for (; i < x; i++)
    {
        temp = temp->next;
    }

    position->next = (temp->next);
    temp->next = position;
    return;
}
int Length(List L)
{
    int i = 0;
    if (L->next == NULL)
        return 0;
    for (i = 0; L->next != NULL; i++)
    {
        L = L->next;
    }
    return i;
}
int Locateelem(List L, int e)
{
    int i = 1;
    L = L->next;
    for (i = 1; L->element != e; i++)
    {
        if (L->next == NULL)
        {
            printf("\n no result!\n");
            return -1;
        }
        L = L->next;
    }
    return i;
}
int getelem(List L, int n)
{
    L = L->next;
    for (int i = 1; i < n; i++)
    {
        if (L->next == NULL)
        {
            printf("\n no result!\n");
            return -1;
        }
        L = L->next;
    }
    return L->element;
}
int Listdelete(List L, int n)
{
    List tempcell;
    if (n == 1)
    {
        free(L->next);
        L->next = NULL;
        return 0;
    }
    L = L->next;
    for (int i = 2; i < n; i++)
    {
        if (L->next == NULL)
        {
            printf("\n error!\n");
            return -1;
        }
        L = L->next;
    }
    tempcell = L->next;
    L->next = L->next->next;
    free(tempcell);
    return 0;
}
/* void printList(List L)
{
    int n=Length(L),i=0,tmp,tmp2;
    int a[n]={0};
    L=L->next;
    tmp=L->element;
    a[i]=tmp;
    while(L!=NULL)
    {

    }

} */
int empty(List L)
{
    if (L->next == NULL)
        return 1;
    else
        return 0;
}
void destoryList(List L)
{
    List temp, p;
    p = L->next;
    L->next = NULL;
    while (p != NULL)
    {
        temp = p;
        p = p->next;
        free(temp);
    }
    return;
}
