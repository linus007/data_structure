#include<stdio.h>
#include<stdlib.h>

int max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}
/**
 * 生成一个二维数组
 * */
int **create2DArray(int m, int n) {
    int **p = (int **) malloc(sizeof(int*) * m);
    if (p == NULL) {
        printf("memory allocation failed!\n");
        exit(0);
    }
    int i = 0;
    for (; i < m; ++i) {
        p[i] = (int *) malloc(sizeof(int) * n);
        if (p[i] == NULL) {
            printf("memory allocation failed!\n");
            exit(0);
        }
    }
    return p;
}
/**
 * 将数组清0
 *
 * */
void setZero2DArray(int **arr, int m, int n) {
    int i, j;
    for(i = 0; i < m; ++i) {
        for (j = 0; j < n; ++j) {
            arr[i][j] = 0;
        }
    }
}
void print2DArray(int **arr, int m, int n) {
    int i, j;
    for (i = 0; i < m; ++i) {
        for (j = 0; j < n; ++j) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}
/**
 * 输出一条最长公共子序列
 * */
void printLCS(char *arr1, int **b, int i, int j) {
    if (i == 0 || j == 0) {
        return;
    }
    if (b[i][j] == 1) {
        printLCS(arr1, b, i - 1, j - 1);
        printf("%c ", arr1[i - 1]);
    } else if (b[i][j] == 2) {
        printLCS(arr1, b, i - 1, j);
    } else if (b[i][j] == 3){
        printLCS(arr1, b, i, j - 1);
    }
}

void lcs(char *arr1, int m, char *arr2, int n) {
    // 保存i，j最大公共子序列长度
    int **c = create2DArray(m + 1, n + 1);
    // 简化最优解的构造
    int **b = create2DArray(m + 1, n + 1);
    int i = 0;
    while (i <= n) {
        c[i][0] = 0;
        ++i;
    }
    int j = 0;
    while(j <= m) {
        c[0][j++] = 0;
    }
    for (i = 1; i <= m; ++i) {
        for (j = 1; j <= n; ++j) {
            if (arr1[i - 1] == arr2[j - 1]) {
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = 1;
            } else {
                if (c[i - 1][j] > c[i][j - 1]) {
                    c[i][j] = c[i - 1][j];
                    b[i][j] = 2;
                } else {
                    c[i][j] = c[i][j - 1];
                    b[i][j] = 3;
                }
            }
        }
    }
    print2DArray(c, n + 1, n + 1);
    print2DArray(b, n + 1, n + 1);
    printLCS(arr1, b, m, n);
}


int main() {
    char arr1[7] = {'a', 'b', 'c', 'b', 'd', 'a', 'b'};
    char arr2[6] = {'b', 'd', 'c', 'a', 'b', 'a'};
    lcs(arr1, 7, arr2, 6);
    return 0;
}
