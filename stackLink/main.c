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
        printf("\n请选择：1.初始化空栈  2.判空  3.入栈  4.出栈  5.读栈顶  6.销毁  7.退出\n");
        scanf("%d", &a);
        switch (a)
        {
        case 1:
            s = initstack();
            printf("请输入数据（英文逗号隔开,回车结束）：");
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
            printf("数据：");
            scanf("%d", &a);
            push(s, a);
            break;
        case 4:
            pop(s, &a);
            printf("弹出元素：%d\n", a);
            break;
        case 5:
            gettop(s, &a);
            printf("栈顶元素：%d\n", a);
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
