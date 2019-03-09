#include "Profiler.h"
#include <stdio.h>
//#define lungime 500
Profiler	p("Source");
//Profiler    p1("main");

//am ales sa folosesc biblioteca profiler

//-am implementat 3 functii pentru cele 3 sortari( bubble sort, insertion sort
//si selection sort),3 functii pentru cele 3 cazuri( average, best, worse) 
//o fucntie de scriere si alta pentru copiere( folosit la trimiterea acelorasi
//valori pentru cele 3 sortari)
//- in functia dest_demo am testat daca algoritmii sunt corecti;
//-in main apelez funtiile pe rand
//in fiecare functie afisez, doar cu o parte din sir, la inceputul si sfarsitul sortarii
//sa verific daca au intervenit erori de-alungul sortarii;

//-pe cazul MEDIU STATISTIC, numarul de atribuiri  este mai
//mare la bubble sort decat la insertion sort, respectiv mult mai mare decat 
//selection sort; 
//-nr de comparatii la bubble sort e cel mai mare, urmat de selection
//si inserion sort ; 
//-datorita acestora, totalul, suma comparatiilor cu atribuirile, face ca bubble sort
// sa fie mult mai mare fata de insertion si selection care se afla, relativ,
//pe aceeasi curba
//-timpul de parcurgere la toate cele 3 sortari, in cazul mediu, este O(n^2)

//-cazul CEL MAI NEFAVORABIL este atunci cand vectorii sunt sortati decrescator,
//numarul total de selectii si atribuiri este cul mai mare la bubble urmat de insertion,
//restpectiv selection;
//-comparatiile sunt aproximativ egale pt insertiion si selection sort,pe cand 
//la bubble numarul este mai mare;
//-in cazul atribuirilor, selection sort are un numar mic de atribuiri (aprox 6000 pt
//vector de 9900 el; bubble sort un numar mult mai amre( 146985159), insertion(49014851)
//bubble sort si insertion sort au timp liniar, O(n);
//-selection sort are timp patratic O(n^2);;

//-in cazul CEL MAI FAVORABIL, vectorii sunt sortati crescator,selection sort va face
//0 atribuiri, dar multe comparatii ;
//-insert sort  va face n atribuiri si n comparatii;
//-bubble sort  va face 0 atribuiri, dar n comparatii

//-insertion sort este STABIL
//-selection sort NU este STABIL
//-bubble sort NU este STABIL

// OBSERVATII PERSONALE
//-aceasta tema mi s-a parut interesanta deoarece am putut urmari, pe grafic,
//practic, evolutiile si diferentele dintre sortari;
//-am avut dificultati, la inceputul implementarii, in folosirea functiilor incluse 
//in header;
//- de asemenea, am avut dificultati la incercarea initiala de a genera in excel
// rezultatele, deoarece nu am reusit sa aduc pe acelasi grafic sortarile 



void bubble(int v[], int n) {
	int ok;
	int aux;
	int k = 0;
	Operation o1 = p.createOperation("BUBBLE_atribuiri", n);//daca nu le declar
	Operation o2 = p.createOperation("BUBBLE_comparatii", n);//voi avea null daca
	Operation o3 = p.createOperation("BUBBLE_total", n);//nu se executa operatia
	ok = 1;                                            //si nu voi putea aduna la total
	while (ok)
	{
	
		ok = 0;

		k++;
		for (int i = 0; i < n - 1; i++) {
			if (v[i] > v[i + 1])
			{
				aux = v[i];
				v[i] = v[i + 1];
				v[i + 1] = aux;
				ok = 1;
				
				p.countOperation("BUBBLE_atribuiri", n, 3);

			}
			p.countOperation("BUBBLE_comparatii", n, 1);
		}

	}

}


void insertion(int v[], int n) {
	int x, j;
	Operation o4 = p.createOperation("INSERTION_atribuiri", n);
	Operation o5 = p.createOperation("INSERTION_comparatii", n);
	Operation o6 = p.createOperation("INSERTION_total", n);

	for (int i = 1; i < n; i++)
	{
		
		x = v[i];
		j = i - 1;
		p.countOperation("INSERTION_atribuiri", n, 1);

		while (j >= 0 && x < v[j])
		{
			v[j + 1] = v[j];
			j--;
			p.countOperation("INSERTION_comparatii", n, 1);
			p.countOperation("INSERTION_atribuiri", n, 1);
		}

		v[j + 1] = x;
		p.countOperation("INSERTION_comparatii", n, 1);
		p.countOperation("INSERTION_atribuiri", n, 1);

	}

}

void selection(int v[], int n) {
	int di, aux;
	Operation o7 = p.createOperation("SELECTION_atribuiri", n);
	Operation o8 = p.createOperation("SELECTION_comparatii", n);
	Operation o9 = p.createOperation("SELECTION_total", n);


	for (int i = 0; i < n - 1; i++)
	{
		
		di = i; //di e dublura index
		for (int j = i + 1; j < n; j++)
		{
			p.countOperation("SELECTION_comparatii", n, 1);

			if (v[di] > v[j])
			{
				di = j;
			}
		}

		if (v[di] < v[i])
		{
			aux = v[di];
			v[di] = v[i];
			v[i] = aux;
			p.countOperation("SELECTION_atribuiri", n, 1);

		}
	}
}

void printare(int v[], int n) {
	for (int i = 0; i < n; i++)
		printf("%d, ", v[i]);
}

void copiere(int v[], int a[], int n) {
	for (int i = 0; i < n; i++)
		a[i] = v[i];
}

void test_demo() {
	int v1[10] = { 17, 21, 34, -3, 24, 12, 10, -10, 9, 2 };
	bubble(v1, 10);
	printf("\n  Vectorul sortat cu test_demo_BUBBLE: \n ");
	printare(v1, 10);


	int v2[10] = { 69, 22, 11, -4, -1, 33, 321, -10, 9, 2 };
	insertion(v2, 10);
	printf("\n  Vectorul sortat cu test_demo_INSERTION: \n ");
	printare(v2, 10);

	int v3[10] = { 34, 22, 21, -4, 51, -3, 18, -10, 9, 2 };
	selection(v3, 10);
	printf("\n  Vectorul sortat cu test_demo_SELECTION: \n ");
	printare(v3, 10);
}





void test_avg() {

	int i;

	int v1[10000], v2[10000], v3[10000];
	for (i = 0; i < 10000; i++) {
		v1[i] = 0;
		v2[i] = 0;
		v3[i] = 0;
	}


	printf(" \n \n Vectorul nesortat test_avg_BUBBLE: \n");
	printare(v1, 100);
	printf(" \n \n Vectorul nesortat test_avg_INSERTION: \n");
	printare(v2, 100);
	printf(" \n \n Vectorul nesortat test_avg_SELECTION: \n");
	printare(v3, 100);

	
		
	for (int i = 0; i < 10000; i += 100) {
		FillRandomArray(v1, i);
		copiere(v1, v2, i);
		bubble(v1, i);

		copiere(v2, v3, i);
		insertion(v2, i);

		selection(v3, i);
	}
	p.addSeries("BUBBLE_total", "BUBBLE_atribuiri", "BUBBLE_comparatii");
	p.addSeries("INSERTION_total", "INSERTION_atribuiri", "INSERTION_comparatii");
	p.addSeries("SELECTION_total", "SELECTION_atribuiri", "SELECTION_comparatii");

	printf(" \n \n Vectorul nesortat test_avg_BUBBLE: \n");
	printare(v1, 100);
	printf(" \n \n Vectorul nesortat test_avg_INSERTION: \n");
	printare(v2, 100);
	printf(" \n \n Vectorul nesortat test_avg_SELECTION: \n");
	printare(v3, 100);
	
	p.createGroup("MEDIU_STATISTIC_ATRIBUIRI", "BUBBLE_atribuiri", "INSERTION_atribuiri", "SELECTION_atribuiri");
	p.createGroup("MEDIU_STATISTIC_COMPARATII", "BUBBLE_comparatii", "INSERTION_comparatii", "SELECTION_comparatii");
	p.createGroup("MEDIU_STATISTIC_TOTAL", "BUBBLE_total", "INSERTION_total", "SELECTION_total");
	p.showReport();
}


void test_best() {
	int v1[10000], v2[10000], v3[10000];
	for (int i = 0; i < 10000; i++) {
		v1[i] = 0;
		v2[i] = 0;
		v3[i] = 0;
	}
	printf(" \n \n Vectorul nesortat test_best_BUBBLE: \n");
	printare(v1, 100);
	printf(" \n \n Vectorul nesortat test_best_INSERTION: \n");
	printare(v2, 100);
	printf(" \n \n Vectorul nesortat test_best_SELECTION: \n");
	printare(v3, 100);

	for (int i = 0; i < 10000; i += 100) {
		FillRandomArray(v1, i, 10, 10000, 0, 1);
		copiere(v1, v2, i);
		bubble(v1, i);

		copiere(v2, v3, i);
		insertion(v2, i);

		selection(v3, i);
	}

	p.addSeries("BUBBLE_total", "BUBBLE_atribuiri", "BUBBLE_comparatii");
	p.addSeries("INSERTION_total", "INSERTION_atribuiri", "INSERTION_comparatii");
	p.addSeries("SELECTION_total", "SELECTION_atribuiri", "SELECTION_comparatii");

	printf(" \n \n Vectorul nesortat test_best_BUBBLE: \n");
	printare(v1, 100);
	printf(" \n \n Vectorul nesortat test_best_INSERTION: \n");
	printare(v2, 100);
	printf(" \n \n Vectorul nesortat test_best_SELECTION: \n");
	printare(v3, 100);

	p.createGroup("BEST_ATRIBUIRI", "BUBBLE_atribuiri", "INSERTION_atribuiri", "SELECTION_atribuiri");
	p.createGroup("BEST_COMPARATII", "BUBBLE_comparatii", "INSERTION_comparatii", "SELECTION_comparatii");
	p.createGroup("BEST_TOTAL", "BUBBLE_total", "INSERTION_total", "SELECTION_total");
	p.showReport();
}

void test_worse() {
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
		copiere(v1, v2, i);
		bubble(v1, i);

		copiere(v2, v3, i);
		insertion(v2, i);

		selection(v3, i);
	}

	p.addSeries("BUBBLE_total", "BUBBLE_atribuiri", "BUBBLE_comparatii");
	p.addSeries("INSERTION_total", "INSERTION_atribuiri", "INSERTION_comparatii");
	p.addSeries("SELECTION_total", "SELECTION_atribuiri", "SELECTION_comparatii");

	printf(" \n \n Vectorul sortat test_worse_BUBBLE: \n");
	printare(v1, 100);
	printf(" \n \n Vectorul sortat test_worse_INSERTION: \n");
	printare(v2, 100);
	printf(" \n \n Vectorul sortat test_worse_SELECTION: \n");
	printare(v3, 100);

	p.createGroup("WORSE_ATRIBUIRI", "BUBBLE_atribuiri", "INSERTION_atribuiri", "SELECTION_atribuiri");
	p.createGroup("WORSE_COMPARATII", "BUBBLE_comparatii", "INSERTION_comparatii", "SELECTION_comparatii");
	p.createGroup("WORSE_TOTAL", "BUBBLE_total", "INSERTION_total", "SELECTION_total");
	p.showReport();
}

int	main(void)
{
	test_demo();
	//test_avg();
	//test_best();
	//test_worse();

	return(0);
}