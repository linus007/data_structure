#include<stdio.h>
#include<stdlib.h>
int ** create2DArray(int m, int n) {
    int **p;
    p = (int **) malloc(sizeof (int *) * m);
    if (p == NULL) {
        printf("memory allocation failed!\n");
        exit(0);
    }
    int i;
    for (i = 0; i < n; ++i) {
        p[i] = (int *) malloc(sizeof (int) * n);
        if (p[i] == NULL) {
            printf("memory allocation failed\n");
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

void write2DArray_into_txt(int **arr, int m, int n, int format) {
    FILE *fp;
    if ((fp =fopen("out.txt", "w")) == NULL) {
        printf("file cant be opened!\n");
        exit(0);
    } else {
        int i, j;
        for (i = 0; i < m; ++i) {
            for (j = 1; j < n; ++j) {
                fprintf(fp, "%3d ", arr[i][j]);
            }
            fputc('\n', fp);
        }
    }
}

int max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

int ** knapsack(int *v, int *s, int n, int c) {
    // produce a table
    int **V = create2DArray(n + 1, c + 1);
    int i;
    int j;
    for (i = 0; i <= n; ++i) {
        V[i][0] = 0;
    }
    for (j = 0; j <= c; ++j) {
        V[0][j] = 0;
    }
    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= c; ++j) {
            V[i][j] = V[i-1][j];
            if (s[i] <= j) {
                V[i][j] = max(V[i][j], V[i - 1][j - s[i]] + v[i]);
            }
        }
    }
    return V;
}
int main() {
    int **p;
    p = create2DArray(3, 4);
    print2DArray(p, 3, 4);
    printf("********************\n");
    int v[4] = {0, 60, 100, 120};
    int s[4] = {0, 10, 20, 30};
    int **p1 = knapsack(v, s, 3, 50);
    write2DArray_into_txt(p1, 4, 51, 0);
}
