#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a[20],i=1,tmp,j;
    a[0]=-256;
    printf("ÇëÊäÈë£º");
    scanf("%d",&a[1]);
    while(getchar()!='\n')
    {
        scanf("%d",&tmp);
        for(j=i;j>=0;j--)
        {
            if(tmp>a[j])
            {
                a[j+1]=tmp;
                break;
            }
            else a[j+1]=a[j];
        }
        i++;
    }
    printf("\n");
    for(j=1;j<=i;j++)
    {
        printf("%4d",a[j]);
    }
    return 0;
}

