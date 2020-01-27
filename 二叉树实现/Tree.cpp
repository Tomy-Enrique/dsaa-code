#include<iostream>
//#include<stdlib.h>
using namespace std;
#define max_size 20

//原树(n叉树)的数据结构 
typedef struct origin_tree {
	char data;
	origin_tree *parent;
	int cnChild;
	origin_tree *child[max_size];
}origin_tree;

//左孩子有兄弟表示法 
typedef struct LCR
{
	char element;
	LCR *first_child;
	LCR *next_sibling;
}LCR;

//原树的建立、插入和后序遍历 
origin_tree *InitTree(char ch);
origin_tree *InsertNode(origin_tree *T, char ch);
void post_order(origin_tree *T);

//LCR二叉树的建立、插入和中序遍历 
LCR *newTree(char ch);
LCR *addSibling(LCR *T, char ch);
LCR *addChild(LCR *T, char ch);
void in_order(LCR *T);

void transform(LCR *tree, origin_tree *T);

void input1();
void input2();

int main()
{
	input1();
	input2();
}

origin_tree *InitTree(char ch) {
	origin_tree *Tree;
	//Tree = (origin_tree *)malloc(sizeof(origin_tree));
	Tree = new origin_tree[sizeof(origin_tree)];
	Tree->data = ch;
	Tree->cnChild = 0;
	Tree->parent = NULL;
	//memset;
	return Tree;
}

origin_tree *InsertNode(origin_tree *T, char ch) {
	int cnChild = T->cnChild;
	origin_tree *Temp;
	Temp = new origin_tree[sizeof(origin_tree)];
	Temp->data = ch;
	Temp->parent = T;
	T->child[cnChild] = Temp;
	T->cnChild++;
	//cout << Temp->data;
	return Temp;
}

void post_order(origin_tree *T) {
	int depth = 0;
	int i;
	if (T == NULL) return;
	for (i = 0; i < T->cnChild; i++) {
		//depth++;
		post_order(T->child[i]);
		//depth--;
		//cout << T->data << " ";
	}
	cout << T->data << " ";
}

LCR *newTree(char ch) {
	LCR *T = new LCR;
	T->element = ch;
	T->first_child = T->next_sibling = NULL;
	return T;
}

LCR *addSibling(LCR *T, char ch) {
	if (T == NULL) return NULL;
	while (T->next_sibling) {
		T = T->next_sibling;
	}
	T->next_sibling = newTree(ch);
	return T->next_sibling;
}

LCR *addChild(LCR *T, char ch) {
	if (T == NULL) return NULL;
	if (T->first_child) {
		return addSibling(T->first_child, ch);
	}
	else {
		T->first_child = newTree(ch);
		return T->first_child;
	}
}

void in_order(LCR *T) {
	if (T) {
		in_order(T->first_child);
		cout << T->element << " ";
		in_order(T->next_sibling);
	}
}

void transform(LCR *tree, origin_tree *T) {
	LCR *Node;
	Node = new LCR[sizeof(LCR)];
	if (T == NULL) return;
	for (int i = 0; i < T->cnChild; i++) {
		Node = addChild(tree,T->child[i]->data);
		transform(Node, T->child[i]);
	}
}

void input1() {
	cout << "测试样例1：" << endl;
	
	origin_tree *Tree = InitTree('R');
	origin_tree *p1 = InsertNode(Tree, 'A');
	origin_tree *p2 = InsertNode(Tree, 'B');
	origin_tree *p3 = InsertNode(Tree, 'C');
	InsertNode(p1, 'D');
	InsertNode(p1, 'E');
	origin_tree *p4 = InsertNode(p3, 'F');
	InsertNode(p4, 'G');
	InsertNode(p4, 'H');
	InsertNode(p4, 'K');
	cout << "原树的后序遍历：      ";
	post_order(Tree);

	cout << endl;

	
	LCR *tree = newTree(Tree->data);
	transform(tree, Tree); //Kruth transform 
	cout << "LCRS二叉树的中序遍历：";
	in_order(tree);
	cout << endl;
}

void input2(){
	cout << endl << "测试样例2：" << endl;
	
	origin_tree *Tree = InitTree('A');
	origin_tree *p1 = InsertNode(Tree, 'B');
	origin_tree *p2 = InsertNode(Tree, 'C');
	origin_tree *p3 = InsertNode(Tree, 'D');
	InsertNode(p1, 'E');
	InsertNode(p1, 'F');
	InsertNode(p1, 'G');
	InsertNode(p2, 'H');
	InsertNode(p3, 'K');
	InsertNode(p3, 'I');
	InsertNode(p3, 'J');
	cout << "原树的后序遍历：      ";
	post_order(Tree);

	cout << endl;

	
	LCR *tree = newTree(Tree->data);
	transform(tree, Tree); //Kruth transform 
	cout << "LCRS二叉树的中序遍历：";
	in_order(tree);
	cout << endl;	
}
