#define _CRT_SECURE_NO_WARNINGS
#define MAX_VERTICES 50
#include <stdio.h>
#include <stdlib.h>

typedef struct GraphType {
	int n; // 정점의 개수
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
}GraphType;

void init(GraphType* g) {
	int r, c;
	g->n = 0;

	for (r = 0; r < MAX_VERTICES; r++)
		for (c = 0; c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = 0;
}

void insert_vertex(GraphType* g, int v) { // 정점 삽입
	if (g->n + 1 > MAX_VERTICES) {
		fprintf(stderr, "그래프 : 정점의 개수 초과");
		return 0;
	}
	g->n++;
}

void insert_edge(GraphType* g, int start, int end) { // 간선 삽입
	if (start< 0 || start>= g->n || end<0 || end>=g->n) {
		fprintf(stderr, "그래프 : 정점 번호 오류");
		return 0;
	}
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}

void delete_edge(GraphType* g, int start, int end) { // 간선 삭제
	if (start< 0 || start>= g->n || end<0 || end>=g->n) {
		fprintf(stderr, "그래프 : 정점 번호 오류");
		return 0;
	}
	g->adj_mat[start][end] = 0;
	g->adj_mat[end][start] = 0;
}

void read_graph(GraphType* g, char* filename) {
	FILE* fp;
	int n; // 정점 개수
	int i, start, end;

	fp = fopen(filename, "r");
	if (fp == NULL) {
		fprintf(stderr, "파일을 열 수 없습니다.\n");
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

void write_graph(GraphType* g, char* filename) { // 인접 행렬로 표현된 그래프를 파일에 저장하는(형식은 위의 입력파일과 같게)
	// 화면에도 출력 + 파일에도 출력
	FILE* fp;
	int r, c;

	fp = fopen(filename, "w");
	if (fp == NULL) {
		fprintf(stderr, "파일을 열 수 없습니다.\n");
		exit(1);
	}

	fprintf(fp, "%d\n", g->n); // 파일에 출력
	fprintf(stdout, "%d\n", g->n); // 화면에 출력
	
	for (r = 0; r < g->n; r++) {
		for (c = 0; c <= r; c++) {
			if (g->adj_mat[r][c]) {
				fprintf(fp, "%d %d\n", r, c); // 파일에 출력
				fprintf(stdout, "%d %d\n", r, c); // 화면에 출력
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