#include<stdio.h>
#include<stdlib.h>

// initial lenght
#define INI_SIZE 40

typedef int ElemType;

typedef struct queue{
    // 队列
    ElemType * q;
    int size;
    int length;
    int s;
    int f;
} *Queue;


void initQueue(Queue *q);

ElemType deQueue(Queue q);

int enQueue(Queue que, ElemType e);

void printQueue(Queue que);
