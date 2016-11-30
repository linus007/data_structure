#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
int ** create2DArray(int m, int n) {
    int **p = (int **) malloc(sizeof(int *) * m);
    if (p == NULL) {
        printf("memory allocation failed\n");
        exit(0);
    }
    int i;
    for(i = 0; i < m; ++i) {
        p[i] = (int *) malloc(sizeof(int) * n);
        if (p[i] == NULL) {
            printf("memory allocation failed\n");
            exit(0);
        }
    }
    return p;
}

void print_Optimal_parens(int **s, int i, int j) {
    if (i == j) {
        printf("A%d", i);
    } else {
        printf("(");
        print_Optimal_parens(s, i, s[i][j]);
        print_Optimal_parens(s, s[i][j] + 1, j);
        printf(")");
    }

}

void print2DArray(int **arr, int m, int n) {
    int i, j;
    for (i = 0; i < m; ++i) {
        for (j = 0; j < n; ++j) {
            printf("%4d ", arr[i][j]);
        }
        printf("\n");
    }
}

void matrix_Chain_Order(int *p, int n) {
    int len = n - 1;
    int **m = create2DArray(len, len);
    int **s = create2DArray(len, len);
    int i;
    for (i = 0; i < len; ++i) {
        m[i][i] = 0;
    }
    int l;
    for (l = 2; l <= len; ++l) {
        for (i = 0; i < len - l + 1; ++i) {
            int j = i + l - 1;
            int k;
            m[i][j] = 32767;
            for (k = i; k < j; ++k) {
                // min {m[i][k] + m[k + 1]j[j] + p[i]*p[k+1]*p[j+1]}
                int q = m[i][k] + m[k + 1][j] + p[i] * p[k + 1] * p[j + 1];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
    print2DArray(m, len, len);
    print2DArray(s, len, len);
    print_Optimal_parens(s, 0, 4);
}
int main() {
    int p[10] = {1, 4, 2, 4, 2, 5};
    matrix_Chain_Order(p, 6);
    printf("hello world!\n");
}
