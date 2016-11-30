#include<stdio.h>
#define MAX_LENGTH 5

// 用来存储二项式系数
int arr[MAX_LENGTH + 1][MAX_LENGTH + 1];

void initBinomialTable() {
    int i = 0;
    while (i < MAX_LENGTH + 1) {
        int j = 0;
        while (j <= i) {
            if (j == 0 || j == i){
                arr[i][j] = 1;
            } else {
                arr[i][j] = arr[i - 1][j] + arr[i - 1][j - 1];
            }
            ++j;
        }
        ++i;
    }
}

int main() {
    initBinomialTable();
    printf("%d\n", arr[5][2]);
    return 0;
}
