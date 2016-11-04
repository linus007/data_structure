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
	printf("\n");
	printf("\n*************************\n");
	ElemType arr[6] = {3, 45, 13, 1, 96, 34};
	//rand_in_Array(arr, 9);
	printfArray(arr, 6);
	printf("\n");
	treeInser_in_Array(&bst, arr, 6);
	showAll(bst);
	return 1;
}
