#include<stdio.h>
#include<stdlib.h>
#include"circle_queue.h"

void initQueue(Queue *q) {
    (*q) = (struct queue*)malloc(sizeof(struct queue));
    if ((*q) == NULL) {
        printf("memory allocation failed!\n");
        exit(0);
    }
    (*q)->q = (ElemType *) malloc(sizeof(ElemType) * INI_SIZE);
    if ((*q)->q == NULL) {
        printf("memory allocation failed!\n");
        exit(0);
    }
    (*q)->f = 0;
    (*q)->s = 0;
    (*q)->size = INI_SIZE;
    (*q)->length = 0;
}

ElemType deQueue(Queue q) {
    if (q->length == 0) {
        printf("queue is empty!\n");
        return -1000;
    }
    --q->length;
    int res = q->q[q->s];
    q->s = (q->s + 1) % q->size;
    return res;
}

int enQueue(Queue que, ElemType e) {
    if (que->size == que->length) {
        printf("cant increase the queue!\n");
        return 0;
    }
    ++que->length;
    que->q[que->f] = e;
    que->f = (que->f + 1) % que->size;
    return 1;
}

int isEmpty(Queue q) {
    if(q->length == 0) {
        return 1;
    }
    return 0;
}

void printQueue(Queue que) {
    printf("len:%d  ; size:%d ; s:%d ; f:%d \n", que->length, que->size, que->s, que->f);
    if (que->length != 0) {
        printf("elem:\n");
    }
    int i = que->s;
    if (que->length == que->size) {
        printf("%d ", que->q[i++]);
    }
    while (i != que->f) {
       printf("%d ", que->q[i++]);
       i %= que->size;
   }
   printf("\n");
}
