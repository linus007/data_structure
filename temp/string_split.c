#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"string_split.h"


/**************************************************
 *
 * 创建一个利用尾插法的单链表
 *
***************************************************/
void createWordLinkList(word_LinkList *wl) {
    (*wl) = (word_LinkList)malloc(sizeof(word_Node));
    if ((*wl) == NULL) {
        printf("LinkList creation failed!\n");
        exit(0);
    }
    (*wl)->next = NULL;
    (*wl)->w_len = 0;
}
/**************************************************
 * 功能利用尾插法插入整个单词
 *
**************************************************/
void insert(word_LinkList l, const char *w, int len) {
    word_Node * node = (word_Node *) malloc(sizeof(word_Node));
    if (node == NULL) {
        printf("word_Node allocation failed!\n");
        exit(0);
    }
    strcpy(node->word, w);
    node->w_len = strlen(w);
    node->next = NULL;
    word_Node * prev = l;
    while (prev->next != NULL) {
        prev = prev->next;
    }
    prev->next = node;
}
/****************************************
 *
 * 清除链表所有的节点并，释放空间
 *
*****************************************/ 
void clear_WordLinkList(word_LinkList *l) {
    word_Node * next;
    word_Node * cur;
    next = (*l)->next;
    while (next != NULL) {
        cur = next;
        next = next->next;
        free(cur);
        cur = NULL;
    }
    (*l)->next = NULL;
}

/**************************************************
 *
 * 删除整个链表
 *
***************************************************/
void delete_WordLinkList(word_LinkList *l) {
    if (*l != NULL) {
        clear_WordLinkList(l);
        free(*l);
        *l = NULL;
    }
}

/**************************************************
 *
 *读取一个节点的单词，并返回下一个节点的指针
 *
***************************************************/
word_Node * readWord(word_Node *cur, char arr[], int *len) {
    strcpy(arr, cur->word);
    *len = cur->w_len;
    return cur->next;
}
/******************************************
 *
 *判断一个字符是否在一个字符串中
 *
 *******************************************/
int isInArray(char c, char *arr, int len) {
    int i;
    for (i = 0; i < len; ++i) {
        if (arr[i] == c) {
            return 1;
        }
    }
    return 0;
}

/**************************************************
 *
 * 输出整个链表记录的单词
 *
***************************************************/
void printWordLinkList(word_LinkList l) {
    word_Node * cur = l->next;
    while (cur != NULL) {
        printf("%s ", cur->word);
        cur = cur->next;
    }
    printf("\n");
}

/**************************************************
 *
 * 返回整个链表的长度
 *
***************************************************/
int len_WordLinkList(word_LinkList l) {
    word_Node * cur = l->next;
    int len = 0;
    while (cur != NULL) {
        ++len;
        cur = cur->next;
    }
    return len;
}

/**************************************************
 *
 * 读入一个字符串，并将单词分离，插入单链表
 *
***************************************************/
void readString(word_LinkList l, char *arr, int len_arr) {
    int i;
    char specialCS[10] = ",\"?;'!";
    char word[MAX_LEN];
    int j = 0;
    for (i = 0; i < len_arr; ++i) {
        if (isInArray(arr[i], specialCS, 6) == 1) {
            if (j != 0) {
                // 添加单词
                word[j] = '\0';
                insert(l, word, j);
                // 添加标点符号
                j = 0;
            }
            // 添加标点符号
            word[j++] = arr[i];
            word[j] = '\0';
            insert(l, word, j);
            j = 0;
        } else if (arr[i] == ' ') {
            if (j != 0) {
                word[j] = '\0';
                insert(l, word, j);
                j = 0;
            }
        } else {
            word[j++] = arr[i];
            if (i == strlen(arr) - 1) {
                word[j] = '\0';
                insert(l, word, j);
            }
        }
    }
}
/**********************************************
 *
 * 函数测试
 *
***********************************************/
/*
int main() {
    char arr[100] = "? dda sdfas dds! efef!";
    word_LinkList l;
    createWordLinkList(&l);
    printWordLinkList(l);
    readString(l, arr, strlen(arr));
    printWordLinkList(l);
    char word[100];
    int len;
    word_Node * n = readWord(l->next->next, word, &len);
    printf("cur:%s, next:%s\n", word, n->word);
    clear_WordLinkList(&l);
    delete_WordLinkList(&l);
    printWordLinkList(l);
}*/
