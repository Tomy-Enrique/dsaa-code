#include<iostream>
#include<cstdlib>
using namespace std;

void adjust_node(int *arr, int n, int len)
{
    int l, r, min, temp;
    l = 2*n+1;
    r = 2*n+2;
    min = n;
    
    if(l < len && arr[min] > arr[l]){
   		min = l;
	}
	if(r < len && arr[min] > arr[r]){
		min = r;
	}
	
	if(min != n){
		temp = arr[n];
		arr[n] = arr[min];
		arr[min] = temp;
		adjust_node(arr, min, len);
	} 	
}

void push(int *arr, int i){
	arr[0] = arr[i];
}

int pop(int *arr){
	return arr[0];
}

void sort_heap(int *arr, int len)
{
    for (int i = len / 2; i >= 0; i--){
        adjust_node(arr, i, len);
    }
    int tmp;
    for (int i = 0; i < len; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
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
	for(i = 0; i < len; i++){
		array[i] = rand() % 100;
		cout << array[i] << " ";
	}
	cout << endl;
	cout << endl << "mix-heap: " << endl;
	sort_heap(array, len);
	cout << endl << "after Heap Sort......" <<endl;
	for(i = len-1; i >= 0; i--){
		cout << array[i] << " ";
	}
	
	return 0;
}
