#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define QUEEN 4     // 皇后的数目
#define INITIAL -1000   // 棋盘的初始值

int a[QUEEN];       // 使用一维数组表示棋盘
int n = 0;          // 用以记录棋盘皇后位置的方法的次数
// 初始化棋盘数组值
void init() {
    int *p = a;
    for(p = a; p < a + QUEEN; ++p) {
        *p = INITIAL;
    }
}

int valid(int row, int col) {
    int i;
    for (i = 0; i < QUEEN; ++i) {
        // 对棋盘进行扫描判断是否合法
        if(a[i] == col || abs(i - row) == abs((a[i] - col))) {
            return 0;
        }
    }
    return 1;
}

void print() {
    int i, j;
    for (i = 0; i < QUEEN; ++i) {
        for (j = 0; j < QUEEN; ++j) {
            if (a[i] != j) {
                printf("%c ", '*');
            } else {
                printf("%c ", '#');
            }
        }
        printf("\n");
    }
    for(i = 0; i < QUEEN; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
    printf("---------------------------------------\n");
}

void queen() {
    int i = 0;
    int j = 0;
    while (i < QUEEN) {
        while (j < QUEEN) {
            if(valid(i, j)) {
                a[i] = j;
                j = 0;
                break;
            }
            // 否则说明 第i行和第j列不能放置此皇后
            ++j;
        }
        // 说明在第i行找不到皇后能够放置的列,
        // 所以需要回溯
        if (a[i] == INITIAL) {
            // 当回溯到i == 0时,表明已经没有可能的情况可查找
            if (i == 0) {
                break;
            } else {
                // 进行回溯
                --i;
                // 把上一行的皇后往后移动一列
                j = a[i] + 1;
                // 把上一行的皇后位置清除,并重新探测
                a[i] = INITIAL;
                continue;
            }
        }

        if (i == QUEEN - 1) {
            printf("answer %d: \n", ++n);
            print();
            // 为了找出所有N皇后的所有解,此时应该清除当前位置
            // 并从当前位置的下一列重新探测
            j = a[i] + 1;
            a[i] = INITIAL;
            continue;
        }
        ++i;
    }
}


int main() {
    init();
    queen();
    system("pause");
    return 0;
}
