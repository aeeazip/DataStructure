#define _CRT_SECURE_NO_WARNINGS
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

typedef int element;
typedef struct GraphNode{
	int vertex;
	struct GraphNode* link;
} GraphNode;

typedef struct GraphType {
	int n;	// 정점의 개수
	GraphNode* adj_list[MAX_VERTICES];
} GraphType;

// 그래프 초기화 
void graph_init(GraphType* g) {
	int v;
	g->n = 0;
	for (v = 0; v < MAX_VERTICES; v++)
		g->adj_list[v] = NULL;
}

// 정점 삽입 연산
void insert_vertex(GraphType* g, int v) {
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->n++;
}

// 간선 삽입 연산, end를 start의 인접 리스트에 삽입한다.
void insert_edge(GraphType* g, int start, int end) {
	GraphNode* node;

	if (start < 0 || start >= g->n || end < 0 || end >= g->n) {
		fprintf(stderr, "그래프 : 정점 번호 오류");
		return 0;
	}

	node = (GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = end;
	node->link = g->adj_list[start];
	g->adj_list[start] = node;

	node = (GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = start;
	node->link = g->adj_list[end];
	g->adj_list[end] = node;
}

int visited[MAX_VERTICES];

// 너비 우선 탐색(인접 리스트)
// 이 코드에 간선을 출력하기 위한 코드를 삽입하는 것이 HW6_2_2의 숙제이다
void bfs_list(GraphType* g, int v) {
	GraphNode* w;
	QueueType q;
	init(&q);    				// 큐 초기 화 
	visited[v] = TRUE;      // 정점 v 방문 표시 
	enqueue(&q, v);			// 시작정점을 큐에 저장 
	while (!is_empty(&q)) {
		v = dequeue(&q);		// 큐에 저장된 정점 선택 
		for (w = g->adj_list[v]; w; w = w->link) //인접 정점 탐색
			if (!visited[w->vertex]) {	// 미방문 정점 탐색 
				visited[w->vertex] = TRUE;   // 방문 표시
				printf("(%d %d)\n", v, w->vertex);
				enqueue(&q, w->vertex);	//정점을 큐에 삽입
			}
	}
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

int main(void) {
	GraphType graph;
	int u, v;

	graph_init(&graph);
	read_graph(&graph, "infile.txt");

	printf("Enter 정점:");
	scanf("%d", &v);

	bfs_list(&graph, v);
}
