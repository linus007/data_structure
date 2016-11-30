#include<stdio.h>
#include<stdlib.h>
#define MAX_LENGTH 20
int count_global = 0;
int select_set[MAX_LENGTH];

void recusive_Activity_Selector(int *s, int *f, int i, int n) {
    int m = i + 1;
    // 寻找第一个满足的活动
    while (m <= n && s[m] < f[i]) {
        ++m;
    }
    if (m <= n) {
        select_set[count_global++] = m;
        recusive_Activity_Selector(s, f, m, n);
    }
}

void printArray(int *arr, int length) {
    int i = 0;
    for (; i < length; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int s[13] = {0, 1, 3, 0, 5, 3, 5,  6,  8,  8,  2, 12};
    int f[13] = {0, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    recusive_Activity_Selector(s, f, 0, 11);
    printArray(select_set, count_global);
    printf("hello world\n");
}
