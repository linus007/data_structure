#include<stdio.h>
#include<stdlib.h>

// 创建一个二维数组
int **create2DArray(int m, int n);

// 给数组输入值
void init2DArray(int **arr, int m, int n);

// 输出二维数组
void print2DArray(int **arr, int m, int n);


// 输出一个一维数组
void printArray(int *arr, int n);

// 输出一个类似于int arr[len]的数组
void printArray_Int(int *arr, int n);
