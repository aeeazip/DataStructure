#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50

int visited[MAX_VERTICES];

typedef struct GraphType {
	int n;	// 정점의 개수
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

// 그래프 초기화 
void graph_init(GraphType* g) // 변경하지 말라
{
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++)
		for (c = 0; c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = 0;
}
// 정점 삽입 연산
void insert_vertex(GraphType* g, int v) // 변경하지 말라
{
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->n++;
}
// 간선 삽입 연산
void insert_edge(GraphType* g, int start, int end) // 변경하지 말라. 방향그래프 삽입연산으로 수정했음
{
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	g->adj_mat[start][end] = 1;
	//g->adj_mat[end][start] = 1;
}

int calc_in_degree(GraphType* g, int v) // 코드 작성
{
	int i, count = 0;

	for (i = 0; i < g->n; i++) {
		if (g->adj_mat[i][v] == 1)
			count++;
	}
	return count;
}

int main(void) // 변경하지 말라
{
	GraphType g;
	int num;
	int u, v;

	graph_init(&g);

	scanf("%d", &num); // 정점의 개수
	g.n = num;
	scanf("%d %d", &u, &v);
	while (u != -1 && v != -1) {
		insert_edge(&g, u, v);
		scanf("%d %d", &u, &v);
	}

	scanf("%d", &v);
	printf("%d\n", calc_in_degree(&g, v));
}