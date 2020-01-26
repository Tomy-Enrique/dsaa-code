#include<iostream>
using namespace std;

typedef struct adj Adj;
struct adj {
	string* arr;
	int indegree;
};

typedef struct graph Graph;
struct graph {
	string peak;
	Adj adj;
};

typedef struct queue Queue;
struct queue {
	int head;
	int tail;
	string* arr;
};

Graph Init_Graph(string s, int n) {
	Graph g;
	g.peak = s;
	if (n == 0) {
		g.adj.arr = NULL;
	}
	else {
		g.adj.arr = new string[n];
	}
	g.adj.indegree = 0;
	return g;
}

void addEdge(Graph* g, string s) {
	(*g).adj.arr[(*g).adj.indegree] = s;
	(*g).adj.indegree++;
}

void Traverse_Graph(Graph* g, int n) {
	int i, j;
	for (i = 0; i < n; i++) {
		cout << g[i].peak << " <- ";
		for (j = 0; j < g[i].adj.indegree; j++) {
			cout << g[i].adj.arr[j];
			if (j != g[i].adj.indegree-1) {
				cout << ",";
			}
		}
		cout << endl;
	}
}

Queue Init_queue(int n) {
	Queue q;
	q.arr = new string[n];
	q.head = 0;
	q.tail = -1;
	return q;
}

void push(Queue* q, string s) {
	q->tail++;
	q->arr[q->tail] = s;
}

string pop(Queue* q) {
	string temp = q->arr[q->head];
	q->head++;
	return temp;
}

void toloplogicalSort(Graph g[], Queue* q, int n) {
	int i, j;
	while (q->head != n) {
		for (i = 0; i < n; i++) {
			if (g[i].adj.indegree == 0) {
				push(q, g[i].peak);
				g[i].adj.indegree = -1;
			}
		}
		string temp;
		temp = pop(q);
		for (i = 0; i < n; i++) {
			for (j = 0; j < g[i].adj.indegree; j++) {
				if (g[i].adj.arr[j] == temp) {
					if (g[i].adj.indegree-- != 0) {
						g[i].adj.arr[j] = g[i].adj.arr[g[i].adj.indegree];
					}
				}
			}
		}
		cout << temp << " ";
	}
	cout << endl;
}

int main()
{
	int n = 12;
	Graph* g;
	g = new Graph[n];
	Queue q;
	q = Init_queue(n);
	g[0] = Init_Graph("A", 1);
	g[1] = Init_Graph("B", 1);
	g[2] = Init_Graph("C", 0);
	g[3] = Init_Graph("D", 2);
	g[4] = Init_Graph("E", 4);
	g[5] = Init_Graph("F", 2);
	g[6] = Init_Graph("G", 1);
	g[7] = Init_Graph("H", 0);
	g[8] = Init_Graph("I", 1);
	g[9] = Init_Graph("J", 1);
	g[10] = Init_Graph("K", 1);
	g[11] = Init_Graph("L", 2);

	addEdge(&g[0], "D");
	addEdge(&g[1], "A");
	addEdge(&g[3], "C");
	addEdge(&g[3], "H");
	addEdge(&g[4], "B");
	addEdge(&g[4], "D");
	addEdge(&g[4], "F");
	addEdge(&g[4], "G");
	addEdge(&g[5], "D");
	addEdge(&g[5], "J");
	addEdge(&g[6], "F");
	addEdge(&g[8], "H");
	addEdge(&g[9], "I");
	addEdge(&g[10], "F");
	addEdge(&g[11], "G");
	addEdge(&g[11], "K");
	Traverse_Graph(g, n);

	cout << endl << "After Topological Sort..." << endl;
	toloplogicalSort(g, &q, n);
	Traverse_Graph(g, n);

}
