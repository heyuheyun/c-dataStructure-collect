#include <stdio.h>
#include <stdlib.h>

//移除链表的第n个数据

 struct ListNode {
     int val;
     struct ListNode *next;
 };

 typedef struct stack{
 struct ListNode *ptr;
 struct stack *next;
 }stack;
 stack *top=NULL;

 void push(struct ListNode *l);
 struct ListNode *pop(void);

struct ListNode* removeNthFromEnd(struct ListNode* head, int n){
    int d=0;struct ListNode *tmp=head,*tmp2;
    while(1)
    {
        push(tmp);
        tmp=tmp->next;
        if(tmp==NULL)
        {
            while(1)
            {
                tmp=pop();
                d++;
                if(d==n)
                {
                    if(tmp==head)
                    {
                        head=head->next;
                        free(tmp);
                        return head;
                    }
                    tmp=pop();
                    tmp2=tmp->next;
                    tmp->next=tmp2->next;
                    free(tmp2);
                    return head;
                }
            }
        }
    }
}
void printfl(struct ListNode* l);

int main()
{
    int d;struct ListNode *l,*tmp;
    printf("链表数据：");
    scanf("%d",&d);
        l=(struct ListNode*)malloc(sizeof(struct ListNode));
        tmp=l;
        tmp->next=NULL;
        tmp->val=d;
        while(getchar()!='\n')
        {
            scanf("%d",&d);
            tmp->next=(struct ListNode*)malloc(sizeof(struct ListNode));
            tmp->next->next=NULL;
            tmp->next->val=d;
            tmp=tmp->next;
        }
    printfl(l);
    printf("倒数第几位？：");
    scanf("%d",&d);
    l=removeNthFromEnd(l,d);
    printfl(l);
    return 0;
}

void printfl(struct ListNode* l)
{
    for(;l!=NULL;l=l->next)
    {
        printf("%d  ",l->val);
    }
    printf("\n");
    return;
}

 void push(struct ListNode *l)
 {
     stack *tmp;
     tmp=(stack*)malloc(sizeof(stack));
     tmp->ptr=l;
     tmp->next=top;
     top=tmp;
     return;
 }
 struct ListNode *pop(void)
 {
     stack *stmp;struct ListNode* ltmp;
     stmp=top;
     top=top->next;
     ltmp=stmp->ptr;
     free(stmp);
     return ltmp;
 }
