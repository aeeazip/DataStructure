#define _CRT_SECURE_NO_WARNINGS
#define MAX_VERTICES 50
#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct GraphNode {
	int vertex;
	struct GraphNode* link;
}GraphNode;

typedef struct GraphType {
	int n; // 정점의 개수
	GraphNode *adj_list[MAX_VERTICES];
}GraphType;

void init(GraphType* g) {
	int v;
	g->n = 0;

	for (v = 0; v < MAX_VERTICES; v++)
		g->adj_list[v] = NULL;
}

void insert_vertex(GraphType* g, int v) { // 정점 삽입
	if (g->n + 1 > MAX_VERTICES) {
		fprintf(stderr, "그래프 : 정점의 개수 초과");
		return 0;
	}
	g->n++;
}

void insert_edge(GraphType* g, int start, int end) { // 간선 삽입 _ 무방향
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

void remove_node(GraphNode** phead, element item) { // 4장 리스트에서 학습한 함수에서 ListNode --> GraphNode로 변경했음
	GraphNode* p, * prevp;

	if (*phead == NULL)
		printf("리스트는 비어있습니다.\n");
	else if ((*phead)->vertex == item) {
		p = *phead;
		*phead = p->link;
		free(p);
	}
	else {
		p = *phead;
		do {
			prevp = p;
			p = p->link;
		} while (p != NULL && p->vertex != item);
		if (p != NULL) {
			prevp->link = p->link;
			free(p);
		}
		else
			printf("%d은 리스트에 없음\n", item);
	}
}

// 간선 삭제 연산, v를 u의 인접 리스트에서 삭제한다.
void delete_edge(GraphType* g, int u, int v)
{
	GraphNode* node;
	

	if (u >= g->n || v >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}

	// 코드 삽입
	// (u, v)를 삭제한다. remove_node를 사용. 
	for (node = g->adj_list[u]; node != NULL; node = node->link) {
		if (node->vertex == v)
			remove_node(&g->adj_list[u], v);
	}

	for (node = g->adj_list[v]; node != NULL; node = node->link) {
		if (node->vertex == u)
			remove_node(&g->adj_list[v], u);
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

void write_graph(GraphType* g, char* filename) { // 인접 행렬로 표현된 그래프를 파일에 저장하는(형식은 위의 입력파일과 같게)
	// 화면에도 출력 + 파일에도 출력
	GraphNode* p;
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
		for (p = g->adj_list[r]; p != NULL; p = p->link) {
			fprintf(fp, "%d %d\n", r, p->vertex);
			fprintf(stdout, "%d %d\n", r, p->vertex);
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