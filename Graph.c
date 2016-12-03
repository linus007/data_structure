#include<stdio.h>
#include<stdlib.h>
#include"circle_queue.h"
#include"linkList.h"
#include"array_Base.h"

typedef enum{WHITE, GRAY, BLACK} color;
/**
 * 将一个邻接矩阵转换为邻接表
 * */
LinkList * adjMatrix_into_adjLinkList(int **mat, int n, char *headers) {
    LinkList *l = (LinkList *) malloc(sizeof(LinkList) * n);
    if (l == NULL) {
        printf("memroy alloxcation failed\n");
        exit(0);
    }
    int i;
    for (i = 0; i < n; ++i) {
        initLinkList(&l[i], headers[i]);
    }
    int j;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            if(mat[i][j] > 0) {
                insertLinkList(l[i], headers[j], mat[i][j]);
            }
        }
    }
    return l;
}

// 找到节点对应数组所在的位置
int findHeader(char header, char *headers, int n) {
    int i;
    for (i = 0; i < n; ++i) {
        if (header == headers[i]) {
            return i;
        }
    }
    return -1;
}

void BFS(LinkList *l, int n, char * headers) {
    // l 的第一个链表的头结点为根
    int color[n];
    // d表示个节点到根的距离
    int d[n];
    // p 表是各个节点的父亲节点
    int p[n];
    int i;
    // color 值为0,1,2分别为white,gray,black
    for (i = 1; i < n; ++i) {
        color[i] = 0;
        // 10000 表示一个无穷大的距离
        d[i] = 10000;
        // -1 表示没有父亲，即为根节点
        // 在这里这些顶点暂时为根节点
        p[i] = -1;
    }
    color[0] = 1;
    d[0] = 0;
    p[0] = -1;
    // 创建一个空队列
    Queue q;
    initQueue(&q);
    enQueue(q, 0);
    while(isEmpty(q) == 0) {
        int which = deQueue(q);
        // 找出which 的所有邻接点
        Node * cur = l[which]->next;
        while(cur != NULL) {
            int index = findHeader(cur->header, headers, n);
            if (color[index] == 0) {
                color[index] = 1;
                d[index] = d[which] + 1;
                p[index] = which;
                enQueue(q, index);
            }
            cur = cur->next;
        }
        color[which] = 2;
    }
    int r;
    printf("hello \n");
    for (r = 1; r < n; ++r) {
        printf("p:%c , d: %2d\n",headers[p[r]], d[r]);
    }
}

// 定义最大的定点数
#define MAX_VERTEXES 20
int color_dfs[MAX_VERTEXES];
// 用来记录节点的父节点
int p_dfs[MAX_VERTEXES];
// 记录全局的时间
int time_dfs = 0;
// 节点开始访问的时间
int d_dfs[MAX_VERTEXES];
// 用来记录节点结束访问的时间
int f_dfs[MAX_VERTEXES];

void DFS_Visit(LinkList *l, char *headers, int u, int n) {
    ++time_dfs;
    color_dfs[u]  = GRAY;
    d_dfs[u] = time_dfs;
    Node * cur = l[u]->next;
    while(cur != NULL) {
        int index =findHeader(cur->header, headers, n);
        if (color_dfs[index] == WHITE) {
            p_dfs[index] = u;
            DFS_Visit(l, headers, index, n);
        }
        cur = cur->next;
    }
    color_dfs[u]  = BLACK;
    ++time_dfs;
    f_dfs[u] = time_dfs;
}

void DFS(LinkList *l, int n, char *headers) {
    int i;
    // color 值为 0 表示为white, 1 表示为gray, 2 表示为black
    for (i = 0; i < n; ++i) {
        color_dfs[i] = WHITE;
        p_dfs[i]  = -1;
    }
    for (i = 0; i < n; ++i) {
        if (color_dfs[i] == WHITE) {
            DFS_Visit(l, headers, i, n);
        }
    }
}


int main() {
    /*   邻接矩阵向邻接表的转换验证代码
    int **mat = create2DArray(3, 3);
    init2DArray(mat, 3, 3);
    char headers[3] = {'a', 'b', 'c'};
    LinkList *l = adjMatrix_into_adjLinkList(mat, 3, headers);
    int i;
    for (i = 0; i < 3; ++i) {
        printLinkList(l[i]);
    }*/
    
    
    /* BFS的验证代码
    int n = 5;
    char headers[5] = {'a', 'b', 'c', 'd', 'e'};
    int **mat = create2DArray(n, n);
    printf("请输入一个5*5的邻接矩阵:\n");
    init2DArray(mat, n, n);
    print2DArray(mat, n, n);
    LinkList *l = adjMatrix_into_adjLinkList(mat, n, headers);
    print2DLinkList(l, n);
    BFS(l, n, headers);*/
    
    int n = 6;
    char headers[6] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int **mat = create2DArray(n, n);
    printf("请输入一个6*6的邻接矩阵:\n");
    init2DArray(mat, n, n);
    print2DArray(mat, n, n);
    LinkList *l = adjMatrix_into_adjLinkList(mat, n, headers);
    print2DLinkList(l, n);
    DFS(l, n, headers);
    printArray_Int(p_dfs, n);
    printArray_Int(d_dfs, n);
    printArray_Int(f_dfs, n);
    return 0;
}
