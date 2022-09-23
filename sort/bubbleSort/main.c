#include <stdio.h>
#include <stdlib.h>

 void bbsort(int *liarray,int len)
    {
        int tmp=0,i,j;
        for(i=len;i>0;i--)
            {
            for(j=0;j<i;j++)
                {
                if(liarray[j]>liarray[j+1])
                    {
                    tmp=liarray[j];
                    liarray[j]=liarray[j+1];
                    liarray[j+1]=tmp;
                    }
                }
            }
    }

int main()
{
    int a[20],i=0,j;
    printf("«Î ‰»Î£∫");
    do
    {
        scanf("%d",&a[i]);
        i++;
    }while(getchar()!='\n');
    bbsort(a,i-1);
    for(j=0;j<=i-1;j++)
        printf("%4d",a[j]);
    return 0;
}

