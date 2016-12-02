#include<stdio.h>
#include<stdlib.h>
#include"linkList.h"

int initLinkList(LinkList *l, char header) {
    (*l) = (struct Link*) malloc (sizeof(struct Link));
    if ((*l) == NULL) {
        printf("memory allocation failed!\n");
        return 0;
    }
    (*l)->header = header;
    (*l)->len = 0;
    (*l)->next = NULL;
    return 1;
}

// 插入节点
void insertLinkList(LinkList l, char header, int weight) {
    Node * n = (Node*) malloc(sizeof(Node));
    if (n == NULL) {
        printf("memory allocation failed\n");
        exit(0);
    }
    n->header = header;
    n->weight = weight;
    n->next = l->next;
    l->next = n;
    ++l->len;
}
// 删除一个节点
int delete_Node_In_LinkList(LinkList l, char header) {
    Node *n = l->next;
    while (n != NULL && n->header != header) {
        n = n->next;
    }
    if (n != NULL) {
        --l->len;
        free(n);
        n = NULL;
        return 1;
    }
    return 0;
}
// 输出整个链表
void printLinkList(LinkList l) {
    if (l != NULL) {
        printf("header:%c ; ", l->header);
        Node *n = l->next;
        while ((n) != NULL) {
            printf("%c , weight:%d ;", n->header, n->weight);
            n = n->next;
        }
        printf("\n");
    }
}
// 删除整个链表
void delete_LinkList(LinkList *l) {
    Node *n = (*l)->next;
    Node *p = n;
    while (n != NULL) {
        n = p->next;
        free(p);
        p = NULL;
    }
    free(*l);
    *l = NULL;
}
