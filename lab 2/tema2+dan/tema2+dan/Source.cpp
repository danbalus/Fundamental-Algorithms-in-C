#include "Profiler.h"
#include <stdio.h>
Profiler	p("Source");

//in aceasta tema au fos studiate cele doua metode de constructie a
//unui heai si heap sort
// cei 2 algortimi sunt testati pe cazul mediu statistic
//algoritmul de construire bottom up are complexitata O(n),
//iar top down are complexitatea O(n log n)
//urmarind numarul de atribuiri si comparatii, se poate observa ca top down 
//are totalul mai mic decat bottom up
//sortarea se face cu ajutorul algoritmului de constructie bottom up
//la sortare se inlocuieste norul dorit cu ultimul din heap apoi se reconstruieste
//heapul
//eficienta algoritmului de sortare este O(n log n) in toate cele 3 cazuri
//(best, worse, average)
//heap sort nu este un algoritm stabil 
//cei 2 algoritmi de constructie formeaza un MAX HEAP (maximul sta in varf)

int lungime;
void max_heapify(int *v, int lungime_heap, int i) {
	Operation o1 = p.createOperation("Bottom_up_atribuiri", lungime);
	Operation o2 = p.createOperation("Bottom_up_comparatii", lungime);
	Operation o3 = p.createOperation("Bottom_up_total", lungime);

	int aux;
	int indice_max;
	int lungime_stanga = 2 * i + 1;
	int lungime_dreapta = 2 * i + 2;
	p.countOperation("Bottom_up_comparatii", lungime, 1);
	if (lungime_stanga <= lungime_heap && v[lungime_stanga] > v[i]) {
		indice_max = lungime_stanga;
		
	}
	else {
		indice_max = i;
	}p.countOperation("Bottom_up_comparatii", lungime, 1);
	if (lungime_dreapta <= lungime_heap && v[lungime_dreapta] > v[indice_max]) {
		indice_max = lungime_dreapta;
	}
	if (indice_max != i) {
		aux = v[i];
		v[i] = v[indice_max];
		v[indice_max] = aux;
		p.countOperation("Bottom_up_atribuiri", lungime, 3);
		max_heapify(v, lungime_heap, indice_max);
	}
}


void bottoom_up(int *v, int i) {
	
	for (int j = (i - 1) / 2; j >= 0; j--) {
		max_heapify(v, i, j);

	}
}

int lungime_heapp;
void insert_heap(int *v, int key) {
	Operation o4 = p.createOperation("top_down_atribuiri", lungime);
	Operation o5 = p.createOperation("top_down_comparatii", lungime);
	Operation o6 = p.createOperation("top_down_total", lungime);

	lungime_heapp = lungime_heapp + 1;
	int i = lungime_heapp;
	while (i > 0 && v[((i - 1) / 2)] < key) {
		v[i] = v[((i - 1) / 2)];
		i = (i - 1) / 2;
		p.countOperation("top_down_comparatii", lungime, 1);
		p.countOperation("top_down_atribuiri", lungime, 1);
	}
	v[i] = key;
	p.countOperation("top_down_comparatii", lungime, 1); //de la while
	p.countOperation("top_down_atribuiri", lungime, 1);

}

void top_down(int *v, int n) {
	
	lungime_heapp = 0;

	for (int i = 1; i < n; i++) {
		insert_heap(v, v[i]);
	}
}

void heap_sort(int *v, int i) {

	bottoom_up(v, i);
	int aux;
	for (int j = 0; j < i; j++) {
		aux = v[i - j - 1];
		v[i - j - 1] = v[0];
		v[0] = aux;
		max_heapify(v, i - j - 2, 0);
	}
}

void printare(int *v, int n) {
	for (int i = 0; i < n; i++)
		printf("%d, ", v[i]);
}

void copiere(int v[], int a[], int n) {
	for (int i = 0; i < n; i++)
		a[i] = v[i];
}

void test_demo() {
	int v[10] = { -13, 14, 34, 64, -23, 123, 1, 4, 444, 100 };
	printf("\n Sirul initial construit cu bottom up: ");
	bottoom_up(v, 10);
	printare(v, 10);

	int v1[10] = { -13, 14, 34, 64, -23, 123, 1, 4, 444, 100 };
	heap_sort(v1, 10);
	printf("\n Sirul sortat cu heap sort bottom up:  ");
	printare(v1, 10);

	int v2[10] = { -13, 14, 34, 64, -23, 123, 1, 4, 444, 100 };
	top_down(v2, 10);

	printf("\n Sirul construit cu top down:  ");
	printare(v2, 10);
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

	for (int i = 0; i < 10000; i += 100 ) {
		//lungime = i;
		FillRandomArray(v1, i);
		lungime = i;
		copiere(v1, v2, i);
		bottoom_up(v1, i);

		copiere(v2, v3, i);
		top_down(v2, i );

		heap_sort(v3, i);
	}

	p.addSeries("Bottom_up_total", "Bottom_up_atribuiri", "Bottom_up_comparatii");
	p.addSeries("top_down_total", "top_down_atribuiri", "top_down_comparatii");

	printf(" \n \n Vectorul cu bottom up: \n");
	printare(v1, 100);
	printf(" \n \n Vectorul cu top_down: \n");
	printare(v2, 100);
	printf(" \n \n Vectorul cu heap sort: \n");
	printare(v3, 100);

	p.createGroup("MEDIU_STATISTIC_ATRIBUIRI", "Bottom_up_atribuiri", "top_down_atribuiri");
	p.createGroup("MEDIU_STATISTIC_COMPARATII", "Bottom_up_comparatii", "top_down_comparatii");
	p.createGroup("MEDIU_STATISTIC_TOTAL", "Bottom_up_total", "top_down_total");
	p.showReport();
}

int	main(void)
{
	test_demo();
	test_avg();


	return(0);
}