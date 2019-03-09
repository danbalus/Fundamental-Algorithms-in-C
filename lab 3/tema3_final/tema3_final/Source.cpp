#include "Profiler.h"
#include <stdio.h>
Profiler	p("Source");


//int lungime;


void max_heapify(int *v, int lungime_heap, int i, int lungime) {
	Operation o1 = p.createOperation("heap_sort_atribuiri", lungime);
	Operation o2 = p.createOperation("heap_sort_comparatii", lungime);
	Operation o3 = p.createOperation("heap_sort_total", lungime);

	int aux;
	int indice_max;
	int lungime_stanga = 2 * i + 1;
	int lungime_dreapta = 2 * i + 2;

	p.countOperation("heap_sort_comparatii", lungime, 1);
	if (lungime_stanga <= lungime_heap && v[lungime_stanga] > v[i]) {
		indice_max = lungime_stanga;

	}
	else {
		indice_max = i;
	}p.countOperation("heap_sort_comparatii", lungime, 1);

	if (lungime_dreapta <= lungime_heap && v[lungime_dreapta] > v[indice_max]) {
		indice_max = lungime_dreapta;
	}

	if (indice_max != i) {
		aux = v[i];
		v[i] = v[indice_max];
		v[indice_max] = aux;
		p.countOperation("heap_sort_atribuiri", lungime, 3);
		max_heapify(v, lungime_heap, indice_max, lungime);
	}
}

void bottoom_up(int *v, int i, int lungime) {

	for (int j = (i - 1) / 2 - 1; j >= 0; j--) {
		max_heapify(v, i, j, lungime);
	}
}


void heap_sort(int *v, int i, int lungime) {

	bottoom_up(v, i, lungime);
	int aux;
	for (int j = 0; j < i; j++) {
		aux = v[i - j - 1];
		v[i - j - 1] = v[0];
		v[0] = aux;
		p.countOperation("heap_sort_atribuiri", lungime, 3);
		max_heapify(v, i - j - 2, 0, lungime);
	}
}
/*void swap(int* a, int* b)
{
int t = *a;
*a = *b;
*b = t;
}
*/
int partition(int *v, int pp, int r, int lungime) {
	Operation o4 = p.createOperation("quick_sort_atribuiri", lungime);
	Operation o5 = p.createOperation("quick_sort_comparatii", lungime);
	Operation o6 = p.createOperation("quick_sort_total", lungime);
	int x, i;
	p.countOperation("quick_sort_atribuiri", lungime, 1);
	x = v[r]; //pivot //r=max//
	i = pp - 1;//p=low

	for (int j = pp; j <= r - 1; j++) {
		p.countOperation("quick_sort_comparatii", lungime, 1);
		if (v[j] <= x) {
			i++;
			int aux = v[i];
			v[i] = v[j];
			v[j] = aux;
			p.countOperation("quick_sort_atribuiri", lungime, 3);
			//swap(&v[i], &v[j]);
		}
	}
	int aux2 = v[i + 1];
	v[i + 1] = v[r];
	v[r] = aux2;
	p.countOperation("quick_sort_atribuiri", lungime, 3);

	//swap(&v[i + 1], &v[r]);
	return (i + 1);
}


void quick_sort(int *v, int p, int r, int lungime) {
	int q;
	if (p < r) {
		q = partition(v, p, r, lungime);
		quick_sort(v, p, q - 1, lungime);
		quick_sort(v, q + 1, r, lungime);
	}
}

int quick_select(int *v, int p, int r, int i, int lungime) {
	if (p == r)
		return v[p];
	int q = partition(v, p, r, lungime);
	int k = q - p + 1;

	if (i == k) {
		return v[q];
	}
	else if (i < k) {
		return quick_select(v, p, q - 1, i, lungime);
	}
	else
		return quick_select(v, q + 1, r, i - k, lungime);

}

void printare(int *v, int n) {
	for (int i = 0; i < n; i++)
		printf("%d, ", v[i]);
}

void copiere(int v[], int a[], int n) {
	for (int i = 0; i < n; i++)
		a[i] = v[i];
}
/*
int partition2(int *v, int pp, int r) {
int x, i;
p.countOperation("quick_sort_atribuiri", lungime, 1);
x = v[(pp + r) / 2]; //pivot //r=max//
i = pp - 1;//p=low

for (int j = pp; j <= r - 1; j++) {
p.countOperation("quick_sort_comparatii", lungime, 1);
if (v[j] <= x) {
i++;
int aux = v[i];
v[i] = v[j];
v[j] = aux;
p.countOperation("quick_sort_atribuiri", lungime, 3);
//swap(&v[i], &v[j]);
}
}
int aux2 = v[i + 1];
v[i + 1] = v[r];
v[r] = aux2;
p.countOperation("quick_sort_atribuiri", lungime, 3);

//swap(&v[i + 1], &v[r]);
return (i + 1);
}


void quick_sort2(int *v, int p, int r) {
int q;
if (p < r) {
q = partition2(v, p, r);
quick_sort2(v, p, q - 1);
quick_sort2(v, q + 1, r);
}
}
*/
void test_demo() {
	int v[10] = { -13, 14, 34, 64, -23, 123, 1, 4, 444, 100 };
	heap_sort(v, 10, 10);
	printf("\n Sirul sortat cu heap sort:  ");
	printare(v, 10);

	int v1[10] = { -13, 14, 34, 64, -23, 123, 1, 4, 444, 100 };
	quick_sort(v1, 0, 9, 10);
	printf("\n Sirul sortat cu quick sort:  ");
	printare(v1, 10);

	int v2[10] = { -13, 14, 34, 64, -23, 123, 1, 4, 444, 100 };
	int q = quick_select(v2, 0, 9, 5, 10);
	printf("\n elementul cu quick select: %d ", q);
	//printare(v2, 10);
	int v4[10] = { -13, 14, 34, 64, -23, 123, 1, 4, 444, 100 };
	//	//quick_sort2(v4, 0, 9);
	printf("\n Sirul sortat cu quick sort2:  ");
	printare(v4, 10);
}

void test_avg() {

	int i;
	int v1[10000], v2[10000], v3[10000];
	for (i = 0; i < 10000; i++) {
		v1[i] = 0;
		v2[i] = 0;
		v3[i] = 0;
	}

	printf(" \n \n Vectorul nesortat cu bottom up  : \n");
	printare(v1, 100);
	printf(" \n \n Vectorul nesortat cu top down: \n");
	printare(v2, 100);
	printf(" \n \n Vectorul nesortat cu heap sort: \n");
	printare(v3, 100);

	for (int i = 0; i < 10000; i += 100) {
		//lungime = i;
		FillRandomArray(v1, i);
		//lungime = i;
		copiere(v1, v2, i);
		quick_sort(v1, 0, i - 1, i);

		copiere(v2, v3, i);
		//quick_select(v2, 0, i - 1, 5);

		heap_sort(v3, i, i);
	}

	p.addSeries("heap_sort_total", "heap_sort_atribuiri", "heap_sort_comparatii");
	p.addSeries("quick_sort_total", "quick_sort_atribuiri", "quick_sort_comparatii");

	printf(" \n \n Vectorul cu bottom up: \n");
	printare(v1, 100);
	printf(" \n \n Vectorul cu top_down: \n");
	printare(v2, 100);
	printf(" \n \n Vectorul cu heap sort: \n");
	printare(v3, 100);

	p.createGroup("MEDIU_STATISTIC_ATRIBUIRI", "heap_sort_atribuiri", "quick_sort_atribuiri");
	p.createGroup("MEDIU_STATISTIC_COMPARATII", "heap_sort_comparatii", "quick_sort_comparatii");
	p.createGroup("MEDIU_STATISTIC_TOTAL", "heap_sort_total", "quick_sort_total");
	p.showReport();
}
void test_worst() {
	int v1[10000], v2[10000], v3[10000];
	for (int i = 0; i < 10000; i++) {
		v1[i] = 0;
		v2[i] = 0;
		v3[i] = 0;
	}

	printf(" \n \n Vectorul sortat test_worse_BUBBLE: \n");
	printare(v1, 100);
	printf(" \n \n Vectorul sortat test_worse_INSERTION: \n");
	printare(v2, 100);
	printf(" \n \n Vectorul sortat test_worse_SELECTION: \n");
	printare(v3, 100);

	for (int i = 0; i < 10000; i += 100) {
		FillRandomArray(v1, i, 10, 10000, 0, 2);
		//lungime = i;
		copiere(v1, v2, i);
		quick_sort(v1, 0, i - 1, i);

		copiere(v2, v3, i);
		//quick_select(v2, 0, i - 1, 5);

		heap_sort(v3, i, i);//nu cnnt
	}

	p.addSeries("heap_sort_total", "heap_sort_atribuiri", "heap_sort_comparatii");
	p.addSeries("quick_sort_total", "quick_sort_atribuiri", "quick_sort_comparatii");

	printf(" \n \n Vectorul cu bottom up: \n");
	printare(v1, 100);
	printf(" \n \n Vectorul cu top_down: \n");
	printare(v2, 100);
	printf(" \n \n Vectorul cu heap sort: \n");
	printare(v3, 100);

	p.createGroup("WORST_ATRIBUIRI", "heap_sort_atribuiri", "quick_sort_atribuiri");
	p.createGroup("WORST_STATISTIC_COMPARATII", "heap_sort_comparatii", "quick_sort_comparatii");
	p.createGroup("WORST_STATISTIC_TOTAL", "heap_sort_total", "quick_sort_total");
	p.showReport();
}

void test_best() {
	int v1[10000], v2[10000], v3[10000];
	for (int i = 0; i < 10000; i++) {
		v1[i] = 0;
		v2[i] = 0;
		v3[i] = 0;
	}

	printf(" \n \n Vectorul sortat test_worse_BUBBLE: \n");
	printare(v1, 100);
	printf(" \n \n Vectorul sortat test_worse_INSERTION: \n");
	printare(v2, 100);
	printf(" \n \n Vectorul sortat test_worse_SELECTION: \n");
	printare(v3, 100);

	for (int i = 0; i < 10000; i += 100) {
		FillRandomArray(v1, i);
		//lungime = i;
		copiere(v1, v2, i);
		//quick_sort2(v1, 0, i - 1);

		copiere(v2, v3, i);
		//quick_select(v2, 0, i - 1, 5);

		heap_sort(v3, i, i);//nu cnnt
	}

	p.addSeries("heap_sort_total", "heap_sort_atribuiri", "heap_sort_comparatii");
	p.addSeries("quick_sort_total", "quick_sort_atribuiri", "quick_sort_comparatii");

	printf(" \n \n Vectorul cu bottom up: \n");
	printare(v1, 100);
	printf(" \n \n Vectorul cu top_down: \n");
	printare(v2, 100);
	printf(" \n \n Vectorul cu heap sort: \n");
	printare(v3, 100);

	p.createGroup("BEST_ATRIBUIRI", "heap_sort_atribuiri", "quick_sort_atribuiri");
	p.createGroup("BEST_STATISTIC_COMPARATII", "heap_sort_comparatii", "quick_sort_comparatii");
	p.createGroup("BEST_STATISTIC_TOTAL", "heap_sort_total", "quick_sort_total");
	p.showReport();
}
int	main(void)
{
	test_demo();
	test_avg();
	//test_worst();
	//test_best();


	return(0);
}