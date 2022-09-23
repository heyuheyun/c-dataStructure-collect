#include <stdio.h>
#include <stdlib.h>

void select_sort(int *a,int n);
void select_sort2(int *a,int n);

int main()
{
    int a[20],i=0,j;
    printf("«Î ‰»Î£∫");
    do
    {
        scanf("%d",&a[i]);
        i++;
    }while(getchar()!='\n');
    select_sort2(a,i-1);
    for(j=0;j<=i-1;j++)
        printf("%4d",a[j]);
    return 0;
}

void select_sort(int *a,int n)
{
    int tmp1,tmp2,min,i,j;
    for(i=0;i<n;i++)
    {
        min=a[i];
        for(j=i+1;j<=n;j++)
        {
            if(a[j]<min)
            {
                min=a[j];
                tmp1=j;
            }
        }
        if(a[i]>min)
        {
            tmp2=a[i];
            a[i]=a[tmp1];
            a[tmp1]=tmp2;
        }
    }
}
void select_sort2(int *a,int n)
{
    int i,j,k,tmp;
    for(i=0;i<n;i++)
    {
        k=i;
        for(j=i+1;j<=n;j++)
            if(a[k]>a[j]) k=j;
        if(a[k]<a[i])
        {
            tmp=a[i];
            a[i]=a[k];
            a[k]=tmp;
        }
    }
}
