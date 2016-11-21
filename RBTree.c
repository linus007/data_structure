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
    (*tree)->root = nilT;
    (*tree)->nilT = nilT;
    return 1;
}

RBTreeNode* minInNode(RBTree rbt, RBTreeNode *x) {
    if (x == rbt->nilT) {
        return rbt->nilT;
    }
    while (x->left != rbt->nilT) {
        x = x->left;
    }
    return x;
}
RBTreeNode * min(RBTree rbt) {
    return minInNode(rbt, rbt->root);
}
RBTreeNode *maxInNode(RBTree rbt, RBTreeNode *x) {
    if (x == rbt->nilT) {
        return rbt->nilT;
    }
    while (x->right != rbt->nilT) {
        x = x->right;
    }
    return x;
}
RBTreeNode * max(RBTree rbt) {
    return maxInNode(rbt, rbt->root);
}

RBTreeNode * successor(RBTree rbt, RBTreeNode *x) {
    if (x->right != rbt->nilT) {
        return minInNode(rbt, x->right);
    }
    RBTreeNode *y = x->p;
    while (y != rbt->nilT && x == y->right) {
        x = y;
        y = y->p;
    }
    return y;
}
/**
 * 左旋
 * */
void leftRotate(RBTree rbt, RBTreeNode *x) {
    RBTreeNode * y = x->right;
    x->right = y->left;
    if (y->left != rbt->nilT) {
        y->left->p = x;
    }
    y->p = x->p;
    if (x->p == rbt->nilT) { // x节点原先为树根
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
    if (y->left != rbt->nilT) {
        y->right->p = x;
    }
    y->p = x->p;
    if (x->p == rbt->nilT) {
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
            } else {
                if (z == z->p->right) {
                    //  case2
                    z = z->p;
                    leftRotate(rbt, z);
                }
                // case3
                z->p->color = BLACK;
                z->p->p->color = RED;
                rightRotate(rbt, z->p->p);
            }
        }
        else {
            y = z->p->p->left;
            if (y->color == RED) {
                y->color = BLACK;
                z->p->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            } else {
                if (z == z->p->left) {
                    z = z->p;
                    rightRotate(rbt, z);
			    }
                z->p->color = BLACK;
                z->p->p->color = RED;
                leftRotate(rbt, z->p->p);
            }
        }
    }
    rbt->root->color = BLACK;
}
RBTreeNode * findByElem(RBTree rbt, ElemType data) {
    RBTreeNode * y = rbt->nilT;
    RBTreeNode * x = rbt->root;
    while (x != rbt->nilT) {
        if (x->data < data) {
            x = x->right;
        } else if (x->data > data) {
            x = x->left;
        } else {
            return x;
        }
    }
    return rbt->nilT;
}

/**
 * 向树中插入节点
 * **/
int insert(RBTree rbt, RBTreeNode *node) {
    RBTreeNode *y = rbt->nilT;
    RBTreeNode *x = rbt->root;
    while (x != rbt->nilT) {
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
    rbInsertFixUp(rbt, node);
	return 1;
}
int insertInElem(RBTree rbt, ElemType data) {
	RBTreeNode *node = (RBTreeNode *) malloc(sizeof(RBTreeNode));
	if (!node) {
		printf("memory allocation failed!\n");
		exit(0);
	}
    node->data = data;
	node->left = rbt->nilT;
	node->right = rbt->nilT;
	node->p = rbt->nilT;
	return insert(rbt, node);
}


void deleteFixUp(RBTree rbt, RBTreeNode *x) {
    while (x != rbt->root && x->color == BLACK) {
        if (x == x->p->left) {
            RBTreeNode *w = x->p->right;
            if (w->color == RED) {  
                // case1: w red, childre uncertain
                w->color = BLACK;
                x->p->color = RED;
                leftRotate(rbt, x->p);
                w = x->p->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                // case2:w black and two child also black
                w->color = BLACK;
                x = x->p;
            } else {
                if (w->right->color == BLACK) {
                    //case3:w black and right child black,
                    //left child red
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(rbt, w);
                    w = x->p->right;
                }
                // case4: w black, right child black, 
                // leftchild uncertain
                w->color = x->p->color;
                x->p->color = BLACK;
                w->right->color = BLACK;
                leftRotate(rbt, x->p);
                // 跳出循环
                x = rbt->root;
            }
        } else {
            RBTreeNode *w = x->p->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->p->color = RED;
                rightRotate(rbt, x->p);
                w = x->p->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->p;
            } else {
                if (w->left->color == BLACK) {
                    w->color = RED;
                    leftRotate(rbt, w);
                    w = x->p->left;
                }
                w->color = x->p->color;
                x->p->color = BLACK;
                w->left->color = BLACK;
                rightRotate(rbt, x->p);
                x = rbt->root;
            }
        }
    }
    x->color = BLACK;
}

int delete(RBTree rbt, RBTreeNode *z) {
    RBTreeNode *y = rbt->nilT;
    if (z->left == rbt->nilT || z->right == rbt->nilT) {
        y = z;
    } else {
        y = successor(rbt, z);
    }
    RBTreeNode * x = rbt->nilT;
    if (y->left != rbt->nilT) {
        x = y->left;
    } else {
        x = y->right;
    }
    x->p = y->p;
    if (y->p == rbt->nilT) {
        rbt->root = x;
    } else if (y->p->left == y) {
        y->p->left = x;
    } else {
        y->p->right = x;
    }
    if (y != z) {
        z->data = y->data;
    }
    if (y->color == BLACK) {
        // rb-delete-fix-up
        deleteFixUp(rbt, x);
    }
    // 释放y节点的内存
    //free(y);
    //y = NULL;
    return 1;
}

int deleteByElem(RBTree rbt, ElemType data) {
    RBTreeNode * node = findByElem(rbt, data);
    if (node == rbt->nilT) {
        printf("elem not found!\n");
        return 0;
    }
    return delete(rbt, node);
}
void print(RBTree rbt, RBTreeNode *x) {
	if (x != rbt->nilT) {
		print(rbt, x->left);
		printf("x:%d,p:%d, left:%d,right:%d,data:%d, color:%d\n", x, x->p, x->left, x->right,x->data, x->color);
		print(rbt, x->right);
	}
}
void printAll(RBTree rbt) {
	print(rbt, rbt->root);
}



int main() {
    printf("hello world!\n");
    RBTree rbt;
    createRBTree(&rbt);
	insertInElem(rbt, 1);
	insertInElem(rbt, 44);
	insertInElem(rbt, 53);
	insertInElem(rbt, 23);
	insertInElem(rbt, 63);
	insertInElem(rbt, 23);
	insertInElem(rbt, 13);
	insertInElem(rbt, 73);
	insertInElem(rbt, 3);
	RBTreeNode *n = findByElem(rbt, 44);
    printf("min:%d\n", min(rbt)->data);
    printf("max:%d\n", max(rbt)->data);
    printAll(rbt);
    RBTreeNode * sus = findByElem(rbt, 44);
    if (sus != rbt->nilT) {
        RBTreeNode * rbn = successor(rbt, sus);
        if (rbn != rbt->nilT) {
            printf("successor:%d\n", successor(rbt, sus)->data);
        }
    }
    printf("\n*****************\n");
    deleteByElem(rbt, 1);
    printf("delete:\n");
    printAll(rbt);
    return 1;
}
