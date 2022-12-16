#define _CRT_SECURE_NO_WARNINGS
#define MAX_VERTICES 100
#define INF 9999
#define TRUE 1
#define FALSE 0

#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

typedef struct GraphType {
	int n; // 정점의 개수
	int weight[MAX_VERTICES][MAX_VERTICES]; // 인접 행렬로 구현
}GraphType;

int distance[MAX_VERTICES];
int found[MAX_VERTICES];
int previous[MAX_VERTICES];
char subway[MAX_VERTICES][10] = {"월곡", "종묘", "신당", "청구", "약수", "충무로", "서울역", "시청", "종로3가", "동대문", "을지로3가", "동대문역사"};

void graph_init(GraphType* g) {
	g->n = 0;

	for (int i = 0; i < MAX_VERTICES; i++)
		for (int j = 0; j < MAX_VERTICES; j++)
			g->weight[i][j] = INF;
}

void read_graph(GraphType* g) {
	FILE* fp = fopen("input.txt", "r");
	int n, u, v, w;

	if (fp == NULL) {
		printf("파일 오픈 에러\n");
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

int choose(int distance[], int n, int found[]) { // 선택되지 않은 정점 중 가장 작은 distance값을 갖는 정점의 번호를 반환
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
		printf("%s", subway[start]);
		return;
	}
	else {
		print_path(previous, previous[u], start);
		printf(" -> %s", subway[previous[u]]);
	}
}

void shortest_path(GraphType* g) {
	int i, j, u, w;
	int start = -1, end = -1;
	char s[15], e[15];

	printf("출발역:");
	scanf("%s", s);
	while (getchar() != '\n');
	printf("도착역:");
	scanf("%s", e);

	for (i = 0; i < g->n; i++) {
		if (strcmp(s, subway[i]) == 0)
			start = i;
		if (strcmp(e, subway[i]) == 0)
			end = i;
	}

	for (i = 0; i < g->n; i++) { //시작정점에서 i번째 정점까지의 최단거리 초기화
		distance[i] = g->weight[start][i];
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
			printf(" -> %s <%d>\n", subway[u], distance[u]);
			break;
		}

		for (w = 0; w < g->n; w++) {
			if (!found[w]) { // 아직 방문하지 않은 정점만 거리 조정
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
	shortest_path(&g);
}