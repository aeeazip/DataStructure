#define _CRT_SECURE_NO_WARNINGS
#define MAX_VERTICES 50
#include <stdio.h>
#include <stdlib.h>

typedef struct GraphType {
	int n; // ������ ����
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
}GraphType;

void init(GraphType* g) {
	int r, c;
	g->n = 0;

	for (r = 0; r < MAX_VERTICES; r++)
		for (c = 0; c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = 0;
}

void insert_vertex(GraphType* g, int v) { // ���� ����
	if (g->n + 1 > MAX_VERTICES) {
		fprintf(stderr, "�׷��� : ������ ���� �ʰ�");
		return 0;
	}
	g->n++;
}

void insert_edge(GraphType* g, int start, int end) { // ���� ����
	if (start< 0 || start>= g->n || end<0 || end>=g->n) {
		fprintf(stderr, "�׷��� : ���� ��ȣ ����");
		return 0;
	}
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}

void delete_edge(GraphType* g, int start, int end) { // ���� ����
	if (start< 0 || start>= g->n || end<0 || end>=g->n) {
		fprintf(stderr, "�׷��� : ���� ��ȣ ����");
		return 0;
	}
	g->adj_mat[start][end] = 0;
	g->adj_mat[end][start] = 0;
}

void read_graph(GraphType* g, char* filename) {
	FILE* fp;
	int n; // ���� ����
	int i, start, end;

	fp = fopen(filename, "r");
	if (fp == NULL) {
		fprintf(stderr, "������ �� �� �����ϴ�.\n");
		exit(1);
	}

	fscanf(fp, "%d", &n);
	for (i = 0; i < n; i++)
		insert_vertex(g, i);

	while (!feof(fp)) {
		fscanf(fp, "%d %d", &start, &end);
		insert_edge(g, start, end);
	}

	fclose(fp);
}

void write_graph(GraphType* g, char* filename) { // ���� ��ķ� ǥ���� �׷����� ���Ͽ� �����ϴ�(������ ���� �Է����ϰ� ����)
	// ȭ�鿡�� ��� + ���Ͽ��� ���
	FILE* fp;
	int r, c;

	fp = fopen(filename, "w");
	if (fp == NULL) {
		fprintf(stderr, "������ �� �� �����ϴ�.\n");
		exit(1);
	}

	fprintf(fp, "%d\n", g->n); // ���Ͽ� ���
	fprintf(stdout, "%d\n", g->n); // ȭ�鿡 ���
	
	for (r = 0; r < g->n; r++) {
		for (c = 0; c <= r; c++) {
			if (g->adj_mat[r][c]) {
				fprintf(fp, "%d %d\n", r, c); // ���Ͽ� ���
				fprintf(stdout, "%d %d\n", r, c); // ȭ�鿡 ���
			}
		}
	}
	printf("\n");

	fclose(fp);
}

int main(void) {
	GraphType* g = (GraphType*)malloc(sizeof(GraphType));
	init(g);

	read_graph(g, "graph.txt");

	insert_edge(g, 0, 3);
	write_graph(g, "result.txt");

	delete_edge(g, 2, 4);
	write_graph(g, "result.txt");
}