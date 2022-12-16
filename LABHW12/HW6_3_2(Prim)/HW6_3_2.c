#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000L

typedef struct GraphType {
	int n;	// 정점의 개수
	int weight[MAX_VERTICES][MAX_VERTICES]; // 인접행렬로 표현
} GraphType;

int selected[MAX_VERTICES]; // 신장트리집합
int distance[MAX_VERTICES];
int connectedVertex[MAX_VERTICES]; // 정점 선택 후에 

// 최소 dist[v] 값을 갖는 정점을 반환
int get_min_vertex(int n)
{
	int v, i;
	for (i = 0; i < n; i++)
		if (!selected[i]) {
			v = i;
			break;
		}
	for (i = 0; i < n; i++)
		if (!selected[i] && (distance[i] < distance[v])) v = i; 
	return (v);
}

void prim(GraphType* g, int s)
{
	int i, u, v, j;

	for (u = 0; u < g->n; u++) // 초기화
		distance[u] = INF;
	distance[s] = 0; // 시작 정점
	connectedVertex[s] = s;

	for (i = 0; i < g->n; i++) {
		u = get_min_vertex(g->n);
		selected[u] = TRUE;
		
		if (distance[u] == INF) return;
		printf("<%d %d> %d\n", connectedVertex[u], u, g->weight[connectedVertex[u]][u]);

		for (v = 0; v < g->n; v++) {
			if (g->weight[u][v] != INF) {
				if (!selected[v] && g->weight[u][v] < distance[v]) {
					distance[v] = g->weight[u][v];
					connectedVertex[v] = u;
				}
			}
		}

		printf("selected[] = \t");
		for (j = 0; j < g->n; j++)
			printf("%6d", selected[j]);
		printf("\ndist[] = \t");
		for (j = 0; j < g->n; j++)
			printf("%6d", distance[j]);
		printf("\n\n");
	}
}

int main(void)
{
	GraphType g = { 6,
	{{ 0, 10, INF, 20, 70, INF },
	{ 10,  0, 50, 30, 60, INF },
	{ INF, 50, 0, INF, 40, 90 },
	{ 20, 30, INF, 0, INF, 80 },
	{ 70, 60, 40, INF, 0, INF },
	{ INF, INF, 90, 80, INF, 0 }}
	};
	prim(&g, 0);
	return 0;
}