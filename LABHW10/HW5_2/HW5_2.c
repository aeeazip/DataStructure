#define _CRT_SECURE_NO_WARNINGS
#define MAX_ELEMENT 200
#include <stdio.h>
#include <stdlib.h>
typedef struct {
	int key;
}element;

typedef struct HeapType {
	element heap[MAX_ELEMENT];
	int heap_size;
}HeapType;

void init(HeapType* h) {
	h->heap_size = 0;
}

void insert_max_heap(HeapType* h, element item) { //파일에서 읽어서 max Heap 에 저장한다.
	int i;
	i = ++(h->heap_size);

	while ((i != 1) && (item.key > h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}

element delete_max_heap(HeapType* h) {
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;

	while (child <= h->heap_size) {
		if ((child < h->heap_size) && h->heap[child].key < h->heap[child + 1].key)
			child++;
		if (temp.key >= h->heap[child].key)
			break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

void read_heap(HeapType* h, char* filename) {
	int num;
	element temp;

	FILE* fp;
	if ((fp = fopen(filename, "r")) == NULL) {
		fprintf(stderr, "파일을 열 수 없습니다.\n");
		exit(1);
	}

	while (!feof(fp)) {
		fscanf(fp, "%d", &num);
		temp.key = num;
		insert_max_heap(h, temp);
	}

	fclose(fp);
}

void write_heap_array(HeapType* h, char* filename) { //max Heap 에 저장된 내용을 배열적 표현 그대로 파일에 출력한다.
	FILE* fp;
	if ((fp = fopen(filename, "w")) == NULL) {
		fprintf(stderr, "파일을 열 수 없습니다.\n");
		exit(1);
	}

	for (int i = 1; i <= h->heap_size; i++) {
		fprintf(fp, "%d\n", h->heap[i]);
	}
	fclose(fp);
}


void write_descending_order(HeapType* h, char* filename) { // max Heap 에 저장된 내용을 내림차순으로 파일에 출력한다.
	FILE* fp;
	if ((fp = fopen(filename, "w")) == NULL) {
		fprintf(stderr, "파일을 열 수 없습니다.\n");
		exit(1);
	}
	
	element temp;
	int n = h->heap_size;
	for (int i = 0; i < n; i++) {
		temp = delete_max_heap(h);
		fprintf(fp, "%d\n", temp.key);
	}
	fclose(fp);
}


int main(void)
{
	HeapType heap;
	element e1 = { 20 }, e2 = { 40 };
	init(&heap);
	read_heap(&heap, "input.txt");
	insert_max_heap(&heap, e1);
	insert_max_heap(&heap, e2);
	write_heap_array(&heap, "heapArray.txt");
	write_descending_order(&heap, "sorted.txt");
}