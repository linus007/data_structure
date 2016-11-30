#include<stdio.h>

int max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}



void lcs(char *arr1, int n, char *arr2, int m, int L[][7]) {
    int i = 0;
    while (i <= n) {
        L[i][0] = 0;
        ++i;
    }
    int j = 0;
    while(j <= m) {
        L[0][j++] = 0;
    }
    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= m; ++j) {
            if (arr1[i - 1] == arr2[j - 1]) {
                L[i][j] = L[i - 1][j - 1] + 1;
            } else {
                L[i][j] = max(L[i - 1][j], L[i][j - 1]);
            }
        }
    }
}

void printArray(int arr[][7], int n) {
    int i = 0;
    while (i < n) {
        int j = 0;
        while (j < 7) {
            printf("%2d", arr[i][j++]);
        }
        ++i;
        printf("\n");
    }
}

int main() {
    char arr1[7] = {'a', 'b', 'c', 'b', 'd', 'a', 'b'};
    char arr2[6] = {'b', 'd', 'c', 'a', 'b', 'a'};
    int L[8][7];
    lcs(arr1, 7, arr2, 6, L);
    printf("%d \n", L[7][6]);
    printArray(L, 8);
    return 0;
}
