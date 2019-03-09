#include<iostream>
using namespace std;
#define n 4
//#define k 3
#define INT_MAX 100000
struct element
{
	int value;
	int index;    //index of the array
	int arrIndex; //index of the next element in the array
};
void swap(struct element *a, struct element *b)
{
	struct element temp = *a;
	*a = *b;
	*b = temp;
}

void minHeapify(struct element a[], int size, int i)
{
	int l = 2 * i;
	int r = 2 * i + 1;
	int smallest = i;
	if (l<size && a[l].value<a[smallest].value)
		smallest = l;
	if (r<size && a[r].value<a[smallest].value)
		smallest = r;
	if (smallest != i)
	{
		swap(&a[i], &a[smallest]);
		minHeapify(a, size, smallest);
	}

}
void buildMinHeap(struct element a[], int size) {
	for (int i = size / 2;i >= 0;i--)
		minHeapify(a, size, i);
}
int *mergesortedArrays(int arr[3][4], int k)
{
	int *ans = new int[12];
	struct element minHeap[100];
	for (int i = 0; i < k; i++)
	{
		minHeap[i].value = arr[i][0];
		minHeap[i].index = i;
		minHeap[i].arrIndex = 1;
	}
	buildMinHeap(minHeap, k);
	for (int count = 0; count < n*k; count++)
	{
		ans[count] = minHeap[0].value;
		int index = minHeap[0].index;
		int c = minHeap[0].arrIndex;
		if (c<n)
		{
			minHeap[0].value = arr[index][n];
			minHeap[0].arrIndex += 1;
		}
		else
			minHeap[0].value = INT_MAX;
		minHeapify(minHeap, k, 0);
	}
	return ans;
}
void printArray(int arr[], int size)
{
	for (int i = 0; i < size; i++)
		cout << arr[i] << " ";
}
int main()
{
	int a[3][4] = { { 3, 5, 15, 30 },
	{ 1, 8, 21, 56 },
	{ 6, 25, 50, 108 } };
	int k = sizeof(a) / sizeof(a[0]);

	int *ans = mergesortedArrays(a, k);

	cout << "Merged sorted array : " << endl;
	printArray(ans, n*k);

	return 0;
}
