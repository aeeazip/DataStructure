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
	int n; // ������ ����
	GraphNode *adj_list[MAX_VERTICES];
}GraphType;

void init(GraphType* g) {
	int v;
	g->n = 0;

	for (v = 0; v < MAX_VERTICES; v++)
		g->adj_list[v] = NULL;
}

void insert_vertex(GraphType* g, int v) { // ���� ����
	if (g->n + 1 > MAX_VERTICES) {
		fprintf(stderr, "�׷��� : ������ ���� �ʰ�");
		return 0;
	}
	g->n++;
}

void insert_edge(GraphType* g, int start, int end) { // ���� ���� _ ������
	GraphNode* node;

	if (start < 0 || start >= g->n || end < 0 || end >= g->n) {
		fprintf(stderr, "�׷��� : ���� ��ȣ ����");
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

void remove_node(GraphNode** phead, element item) { // 4�� ����Ʈ���� �н��� �Լ����� ListNode --> GraphNode�� ��������
	GraphNode* p, * prevp;

	if (*phead == NULL)
		printf("����Ʈ�� ����ֽ��ϴ�.\n");
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
			printf("%d�� ����Ʈ�� ����\n", item);
	}
}

// ���� ���� ����, v�� u�� ���� ����Ʈ���� �����Ѵ�.
void delete_edge(GraphType* g, int u, int v)
{
	GraphNode* node;
	

	if (u >= g->n || v >= g->n) {
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}

	// �ڵ� ����
	// (u, v)�� �����Ѵ�. remove_node�� ���. 
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
	GraphNode* p;
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