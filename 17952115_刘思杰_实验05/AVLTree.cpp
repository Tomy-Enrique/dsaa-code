#include<iostream>
#include<algorithm> 

using namespace std;

/*
Lab Work 05-1. Balance Rotations of AVL Trees

Note. Programming in C/C++, including <iostream>/<iostream.h> only

An AVL tree is a binary search tree where every node in the tree has a balance factor of -1, 0 or +1. But any insertion into the AVL tree may cause violations of balance in four cases: Left-Left, Left-Right, Right-Right, and Right-Left. Single Rotations and Double Rotations are introduced to fix these cases.

Determine the data structures for an AVL tree
Implement an insertion into the AVL tree
Implement the four possible rotations to fix violations of balance caused by the insertion.
(End)
*/
typedef struct AVLNode *AVLTree;
typedef struct AVLNode *Position;

struct AVLNode {
	int data;
	AVLTree left;
	AVLTree right;
	int height;
};

AVLTree Init(int t_data) {
	AVLTree T;
	T = (AVLTree)malloc(sizeof(AVLNode));
	T->data = t_data;
	T->left = T->right = NULL;
	return T;
}


static int Height(Position P) {
	if (P == NULL) {
		return -1;
	}
	else {
		return P->height;
	}
}

static Position SingleRotateWithLeft(Position k2) {
	Position k1;
	k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->height = max(Height(k2->left), Height(k1->right)) + 1;
	k1->height = max(Height(k1->left), k2->height) + 1;
	return k1;
}

static Position DoubleRotateWithLeft(Position k3) {
	k3->left = SingleRotateWithLeft(k3->left);
	return SingleRotateWithLeft(k3);
}

static Position SingleRotateWithRight(Position k2) {
	Position k1;
	k1 = k2->right;
	k2->right = k1->left;
	k1->left = k2;
	k2->height = max(Height(k2->left), Height(k2->right)) + 1;
	k1->height = max(Height(k1->right), k2->height) + 1;
	return k1;
}

static Position DoubleRotateWithRight(Position k3) {
	k3->right = SingleRotateWithRight(k3->right);
	return SingleRotateWithRight(k3);
}

AVLTree insert(int t_data, AVLTree T) {
	if (T == NULL) {
		T = (AVLTree)malloc(sizeof(AVLNode));
		T->data = t_data;
		T->left = T->right = NULL;
		T->height = 0;
	}
	else if (t_data < T->data)
	{
		T->left = insert(t_data, T->left);
		if (Height(T->left) - Height(T->right) == 2) {
			if (t_data < T->left->data) {
				T = SingleRotateWithLeft(T);
			}
			else {
				T = DoubleRotateWithLeft(T);
			}
		}
	}
	else if (t_data > T->data) {
		T->right = insert(t_data, T->right);
		if (Height(T->right) - Height(T->left) == 2) {
			if (t_data > T->right->data) {
				T = SingleRotateWithRight(T);
			}
			else {
				T = DoubleRotateWithRight(T);
			}
		}
	}

	T->height = max(Height(T->left), Height(T->right)) + 1;
	return T;
}

void post_order(AVLTree T) {
	if (T != NULL) {
		post_order(T->left);
		cout << T->data << " ";
		post_order(T->right);
	}
}

int main()
{
	AVLTree tree = Init(70);
	insert(70, tree);
	insert(81, tree);
	insert(60, tree);
	insert(65, tree);
	insert(91, tree);
	insert(55, tree);
	insert(45, tree);
	insert(11, tree);
	insert(23, tree);
	insert(37, tree);
	insert(25, tree);
	insert(69, tree);
	post_order(tree);
}
