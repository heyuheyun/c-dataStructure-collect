#include <stdio.h>
#include <stdlib.h>

struct node
{
    int elem;
    struct node *next;
};
typedef struct node node;
typedef node *ptr;
typedef ptr queue;
queue front = NULL, rear = NULL;
queue initqueue(void);
int queueempty(queue q);
void enqueue(queue q, int e);
void dequeue(queue q, int *e);
void getqueue(queue q, int *e);

int main()
{
    int a = 1, i = 1;
    queue q;
    while (i)
    {
        printf("请输入：1.初始化队列  2.判空  3.入队  4.出队  5.读队头元素  6.离开");
        scanf("%d", &a);
        switch (a)
        {
        case 1:
            q = initqueue();
            printf("是否需要输入元素？  1.确定  2.否");
            scanf("%d", &a);
            if (a == 2)
                continue;
            printf("请输入数据（用英文句号隔开，回车结束）：");
            while (1)
            {
                scanf("%d", &a);
                enqueue(q, a);
                if (getchar() == '\n')
                    break;
            }
            break;
        case 2:
            if (queueempty(q))
            {
                printf("empty");
                break;
            }
            printf("no empty");
            break;
        case 3:
            printf("入队数据：");
            scanf("%d", &a);
            enqueue(q, a);
            break;
        case 4:
            dequeue(q, &a);
            printf("出队元素：%d\n", a);
            break;
        case 5:
            getqueue(q, &a);
            printf("队头元素：%d\n", a);
            break;
        case 6:
            i = 0;
        }
        if (front != NULL)
        {
            q = front;
            do
            {
                printf("%d  ", q->elem);
                q = q->next;
            } while (q != NULL);
        }
        printf("\n");
    }
    return 0;
}

queue initqueue(void)
{
    if (front != NULL)
    {
        queue tmp;
        while (front != NULL)
        {
            tmp = front;
            front = front->next;
            free(tmp);
        }
    }
    queue q;
    q = malloc(sizeof(node));
    q->next = NULL;
    rear = q;
    return q;
}
int queueempty(queue q)
{
    if (front == NULL)
        return 1;
    return 0;
}
void enqueue(queue q, int e)
{
    if (front == NULL)
    {
        q->elem = e;
        front = q;
        return;
    }
    queue tmp;
    tmp = malloc(sizeof(node));
    tmp->elem = e;
    tmp->next = NULL;
    rear->next = tmp;
    rear = tmp;
    return;
}
void dequeue(queue q, int *e)
{
    queue tmp;
    *e = front->elem;
    tmp = front;
    front = front->next;
    free(tmp);
    return;
}
void getqueue(queue q, int *e)
{
    *e = front->elem;
    return;
}
