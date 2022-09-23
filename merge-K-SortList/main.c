#include <stdio.h>
#include <stdlib.h>

//����˵�����ϲ�k����������

struct ListNode
{
    int val;
    struct ListNode *next;
};

void printfl(struct ListNode *l);

struct ListNode *mergeKLists(struct ListNode **lists, int listsSize)
{
    int data[listsSize], ptr[listsSize], i, min = 0, tmp, bk = listsSize, j;
    struct ListNode *l;
    struct ListNode *tcell;
    for (i = 0; i < listsSize; i++) //��data[]��ʾ����ĵ�һ����
    {
        data[i] = lists[i]->val;
        lists[i] = lists[i]->next;
    }
    int s[listsSize];
    for (i = 0; i < listsSize; i++)
        s[i] = i;
    while (i) //��data[]�����ð��������s[]�����±�
    {
        i = 0;
        for (j = 0; j < listsSize - 1; j++)
        {
            if (data[s[j]] > data[s[j + 1]])
            {
                tmp = s[j];
                s[j] = s[j + 1];
                s[j + 1] = tmp;
                i = 1;
            }
        }
    }
    min = s[0];
    tmp = min;
    for (i = 1; i < listsSize; i++) //����ָ�����飬ptr[i]ָ����һ����data[i]�����
    {
        ptr[tmp] = s[i];
        tmp = s[i];
    }
    ptr[tmp] = listsSize; //������ptrָ����������������ʾû�б�data[i]�������
    l = (struct ListNode *)malloc(sizeof(struct ListNode));
    l->val = data[min];
    l->next = NULL;
    tcell = l;

    for (i = 0; i < listsSize; i++)
        printf("%d  ", s[i]);
    printf("\ndata:");
    for (i = 0; i < listsSize; i++)
        printf("%d  ", data[i]);
    printf("\nptr:");
    for (i = 0; i < listsSize; i++)
        printf("%d  ", ptr[i]);
    printf("*******************************\n");
    while (bk)
    {
        if (lists[min])
        {
            printf("\nmin:%d  bk:%d\n", min, bk);
            printf("data:");
            for (i = 0; i < listsSize; i++)
                printf("%2d  ", data[i]);
            printf("\n ptr:");
            for (i = 0; i < listsSize; i++)
                printf("%2d  ", ptr[i]);
            printf("\n��β��\n");
            data[min] = lists[min]->val;
            lists[min] = lists[min]->next;
            if (data[min] > data[ptr[min]] && ptr[min] != listsSize) //��minָ��ĸ��º��������һ������������Ƚ�
            {
                tmp = min;
                min = ptr[min];

                if (data[tmp] < data[ptr[min]] && ptr[min] != listsSize) //���ԭ����min����min��ptrָ�����С������min��ptrָ��ԭ����min���±�
                {
                    ptr[tmp] = ptr[min];
                    ptr[min] = tmp;
                }
                else
                    for (i = min;;) //Ϊԭ����min������ptr
                    {
                        if (ptr[i] == listsSize) //���ԭmin�±��ʾ�������������ģ�����ptr��ԭ���������ptr����
                        {
                            ptr[tmp] = listsSize;
                            ptr[i] = tmp;
                            break;
                        }
                        if (data[tmp] >= data[ptr[i]])
                            i = ptr[i];
                        else
                        {
                            ptr[tmp] = ptr[i];
                            ptr[i] = tmp;
                            break;
                        }
                    }
            }
            tcell->next = (struct ListNode *)malloc(sizeof(struct ListNode));
            tcell->next->val = data[min];
            tcell->next->next = NULL;
            tcell = tcell->next;
        }
        else
        {
            --bk;   //ÿ��һ������ͷʱ��bk-1
            if (bk) // min����Ϊ�ѵ���ͷ�������ptr�������
            {
                min = ptr[min];
                tcell->next = (struct ListNode *)malloc(sizeof(struct ListNode));
                tcell->next->val = data[min];
                tcell->next->next = NULL;
                tcell = tcell->next;
            }
        }
        printf("\nl:");
        printfl(l);
        printf("-----------------------------------------------------------------------\n");
    }
    return l;
}

int main()
{
    int i, i2, d;
    struct ListNode *l[10];
    struct ListNode *tmp;
    printf("��������");
    scanf("%d", &i);
    i2 = i;
    while (i--)
    {
        printf("����������%d: ", i);
        scanf("%d", &d);
        l[i] = (struct ListNode *)malloc(sizeof(struct ListNode));
        tmp = l[i];
        tmp->next = NULL;
        tmp->val = d;
        while (getchar() != '\n')
        {
            scanf("%d", &d);
            tmp->next = (struct ListNode *)malloc(sizeof(struct ListNode));
            tmp->next->next = NULL;
            tmp->next->val = d;
            tmp = tmp->next;
        }
    }
    for (i = i2; i--;)
    {
        printfl(l[i]);
    }
    printf("\n");
    l[9] = mergeKLists(l, i2);
    printfl(l[9]);
    return 0;
}

void printfl(struct ListNode *l)
{
    for (; l != NULL; l = l->next)
    {
        printf("%d  ", l->val);
    }
    printf("\n");
    return;
}
