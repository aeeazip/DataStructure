#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <limits.h>

#define TRUE	1
#define FALSE	0
#define MAX_VERTICES	100		// 노드의 수 
#define INF 	999		// 

int distance[MAX_VERTICES];	// 시작노드로부터의 최단경로 거리 
int found[MAX_VERTICES];	//  방문한 노드 표시 

typedef struct GraphType {
	int n;					// 정점의 개수
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

// 그래프 초기화 
void graph_init(GraphType* g) // 변경하지 말라
{
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++)
		for (c = 0; c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = INF;

	for (r = 0; r < MAX_VERTICES; r++)
		g->adj_mat[r][r] = 0;
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
void insert_edge(GraphType* g, int start, int end, int weight) // 변경하지 말라
{
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	g->adj_mat[start][end] = weight;
	g->adj_mat[end][start] = weight;
}

int choose(int distance[], int n, int found[]) // 변경하지 말라
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
		printf("-<%d>->%d", distance[previous[u]] - distance[previous[previous[u]]], previous[u]); //점과 점 사이의 거리
	}
}

void shortest_path(GraphType* g, int start, int end) // 코드 작성  //4-<20>->2-<5>->3(25)   	4-->2-->3(25)
{
	int i, u, w;
	int total = 0; // 총거리

	for (i = 0; i < g->n; i++) { //시작정점에서 i번째 정점까지의 최단거리 초기화
		distance[i] = g->adj_mat[start][i];
		found[i] = FALSE;
	}

	for (i = 0; i < g->n; i++)
		previous[i] = start;

	found[start] = TRUE; // 시작 정점 방문 표시
	distance[start] = 0;

	for (i = 0; i < g->n - 1; i++) { // 자기 자신과의 거리는 최단거리에서 제외하니까 (g->n-1)번만큼 반복
		u = choose(distance, g->n, found);
		found[u] = TRUE;

		if (u == end) {
			print_path(previous, u, start);
			printf("-<%d>->%d(%d)\n", distance[u] - distance[previous[u]], u, distance[u]);   //4-<20>->2-<5>->3(25)   	4-->2-->3(25)
		}

		for (w = 0; w < g->n; w++) {
			if (!found[w]) { // 아직 방문하지 않은 정점만 거리 조정
				if (distance[w] > distance[u] + g->adj_mat[u][w]) {
					distance[w] = distance[u] + g->adj_mat[u][w];
					previous[w] = u;
					total = distance[u];
				}
			}
		}
	}

}

int main(void) // 변경하지 말라
{
	GraphType g;
	int u, v, w;
	int start, end;

	graph_init(&g); // 그래프 초기화

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