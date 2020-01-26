#include<iostream>
using namespace std;

typedef struct edge Edge;
typedef struct graph Graph;
typedef struct subset Subset;

struct edge
{
	char src;		//起始点
	char dest;		//终点
	int weight;		//度
};

struct graph
{
	int V;		//顶点个数
	int E;		//边个数
	edge* edge;	
};

struct subset
{
	char elem[12];
	int num;
};

Graph* CreateGraph(int V, int E) {
	Graph* g = new graph;
	g->V = V;
	g->E = E;
	g->edge = new edge[E];
	return g;
}

void AddEdge(Edge* e, char src, char dest, int weight) {
	e->src = src;
	e->dest = dest;
	e->weight = weight;
}

Subset* InitSubset(int* len) {
	int i;
	Subset* s;
	s = new subset[*len];
	s[0].elem[0] = 'A';
	s[1].elem[0] = 'B';
	s[2].elem[0] = 'C';
	s[3].elem[0] = 'D';
	s[4].elem[0] = 'E';
	s[5].elem[0] = 'F';
	s[6].elem[0] = 'G';
	s[7].elem[0] = 'H';
	s[8].elem[0] = 'I';
	s[9].elem[0] = 'J';
	s[10].elem[0] = 'K';
	s[11].elem[0] = 'L';
	for (i = 0; i < (*len); i++) {
		s[i].num = 1;
	}
	return s;
}

void MergeSubset(Subset* s, int merge, int merged, int* len) {
	int i;
	for (i = 0; i < s[merged].num; i++) {
		s[merge].elem[s[merge].num + i] = s[merged].elem[i];
		//cout << s[merge].elem[s[merge].num + i];
	}
	s[merge].num += s[merged].num;
	(*len)--;
	for (i = merged; i < (*len); i++) {
		s[i] = s[i + 1];
	}
	//return count;		//�����Ӽ�����
}

//�����Ӽ����±�
int Find(Subset* s, int* len, char elem) {
	int i, j;
	for (i = 0; i < (*len); i++) {
		for (j = 0; j < s[i].num; j++) {
			if (s[i].elem[j] == elem) {
				return i;
			}
		}
	}
}

void Sort(char* s, int len) {
	char temp;
	int i, j;
	for (i = 0; i < len - 1; i++){
		for (j = 0; j < len - 1 - i; j++) {
			if (s[j] > s[j + 1]) {
				temp = s[j];
				s[j] = s[j + 1];
				s[j + 1] = temp;
			}
		}
	}
}

void PrintSubset(Subset* s, int* len) {
	int i, j;
	for (i = 0; i < (*len); i++) {
		Sort(s[i].elem, s[i].num);
		cout << "{";
		for ( j = 0; j < s[i].num; j++) {
			cout << s[i].elem[j];
			if (j+1 != s[i].num) {
				cout << ",";
			}
		}
		cout << "}";
		if (i + 1 != (*len)) {
			cout << ",";
		}
	}
}

void Kurskal(Graph* g, Subset* s, int* len) {
	int i;
	for (i = 0; i < g->E; i++) {
		int merge = Find(s, len, g->edge[i].src);
		int merged = Find(s, len, g->edge[i].dest);
		cout << "Add {" << g->edge[i].src << "," << g->edge[i].dest << "}" << endl;
		if (merge != merged) {
			if (merge > merged) {
				MergeSubset(s, merged, merge, len);
			}
			else {
				MergeSubset(s, merge, merged, len);
			}
		}
		PrintSubset(s, len);
		cout << endl;
		cout << endl;
	}
}

void PrintGraph(Graph* g) {
	int i;
	for (i = 0; i < g->E; i++) {
		cout << g->edge[i].src << endl;
	}
}

int main()
{
	Graph* g = CreateGraph(12, 22);	
	int len = 12;
	Subset* s = InitSubset(&len);
	AddEdge(&g->edge[0], 'C', 'E', 1);
	AddEdge(&g->edge[1], 'H', 'I', 2);
	AddEdge(&g->edge[2], 'G', 'I', 3);
	AddEdge(&g->edge[3], 'F', 'G', 4);
	AddEdge(&g->edge[4], 'B', 'E', 5);
	AddEdge(&g->edge[5], 'E', 'H', 6);
	AddEdge(&g->edge[6], 'B', 'C', 7);
	AddEdge(&g->edge[7], 'H', 'K', 8);
	AddEdge(&g->edge[8], 'H', 'L', 9);
	AddEdge(&g->edge[9], 'D', 'E', 10);
	AddEdge(&g->edge[10], 'G', 'H', 11);
	AddEdge(&g->edge[11], 'I', 'K', 12);
	AddEdge(&g->edge[12], 'B', 'D', 13);
	AddEdge(&g->edge[13], 'D', 'F', 14);
	AddEdge(&g->edge[14], 'E', 'G', 15);
	AddEdge(&g->edge[15], 'K', 'L', 16);
	AddEdge(&g->edge[16], 'J', 'K', 17);
	AddEdge(&g->edge[17], 'I', 'J', 18);
	AddEdge(&g->edge[18], 'G', 'J', 19);
	AddEdge(&g->edge[19], 'A', 'B', 20);
	AddEdge(&g->edge[20], 'A', 'D', 21);
	AddEdge(&g->edge[21], 'E', 'F', 22);
	Kurskal(g, s, &len);
	//PrintSubset(s, &len);
}

