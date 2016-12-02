#include<stdio.h>
#include<stdlib.h>

// 子节点
typedef struct Node{
    char header;
    struct Node *next;
    int weight;
}Node;

// 头结点
typedef struct Link{
    char header;
    int len;
    Node *next;
} *LinkList;
int initLinkList(LinkList *l, char header);

// 插入节点
void insertLinkList(LinkList l, char header, int weight);

// 删除一个节点
int delete_Node_In_LinkList(LinkList l, char header);

// 输出整个链表
void printLinkList(LinkList l);

// 输出一个二维链表
void print2DLinkList(LinkList *l, int n);

// 删除整个链表
void delete_LinkList(LinkList *l);
