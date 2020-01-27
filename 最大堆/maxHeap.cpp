#include<iostream>
#include<cstdlib>
using namespace std;

/*
Note. Programmaxg in C/C++, including <iostream>/<iostream.h> and <cstdlib>/<cstdlib.h>only

Determaxe the array structures for a complete max-heap
Input a linear list of 20 random numbers, building a complete max-heap to store the numbers by the process of in-place heapification
Implement an in-place sorting, making use of POP operation for the built complete max-heaps .
(End)

Note. 5C for a technical report: Correct (准确), Clear (清晰), Concise (简洁), Complete (完整) and Consistent (一致)

Description of Work 07-1 and data structures applied
Testing cases of Work 07-1
Run time analysis
*/

void adjust_node(int *arr, int n, int len)
{
	int l, r, max, temp;
	l = 2 * n + 1;
	r = 2 * n + 2;
	max = n;

	if (l < len && arr[max] < arr[l]) {
		max = l;
	}
	if (r < len && arr[max] < arr[r]) {
		max = r;
	}

	if (max != n) {
		temp = arr[n];
		arr[n] = arr[max];
		arr[max] = temp;
		adjust_node(arr, max, len);
	}
}

void push(int *arr, int i) {
	arr[0] = arr[i];
}

int pop(int *arr) {
	return arr[0];
}

void BuildMax_Heap(int *arr, int len){
	for (int i = len / 2; i >= 0; i--) {
		adjust_node(arr, i, len);
	}	
}

void sort_heap(int *arr, int len)
{
	int tmp;
	for (int i = len - 1; i >= 0; i--)
	{
		tmp = pop(arr);
		push(arr, i);
		arr[i] = tmp;
		adjust_node(arr, 0, i);
	}
}

int main()
{
	int i;
	int len = 20;
	int array[len];
	cout << "Input: ";
	for (i = 0; i < len; i++) {
		array[i] = rand() % 100;
		cout << array[i] << " ";
	}
	cout << endl;
	cout << endl << "max-heap: " << endl;
	BuildMax_Heap(array, len);
	for(i = 0; i < len; i++){
		cout << array[i] << " ";
	}
	cout << endl;
	sort_heap(array, len);
	cout << endl << "after Heap Sort......" << endl;
	for (i = len - 1; i >= 0; i--) {
		cout << array[i] << " ";
	}

	return 0;
}