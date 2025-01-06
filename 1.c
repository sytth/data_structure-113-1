#include <stdio.h>
#include <stdlib.h>
void allocArray(int **p, int m, int n)
{
    *p = (int *)malloc(m * n * sizeof(int));
}

int main()
{
    int *array;
    int j, k;
    allocArray(&array, 5, 10);

    for(j = 0;j < 5;j ++){
        for(k = 0;k < 10;k ++){
        array[j * 10 + k] = j * 10 + k;
        }
    }

    for(j = 0;j < 5;j ++){
        for(k = 0;k < 10;k ++){
            printf("%p ", &(array[j * 10 + k]));
        }
    }

    free(array);
    
    return 0;
}
