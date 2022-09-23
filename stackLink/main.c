#include <stdio.h>
#include <stdlib.h>

struct node
{
    int elem;
    struct node *last;
};
typedef struct node *ptr;
typedef ptr stack;
typedef struct node node;
stack top = NULL;
stack initstack(void);
int stackempty(stack s);
void push(stack s, int x);
void pop(stack s, int *x);
void gettop(stack s, int *x);
void destorystack(stack s);

int main()
{
    stack s;
    int i = 1, a = 0;
    while (i)
    {
        printf("\n��ѡ��1.��ʼ����ջ  2.�п�  3.��ջ  4.��ջ  5.��ջ��  6.����  7.�˳�\n");
        scanf("%d", &a);
        switch (a)
        {
        case 1:
            s = initstack();
            printf("���������ݣ�Ӣ�Ķ��Ÿ���,�س���������");
            while (1)
            {
                scanf("%d", &a);
                push(s, a);
                if (getchar() == '\n')
                    break;
            }
            break;
        case 2:
            if (stackempty(s))
                printf("empty");
            else
                printf("no empty");
            break;
        case 3:
            printf("���ݣ�");
            scanf("%d", &a);
            push(s, a);
            break;
        case 4:
            pop(s, &a);
            printf("����Ԫ�أ�%d\n", a);
            break;
        case 5:
            gettop(s, &a);
            printf("ջ��Ԫ�أ�%d\n", a);
            break;
        case 6:
            destorystack(s);
            break;
        case 7:
            i = 0;
        }
        if (top != NULL)
        {
            s = top;
            do
            {
                printf("%d  ", s->elem);
                s = s->last;
            } while (s != NULL);
        }
    }
    return 0;
}
stack initstack(void)
{
    stack s;
    s = malloc(sizeof(node));
    s->last = NULL;
    return s;
}
int stackempty(stack s)
{
    if (top == NULL)
        return 1;
    return 0;
}
void push(stack s, int x)
{
    if (top == NULL)
    {
        s->elem = x;
        top = s;
        return;
    }
    stack tmp;
    tmp = malloc(sizeof(node));
    tmp->last = top;
    tmp->elem = x;
    top = tmp;
    return;
}
void pop(stack s, int *x)
{
    if (top == NULL)
    {
        printf("error");
        return;
    }
    stack tmp = top;
    *x = (top->elem);
    top = top->last;
    free(tmp);
    return;
}
void gettop(stack s, int *x)
{
    if (top == NULL)
    {
        printf("error");
        return;
    }
    *x = top->elem;
    return;
}
void destorystack(stack s)
{
    stack tmp;
    while (top != NULL)
    {
        tmp = top;
        top = top->last;
        free(tmp);
    }
    return;
}
