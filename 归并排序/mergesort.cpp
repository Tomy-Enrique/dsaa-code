#include<iostream>
#include<stdlib.h>
using namespace std;

/*
测试用例
5,13,25,30,42,48,51,51,55,68,
2,16,19,26,38,49,58,66,70,71,
7,16,19,33,44,44,45,59,65,95,
2,34,43,47,47,48,66,84,85,93,
5,8,20,24,34,38,47,48,61,67,
15,17,27,50,54,84,94,94,95,99,
0,6,14,21,41,43,48,57,83,89,
12,25,27,29,30,42,60,85,93,98,
*/
typedef int KeyType;
typedef struct queue *Queue;
typedef struct heap* Heap;

struct queue {
    int capacity;        // 数组容量
    int front;            // 队头的位置
    int rear;            // 队尾的位置
    int size;            // 队列大小
    KeyType* array;    // 用于存放队列的数组
};

struct heap
{
    KeyType* array;     //用于存放堆的数组
    int KeyNum;         //堆里的关键字个数
};

struct result {
    Queue* q;
    KeyType k;
};

typedef struct result Result;

Queue CreateQueue(int Capacity);
void EnQueue(Queue* q, KeyType element);
bool DeQueue(Queue* q);
bool IsFull(Queue* q);
bool IsEmpty(Queue* q);
void TraverseQueue(Queue* q);
KeyType Peek(Queue* q);

Heap InitHeap(int Capacity);
bool IsHeapempty(Heap* h);
void Ajust_Node(Heap* h, int n);
void BuildMin_Heap(Heap* h);
void Push(Heap* h, KeyType k);
int Pop(Heap* h);
void TraverseHeap(Heap* h);
Queue* From(Queue* q, int QueueNum, KeyType k);
void Sort(Queue* q, int QueueNum, int PreQueueCap, Heap* h);

int main() {
    int array1[30] = {
        5,13,25,30,42,48,51,51,55,68,
        2,16,19,26,38,49,58,66,70,71,
        7,16,19,33,44,44,45,59,65,95
    };
    int array2[80] = {
        5,13,25,30,42,48,51,51,55,68,
        2,16,19,26,38,49,58,66,70,71,
        7,16,19,33,44,44,45,59,65,95,
        2,34,43,47,47,48,66,84,85,93,  
        5,8,20,24,34,38,47,48,61,67,
        15,17,27,50,54,84,94,94,95,99,
        0,6,14,21,41,43,48,57,83,89,
        12,25,27,29,30,42,60,85,93,98
    };
        
    Queue q1[3];
    Queue q2[8];

    for (int i = 0; i < 3; i++) {
        q1[i] = CreateQueue(10);
        for (int j = 0; j < 10; j++) {
            EnQueue(&q1[i], array1[i * 10 + j]);
        }
    }
    for (int i = 0; i < 8; i++) {
        q2[i] = CreateQueue(10);
        for (int j = 0; j < 10; j++) {
            EnQueue(&q2[i], array2[i * 10 + j]);
        }
    }

    Heap h1 = InitHeap(3);
    Heap h2 = InitHeap(8);
    
    for (int i = 0; i < 3; i++) {
        cout << "Queue" << i + 1 << ": ";
        TraverseQueue(&q1[i]);
    }
    cout << "M-way merge sort......" << endl;
    Sort(q1, 3, 10, &h1);

    for (int i = 0; i < 8; i++) {
        cout << "Queue" << i + 1 << ": ";
        TraverseQueue(&q2[i]);
    }
    cout << "M-way merge sort......" << endl;
    Sort(q2, 8, 10, &h2);
    return 0;
}

Queue CreateQueue(int Capacity) {
    Queue q;
    q = (Queue)malloc(sizeof(queue));
    q->array = (KeyType*)malloc(sizeof(KeyType) * Capacity);
    q->capacity = Capacity;
    q->front = 1;
    q->rear = 0;
    q->size = 0;
    return q;

}

void EnQueue(Queue* q, KeyType k) {
    if (IsFull(q)) {
        cout << "队列已满，入队失败\n";
    }
    else {
        (*q)->size++;
        if (++(*q)->rear == (*q)->capacity) {
            (*q)->rear = 0;
        }
        (*q)->array[(*q)->rear] = k;
    }
}

bool DeQueue(Queue* q) {
    if (IsEmpty(q)) {
        return false;
    }
    else {
        (*q)->size--;
        if (++(*q)->front == (*q)->capacity) {
            (*q)->front = 0;
        }
        return true;
    }    
}

bool IsFull(Queue* q) {
    return (*q)->size == (*q)->capacity;
}

bool IsEmpty(Queue* q) {
    if (q == NULL) {
        return true;
    }
    else {
        return (*q)->size == 0;
    }
}

void TraverseQueue(Queue* q) {
    if ((*q)->size == 0) {
        cout << "队列为空\n";
    }

    for (int i = 0; i < (*q)->size; i++) {
        if ((*q)->front + i < (*q)->capacity) {
            cout << (*q)->array[(*q)->front + i] << " ";
        }
        else {
            cout << (*q)->array[(*q)->front + i - (*q)->capacity] << " ";
        }
    }
    cout << endl;
}

KeyType Peek(Queue* q) {
    return (*q)->array[(*q)->front];
}

Heap InitHeap(int Capacity) {
    Heap h;
    h = (Heap)malloc(sizeof(heap));
    h->array = (KeyType*)malloc(sizeof(KeyType) * Capacity);
    h->KeyNum = 0;
    return h;
}

bool IsHeapempty(Heap* h) {
    if ((*h)->KeyNum == 0) {
        return true;
    }
    return false;
}

void Ajust_Node(Heap* h, int n) {
    int l, r, min, temp;
    l = 2 * n + 1;
    r = 2 * n + 2;
    min = n;

    if (l < (*h)->KeyNum && (*h)->array[min] > (*h)->array[l]) {
        min = l;
    }
    if (r < (*h)->KeyNum && (*h)->array[min] > (*h)->array[r]) {
        min = r;
    }

    if (min != n) {
        temp = (*h)->array[n];
        (*h)->array[n] = (*h)->array[min];
        (*h)->array[min] = temp;
        Ajust_Node(h, min);
    }
}

void BuildMin_Heap(Heap* h) {
    for (int i = (*h)->KeyNum / 2; i >= 0; i--) {
        Ajust_Node(h, i);
    }
}

void Push(Heap* h, KeyType k) {
    for (int i = (*h)->KeyNum; i >= 0; i--) {
        (*h)->array[i] = (*h)->array[i - 1];
    }
    (*h)->array[0] = k;
    (*h)->KeyNum++;
}

int Pop(Heap* h) {
    if (!IsHeapempty(h)) {
        KeyType temp = (*h)->array[0];
        for (int i = 0; i < (*h)->KeyNum; i++) {
            (*h)->array[i] = (*h)->array[i + 1];
        }
        (*h)->KeyNum--;
        return temp;
    }
}

void TraverseHeap(Heap* h) {
    for (int i = (*h)->KeyNum - 1; i >= 0; i--) {
        cout << (*h)->array[i] << " ";
    }
    cout << endl;
}

Queue* From(Queue* q, int QueueNum, KeyType k) {
    for (int i = 0; i < QueueNum; i++) {
        if (q[i]->array[q[i]->front] == k) {
            return &q[i];
        }
    }
    return NULL;
}

void Sort(Queue* q, int QueueNum, int PreQueueCap, Heap* h) {
    KeyType tempK;
    KeyType result[100];
    int count = 0;
    Queue* tempQueue = (Queue*)malloc(sizeof(Queue));
    for (int i = 0; i < QueueNum; i++) {
        Push(h, q[i]->array[q[i]->front]);
    }
    BuildMin_Heap(h);
    
    while (!IsHeapempty(h))
    {
        tempK = Pop(h);
        result[count] = tempK;
        count++;
        tempQueue = From(q, QueueNum, tempK);
        if (DeQueue(tempQueue)) {
            if (!IsEmpty(tempQueue)) {
                Push(h, Peek(tempQueue));
            }
            BuildMin_Heap(h);
        }
        else {
            KeyType t = (*h)->array[(*h)->KeyNum--];
            Push(h, t);
            BuildMin_Heap(h);
            //cout << t << endl;
        }
    }
    for (int i = 0; i < QueueNum; i++) {
        for (int j = 0; j < PreQueueCap; j++) {
            cout << result[i * PreQueueCap + j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}


