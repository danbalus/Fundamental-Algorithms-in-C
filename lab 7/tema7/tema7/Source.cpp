#include <stdio.h>
#include <stdlib.h>
#include "Profiler.h"
Profiler	pp("Source");

int rep1[10] = { -9999, 2, 7, 5, 2, 7, 7, -1, 5, 2 };//am luat for urile de la 1, deci prima valoare nu se foloseste


typedef struct structura_rep2 {
	int nr;
	int key;
	struct structura_rep2 *fii[20];//locul unde se vor tine fii fiecarui nod
}rep2;

rep2 *root = NULL;
rep2 *noduri_R2[20]; //aici vor fi stocati toate nodurile de tip r2

typedef struct structura_rep3 {
	int key;
	struct structura_rep3 *fiu;
	struct structura_rep3 *frate;
}rep3;

//r3 *root3 = NULL;
rep3 *nod3;
rep3 *noduri_R3[20];//aici vor fi stocati toate nodurile de tip r3


void printareR1(int radacina, int lungime, int nivel) {
	for (int i = 1; i < lungime; i ++)
	{
		if (rep1[i] == radacina) //daca aici este radacina(prima data cand se intra),dupa vor fi nodurile
		{
			for (int j = 0; j < nivel; j ++)
			{
				printf("\t");
				//printf("%d", j);
			}
			printf("%d\n", i); //se printeaza valoare nodului
			printareR1(i, lungime, nivel + 1);//se apeleaza recursiv functia cu locatia urmatorului nod
		}
	}
}

void R1R2(int *r1, int lungime) {
	for (int i = 1; i <= lungime; i ++)
	{
		noduri_R2[i] = (rep2*)malloc(sizeof(rep2)); //alocam memorie vectorului de nodului
		noduri_R2[i] -> nr = 0; //initializam nr
		noduri_R2[i] -> key = i; //valoarea nodurilor, 1 2 3 4 5 6 7
		
	}
	for (int i = 1; i < lungime; i ++)  //cautam pana dam de radacina
	{
		if (r1[i] == -1) // daca e radacina, atunci
		{ 
			root = noduri_R2[i]; //point am nodul din vector la root
		}
		else  //daca nu e radacina, atunci
		{
			rep2 *parinte = noduri_R2[r1[i]]; //cautam parintele datorita vectorului r1
			rep2 *copil = noduri_R2[i]; // inseamna ca nodul e copilul cuiva
			parinte -> fii[parinte -> nr] = copil; //parinte->nr e indicele de copil (Cati copii are +1)
			(parinte -> nr)++;//incrementam indicele
		}
	}

}

void printare_R1R2(rep2 *nod, int nivel)
{
	for (int i = 1; i <= nivel; i ++)
	{
		printf("\t");
	}
	printf("%d\n", nod -> key); //afisam cheia nodului
	for (int i = 0; i < nod -> nr; i ++) //nod->nr este numarul de fii
	{
		printare_R1R2((nod -> fii)[i], nivel + 1);//fiind fii, trebuie pusi pe nivele diferite
	}
}

void init(int lungime)
{
	for (int i = 0; i <= lungime; i++)
	{
		noduri_R3[i] = (rep3*)malloc(sizeof(rep3)); //alocam memorie vectorului de nodului
		noduri_R3[i] -> key = i; //nodurile, 1 2 3 4 5 6 7
		noduri_R3[i] -> fiu = NULL; //facem fiul sa pointeze la null
		noduri_R3[i] -> frate = NULL;//facem fratele sa pointeze la null

	}
}


void init1(int lungime) //aici vom initializa  R1R2
{
	for (int i = 1; i <= lungime; i++)
	{
		if (rep1[i] == -1)   //CAUTAM RADACINA
		{
			printf("%d\n", i); //printam valoarea
			printareR1(i, lungime, 1);//trimitem locul radacinii, lungimea si nivelul
		}
	}
}


void R2R3(rep2 *nod) {
	if (nod != NULL)//daca nu s a ajuns la final
	{
		//printf("aici-1 ");
		int i = 0;
		for(int i = 0; i < nod -> nr; i ++) //nod -> nr este nr de copii
		{
			//noduri_R3[i] = (r3*)malloc(sizeof(r3)); //alocam memorie vectorului de nodului
			if (i == 0) //daca este primul nod
			{
				//noduri_R3[i]->fiu = NULL;
				//noduri_R3[i]->frate = NULL;
				//printf("aici-1-2 ");
				noduri_R3[nod-> key] -> fiu = noduri_R3[nod-> fii[0] -> key]; //daca e primul nod adunci nu are frate inca
				//printf("aici-2 ");
			}
			else 
			{
				//printf("aici-2-3 ");
				noduri_R3[nod-> fii[i - 1] -> key] -> frate = noduri_R3[nod-> fii[i] -> key];//fratele e cel din stanga
				//printf("aici-3 ");

			}
			//printf("aici-4 ");
			R2R3(nod-> fii[i]); //apelam functia cu fiul
			//printf("aici-5 ");
		}
	}
	//printf("gATA");
}


void printare_R2R3(int cheie, int nivel) {
	for (int i = 0; i < nivel; i++)
	{
		printf("\t");
	}
	printf("%d\n", cheie);//printam cheia
	//printf("\n"); 
	if (noduri_R3[cheie] -> fiu != NULL)  //daca mai este un fiu
	{
		printare_R2R3(noduri_R3[cheie] -> fiu -> key, nivel + 1);//daca e fiu, atunci trebuie sa fie pe nivelul urmator
	}
	if (noduri_R3[cheie] -> frate != NULL) //daca mai este un frate
	{
		printare_R2R3(noduri_R3[cheie] -> frate -> key, nivel); //daca e frate, atunci trebuie sa fie pe acelasi nivel
	}

}


int main() {

	R1R2(rep1, 10);
	printf("\n\n\n Arbore R1: \n\n");
	init1(10);

	printf("\n\n\n Arbore R1R2: \n\n");
	printare_R1R2(root, 0);

	printf("\n\n\n Arbore R2R3: \n\n");
	init(10);
	R2R3(root);
	printare_R2R3(root -> key, 0);

	return 0;
}
