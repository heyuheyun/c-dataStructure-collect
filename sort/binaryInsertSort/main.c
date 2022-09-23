#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a[20],i=1,j,tmp,high,low,mid;
    a[0]=-256;
    printf("«Î ‰»Î£∫");
    scanf("%d",&a[1]);
    while(getchar()!='\n')
    {
        scanf("%d",&tmp);
       for(low=1,high=i;low<=high;)
        {
            mid=(high+low)/2;
            if(tmp>=a[mid]) low=mid+1;
            else high=mid-1;
        }
        for(j=i;low<=j;j--)
        {
            a[j+1]=a[j];
        }
        a[low]=tmp;
        i++;
    }
    printf("\n");
    for(j=1;j<=i;j++)
    {
        printf("%4d",a[j]);
    }
    return 0;
}
