#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_VERTICES 50

typedef struct GraphType {
    int n;
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int visited[MAX_VERTICES] = { 0 };

// �׷��� �ʱ�ȭ 
void graph_init(GraphType* g)
{
    int r, c;
    g->n = 0;
    for (r = 0; r < MAX_VERTICES; r++)
        for (c = 0; c < MAX_VERTICES; c++)
            g->adj_mat[r][c] = 0;
}

void insert_vertex(GraphType* g, int v) { // ���� ����
    if (g->n + 1 > MAX_VERTICES) {
        fprintf(stderr, "�׷��� : ������ ���� �ʰ�");
        return 0;
    }
    g->n++;
}

void insert_edge(GraphType* g, int start, int end) { // ���� ����
    if (start < 0 || start >= g->n || end < 0 || end >= g->n) {
        fprintf(stderr, "�׷��� : ���� ��ȣ ����");
        return 0;
    }
    g->adj_mat[start][end] = 1;
    g->adj_mat[end][start] = 1;
}

void read_graph(GraphType* g, char* filename)
{
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

// �� �Լ��� ������ ����ϱ����� �ڵ带 �����ϴ� ���� HW6_2_1�� �䱸�̴�
void dfs_mat(GraphType* g, int v)
{
    int w;
    visited[v] = 1;

    for (w = 0; w < g->n; w++) {
        if ((g->adj_mat[v][w] == 1) && (visited[w] == 0)) { // u�� ������ �����̰� u�� ���� �湮���� �ʾ�����
            printf("(%d %d)\n", v, w);
            dfs_mat(g, w);
        }
    }
}

int main(void)
{
    GraphType graph;
    int u, v;

    graph_init(&graph);
    read_graph(&graph, "infile.txt");
    //read_graph(&graph, "infile2.txt");

    printf("Enter ����:");
    scanf("%d", &v);

    dfs_mat(&graph, v);
}

