#include<stdio.h>
#include<stdlib.h>
typedef int ElemType;
typedef struct BSTree_Node{
	ElemType data;
	struct BSTree_Node *p;
	struct BSTree_Node *left;
	struct BSTree_Node *right;
}* BSTree;

struct BSTree_Node * createNOde(ElemType e) {
	struct BSTree_Node * node_p = (struct BSTree_Node *) malloc (sizeof(struct BSTree_Node));
	if (!node_p) {
		printf("memorry allocate failed");
		exit(0);
	}
	node_p->data = e;
	//Modify By Lin Start Initial the value of NULL
	node_p->right = NULL;
	node_p->left = NULL;
	node_p->p = NULL;
    //Modify By Lin End
	return node_p;
}
int treeInsert(BSTree *bst, ElemType e) {

	struct BSTree_Node * y = NULL;
	struct BSTree_Node * x = *bst;
	while (x != NULL) {
        y = x;
		if (e > x->data) {
			x = x->right;
		} else if (e < x->data) {
			x = x->left;
		} else {
			return 0;
		}
	}
	struct BSTree_Node * node = createNOde(e);

	node->p = y;

	if (y == NULL) {
		*bst = node;
	}
	else {
		if (e < y->data) {
			y->left = node;
		} else {
			y->right = node;
		}

	}

	return 1;
}

struct BSTree_Node *find_Elem(BSTree bst, ElemType e) {
    struct BSTree_Node *p = bst;
    while (p != NULL) {
        if (p->data > e) {
            p = p->left;
        } else if (p->data < e) {
            p = p->right;
        } else {
            break;
        }
    }
    return p;
}
int treeInser_in_Array(BSTree *bst, ElemType arr[], int len) {
	int i = 0;
	while (i < len) {
		treeInsert(bst, arr[i++]);
	}
	return i;
}

struct BSTree_Node* minimum(BSTree bst) {
    if (bst == NULL) {
        printf("empty tree\n");
        return NULL;
    }
    struct BSTree_Node *x = bst;
    while (x->left) {
        x = x->left;    
    }
    return x;
}

struct BSTree_Node *maxmum(BSTree bst) {
    if (bst == NULL) {
        printf("empty tree\n");
        return NULL;
    }
    struct BSTree_Node * x = bst;
    while(x->right) {
        x = x->right;
    }
    return x;
}

struct BSTree_Node * successor(BSTree bst, struct BSTree_Node *node) {
    if (node->right != NULL) {
        return minimum(node->right);
    }
    struct BSTree_Node * y = node->p;
    while (y != NULL && node == y->right) {
        node = y;
        y = y->p;
    }
    return y;
}

struct BSTree_Node *successor_in_Elem(BSTree bst, ElemType e) {
    struct BSTree_Node * node = find_Elem(bst, e);
    if (node == NULL) {
        printf("elem is not in the tree\n");
        return NULL;
    }
    return successor(bst, node);
}

void showAll(BSTree bst) {
	if (bst != NULL) {
		showAll(bst->left);
		printf("%d ", bst->data);
		showAll(bst->right);
	}

}

void rand_in_Array(int *arr, int len) {
	int i = 0;
	for (; i < len; ++i) {
		arr[i] = rand() % 100;
	}
}
void printfArray(int *arr, int len) {
	int i = 0;
	while (i < len) {
		printf ("%d ", arr[i++]);
	}
}
int main() {
	BSTree bst = NULL;
	//Modify By Lin Start, allocate memory to the Struct
	//bst = (BSTree)malloc(sizeof(struct BSTree_Node));
	//bst->data = 10;
	//bst->right = NULL;
	//bst->left = NULL;
    //Modify By Lin End
	treeInsert(&bst, 3);
	showAll(bst);

	printf("\n*************************\n");
	ElemType arr[] = {3, 45, 13, 1, 96, 34};
	//rand_in_Array(arr, 9);
	printfArray(arr, 6);
	printf("\n");
	treeInser_in_Array(&bst, arr, 6);
	showAll(bst);
	struct BSTree_Node * f = find_Elem(bst, 13);
    char *p;
   if (f->data == 13) {
        printf("sucess!\n");
   }
    printf("minimum:%d\n", minimum(bst)->data);
    printf("maxmum:%d\n", maxmum(bst)->data);
    showAll(bst);
    int i = 0;
    printf("\n");
    while (i < 6) {
       struct BSTree_Node * p = successor_in_Elem(bst, arr[i++]); 
       if (p) {
            printf ("%d ", p->data);   
        }
    }
    
    printf("\n");
    return 1;
}
