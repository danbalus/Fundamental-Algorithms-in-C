//Am facut o functie de inserare si una de cautare. De asemenea
//am mai facut 2 functii, una de testare si una unde voi calcula
//cazul mediu, cu elemente generate random
//De observat ca algoritmul este mult mai rapid decat cele studiate anterior
//pe masura ce se creste factorul de umplere se creste si efortul


#include "Profiler.h"
#include <stdio.h>

Profiler	p("Source");

#define N 10007 //cel mai apropiat nr prim de 10000, lungimea cu care se obisnuieste sa se faca numaratorile
#define K1 1 //ct 1 din hash
#define K2 1//ct 2 din hash

int contor = 0; //pt a fi vizibil peste tot si pt a ramane valoare dupa parasirea fc


int inserare_hash(int *v, int x) { //tabloul si valoarea de inserat
	int i = 0, locatie = -1;

	do {
		locatie = (x + K1 * i + K2 * i * i) % N; //Fc de hash
		if (v[locatie] == -1)  //daca locatia e goala
		{
			v[locatie] = x; // punem in ea valoarea lui x
			return locatie; //returnam indicele la care se afla
		}
		else
		{
			locatie = -1;
			i++;  //cautam in continuare un loc liber
		}
	} while (i < N);

	return locatie; //val din locatie poate fi locatia sau -1 
}

int cautare_hash(int *v, int x) { //tabloul si val de cautat
	int i = 0, locatie = -1;

	do
	{
		locatie = (x + K1 * i + K2 * i * i) % N; //fc hash
		contor++;

		if (v[locatie] == x)
		{
			return 1; //s-a gasit val cautata
		}
		else
		{
			i++; //nu s-a gasit, se continua cautarea
		}
	} while ((v[locatie] != -1) && (i != N)); //se cauta ata timp cat nu se da peste o locatie goala si nu se ajunge la sfarsitul sirului

	return 0; //nu s-a gasit nr
}

void init_vector(int *v) {  //folosim functia pentru a intitializa vectorul cu -1, pt a sti daca s-a scris pe anumita pozitie
	for (int i = 0; i < N; i++)
	{
		v[i] = -1;  //puteam si 0, dar am ales sa umplu vectorul de la 0 inclusiv
	}
}

void test_demo() {
	int a[N];
	int v[10] = { 13, 14, 34, 64, 23, 123, 1, 4, 444, 100 };// elementele unde caut
	int v2[5] = { 2, 13, 64, 333, 7777 }; //el pe care le caut

	init_vector(a); //punem -1 peste tot

	for (int i = 0; i < 10; i++)
	{
		inserare_hash(a, v[i]); //punem in hash valorile din vector
	}
	for (int i = 0; i < 5; i++)  //cautam cele 5 valori din v2
	{
		if ((cautare_hash(a, v2[i]) != 0)) //daca sunt gasite
		{
			printf("\n Elementul %d a fost gasit pe pozitia %d \n", v2[i], i);
		}
		else //daca nu sunt gasite
		{
			printf("\n Elementul %d NU a fost gasit \n", v2[i]);

		}

	}

}
  
void test_avg(int n) {
	int gas = 0, neg = 0, max_gas = 0, max_neg = 0;
	int a[N];
	int v[N + 1500];
	int v2[1500];
	for (int nr_mas = 0; nr_mas < 5; nr_mas++) //am masurat de 5 ori
	{
		init_vector(a);
		FillRandomArray(v, n + 1500, 0, 1000000, true, 0);// am luat de la 0 ca am umplut initial cu -1
		FillRandomArray(v2, 1500, 0, n - 1, true, 0);//n = alfa * N= fac umplere *10007

		for (int i = 0; i < n; i++)
		{
			inserare_hash(a, v[i]);//inseram in a valorile din vector
		}
		for (int i = 0; i < 1500; i++) //cautam unde stim ca vom gasi, 1500 el
		{
			contor = 0;
			cautare_hash(a, v[v2[i]]); //cautam in a pe v[v2[i]], se creste automat contorul
			if (contor > max_gas)
			{
				max_gas = contor;  //actualizam contorul
			}
			gas = gas + contor;  //calc nr de el gasite
		}

		for (int i = n; i < n + 1500; i++) //cautam unde vom sti ca nu vom gasi
		{
			contor = 0;
			cautare_hash(a, v[i]); //cautam in a pe v[v2[i]], se creste automat contorul
			if (contor > max_neg)
			{
				max_neg = contor;  //actualizam contorul
			}
			neg = neg + contor; //calc nr de el negasite
		}
	}
	double NR_MAS = 5.00;
	double negasite = neg / NR_MAS; //ca am ams de 5 ori
	double gasite = gas / NR_MAS;
	double factor_umplere = (double)n / 10000.00; //calculam factor umplere

	printf("\nPt factorul de umplere %.2f, efortul MAXIM la GASITE: %d \n", factor_umplere, max_gas); //afisam ef max LA GASITE
	printf("Pt factorul de umplere %.2f, efortul MAXIM la NEGASITE: %d \n", factor_umplere, max_neg);//AFISAM EF MAX LA NEGASITE

	double efort_gasite = (double)gasite / 1500.00; //calc efort mediu pt cele 1500 de val
	double efort_negasite = (double)negasite / 1500.00;
	printf("Pt factorul de umplere %.2f, efortul MEDIU la GASITE: %.2f \n", factor_umplere, efort_gasite);
	printf("Pt factorul de umplere %.2f, efortul MEDIU la NEGASITE: %.2f \n\n", factor_umplere, efort_negasite);
}

void main() {
	test_demo();
	///*
	int v[5] = { 8000, 8500, 9000, 9500, 9900 };
	for (int i = 0; i < 5; i++) //apelam pentru cei 5 factori de umplere
		test_avg(v[i]);
	//*/ 
}
