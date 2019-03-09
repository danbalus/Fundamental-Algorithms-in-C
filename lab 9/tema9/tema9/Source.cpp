

#include <stdio.h>
#include <stdlib.h>
#include "Profiler.h"
#include <string.h>
#include <stdbool.h>
Profiler profiler("Source");
#define MAX 201

typedef struct NOD_STRUCTURA {//structura nodului
	int key;  //cheia din nod, valoarea
	int parinte; 
	int distanta; //distanta 
	int culoare; //culoarea pe care o are la un moment dat
	struct NOD_STRUCTURA *next;
}nod;


nod *v[201];// prin liste de adiacenta
int n;
char *nume_grafic; //folosit pt generarea graficului
int nr_muchii = 10; //initializam pt testul demo
int numar_varfuri = 100; 
int lungime_count; //pentru numararea operatiilor
int val_el, max; 

int coada[MAX]; //pt coada
int fata = 0; //pt coada
int spate = -1; //pt coada
int count = 0; //pt coada

int selectare_element() //fc care ia elementul din vector
{
	return coada[fata];
}

bool e_fara_elemente() //fc care verifica daca coada e nula
{
	return count == 0;//returneaza true in cazul in care sunt 0 elemente in coada
}

bool e_plina()//fc care verifica daca fc e plina
{
	return count == MAX; //returneaza true in cazul in care coada e plina(Are nr max de elemente disponibile in vector)
}

int size() //fc care returneaza marimea cozii cu ajutorul lui count(count se incrementeaza de fiecare data cand se introduce un nou element in coada)
{
	return count;
}

void pushh(int data)//fc care pune in coada elementul
{
	if (!e_plina()) //daca mai este loc in coada, at
	{
		if (spate == MAX - 1) //daca e penultimul inseamna ca urmeaza sa fie plina
		{
			spate = -1;//cand se va umple se va pune pe prima pozitie 
		}

		coada[++spate] = data;  //se va aseza pe acea pozitie elementul in vector
		count++; // se incrementeaza pozitia
	}
}

int popp() //fc care extrage din coada un elemnt
{
	int data = coada[fata++]; 
	if (fata == MAX)
	{
		fata = 0;
	}
	count--;
	return data;
}



void adaugare_nod(int nod1, int nod2)//adauga nodul nod1 la lista lui nod2 si invers
{
	nod *p = (nod*)malloc(sizeof(nod));//acordam memorie pt pointeri
	nod *r = (nod*)malloc(sizeof(nod));//acordam memorie pt pointeri
	p -> key = nod2; //punem valoarea nodului in cheie
	p -> culoare = 0;//setam culoarea pe alb
	p -> next = v[nod1];//
	v[nod1] = p;
	r -> key = nod1;
	r -> culoare = 0;//setam culoarea pe alb
	r -> next = v[nod2];
	v[nod2] = r;
}

void printare();
//bfs alg
void bfs(int x)
{
	//printf("intra\n");
	for (int i = 1; i <= numar_varfuri; i ++)
	{
		v[i] -> culoare = 0;//alb
		v[i] -> distanta = 9999999;//distanta
		v[i] -> parinte = NULL;//parintele va pointa catre null
	}
	v[x] -> culoare = 1;//gri
	v[x] -> distanta = 0;//setam distanta pe 0
	//printf("intra2\n");

	pushh(x);//punem in coada pe x
	//printf("intra3\n");
	max = -1;
	while (!e_fara_elemente())//atat timp cat coada nu e vida
	{
		//printf("intra3--3--3--34\n");
		profiler.countOperation(nume_grafic, lungime_count, 1);
		//printf("intra3--3---34\n");
		val_el = selectare_element();//acceseaza noul element
		//printf("intra3----34\n");
		printare();//afisare
		//printf("intra34\n");
		popp();//scoatem primul element intrat
		//printf("intra4\n");
		nod *aux = v[val_el];
		profiler.countOperation(nume_grafic, lungime_count, 1);
		while (aux != NULL)
		{
			profiler.countOperation(nume_grafic, lungime_count, 1);
			if (v[aux->key] -> culoare == 0)// daca varful e alb
			{
				profiler.countOperation(nume_grafic, lungime_count, 3);
				v[aux->key] -> culoare = 1;//se seteaza culoare pe gri
				v[aux->key] -> distanta = v[val_el] -> distanta + 1;//se incrementeaza distanta
				v[aux->key] -> parinte = val_el;
				pushh(aux -> key);//se pune pe stiva
			}
			aux = aux -> next;//trecem la urmatorul element
		}
		v[val_el]->culoare = 2;//negru
	}
	//printf("intra_iese\n");

}

void printare()
{
	if (v[val_el] -> distanta > max)//daca valoarea e mai amre decat amximul
	{
		max = v[val_el] -> distanta;//se actualizeaza maximul
		printf("\n");
	}
	printf("%d ", val_el);//se printeaza valoarea
}

/*void afisare(int nr_nod) //afiseaza lista vecinilorvarfuluii nr_nod
{
	printf("\n");
	nod *p = v[nr_nod];
	if (p != 0)
	{
		printf(" %d\n", nr_nod);
		nod *c = p;
		while (c)
		{
			
			printf(" %d", c -> key);
			c = c -> next;
		}
		printf("\n");
	}
}
*/
void test() {//test
	for (int i = 1; i <= numar_varfuri; i++)//initializam
	{
		v[i] = NULL;//initializam
	}
	nume_grafic = "MUCHII_VARIAT";//dam asa sa putem numara operatiile, daca nu crapa programul
	numar_varfuri = 7;
	adaugare_nod(7, 6);
	adaugare_nod(3, 6);
	adaugare_nod(7, 3);
	adaugare_nod(1, 2);
	adaugare_nod(2, 3);
	adaugare_nod(4, 3);
	adaugare_nod(4, 5);
	adaugare_nod(5, 6);
	bfs(6);//nodul de inceput este 6
	/*for (int i = 1; i <= numar_varfuri; i++) {
		afisare(v[i] -> key);
	}*/
	
}

bool nu_exista_muchia(int nod1, int nod2)//returnesaza true daca muchia nu exista
{
	nod *p = v[nod1];
	while (p != NULL)//atat timp cat nu se ajunge la sfarsit
	{
		if (p -> key == nod2)
		{
			return false;
		}
		p = p -> next;// cautam mai departe
	}
	return true;
}

void generare_graf() { //generarea muchiilor grafului
	int contor = nr_muchii;
	int nod1, nod2;
	while (contor > 0)//atat timp cat nu se ajunge la 0 cu decrementarea
	{
		nod1 = rand() % numar_varfuri + 1; //asa voi genera random  valoarea nodului destinatie
		nod2 = rand() % numar_varfuri + 1;  //asa voi genera random  valoarea nodului sursa
		if ((nod1 != nod2) && nu_exista_muchia(nod1, nod2)) //daca valorile sunt diferite si nu exista muchia in graf, atunci
		{
			adaugare_nod(nod1, nod2); //se adauga muchia
			contor--;  //se decrementeaza contorul 
		}
	}
}

void avg(int selectie) //fc cu care se genereaza graficele
{
	if (selectie == 1)
	{
		nume_grafic = "MUCHII_VARIAT";  //vom da nume diferite pentru string ul la numarare 
		numar_varfuri = 100;//nr varfuri fix si muchii variabile
		for (nr_muchii = 1000; nr_muchii < 5000; nr_muchii += 100)//variem nr de muchii
		{
			for (int i = 1; i <= numar_varfuri; i++)//initializam
			{
				v[i] = NULL;//initializam
			}
			generare_graf(); //generam graful
			lungime_count = nr_muchii; //dam lungimea pt count(grafice)
			n = numar_varfuri; 
			for (int i = 1; i <= numar_varfuri; i++)//pt toate varfurile 
			{
				if (v[i] -> culoare == 0) //daca nu a fost vizitat se apeleaza bfs
				{
					bfs(i);
				}
			}
		}
	}
	else
	{
		nume_grafic = "VARFURI_VARIAT";
		nr_muchii = 5500;
		for (numar_varfuri = 110; numar_varfuri < 200; numar_varfuri += 10) //variem nr de varfuri9
		{
			for (int i = 1; i <= numar_varfuri; i++)//initializam
			{
				v[i] = NULL; //initializam
			}
			generare_graf();
			lungime_count = numar_varfuri;
			n = numar_varfuri;
			for (int i = 1; i <= numar_varfuri; i++) //pt toate varfurile
			{
				if (v[i] -> culoare == 0) //daca nu a fost vizitat se apeleaza bfs
				{
					bfs(i);
				}
			}
		}
	}

}
void main() {
	test();
	//avg(1);
	//avg(2);
	//profiler.showReport();
}