#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <limits.h>

#define TRUE	1
#define FALSE	0
#define MAX_VERTICES	100		// ����� �� 
#define INF 	999		// 

int distance[MAX_VERTICES];	// ���۳��κ����� �ִܰ�� �Ÿ� 
int found[MAX_VERTICES];	//  �湮�� ��� ǥ�� 

typedef struct GraphType {
	int n;					// ������ ����
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

// �׷��� �ʱ�ȭ 
void graph_init(GraphType* g) // �������� ����
{
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++)
		for (c = 0; c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = INF;

	for (r = 0; r < MAX_VERTICES; r++)
		g->adj_mat[r][r] = 0;
}

// ���� ���� ����
void insert_vertex(GraphType* g, int v) // �������� ����
{
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "�׷���: ������ ���� �ʰ�");
		return;
	}
	g->n++;
}

// ���� ���� ����
void insert_edge(GraphType* g, int start, int end, int weight) // �������� ����
{
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}
	g->adj_mat[start][end] = weight;
	g->adj_mat[end][start] = weight;
}

int choose(int distance[], int n, int found[]) // �������� ����
{
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for (i = 0; i < n; i++)
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	return minpos;
}

int previous[MAX_VERTICES];

void print_path(int previous[], int u, int start) { //4-<20>->2-<5>->3(25)   	4-->2-->3(25)
	if (previous[u] == start) {
		printf("%d", start);
		return;
	}
	else {
		print_path(previous, previous[u], start);
		printf("-<%d>->%d", distance[previous[u]] - distance[previous[previous[u]]], previous[u]); //���� �� ������ �Ÿ�
	}
}

void shortest_path(GraphType* g, int start, int end) // �ڵ� �ۼ�  //4-<20>->2-<5>->3(25)   	4-->2-->3(25)
{
	int i, u, w;
	int total = 0; // �ѰŸ�

	for (i = 0; i < g->n; i++) { //������������ i��° ���������� �ִܰŸ� �ʱ�ȭ
		distance[i] = g->adj_mat[start][i];
		found[i] = FALSE;
	}

	for (i = 0; i < g->n; i++)
		previous[i] = start;

	found[start] = TRUE; // ���� ���� �湮 ǥ��
	distance[start] = 0;

	for (i = 0; i < g->n - 1; i++) { // �ڱ� �ڽŰ��� �Ÿ��� �ִܰŸ����� �����ϴϱ� (g->n-1)����ŭ �ݺ�
		u = choose(distance, g->n, found);
		found[u] = TRUE;

		if (u == end) {
			print_path(previous, u, start);
			printf("-<%d>->%d(%d)\n", distance[u] - distance[previous[u]], u, distance[u]);   //4-<20>->2-<5>->3(25)   	4-->2-->3(25)
		}

		for (w = 0; w < g->n; w++) {
			if (!found[w]) { // ���� �湮���� ���� ������ �Ÿ� ����
				if (distance[w] > distance[u] + g->adj_mat[u][w]) {
					distance[w] = distance[u] + g->adj_mat[u][w];
					previous[w] = u;
					total = distance[u];
				}
			}
		}
	}

}

int main(void) // �������� ����
{
	GraphType g;
	int u, v, w;
	int start, end;

	graph_init(&g); // �׷��� �ʱ�ȭ

	scanf("%d", &g.n);
	scanf("%d %d %d", &u, &v, &w);
	while (u != -1) {
		insert_edge(&g, u, v, w);
		scanf("%d %d %d", &u, &v, &w);
	}
	scanf("%d", &start);
	scanf("%d", &end);

	shortest_path(&g, start, end);
}