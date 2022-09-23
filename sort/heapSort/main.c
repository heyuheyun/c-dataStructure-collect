#include <stdio.h>
#include <stdlib.h>

void sift(int *a, int low, int high);
void heapSort(int *a, int n);

int main()
{
    int a[30], i = 1, j;
    printf("«Î ‰»Î");
    do
    {
        scanf("%d", &a[i++]);
    } while (getchar() != '\n');
    int data[i--];
    for (j = 1; j <= i; j++)
        data[j] = a[j];
    for (j = 1; j <= i; j++)
        printf("%3d", data[j]);
    printf("\n");
    heapSort(data, i);
    for (j = 1; j <= i; j++)
        printf("%3d", data[j]);
    return 0;
}

void sift(int *a, int low, int high)
{
    int i = low, j = i * 2, temp;
    temp = a[i];
    while (j <= high)
    {
        if (j < high && a[j] < a[j + 1])
            j++;
        if (temp < a[j])
        {
            a[i] = a[j];
            i = j;
            j = i * 2;
        }
        else
            break;
    }
    a[i] = temp;
    return;
}
void heapSort(int *a, int n)
{
    int i, temp;
    for (i = n / 2; i >= 1; i--)
        sift(a, i, n);
    for (i = n; i >= 2; i--)
    {
        temp = a[1];
        a[1] = a[i];
        a[i] = temp;
        sift(a, 1, i - 1);
    }
    return;
}
