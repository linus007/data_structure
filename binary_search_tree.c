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
	return node_p;
}
int treeInsert(BSTree *bst, ElemType e) {
	struct BSTree_Node * y = NULL;
	struct BSTree_Node * x = *bst;
	while (x != NULL) {
		printf("not null\n");
        y = x;
		if (e > x->data) {
			x = x->right;
		} else if (e < x->data) {
			x = x->left;
		} else {
			return 0;
		}
	}
	struct BSTree_Node * data = createNOde(e);
	data->p = y;
	if (y == NULL) {
		*bst = data;
	} else {
		if (e < y->data) {
			y->left = data;
		} else {
			y->right = data;
		}
	}
	return 1;
}
struct BSTree_Node minimum(BSTree bst) {
    if (bst == NULL) {
        printf("empty tree\n");
        reurn NULL;
    }
    BSTree_Node *x = bst;
    while (x->left) {
        x = x-left;
    }
    return x;
}
struct BSTree_Node maxmum(BSTree bst) {
    if (bst == NULL) {
        printf("empty tree\n");
        return NULL;
    }
    BSTree_Node * x = bst;
    while (x->right) {
        x = x->right;
    }
     return x;


}
struct BSTree_Node *treeSuccessor(BSTree bst, BSTree_Node * z){
    BSTree_Node * node = find_Elem(bst, z->data);
    if (node != z) {
        printf("this node is not in this tree\n");    
        return NULL;
    }
    if (z->right) {
        return minimum(bst);
    }
    
}
int treeDelete(BSTree *bst, ElemType e) {
    struct BSTree_Node * z = find_Elem(e);
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
int treeInser_in_Array(BSTree *bst, ElemType *arr, int len) {
	int i = 0;
	while (i < len) {
		treeInsert(bst, arr[i++]);
	}
	return i;
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
	BSTree bst;
    
	treeInsert(&bst, 3);
	showAll(bst);
	printf("\n*************************\n");
	ElemType arr[6] = {3, 45, 13, 1, 96, 34};
	//rand_in_Array(arr, 9);
	printfArray(arr, 6);
	printf("\n");
	treeInser_in_Array(&bst, arr, 6);
	showAll(bst);
//	struct BSTree_Node * f = find_Elem(bst, 13);
    char *p;
    //if (f->data == 13) {
    //    printf("sucess!\n");
    //}
    //showAll(bst);
    return 1;
}
