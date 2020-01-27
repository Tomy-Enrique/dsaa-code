#include <iostream>
//#include <stdlib.h>
#include<windows.h>
using namespace std;

#define M 5		
#define L 5

typedef int KeyType;
typedef struct BPTNode						
{
	int keynum;									//关键字数量
	struct BPTNode* parent;						//指向父结点								  
	KeyType key[M + 1];							//关键字
	struct BPTNode* child[M + 1];				//儿子结点
	int leaf;									//叶结点标志
	struct BPTNode* next;						//链表
}BPTNode;										//B+树结点

typedef struct
{
	BPTNode* data;								//叶结点头指针
	BPTNode* root;								//根结点
}BPTree;										//B+树结构

//B+树查找结果类型
typedef struct
{
	BPTNode* pt;								//指向当前结点
	int i;										//关键字在结点中的次序
	int tag;									//查询结果标志
}Result;


int Search(BPTNode* p, KeyType K);									//返回关键字在此结点中的次序
Result SearchBPTree(BPTree BPT, KeyType K);							//对整个B+树搜索，返回查询信息
void split(BPTNode* q, int s, BPTNode** ap);						//分裂结点
void NewRoot(BPTree* BPT, BPTNode* q, int x, BPTNode* ap);			//创建新的根
void Insert(BPTNode* q, int i, KeyType x, BPTNode* ap);				//在此结点中插入关键字
bool InsertBPTree(BPTree* BPT, KeyType K, BPTNode* q, int i);		//将关键字插入结点为*q的第i个位置
bool InsertKey(BPTree* BPT, KeyType K);								//关键字插入
void merge(BPTNode* q, int s);										//合并结点
void deleteK(BPTNode* q, int i, KeyType x);							//在此结点中删除关键字
bool deleteBPTree(BPTree* BPT, KeyType K, BPTNode* q, int i);		//在结点为*q的第i个位置删除关键字
bool deleteKey(BPTree* BPT, KeyType K);								//关键字删除
void PrintBPTree(BPTree BPT);										//打印所有叶结点
BPTree InitBPTree();												//初始化B+树
void DelayOperation(BPTree BPT);									//模拟外部存取操作

int main()
{
	BPTree BPT = InitBPTree();
	PrintBPTree(BPT);
	DelayOperation(BPT);
}

int Search(BPTNode* p, KeyType K) 
{
	int i;
	i = 0;
	while (i < p->keynum && p->key[i] <= K)
	{
		i++;
	}
	return i;
}

Result SearchBPTree(BPTree BPT, KeyType K)
{
	Result R = { NULL, 0, 0 };
	BPTNode* p;
	int found, i;

	p = BPT.root;
	found = false;
	i = 0;						

	while (p && !found)
	{
		i = Search(p, K);		

		if (p->leaf == 1)
		{
			if (i > 0 && p->key[i - 1] == K)
			{
				found = true;
				i--;
			}
			else {
				break;
			}
		}
		else
		{
			if (i > 0) {
				i--;
			}
			p = p->child[i];
		}
	}

	R.i = i;
	R.pt = p;

	if (found) {
		R.tag = 1;
	}
	else {
		R.tag = 0;
	}
	return R;
}

void split(BPTNode* q, int s, BPTNode** ap)		
{
	int i;

	*ap = (BPTNode*)malloc(sizeof(BPTNode));

	if (q->leaf == 1)								//分裂叶结点 
	{
		(*ap)->leaf = 1;
		(*ap)->next = q->next;
		q->next = *ap;
	}
	else {
		(*ap)->leaf = 0;
	}
	for (i = s + 1; i <= M; i++)
	{
		(*ap)->key[i - s - 1] = q->key[i];
		(*ap)->child[i - s - 1] = q->child[i];
	}

	(*ap)->keynum = M - s;
	q->keynum = s + 1;

	(*ap)->parent = q->parent;

	for (i = 0; i < (*ap)->keynum; i++)
	{
		if ((*ap)->child[i])
			(*ap)->child[i]->parent = *ap;
	}
}

void NewRoot(BPTree* BPT, BPTNode* q, int x, BPTNode* ap)
{
	BPTNode* p;

	p = (BPTNode*)malloc(sizeof(BPTNode));
	p->keynum = 1;
	p->parent = NULL;
	p->key[0] = x;
	p->child[0] = ap;
	if (p->child[0])
		p->child[0]->parent = p;

	if (!q && BPT->root)
	{
		Insert(p, 0, BPT->root->key[0], BPT->root);
		if (p->child[0])
			p->child[0]->parent = p;
	}

	BPT->root = p;

	if (BPT->data == NULL)
	{
		p->leaf = 1;
		p->next = NULL;
		BPT->data = p;
	}
	else
		p->leaf = 0;
}

void Insert(BPTNode* q, int i, KeyType x, BPTNode* ap)
{
	int j;
	BPTNode* p;
	p = (BPTNode*)malloc(sizeof(BPTNode));
	for (j = q->keynum; j > i; j--)
	{
		q->key[j] = q->key[j - 1];
		q->child[j] = q->child[j - 1];
	}

	q->key[i] = x;
	q->child[i] = ap;
	q->keynum++;

	p = q->parent;					
	while (!i && p != NULL)
	{
		i = Search(p, q->key[1]);
		--i;
		p->key[i] = x;
		p = p->parent;
	}
}

bool InsertBPTree(BPTree* BPT, KeyType K, BPTNode* q, int i)
{
	KeyType x;
	BPTNode* ap;
	int finished;
	int s;

	x = K;
	ap = NULL;
	finished = false;

	while (q && !finished)
	{
		Insert(q, i, x, ap);		//将x和ap分别插入到q->key[i]和q->child[i]
		q->child[i] = ap;

		if (q->keynum <= M)			//（与B树区别） 
			finished = true;		//插入完成
		else						//关键字数目超出限制	
		{
			s = (double)M / 2;		//B+树结点中关键字个数必须>=ceil(M/2)
			split(q, s, &ap);		//分裂结点*q 
			x = q->key[s + 1];		//将q->key[s+1...M],q->child[s...M]移入新结点*ap;			
			q = q->parent;

			if (q)					//在双亲结点*q中查找x的插入位置 
				i = Search(q, x);
		}
	}

	if (!finished) {					//BPT是空树（参数q初值为NULL）或者根结点已分裂为结点*q和*ap 
		NewRoot(BPT, q, x, ap); 	//生成含信息(BPT,x,ap)的新的根结点*BPT，原BPT和ap为子树指针 
	}
	return true;
}

bool InsertKey(BPTree* BPT, KeyType K)
{
	Result R;
	R = SearchBPTree(*BPT, K);

	if (R.tag == 0)							
	{
		InsertBPTree(BPT, K, R.pt, R.i);
		return true;
	}
	else {
		return false;
	}
}

void merge(BPTNode* q, int s) 
{
	int tag = 0;
	int index, i;
	BPTNode* left, * right, * p;
	KeyType x;
	left = right = (BPTNode*)malloc(sizeof(BPTNode));
	if (q->parent) {
		index = Search(q->parent, q->key[0]);
		index--;
		if (index > 0 && index < q->parent->keynum - 1) {
			left = q->parent->child[index - 1];
			right = q->parent->child[index + 1];
			tag = 1;
		}
		else if (index == q->parent->keynum - 1) {
			left = q->parent->child[index - 1];
			right = NULL;
			tag = 2;
		}
		else if (index == 0) {
			left = NULL;
			right = q->parent->child[index + 1];
			tag = 3;
		}
	}

	switch (tag)
	{
	case 1:
		if (left->keynum - s > 1 && right->keynum <= left->keynum) {
			q->keynum++;
			for (i = q->keynum - 1; i > 0; i--) {
				q->key[i] = q->key[i - 1];
			}
			q->key[0] = left->key[left->keynum - 1];
			left->keynum--;
		}
		else if (right->keynum - s > 1 && right->keynum >= left->keynum) {
			q->keynum++;
			q->key[q->keynum - 1] = right->key[0];
			for (i = 0; i < right->keynum; i++) {
				right->key[i] = right->key[i + 1];
			}
			right->keynum--;
			right->parent->key[index + 1] = right->key[0];
		}
		else {
			for (i = left->keynum; i < left->keynum + q->keynum; i++) {
				left->key[i] = q->key[i - left->keynum];
				left->child[i] = q->child[i - left->keynum];
			}
			left->keynum = left->keynum + q->keynum;
			left->next = right;
			for (i = index; i < left->parent->keynum; i++) {
				left->parent->key[i] = left->parent->key[i + 1];
				left->parent->child[i] = left->parent->child[i + 1];
			}
			left->parent->keynum--;
			right->parent = left->parent;
		}

		break;
	case 2:
		if (left->keynum - s > 1) {
			q->keynum++;
			for (i = q->keynum - 1; i > 0; i--) {
				q->key[i] = q->key[i - 1];
			}
			q->key[0] = left->key[left->keynum - 1];
			left->keynum--;
		}
		else {
			for (i = left->keynum; i < left->keynum + q->keynum; i++) {
				left->key[i] = q->key[i - left->keynum];
				left->child[i] = q->child[i - left->keynum];
			}
			left->keynum = left->keynum + q->keynum;
			for (i = index; i < left->parent->keynum; i++) {
				left->parent->key[i] = left->parent->key[i + 1];
				left->parent->child[i] = left->parent->child[i + 1];
			}
			left->parent->keynum--;
		}
		left->next = q->next;
		break;
	case 3:
		if (right->keynum - s > 1) {
			q->keynum++;
			q->key[q->keynum - 1] = right->key[0];
			for (i = 0; i < right->keynum; i++) {
				right->key[i] = right->key[i + 1];
			}
			right->keynum--;
			right->parent->key[index + 1] = right->key[0];
		}
		else {
			for (i = q->keynum; i < right->keynum + q->keynum; i++) {
				q->key[i] = right->key[i - q->keynum];
				q->parent->child[i] = q->parent->child[i + 1];
			}
			q->keynum = q->keynum + right->keynum;
			q->next = right->next;
			for (i = index + 1; i < right->parent->keynum; i++) {
				q->parent->key[i] = q->parent->key[i + 1];
				q->parent->child[i] = q->parent->child[i + 1];
			}
			q->parent->keynum--;
		}
		break;
	}
}

void deleteK(BPTNode* q, int i, KeyType x) 
{
	int j, k;
	BPTNode* p;
	p = (BPTNode*)malloc(sizeof(BPTNode));
	p = q->parent;
	for (k = 0; k < q->keynum; k++) {
		if (q->key[k] == x) {
			for (j = k; j < q->keynum; j++) {
				q->key[j] = q->key[j + 1];
				q->child[j] = q->child[j + 1];
			}
			q->keynum--;
			q->parent = p;
			x = q->key[0];
		}
	}								//最小值发生了变动 
	while (!i && p)
	{
		i = Search(p, q->key[1]);
		--i;
		p->key[i] = x;
		p = p->parent;
	}
}

bool deleteBPTree(BPTree* BPT, KeyType K, BPTNode* q, int i) {
	KeyType x;
	int finished;
	int s;

	x = K;

	finished = false;

	while (q && !finished)
	{
		deleteK(q, i, x);

		if (q->keynum > M / 2)			//（与B树区别） 
			finished = true;		//插入完成
		else						//关键字数目小于M/2
		{
			s = (double)M / 2;
			merge(q, s);
			q = q->parent;
		}
	}

	return true;
}

bool deleteKey(BPTree* BPT, KeyType K) {
	Result R = SearchBPTree(*BPT, K);
	if (R.tag == 1) {
		deleteBPTree(BPT, K, R.pt, R.i);
		return true;
	}
	else {
		return false;
	}
}

void PrintBPTree(BPTree BPT)
{
	BPTNode* p;
	int i;

	for (p = BPT.data; p; p = p->next)
	{
		cout << "[";
		for (i = 0; i < p->keynum; i++) {
			cout << p->key[i];
			if (i < p->keynum - 1) {
				cout << " ";
			}
		}
		cout << "]";
		if (p->next) {
			cout << "->";
		}
	}
	cout << endl << "<--------------------------------------------------------------------------->" << endl;
}

BPTree InitBPTree() {
	BPTree BPT;
	BPT.root = BPT.data = NULL;
	int array[50] = { 15,24,72,36,73,36,44,87,86,58,
					  69,54,82,48,18,95,43,57,69,20,
					  35,59,47,56,92,42,20,43,45,97,
					  29,70,80,5,43,80,54,64,17,59,
					  59,25,81,83,67,64,3,17,8,86};

	for (int i = 0; i < 50; i++) {
		int temp = array[i];
		InsertKey(&BPT, temp);
	}
	cout << "初始化完成......" << endl;
	return BPT;
}

void DelayOperation(BPTree BPT) {
	KeyType K = 0;
	cout << "输入关键字（存在则取出，不存在则存入）";
	cin >> K;
	cout << endl;
	while (K) {
		Result R = SearchBPTree(BPT, K);
		if(R.tag == 1){
			cout << "取出关键字" << K << "......" << endl;
			Sleep(20);
			deleteKey(&BPT, K);
			PrintBPTree(BPT);
		}
		else {
			cout << "存入关键字" << K << "......" << endl;
			Sleep(20);
			InsertKey(&BPT, K);
			PrintBPTree(BPT);
		}
		cout << "输入关键字（存在则取出，不存在则存入）";
		cin >> K;
		cout << endl;
	}
}
