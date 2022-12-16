#define _CRT_SECURE_NO_WARNINGS
#define MAX_VERTICES 100
#define INF 9999

#include <stdio.h>
#include <stdlib.h>
#include "minheap.h"
#include "unionfind.h"

typedef struct GraphType {
	int n;					// ������ ����
	int adj_mat[MAX_VERTICES][MAX_VERTICES]; // ������ ����ġ ����
} GraphType;

// �׷��� �ʱ�ȭ 
void graph_init(GraphType* g)
{
	g->n = 0;

	for (int i = 0; i < MAX_VERTICES; i++)
		for (int j = 0; j < MAX_VERTICES; j++)
			g->adj_mat[i][j] = INF;
}

/*  */
void read_graph(GraphType* g, char* filename)
{
	FILE* fp = fopen(filename, "r");
	int n, start, end, weight;

	if (fp == NULL) {
		fprintf(stderr, "������ �� �� �����ϴ�.\n");
		exit(1);
	}

	fscanf(fp, "%d", &n);
	g->n = n;

	while (!feof(fp)) {
		fscanf(fp, "%d %d %d", &start, &end, &weight);
		g->adj_mat[start][end] = weight;
		g->adj_mat[end][start] = weight;
	}

	fclose(fp);
}

// ���� ����̳� ���� ����Ʈ���� �������� �о �ּ� ������ ���� 
// ����� ���� �׷����� �������� �����Ѵ�.
void insert_all_edges(HeapType* h, GraphType* g)
{
	int i, j;
	int key, u, v;

	for (i = 0; i < g->n; i++) {
		for (j = i; j < g->n; j++){
			element item;
			item.key= g->adj_mat[i][j];
			item.u = i;
			item.v = j;

			insert_min_heap(h, item);
		}
	}
}

void write_graph(GraphType* g, char* filename)
{
	int i, j;
	FILE* fp;

	HeapType* h1 = (HeapType*)malloc(sizeof(HeapType));
	init(h1);
	insert_all_edges(h1, g);

	if (filename == NULL) fp = stdout;
	else {
		fp = fopen(filename, "w");
		if (fp == NULL) {
			fprintf(stderr, "������ �� �� �����ϴ�.\n");
			return 0;
		}
	}

	fprintf(fp, "%d\n", g->n);
	for (i = 0; i < g->n; i++) 
		for (j = i; j < g->n; j++) 
			if (g->adj_mat[i][j] != INF) 
				fprintf(fp, "%d %d %d\n", i, j, g->adj_mat[i][j]);
			
		
	
}

// kruskal�� �ּ� ��� ���� Ʈ�� ���α׷�
void kruskal(GraphType* g, GraphType* t)
{
	int edge_accepted = 0;
	int uset, vset;
	
	HeapType* h = (HeapType*)malloc(sizeof(HeapType));
	init(h);
	insert_all_edges(h, g);

	set_init(g->n);
	printf("���õ� ����(�������):\n");

	while (edge_accepted < (g->n - 1)) {
		element e = delete_min_heap(h);

		uset = set_find(e.u);
		vset = set_find(e.v);

		if (uset != vset) {
			printf("<%d, %d> %d\n", e.u, e.v, e.key);

			edge_accepted++;
			set_union(uset, vset);

			t->adj_mat[e.u][e.v] = e.key;
			t->adj_mat[e.v][e.u] = e.key;
		}
	}
	printf("\n");
}

int main(void)
{
	GraphType g, t;		// �Է� �׷���, ��� Ʈ��

	graph_init(&g);
	//read_graph(&g, "input1.txt");
	read_graph(&g, "input.txt");

	graph_init(&t);
	t.n = g.n;

	kruskal(&g, &t);

	printf("���Ϸ� ���:\n");
	write_graph(&t, "output.txt");
	write_graph(&t, NULL);	// to stdout
}