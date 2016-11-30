#include <stdio.h>
#include <stdlib.h>
#define MAX_LENGTH 20

int selector[MAX_LENGTH];
int count_global = 0;
void greedy_activity_selector(int *s, int *f, int n) {
    selector[count_global++] = 1;
    int i = 1;
    int m = 2;
    for (; m <=n; ++m) {
        if (s[m] >= f[i]) {
            selector[count_global++] = m;
            i = m;
        }
    }
}
void printArray(int *arr, int n) {
    int i;
    for (i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
int main() {
    int s[13] = {0, 1, 3, 0, 5, 3, 5,  6,  8,  8,  2, 12, 100};
    int f[13] = {0, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 100};
    greedy_activity_selector(s, f, 11);
    printArray(selector, count_global);

    printf("hello world\n");
}
