#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>
#include <string.h>
#include "Profiler.h"
Profiler profiler("tema10");

#define MAXV 1024 // nr max de varfuri

#define BUFFER_LEN 1024 // nr max de carac 


typedef struct node node;
struct node { //structura unui nod
	int val;
	struct node *next;
};

// this is for a directed, unweighted graph
typedef struct { //graf orientat
	node *lista_adiacenta[MAXV];
	int outDeg[MAXV];
	int numar_noduri;
	int numar_muchii;
} graph;



typedef enum { UNDISCOVERED, DISCOVERED, PROCESSED } status_nod;
typedef enum { UNKNOWN, TREE, BACK, FORWARD, CROSS } status_muchie;

// data for topological sort using DFS on a directed graph
typedef struct {
	int ceas_contor;
	status_nod status[MAXV];
	int intrare_timp[MAXV];
	int iesire_timp[MAXV];
	int parinte[MAXV];
	int inDeg[MAXV];
	int stack[MAXV];
	int stackSize;
} dfsDataT;

void init(int argc, char *argv[], graph *g, int alege_exemplu);
void initGraph(graph *g);
int readGraph(graph *g, char *filename);
void addEdge(graph *g, int u, int v);

void initDFS(graph *g, dfsDataT *data);
void topSort(graph *g);
void dfs(graph *g, int u, dfsDataT *data);
status_muchie classifyEdge(int u, int v, dfsDataT *data);

int numar_varfuri =0;  //folosit pt generarea graficului
int nr_muchii = 0;  //folosit pt generarea graficului
char *nume_grafic="demo"; ; //folosit pt generarea graficului
int lungime_count; //pentru numararea operatiilor

void topSort(graph *g) {
	dfsDataT data;
	int i;

	initDFS(g, &data);
	for (i = 0; (i < g->numar_noduri) && (data.stackSize < g->numar_noduri); i++) {  //toate nodurile sunt in stack cand stackSize == numVertices
		if (data.inDeg[i] == 0) //incepem dfs de la nodul cu degree ul 0
			dfs(g, i, &data);
	}
	if (data.stackSize < g->numar_noduri)
		printf("Nu este un DAG, unele noduri aLCtuiesc un ciclu\n");

	printf("Sortare Topologica:"); //printare sortarea topologica
	for (i = data.stackSize - 1; i >= 0; i--)
		printf(" %d", data.stack[i]);
	printf("\n");
}
//static int varf_start_cond = 0;
void dfs(graph *g, int u, dfsDataT *data) {
	node *ptr;
	
	int v;
	status_muchie class1;
	profiler.countOperation(nume_grafic, lungime_count, 2);
	//timestamp on entering
	data -> ceas_contor++;
	data -> intrare_timp[u] = data -> ceas_contor;
	data -> status[u] = DISCOVERED;

	//walk through the adjacency list
	ptr = g -> lista_adiacenta[u];
	profiler.countOperation(nume_grafic, lungime_count, 1);
	//if (varf_start_cond == 0){
		//printf("%d", u); 
	//	varf_start_cond++;
	//}
	

	while (ptr != NULL) {
		v = ptr -> val;
		profiler.countOperation(nume_grafic, lungime_count, 1);

		if (data -> status[v] == UNDISCOVERED) {

			printf("%d ", v); //aici se printeaza drumul
			data -> parinte[v] = u;
			profiler.countOperation(nume_grafic, lungime_count, 1);
			dfs(g, v, data);
			//printf("\n ");
			//profiler.countOperation(nume_grafic, lungime_count, 1);//else if

		}
		else if (data->status[v] != PROCESSED) { // == DISCOVERED
			class1 = classifyEdge(u, v, data);

			if (class1 == BACK)
				printf("\nS-a gasit un ciclu, graful nu va fi DAG\n");
		}
		ptr = ptr->next;
	}

	//push u into the stack, for reverse printing of topological sort
	data -> stack[data -> stackSize ++] = u;
	//profiler.countOperation(nume_grafic, lungime_count, 3);

	//timestamp on leaving
	data -> ceas_contor ++;
	data -> iesire_timp[u] = data -> ceas_contor;
	data -> status[u] = PROCESSED;
	//classifyEdge(u, v, data);

}

status_muchie classifyEdge(int u, int v, dfsDataT *data) {


	if (data -> parinte[v] == u)//&& (data->status[v] != PROCESSED) && (data->status[v] != DISCOVERED))
	{
		printf("\nTipul muchiei ( %d, %d) este de ARBORE", u, v);
		return(TREE);
	}
	if (data -> status[v] == DISCOVERED)
	{
		printf("\nTipul muchiei ( %d, %d) este de INAPOI", u, v);
		return(BACK);
	}
	if (data -> status[v] == PROCESSED && (data -> intrare_timp[v] > data -> intrare_timp[u]))
	{
		printf("\nTipul muchiei ( %d, %d) este de INAINTE", u, v);
		return(FORWARD);
	}
	if (data -> status[v] == PROCESSED && (data -> intrare_timp[v] < data -> intrare_timp[u]) && (data -> iesire_timp[v] < data -> iesire_timp[u]))
	{
		printf("\nTipul muchiei ( %d, %d) este TRANDSVERSALA", u, v);
		return(CROSS);
	}

	printf("Nu se poate clasifica muchia (%d, %d)\n", u, v);
	return(UNKNOWN);
}

void initDFS(graph *g, dfsDataT *data) {
	int i;
	node *ptr;

	data->ceas_contor = 0;
	data->stackSize = 0;

	for (i = 0; i < g->numar_noduri; i++) {
		data->status[i] = UNDISCOVERED;
		data->intrare_timp[i] = -1;
		data->iesire_timp[i] = -1;
		data->parinte[i] = -1;
		data->inDeg[i] = 0;
	}

	for (i = 0; i < g->numar_noduri; i++) {//mergem prin lista de adiacenta si numaram toate nodurile
		ptr = g->lista_adiacenta[i]; //mai tarziu se va porni parcurgerea din nodul cu degree ul 0
		while (ptr != NULL) {
			data -> inDeg[ptr -> val] ++;
			ptr = ptr->next;
		}
	}
}

void initGraph(graph *g) {
	g->numar_noduri = 0;
	g->numar_muchii = 0;
	for ( int i = 0; i<MAXV; i++) {
		g->outDeg[i] = 0;
		g->lista_adiacenta[i] = NULL;
	}
}

void addEdge(graph *g, int u, int v) {
	node *ptr;
	ptr = (node*)malloc(sizeof(node));
	ptr->val = v;
	ptr->next = g->lista_adiacenta[u];
	g->lista_adiacenta[u] = ptr;
	g->outDeg[u]++;
}

int readGraph(graph *g, char *filename) {
	int i, u, v;
	char buffer[BUFFER_LEN];
	FILE *fp = NULL;

	initGraph(g);
	fp = fopen(filename, "r");
	if (!fp)  return -1; //fisierul nu se deschide

	if (!fgets(buffer, BUFFER_LEN, fp)) //[pe prima linie nr de noduri numarul de muchii
		return -1;
	sscanf(buffer, "%d %d", &(g->numar_noduri), &(g->numar_muchii));
	if (g->numar_noduri < 1 || g->numar_noduri > MAXV || g->numar_muchii < 1)
		return -1;

	for (i = 0; i<g->numar_muchii; i++) {
		if (!fgets(buffer, BUFFER_LEN, fp))
			return -1;
		sscanf(buffer, "%d %d", &u, &v);
		if (u < 0 || u >= g->numar_noduri || v < 0 || v >= g->numar_noduri)
			return -1;
		addEdge(g, u, v);
	}

	fclose(fp);

	return g->numar_noduri;
}

void init(int argc, char *argv[], graph *g, int alege_exemplu) {
	int c;
	char filename[BUFFER_LEN];
	if (alege_exemplu == 1)
		strcpy(filename, "exemplul1.txt");
	else if (alege_exemplu == 2)
		strcpy(filename, "exemplul2.txt");
	else if (alege_exemplu == 3)
		strcpy(filename, "exemplul3.txt");


	printf("\n\n\n---------------------------------------------------------------------------------------------");
	printf("\n Fisierul de input e %s\n", filename);
	c = readGraph(g, filename);
	if (c < 1) {
		printf("Fisierul %s nu exista, sau are formatul gresit.\n",
			filename);
		exit(1);
	}
	printf("Graful are  %d varfuri si %d muchii\n", c, g->numar_muchii);
}
void demo(int argc, char *argv[], graph *g, dfsDataT data, int alege_exemplu)
{
	//1-exemplul 1
	//2-exemplul 2
	//3-exemplul 3
	if(alege_exemplu == 1)
	{
		init(argc, argv, g, alege_exemplu);
		topSort(g);
		//init(argc, argv, g, alege_exemplu);
		printf("\nDFS:\n");
		initDFS(g, &data);
		dfs(g, 0, &data);

		classifyEdge(0, 1, &data);
		classifyEdge(1, 2, &data);
		classifyEdge(1, 3, &data);
		classifyEdge(2, 3, &data);
		classifyEdge(2, 4, &data);
		classifyEdge(3, 5, &data);
		classifyEdge(0, 6, &data);
		classifyEdge(3, 6, &data);
		classifyEdge(5, 4, &data);
		classifyEdge(6, 5, &data);
	}
	else if (alege_exemplu == 3) 
	{
		init(argc, argv, g, alege_exemplu);
		topSort(g);
		//init(argc, argv, g, alege_exemplu);
		printf("\nDFS:\n");
		initDFS(g, &data);
		dfs(g, 0, &data);
		classifyEdge(0, 1, &data);
		classifyEdge(1, 2, &data);
		classifyEdge(1, 3, &data);
		classifyEdge(2, 3, &data);
		classifyEdge(2, 4, &data);
		classifyEdge(3, 5, &data);
		classifyEdge(0, 6, &data);
		classifyEdge(3, 6, &data);
		classifyEdge(5, 4, &data);
		classifyEdge(6, 5, &data);
		classifyEdge(0, 4, &data);
	}
	else if (alege_exemplu == 2)
	{
		init(argc, argv, g, alege_exemplu);
		//topSort(g);
		//init(argc, argv, g, alege_exemplu);
		printf("\nDFS:\n");
		initDFS(g, &data);
		dfs(g, 0, &data);
	}
				
}


bool nu_exista_muchia(dfsDataT data, int nod1, int nod2)//returnesaza true daca muchia nu exista
{
	
		if (data.parinte[nod1] == nod2 || data.parinte[nod2] == nod1)
		{
			return false;
		}
	
	return true;
}
void addEdgeRandom(graph *g, dfsDataT data) {
	node *ptr;
	int u, v;
	int contor = nr_muchii;
	
	while (contor > 0)//atat timp cat nu se ajunge la 0 cu decrementarea
	{
		u = rand() % numar_varfuri + 1; //asa voi genera random  valoarea nodului destinatie
		v = rand() % numar_varfuri + 1;  //asa voi genera random  valoarea nodului sursa
		if ((u != v) && nu_exista_muchia(data, u, v)) //daca valorile sunt diferite si nu exista muchia in graf, atunci
		{
			ptr = (node*)malloc(sizeof(node));
			ptr->val = v;
			ptr->next = g->lista_adiacenta[u];
			g->lista_adiacenta[u] = ptr;
			g->outDeg[u]++;
			contor--;
		}
	}
}

void avg(graph *g, dfsDataT data, int selectie) //fc cu care se genereaza graficele
{
	if (selectie == 1)
	{
		nume_grafic = "MUCHII_VARIAT";  //vom da nume diferite pentru string ul la numarare 
		numar_varfuri = 100;//nr varfuri fix si muchii variabile
		for (nr_muchii = 1000; nr_muchii < 5000; nr_muchii += 100)//variem nr de muchii
		{
			//printf("intra");
			//g->numar_muchii = nr_muchii;
			//g->numar_noduri = numar_varfuri;
			initGraph(g); //generam graful
			
			lungime_count = nr_muchii; //dam lungimea pt count(grafice)
			addEdgeRandom(g, data);
			for (int i = 1; i <= numar_varfuri; i++)//pt toate varfurile 
			{
			//if (data.status[i] == UNDISCOVERED) //daca nu a fost vizitat se apeleaza bfs
			//	{
					
					initDFS(g, &data);
					dfs(g, i, &data);
					
			//	}
			}
		}
	}
	else if (selectie == 2)
	{
		nume_grafic = "VARFURI_VARIAT";
		nr_muchii = 9000;

		for (numar_varfuri = 110; numar_varfuri < 200; numar_varfuri += 10) //variem nr de varfuri9
		{
			lungime_count = numar_varfuri;
			//g->numar_muchii = nr_muchii;
			//g->numar_noduri = numar_varfuri;
			initGraph(g);
			
			addEdgeRandom(g, data);
			for (int i = 0; i <= numar_varfuri; i++) //pt toate varfurile
			{
				//if (data.status[i] == UNDISCOVERED) //daca nu a fost vizitat se apeleaza bfs
				//{
					//initGraph(g);
					initDFS(g, &data);
					dfs(g, i, &data);
					
					
				//}
			}
		}
	}

}
int main(int argc, char *argv[]) {
	
	graph g, g1, g2,g3 ,g4;
	dfsDataT data, data1, data2, data3, data4;

	demo(argc, argv, &g, data, 1);
	demo(argc, argv, &g1, data1, 2);
	demo(argc, argv, &g2, data2, 3);
	/*
	initGraph(&g3);
	initGraph(&g4);
	avg(&g3, data3, 1);
	avg(&g4, data4, 2);
	profiler.showReport();
	*/
	return 0;
}