#include <stdio.h>
#include <stdlib.h>

//函数说明：合并k个有序链表

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
    for (i = 0; i < listsSize; i++) //用data[]表示链表的第一个数
    {
        data[i] = lists[i]->val;
        lists[i] = lists[i]->next;
    }
    int s[listsSize];
    for (i = 0; i < listsSize; i++)
        s[i] = i;
    while (i) //将data[]里的数冒泡排序，用s[]储存下标
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
    for (i = 1; i < listsSize; i++) //建立指针数组，ptr[i]指向上一个比data[i]大的数
    {
        ptr[tmp] = s[i];
        tmp = s[i];
    }
    ptr[tmp] = listsSize; //最大的数ptr指向数组链表数，表示没有比data[i]更大的数
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
            printf("\n结尾：\n");
            data[min] = lists[min]->val;
            lists[min] = lists[min]->next;
            if (data[min] > data[ptr[min]] && ptr[min] != listsSize) //将min指向的更新后的数与上一个比它大的数比较
            {
                tmp = min;
                min = ptr[min];

                if (data[tmp] < data[ptr[min]] && ptr[min] != listsSize) //如果原来的min比新min的ptr指向的数小，则将新min的ptr指向原来的min数下标
                {
                    ptr[tmp] = ptr[min];
                    ptr[min] = tmp;
                }
                else
                    for (i = min;;) //为原来的min更新其ptr
                    {
                        if (ptr[i] == listsSize) //如果原min下标表示的数现在是最大的，则将其ptr与原来最大数的ptr互换
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
            --bk;   //每当一链表到尽头时，bk-1
            if (bk) // min更新为已到尽头的链表的ptr，并输出
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
    printf("链表数：");
    scanf("%d", &i);
    i2 = i;
    while (i--)
    {
        printf("请输入链表%d: ", i);
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
