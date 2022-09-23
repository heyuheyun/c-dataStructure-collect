#include <stdio.h>
#include <stdlib.h>

int kmp(char *s, char *tag);

int main()
{
    char a[100];
    int i = 0, j;
    printf("ÇëÊäÈë×Ö·û´®£º");
    a[i] = getchar();
    while (a[i++] != '\n')
    {
        a[i] = getchar();
    }
    char s[--i];
    for (j = 0; j < i; j++)
    {
        s[j] = a[j];
    }
    s[i] = '\0';

    printf("ÇëÊäÈËÄ¿±ê×Ö·û´®£º");
    a[i = 0] = getchar();
    while (a[i++] != '\n')
    {
        a[i] = getchar();
    }
    char tag[--i];
    for (j = 0; j < i; j++)
    {
        tag[j] = a[j];
    }
    tag[i] = '\0';
    printf("%s\n", s);
    printf("%s\n", tag);
    printf("%d", kmp(s, tag));
    return 0;
}

int kmp(char *s, char *tag)
{
    int i = 1, n[25], j = 0;
    n[0] = 0;
    while (tag[i] != '\0')
    {
        if (tag[i] == tag[j])
            n[i++] = 1 + j++;
        else
        {
            if (j == 0)
                n[i++] = 0;
            else
                j = n[j - 1];
        }
    }
    for (i = 0; i < 12; i++)
    {
        printf("%d  ", n[i]);
    }
    printf("\n");
    for (i = 0, j = 0; s[i] != '\0';)
    {
        if (tag[j] == s[i])
        {
            i++;
            j++;
            if (tag[j] == '\0')
                return 1;
        }
        else
        {
            if (j == 0)
                i++;
            else
                j = n[j - 1];
        }
    }
    return 0;
}
