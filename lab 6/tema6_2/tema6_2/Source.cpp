#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "Profiler.h"

Profiler profiler("demo");

int lungime;

typedef struct nod
{
	int val;
	int size;
	struct nod *left, *right;
}Nod;

int A[10000];
int nr = 0;



Nod* creare_bst(int i, int j)
{

	Nod *n = NULL;
	n = (Nod*)malloc(sizeof(Nod));

	if (i <= j)
	{


		int k = (i + j) / 2;
		n->val = A[k];
		n->left = creare_bst(i, k - 1);
		n->right = creare_bst(k + 1, j);
		nr++;
		if (n->left && n->right)
		{
			n->size = n->left->size + n->right->size + 1;
		}
		else
		{
			n->size = nr;
		}

		return n;
	}
	else
	{
		nr = 0;
		return NULL;
	}

}

Nod* Select(Nod *rad, int p)
{
	if (p<1 || p>lungime)
		return NULL;


	int k;
	if (rad->left == NULL)
		k = 1;
	else
		k = rad->left->size + 1;

	profiler.countOperation("bst", lungime, 1);
	if (p == k) {

		return rad;
	}
	else {
		profiler.countOperation("bst", lungime, 1);
		if (p<k) {

			return Select(rad->left, p);
		}
		else return Select(rad->right, p - k);
	}


}



void inordine(Nod *p)
{
	if (p != 0)
	{
		inordine(p->left);
		printf("\n%d", p->val);
		inordine(p->right);
	}

}
void afisare(Nod *p, int niv) {
	int i;
	if (p == NULL)
		return;
	//if (p != NULL) {
	for (i = 0; i < niv; i++)
	{
		printf("\t");

	}
	printf("%d ", p->val);
	printf("\n");
	afisare(p->left, niv + 1);
	afisare(p->right, niv + 1);
	//}

}
void preordine(Nod *p, int nivel)
{
	// int i;
	if (p != 0)
	{
		printf("\n%d  -size- %d", p->val, p->size);
		preordine(p->left, nivel + 1);
		preordine(p->right, nivel + 1);
	}
}
int main()
{
	for (int i = 0; i < 5; i++) {
		int x[10000];
		for (int n = 100; n <= 10000; n += 100) {
			lungime = n;
			Nod	*rad = creare_bst(1, n);
			FillRandomArray(x, n, 1, n, true, 0);
			for (int i = 0; i < n; i++) {

				Select(rad, x[i]);
			}
		}
	}


	profiler.showReport();

	lungime = 1000;
	for (int i = 0;i<10000;i++)
	{

		A[i] = i;

	}
	Nod *rad = creare_bst(1, 9);
	//inordine(rad);
	afisare(rad, 0);
	Nod *s = Select(rad, 3);
	printf("\n Selectia: %d", s->val);
	//preordine(rad,0);

	_getch();
	return 0;
}


