#include <stdio.h>
#include <stdlib.h>

int Max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}
int **create2DArray(int m, int n) {
    int **p = (int **) malloc(sizeof(int *) * m);
    if (p == NULL) {
        printf("memory alloctation failed!\n");
        exit(0);
    }
    int i;
    for (i = 0; i < n; ++i) {
        p[i] = (int *) malloc(sizeof(int ) * n);
        if (p[i] == NULL) {
            printf("memory allocation failed!\n");
            exit(0);
        }
    }
    return p;
}

void print2DArray(int **p, int m, int n) {
    int i, j;
    for (i = 0; i < m; ++i) {
        for (j = 0; j < n; ++j) {
            printf("%3d ", p[i][j]);
        }
        printf("\n");
    }
}

void clear2DArray(int **p, int m, int n) {
    int i, j;
    for (i = 0; i < m; ++i) {
        for (j = 0; j < n; ++j) {
            p[i][j] = 0;
        }
    }
}
int **activity_compatible(int *s, int *f, int n) {
    int **c = create2DArray(n, n);
    // 将所有哦 Sij 为空的 填为 0
    clear2DArray(c, n, n);
    int i = 0;
    // ai 和　ai+1 两节点之间并没有兼容的点存在
    for (i = 0; i < n; ++i) {
        c[i][i + 1] = 0;
    }
    // 剩下的可能相互兼容的情况
    for (i = n - 2; i >= 0; --i) {
        int j;
        for (j = i + 2; j < n; ++j) {
            int k;
            int max = 0;
            // max(c[i][k] + c[k][j] + 1)
            for (k = i +1; k < j; ++k) {
                if (f[i] <= s[k] && f[k] <= s[j]) {
                    max = Max(max, c[i][k] + c[k][j] + 1);
                }
            }
            c[i][j] = max;
        }
    }
    return c;
}

int main() {
    int s[13] = {0, 1, 3, 0, 5, 3, 5,  6,  8,  8,  2, 12, 100};
    int f[13] = {0, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 100};
    int **p = activity_compatible(s, f, 13);
    print2DArray(p, 13, 13);
    printf("helloI\n");

}
