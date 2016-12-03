#include<stdio.h>
#include<stdlib.h>

/**
 * 求一个数组中的最小元素，并返回最小元素
 * ＠param arr　待求数组
 * ＠param len 数组长度
 * @return 返回最小元素索引
 *
 * */
int minInArray(int *arr, int len) {
    if (len <= 0) {
        return -1;
    } else if (len == 1) {
        return 0;
    }
    int i = 1;
    int index = 0;
    while (i < len) {
        if (arr[i] < arr[index]) {
            index = i;
        }
        ++i;
    }
    return index;
}

void printArray(int *arr, int len) {
    int i = 0;
    while (i < len) {
        printf("%d ", arr[i++]);
    }
    printf("\n");
}



/****************************************/
/*            非功能函数                */
/****************************************/


#define MAX_LENGTH 6

/**
 * 从一个邻接矩阵中找出一个节点的后继，并保存到数组arr中去，
 * @param arr 邻接矩阵
 * @param dim 邻接矩阵的维度
 * @param arr1邻接矩阵的后继
 * @param j 邻接矩阵中节点j
 * @return 返回后继的个数
 * */
int follows(int arr[][MAX_LENGTH], int j, int *arr1) {
    int count = 0;
    int i = 0;
    while (i < MAX_LENGTH) {
        if (arr[j][i] != -1) {
            arr1[count++] = i;
        }
        ++i;
    }
    return count;
}
// 用来记录所走过的路径
int road[MAX_LENGTH];
int steps = 0;
int shortPath(int arr[][MAX_LENGTH], int i) {
    
    // 存储后继节点
    int nexts[MAX_LENGTH];
    
    // 用来保存节点i到后继的距离
    int distance[MAX_LENGTH];
    
    // 计算过程中的最短距离
    int shortest;
    
    int size = follows(arr, i, nexts);
    
    if (size == 0) {
        shortest = 0;
    } else {
        int j = 0;
        while (j < size) {
            // opt(Xk, n) = opt((xki, uk) + (xk+1, n))
            distance[j] = shortPath(arr, nexts[j]) + arr[i][nexts[j]];
            ++j;
        }
        int minIndex = minInArray(distance, size);
        shortest = distance[minIndex];
    }
    return shortest;
}
int main() {
    /*
    int arr[4][4] = {
        {-1, 2, 3, -1},
        {1, 0, 3, -1},
        {-1, 2, -3, -1},
        {-1, -2, -3, -1}
    };
    int arr1[4];
    int count = follows(arr, 4, 1, arr1);
    printf("count:%d\n", count);
    printArray(arr1, count);
    */
    
    /*
    int arr[10] = {67,789,045,67,89};
    int i = minInArray(arr, 1);
    printf("min:%d\n", i);

    printf("hello world!\n"); */

    int path[MAX_LENGTH][MAX_LENGTH] = {
        {-1, 1, 2, -1, -1, -1},
        {-1, -1, -1, 6, 1, -1},
        {-1, -1, -1, 4, 3, -1},
        {-1, -1, -1, -1, -1, 2},
        {-1, -1, -1, -1, -1, 1},
        {-1, -1, -1, -1, -1, -1},

    };
    int sp = shortPath(path, 0);
    printf("shortest:%d\n", sp);
}
