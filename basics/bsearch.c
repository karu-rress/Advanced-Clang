#include <stdio.h>
#include <stdlib.h>
#include <search.h>

int intcmp(const void *restrict v1, const void *restrict v2);

int main(void)
{
    int find_value;
    int count;
    int *result;
    int array[] = { 4, 3, 5, 1, 2, 8, 7, 9, 6 };

    count = sizeof(array) / sizeof(array[0]);
    qsort(array, count, sizeof(array[0]), intcmp);

    find_value = 3;
    result = bsearch(&find_value, array, count, sizeof(array[0]), intcmp);

    if (result) {
        printf("%d을 찾았습니다.\n", find_value);
    }
    
    return 0;
}

int intcmp(const void *restrict v1, const void *restrict v2) {
    return *(int *)v1 - *(int *)v2;
}