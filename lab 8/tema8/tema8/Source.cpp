#include <stdio.h>
#include <stdlib.h>
#include "Profiler.h"
Profiler profiler("Source");
#define MAX 10000

int numar_varfuri = 0;
int lungime_numarare = 0;

typedef struct Nod_Structura {//structura nodului din graf
	int rank;
	int key;
	struct Nod_Structura *p;
}nod;


typedef struct Lista_structura { //lista de noduri din graf
	nod *node;
	struct Lista_structura *next;
}lista;
lista *list[MAX];
//typedef struct Muchie_structura {
//	nod *a;
//	nod* b;
//	int cost;
//}muchie;


void make_set(nod *x);//prototip
nod *find_set(nod *x);//prototip
void union_2(nod *x, nod *y);//prototip


void connected_components() {  //cormen
	for (int i = 1; i <= numar_varfuri; i++) 
	{
		make_set(list[i] -> node);//se creeaza multimile de noduri cu 1 el
	}
	for (int i = 1; i <= numar_varfuri; i++) 
	{
		lista *lista_aux = list[i] -> next;
		while (lista_aux != NULL)
		{
			if (find_set(list[i] -> node) != find_set(lista_aux -> node)) 
			{
				union_2(list[i] -> node, lista_aux -> node);
			}
			lista_aux = lista_aux -> next;
		}
	}
}


bool same_components(nod *element1, nod *element2) { //cormen
	if (find_set(element1) == find_set(element2))//se verifica daca el fac parte din aceasi componenta 
	{
		//printf("muchia (%d, %d) exista deja", element1, element2);
		return true;
	}
	return false;

}


void make_set(nod *nod1) { //cormen //creeaza o multime cu un singur element
	nod1 -> p = nod1; //il facem s apointeze la el insusi
	nod1 -> rank = 0;//setam rank ul pe 0
	profiler.countOperation("MAKE_SET_TOTAL", lungime_numarare, 2);
}


void link(nod *nod1, nod *nod2) { //cormen
	profiler.countOperation("UNION_TOTAL", lungime_numarare, 1);
	if (nod1 -> rank > nod2 -> rank)//daca rangul primei structuri e mai amre decat celei de a doua
	{//se vreeaza legatura dintre nodurile trimise ca parametru
		nod2 -> p = nod1;
		profiler.countOperation("UNION_TOTAL", lungime_numarare, 1);
	}
	else 
	{
		nod1 -> p = nod2;
		profiler.countOperation("UNION_TOTAL", lungime_numarare, 2);
		if (nod1 -> rank == nod2 -> rank) 
		{
			profiler.countOperation("UNION_TOTAL", lungime_numarare, 1);
			nod2 -> rank ++;
		}
	}
}


nod *find_set(nod *nod1) { //cormen //gaseste reprezentatntul nodului 
	profiler.countOperation("FIND_SET_TOTAL", lungime_numarare, 1);
	if (nod1 != nod1->p) //daca nu e un sg nod in str, adica daca nu pointeaza la el insusi
	{
		profiler.countOperation("FIND_SET_TOTAL", lungime_numarare, 1);
		nod1 -> p = find_set(nod1 -> p);
	}
	return nod1 -> p;
}


void union_2(nod *nod1, nod *nod2) { //cormen////cormen//uneste 2 multimi de noduri
	link(find_set(nod1), find_set(nod2));//se cauta nodurile si le "lipesc"
}



void initializare() {
	for (int i = 1; i <= numar_varfuri; i ++) 
	{
		lista *lista_init = (lista *) malloc(sizeof(lista));
		nod *nod_init = (nod *) malloc(sizeof(nod));
		nod_init -> rank = 0;//initializam rank ul cu 0
		nod_init -> key = i;//ounem cheile de la 1 la nr de varfuri,nodul1 va avea cheia 1, nodul 2 cheia 2 etc
		nod_init -> p = nod_init;//facem sa pointeze la el insusi
		lista_init -> node = nod_init;//punem nodul in lista
		lista_init -> next = NULL;
		list[i] = lista_init;
	}
}


boolean nu_exista_ca_vecini(int nod1, int nod2) {//aceaasta fc va returna true daca  nodul din dr (antet) nu se afla in lista de vecini a nodului din stanga(antet)
	lista *lista_aux = list[nod1];
	if (nod1 == nod2) //daca sunt aceleasi noduri
	{
		return false;
	}

	while (lista_aux -> next != NULL) //atat timp cat mai sunt elemente
	{
		lista_aux = lista_aux -> next;//parcurgem el
		if (lista_aux -> node -> key == nod2) //daca se gaseste un nod care mai este deja
		{
			return false;//se returneaza false
		}
	}
	return true;
}


void adauga_nod(int nod1, int nod2) { //adaugare nod la lista de vecini
	lista *aux = (lista*)malloc(sizeof(lista));
	//if (same_components(aux->nod1, aux->nod2) == false)
	//{
	//}
	aux -> node = list[nod2] -> node;
	aux -> next = list[nod1] -> next;
	list[nod1]  -> next = aux;
}

void test_demo(int nr_v) {
	numar_varfuri = nr_v;
	initializare();
	// nodul 10 va trebui sa pointeze la el insusi intrucat nu are muchie
	adauga_nod(1, 3); adauga_nod(1, 2); adauga_nod(2, 3);
	adauga_nod(3, 2);//exista deja
	adauga_nod(9, 11);
	adauga_nod(5, 6); adauga_nod(5, 7);
	adauga_nod(9, 1);
	connected_components();//conectam componentele

	for (int i = 1; i <= nr_v; i ++)
	{
		printf(" Nod: %d \t Reprezentant: %d\n", list[i] -> node -> key, (find_set(list[i] -> node)) -> key);
	}
}


void generare_muchii(int n) {
	int i = 0;
	do
	{
		int nr_nod1 = rand() % numar_varfuri + 1;
		int nr_nod2 = rand() % numar_varfuri + 1;
		if (nu_exista_ca_vecini(nr_nod1, nr_nod2) != false && nu_exista_ca_vecini(nr_nod2, nr_nod1 != false)) 
		{
			adauga_nod(nr_nod1, nr_nod2);
			i++;
		}
	} while (n > i);
}

/*
int partition(int *v, int pp, int r, int lungime) {
	//Operation o4 = p.createOperation("quick_sort_atribuiri", lungime);
	//Operation o5 = p.createOperation("quick_sort_comparatii", lungime);
	//Operation o6 = p.createOperation("quick_sort_total", lungime);
	int x, i;
	//p.countOperation("quick_sort_atribuiri", lungime, 1);
	x = v[r]; //pivot //r=max//
	i = pp - 1;//p=low

	for (int j = pp; j <= r - 1; j++) {
		//p.countOperation("quick_sort_comparatii", lungime, 1);
		if (v[j] <= x) {
			i++;
			int aux = v[i];
			v[i] = v[j];
			v[j] = aux;
			//p.countOperation("quick_sort_atribuiri", lungime, 3);
			//swap(&v[i], &v[j]);
		}
	}
	int aux = v[i + 1];
	v[i + 1] = v[r];
	v[r] = aux;
	//p.countOperation("quick_sort_atribuiri", lungime, 3);

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
void Kruskal(int *cost, int *nod, int n, lista *m) {
	int nr = 4 * n;
	for (int i = 0; i < n; i++) {
		make_set(i);

	}
	quick_sort(m, 0, nr - 1);
	for (int i = 0; i < nr; i++) {
		if (same_components(find_set(m[i].a), find_set(m[i].b)) == false) {
			union_2(m[i].a, m[i].b);
		}
		
	}

}
*/

void test_avg() {
	
	for (int i = 100; i < MAX; i += 100) 
	{
		lungime_numarare = i;
		numar_varfuri = i;
		initializare();
		generare_muchii(i);
		connected_components();
	}
}

void main() {
	test_demo(11);

	test_avg();
	profiler.createGroup("multimi_disjuncte_grafic", "MAKE_SET_TOTAL", "UNION_TOTAL", "FIND_SET_TOTAL");
	profiler.showReport();
	
}
