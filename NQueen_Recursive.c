#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define N 4
// 统计解的个数
int count = 0;
// 用以表示棋盘
int q[N];


// 输出一个解
void print() {
    int i, j;
    ++count;
    printf("第%d个解:", count);
    printf("\n");
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            if (q[i] != j) {
                printf("%c ", '*');
            } else {
                printf("%c ", '#');
            }
        }
        printf("\n");
    }
}

int valid(int row, int col) {
    int j;
    for (j = 0; j < row; ++j) {
        if (q[j] == col || abs(j - row) == abs(col - q[j])) {
            return 0;
        }
    }
    return 1;
}

void queen(int k) {
    int j;
    // 当查找到最后一个时,由于0~N-1是合法的解,
    // 所以可以输出
    if (k >= N) {
        print();
    } else {
        // 没有查找完, 应当继续查找
        for (j = 0; j < N; ++j) {
            if (valid(k, j)) {
                q[k] = j;
                queen(k + 1);
            }
        }
    }
}

int main() {
    queen(0);
}
