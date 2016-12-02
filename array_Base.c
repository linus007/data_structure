#include<stdio.h>
#include<stdlib.h>
#include"array_Base.h"
int **create2DArray(int m, int n) {
    if (m <= 0 || n <= 0) {
        printf("param illegal!\n");
        exit(0);
    }
    int **arr = (int **)malloc(sizeof(int *) * m);
    if (arr == NULL) {
        printf("memory allocation failed\n");
        exit(0);
    }
    int i;
    for (i = 0; i < m; ++i) {
        arr[i] = (int *) malloc(sizeof(int) * n);
        if (arr[i]  == NULL) {
            printf("memory allocation failed!\n");
            exit(0);
        }
    }
    return arr;
}

void init2DArray(int **arr, int m, int n) {
    if (arr == NULL) {
        printf("param illegal\n");
        exit(0);
    }
    int i, j;
    for (i = 0; i < m; ++i) {
        for (j = 0; j < n; ++j) {
            scanf("%d", &arr[i][j]);
        }
        getchar();
    }
    setbuf(stdin, NULL);/*清空缓冲区*/
}

void print2DArray(int **arr, int m, int n) {
    int i, j;
    for (i = 0; i < m; ++i) {
        for (j = 0; j < n; ++j) {
            printf("%3d ", arr[i][j]);
        }
        printf("\n");
    }
}
