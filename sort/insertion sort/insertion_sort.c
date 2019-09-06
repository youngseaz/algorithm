#include<stdio.h>

void insertion_sort(int *arr, unsigned int arrSize)
{
    int i, j, tmp;
    for (i = 1; i < arrSize; ++i)
    {
        j = i;
        tmp = arr[i];
        for (; arr[j - 1] > arr[j] && j > 0; )
        {
            arr[j] = arr[j - 1];
            --j;
        }
        arr[j] = tmp;
    }
}

int main()
{
    int test[] = {5, 1, 3, 2, 9, 6, 7, 10};
    unsigned int size = sizeof(test)/sizeof(int);
    insertion_sort(test, size);
    for (int i = 0; i < size; ++i)
    {
        printf("%d ", test[i]);
    }
}
        
        
