#include <stdio.h>
#include <stdlib.h>

void quick_sort(int *a, int low, int high);

int main()
{
    int a[20], i = 0, j;
    printf("«Î ‰»Î£∫");
    do
    {
        scanf("%d", &a[i]);
        i++;
    } while (getchar() != '\n');
    quick_sort(a, 0, i - 1);
    for (j = 0; j <= i - 1; j++)
        printf("%4d", a[j]);
    return 0;
}

void quick_sort(int *a, int low, int high)
{
    int tmp = a[low], i = low, j = high;
    while (i != j)
    {
        for (; tmp < a[j] && i != j; j--)
            ;
        if (i != j)
            a[i++] = a[j];
        for (; tmp > a[i] && i != j; i++)
            ;
        if (i != j)
            a[j--] = a[i];
    }
    a[i] = tmp;
    if (low != i)
        quick_sort(a, low, i - 1);
    if (high != i)
        quick_sort(a, i + 1, high);
}
