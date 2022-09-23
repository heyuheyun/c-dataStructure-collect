#include <stdio.h>
#include <stdlib.h>

void merge(int *a, int low, int mid, int high);
void mergeSort(int *a, int low, int high);

int main()
{
    int a[30], i = 1, j;
    printf("«Î ‰»Î£∫");
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
    mergeSort(data, 1, i);
    for (j = 1; j <= i; j++)
        printf("%3d", data[j]);
    return 0;
    return 0;
}

void merge(int *a, int low, int mid, int high)
{
    int tmp[high + 1];
    int i = low, j = mid + 1, x = 1;
    while (i <= mid && j <= high)
    {
        if (a[i] < a[j])
            tmp[x++] = a[i++];
        else
            tmp[x++] = a[j++];
    }
    while (i <= mid)
        tmp[x++] = a[i++];
    while (j <= high)
        tmp[x++] = a[j++];
    for (x = 1, i = low; i <= high; x++, i++)
        a[i] = tmp[x];
    return;
}
void mergeSort(int *a, int low, int high)
{
    int mid = (low + high) / 2;
    if (low < high)
    {
        mergeSort(a, low, mid);
        mergeSort(a, mid + 1, high);
        merge(a, low, mid, high);
    }
    return;
}
