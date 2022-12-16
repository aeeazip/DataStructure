#define _CRT_SECURE_NO_WARNINGS
#define MAX_VERTICES 100
#define INF 9999
#define TRUE 1
#define FALSE 0

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

typedef struct GraphType {
	int n; // ������ ����
	int weight[MAX_VERTICES][MAX_VERTICES]; // ���� ��ķ� ����
}GraphType;

int distance[MAX_VERTICES];
int found[MAX_VERTICES];
int previous[MAX_VERTICES];

void graph_init(GraphType* g) {
	g->n = 0;

	for (int i = 0; i < MAX_VERTICES; i++) 
		for (int j = 0; j < MAX_VERTICES; j++) 
			g->weight[i][j] = INF;	
}

void read_graph(GraphType *g) {
	FILE* fp = fopen("input.txt", "r");
	int n, u, v, w;

	if (fp == NULL) {
		printf("���� ���� ����\n");
		return -1;
	}
	fscanf(fp, "%d\n", &n);
	g->n = n;
	while (fscanf(fp, "%d %d", &u, &v) != EOF) {
		fscanf(fp, "%d\n", &g->weight[u][v]);
		g->weight[v][u] = g->weight[u][v];
	}
	fclose(fp);
}

int choose(int distance[], int n, int found[]) { // ���õ��� ���� ���� �� ���� ���� distance���� ���� ������ ��ȣ�� ��ȯ
	int i, min = INF, minpos = -1;
	for (i = 0; i < n; i++) {
		if (!found[i] && distance[i] < min) {
			min = distance[i];
			minpos = i;
		}
	}
	return minpos;
}

void print_path(int previous[], int u, int start) {
	if (previous[u] == start) {
		printf("%d", start);
		return;
	}
	else {
		print_path(previous, previous[u], start);
		printf(" -> %d", previous[u]);
	}
}

void shortest_path(GraphType* g, int start) {
	int i, u, w;

	for (i = 0; i < g->n; i++) { //������������ i��° ���������� �ִܰŸ� �ʱ�ȭ
		distance[i] = g->weight[start][i];
		found[i] = FALSE;
	}

	for (i = 0; i < g->n; i++)
		previous[i] = start;

	found[start] = TRUE; // ���� ���� �湮 ǥ��
	distance[start] = 0;
	for (i = 0; i < g->n - 1; i++) { // �ڱ� �ڽŰ��� �Ÿ��� �ִܰŸ����� �����ϴϱ� (g->n-1)����ŭ �ݺ�
		u = choose(distance, g->n, found);
		found[u] = TRUE;

		print_path(previous, u, start);
		printf(" -> %d (%d)\n", u, distance[u]);

		for (w = 0; w < g->n; w++) {
			if (!found[w]) { // ���� �湮���� ���� ������ �Ÿ� ����
				if (distance[w] > distance[u] + g->weight[u][w]) {
					distance[w] = distance[u] + g->weight[u][w];
					previous[w] = u;
				}
			}
		}
	}


}

int main(void) {
	GraphType g;
	graph_init(&g);
	read_graph(&g);
	shortest_path(&g, 4);
}