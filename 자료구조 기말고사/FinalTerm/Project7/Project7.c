#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 3

typedef struct GraphType {
	int n;	// ������ ����
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

// �׷��� �ʱ�ȭ 
void graph_init(GraphType* g) //������������
{
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++)
		for (c = 0; c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = 0;
}

// ���� ���� ����
void insert_edge(GraphType* g, int start, int end) //������������
{
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}
	g->adj_mat[start][end] = 1;
	//g->adj_mat[end][start] = 1;
}
#define MAX_STACK_SIZE 100
typedef int element;
typedef struct {
	element stack[MAX_STACK_SIZE];
	int top;
} StackType;

// ���� �ʱ�ȭ �Լ�
void init(StackType* s) //������������
{
	s->top = -1;
}
// ���� ���� ���� �Լ�
int is_empty(StackType* s) //������������
{
	return (s->top == -1);
}
// ��ȭ ���� ���� �Լ�
int is_full(StackType* s) //������������
{
	return (s->top == (MAX_STACK_SIZE - 1));
}
// �����Լ�
void push(StackType* s, element item) //������������
{
	if (is_full(s)) {
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	else s->stack[++(s->top)] = item;
}
// �����Լ�
element pop(StackType* s) //������������
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->stack[(s->top)--];
}

// ���������� �����Ѵ�.
void topo_sort(GraphType* g) // �ڵ� �ۼ�
{
	int i, j, k;
	StackType s;

	int *degree = (int*)malloc(sizeof(int) * g->n);
	int* in = (int*)malloc(sizeof(int) * g->n);
	for (i = 0; i < g->n; i++) {
		degree[i] = 0;
		in[i] = 0;
	}

	for (i = 0; i < g->n; i++) {
		for (j = 0; j < g->n; j++) {
			if (g->adj_mat[i][j] == 1)
				degree[j]++;
		}
	}

	init(&s);
	for (i = 0; i < g->n; i++) {
		if (degree[i] == 0) {
			in[i] = 1;
			push(&s, i);
		}
	}

	while (!is_empty(&s)) {
		int w;
		w = pop(&s);
		printf("%d->", w);

		for (k = 0; k < g->n; k++) {
			if (g->adj_mat[w][k] == 1)
				degree[k]--;

			if (degree[k] == 0 && in[k] == 0) {
				in[k] = 1;
				push(&s, k);
			}
		}
	}
	free(degree);
}

int main(void) //������������
{
	GraphType g;
	int u, v;
	graph_init(&g);

	scanf("%d", &g.n);
	scanf("%d %d", &u, &v);
	while (u != -1) {
		insert_edge(&g, u, v);
		scanf("%d %d", &u, &v);
	}
	topo_sort(&g);
	printf("���ĳ�\n");
}