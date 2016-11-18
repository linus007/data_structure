#include<stdio.h>
#include<stdlib.h>
typedef int ElemType;
typedef enum {BLACK, RED} COLOR;
/**
 * 红黑树叶节点数据结构
 *
 * */
typedef struct RBTreeNode{
    ElemType data;
    struct RBTreeNode *p;
    struct RBTreeNode *left;
    struct RBTreeNode *right;
    COLOR color;
} RBTreeNode; 

/**
 *
 * 红黑树结构体
 * */
typedef struct {
    RBTreeNode *root;
    RBTreeNode *nilT;
}RBTreeRootNode, *RBTree;

/**
 * 生成一棵空的红黑树
 * */
int createRBTree(RBTree * tree) {
    RBTreeNode *nilT = (RBTreeNode *) malloc (sizeof (RBTreeNode));
    if (!nilT) {
        printf ("memory allocation failed!\n");
        exit(0);
    }
    nilT->data = 0;
    nilT->p = NULL;
    nilT->left = NULL;
    nilT->right = NULL;
    nilT->color = BLACK;
    *tree = (RBTree) malloc(sizeof(RBTreeRootNode));
    if (!(*tree)) {
        printf ("memory allocation failed!\n");
        exit(0);
    }
    (*tree)->root = NULL;
    (*tree)->nilT = nilT;
    return 1;
}
/**
 * 左旋
 * */
void leftRotate(RBTree rbt, RBTreeNode *x) {
    RBTreeNode * y = x->right;
    x->right = y->left;
    if (y->left != NULL) {
        y->left->p = x;
    }
    y->p = x->p;
    if (x->p == NULL) { // x节点原先为树根
        rbt->root = y;
    } else if (x == x->p->left) {
        x->p->left = y;
    } else {
        x->p->right = y;
    }
    y->left = x;
    x->p = y;
}

/**
 * 右旋
 * */
void rightRotate(RBTree rbt, RBTreeNode * x) {
    RBTreeNode *y = x->left;
    x->left = y->right;
    if (y->left != NULL) {
        y->right->p = x;
    }
    y->p = x->p;
    if (x->p == NULL) {
        rbt->root = y;
    } else if (x == x->p->left) {
        x->p->left = y;
    } else {
        x->p->right = y;
    }
    y->right = x;
    x->p = y;
}
/**
 * 红黑树的插入调整
 * */
void rbInsertFixUp(RBTree rbt, RBTreeNode * z) {
    RBTreeNode *y = rbt->nilT;
    while (z->p->color == RED) {
        if (z->p == z->p->p->left) {
            y = z->p->p->right;
            if (y->color == RED) {  // case1
                y->color = BLACK;
                z->p->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            } else if (z == z->p->right) {
                //  case2
                z = z->p;
                leftRotate(rbt, z);
                // case3
                z->p->color = BLACK;
                z->p->p->color = RED;
                rightRotate(rbt, z->p->p);
            }
        }
        else {
            y = z->p->left;
            if (y->color == RED) {
                y->color = BLACK;
                z->p->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            } else if (z == z->p->left) {
                z = z->p;
                leftRotate(rbt, z);
                z->p->color = BLACK;
                z->p->p->color = RED;
                rightRotate(rbt, z->p->p);
            }
        }
    }
    rbt->root->color = BLACK;
}


/**
 * 向树中插入节点
 * **/
int insert(RBTree rbt, RBTreeNode *node) {
    RBTreeNode *y = rbt->nilT;
    RBTreeNode *x = rbt->root;
    while (x != NULL) {
        y = x;
        if (x->data > node->data) {
            x = x->left;
        } else if (x->data < node->data){
            x = x->right;
        } else {
            return 0;
        }
    }
    node->p = y;
    if (y == rbt->nilT) {
        rbt->root = node;
    } else if (node->data < y->data) {
        y->left = node;
    } else {
        y->right = node;
    }
    node->left = rbt->nilT;
    node->right = rbt->nilT;
    node->color = RED;

}

int main() {
    printf("%d\n", BLACK);
    printf("hello world!\n");
    RBTree rbt;
    createRBTree(&rbt);
}
