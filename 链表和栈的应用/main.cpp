#include<iostream>
#include<stdlib.h>
using namespace std;
#define max_size 30

typedef struct Stack {
	int poly[max_size];
	int bottom;
	int top;
}SqStack;

typedef struct Poly {
	int coe;
	int exp;
	struct Poly *next;
}Poly;

void Init_poly_coe(int *coe);   //初识化多项式的系数

SqStack Init_Stack();   //初识化栈

void push(SqStack &S, int coe); //进栈

int pop(SqStack &S);  //出栈

Poly *Creat_poly(SqStack &S, int n);  //生成一个一元多项式

Poly *Add_Poly(Poly *pa, Poly *pb);   //两个一元多项式相加

void Print_Poly(Poly *head);   //打印多项式

int main()
{
	SqStack S = Init_Stack();
	int coe[max_size];
	Init_poly_coe(coe);
	for (int i = 0; i < max_size; i++) {
		push(S, coe[i]);
	}
	int n1, n2;
	printf("定义两个一元多项式的指数大小: ");
	scanf("%d %d", &n1, &n2);
	Poly *LP = Creat_poly(S, n1);
	Poly *LQ = Creat_poly(S, n2);

	printf("一元多项式: P = ");
	Print_Poly(LP);
	printf("一元多项式: Q = ");
	Print_Poly(LQ);

	Poly *LPQ = Add_Poly(LP, LQ);
	printf("一元多项式: PQ = ");
	Print_Poly(LPQ);

	printf("%d garbage units: ", S.top);
	while (S.bottom != S.top)
	{
		printf("%d ", pop(S));
	}
}

void Init_poly_coe(int *coe) {
	for (int i = 0; i < max_size; i++) {
		srand(rand() % 100);
		coe[i] = rand() % 100;
	}
}

SqStack Init_Stack() {
	SqStack S;
	S.bottom = S.top = 0;
	return S;
}

void push(SqStack &S, int coe) {
	if (S.top < max_size) {
		S.poly[S.top] = coe;
		S.top++;
	}
}

int pop(SqStack &S) {
	if (S.top == 0)
		return 0;
	return S.poly[S.top--];
}

int pop_garbage(SqStack &S) {
	return 0;
}

Poly *Creat_poly(SqStack &S, int n) {
	Poly *head, *rear, *p;
	head = (Poly *)malloc(sizeof(Poly));
	rear = head;
	int coe;
	int i = 0;
	do
	{
		//int coe;
		p = (Poly *)malloc(sizeof(Poly));
		p->coe = pop(S);
		coe = p->coe;
		p->exp = i;
		i++;
		rear->next = p;
		rear = p;
	} while (n--);
	rear->next = NULL;
	return head;
}

Poly *Add_Poly(Poly *pa, Poly *pb)
{
	Poly *qa = pa->next;
	Poly *qb = pb->next;
	Poly *headc, *pc, *qc;
	pc = (Poly *)malloc(sizeof(Poly));
	pc->next = NULL;
	headc = pc;
	while (qa != NULL && qb != NULL)
	{
		qc = (Poly *)malloc(sizeof(Poly));
		if (qa->exp < qb->exp)
		{
			qc->coe = qa->coe;
			qc->exp = qa->exp;
			qa = qa->next;
		}
		else if (qa->exp == qb->exp)
		{
			qc->coe = qa->coe + qb->coe;
			qc->exp = qa->exp;
			qa = qa->next;
			qb = qb->next;
		}
		else {
			qc->coe = qb->coe;
			qc->exp = qb->exp;
			qb = qb->next;
		}
		if (qc->coe != 0) {
			qc->next = pc->next;
			pc->next = qc;
			pc = qc;
		}
		else free(qc);
	}
	while (qa != NULL) {
		qc = (Poly *)malloc(sizeof(Poly));
		qc->coe = qa->coe;
		qc->exp = qa->exp;
		qa = qa->next;
		qc->next = pc->next;
		pc->next = qc;
		pc = qc;
	}
	while (qb != NULL) {
		qc = (Poly *)malloc(sizeof(Poly));
		qc->coe = qb->coe;
		qc->exp = qb->exp;
		qb = qb->next;
		qc->next = pc->next;
		pc->next = qc;
		pc = qc;
	}
	return headc;
}


void Print_Poly(Poly *head)
{
	Poly *q = head->next;
	int flag = 1;
	if (!q) {
		putchar('0');
		printf("\n");
		return;
	}
	while (q) {
		if (q->coe > 0 && flag != 1) {
			putchar('+');
		}
		if (q->coe != 1 && q->coe != -1) {
			printf("%d", q->coe);
			if (q->exp == 1) putchar('x');
			else if (q->exp) printf("x^%d", q->exp);
		}
		else {
			if (q->coe == 1) {
				if (!q->exp) putchar('1');
				else if (q->exp == 1) putchar('X');
				else printf("X^%d", q->exp);
			}
			if (q->coe == -1) {
				if (!q->exp) printf("-1");
				else if (q->exp == 1) printf("-X");
				else printf("-X^%d", q->exp);
			}
		}
		q = q->next;
		flag++;
	}
	printf("\n");
}

