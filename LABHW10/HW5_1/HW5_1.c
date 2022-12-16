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

void insert_max_heap(HeapType *h, element item) {
	int i;
	i = ++(h->heap_size);

	while ((i != 1) && (item.key > h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}

void preorder(HeapType* h, int root) {
	if (root <= h->heap_size) {
		printf("%d ", h->heap[root]);
		preorder(h, root * 2);
		preorder(h, root * 2 + 1);
	}
}

int is_power_of_two(int num)
{
	return num && !((num - 1) & num);
}

void print_heap(HeapType* h) {
	for (int i = 1; i <= h->heap_size; i++) {
		if (is_power_of_two(i))
			printf("\n");
		printf("%d ", h->heap[i]);
	}
	printf("\n");
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

int find(HeapType* h, int root, int key) {
	for (int i = 1; i <= h->heap_size; i++) {
		if (key == h->heap[i].key)
			return i;
	}
	return 0;
}

void print_sorted_value(HeapType h) { //�������� ����
	element* arr = (element*)malloc(sizeof(element) * h.heap_size);
	int n = h.heap_size;
	
	for (int i = 0; i < n; i++) {
		arr[i] = delete_max_heap(&h);
		printf("%d ", arr[i].key);
	}
	printf("\n");
}

void modify_priority(HeapType* h, int oldKey, int newKey) { //oldKey�� newKey�� ���� -> heap ������ ���� �ʵ��� �ؾ���
	int index = find(h, 1, oldKey);

	if (index == 0) {
		printf("key���� �������� �ʽ��ϴ�.\n");
		return;
	}
	else {
		h->heap[index].key = newKey;

		if (newKey<h->heap[index / 2].key && newKey>h->heap[index * 2].key && newKey > h->heap[index * 2 + 1].key)
			return;		
		if (newKey > h->heap[index / 2].key) {
			while ((index != 1) && newKey > h->heap[index / 2].key) {
				h->heap[index] = h->heap[index / 2];
				h->heap[index / 2].key = newKey;
				index /= 2;
			}
		}
		if (newKey < h->heap[index * 2].key || newKey < h->heap[index * 2 + 1].key) {
			int parent = index / 2, child = index * 2;

			while (child <= h->heap_size) {
				if((child<h->heap_size) && (h->heap[child].key < h->heap[child+1].key))
					child++;
				if (newKey > h->heap[child].key)
					break;
				h->heap[parent] = h->heap[child];
				h->heap[child].key = newKey;
				parent = child;
				child *= 2;
			}
		}
	}
}

int main(void)
{
	element e1 = { 10 }, e2 = { 5 }, e3 = { 30 }, eA = { 9 }, eB = { 19 }, eC = { 39 };
	element e4, e5, e6;
	int index;
	int key, oldKey, newKey;
	HeapType heap; // ���� ����
	init(&heap); // �ʱ�ȭ
	printf("Step1: ���Ե� 10, 5, 30 �� �߰������� 9, 19, 39 �� <����> �Ѵ�");
	insert_max_heap(&heap, e1);
	insert_max_heap(&heap, e2);
	insert_max_heap(&heap, e3);
	insert_max_heap(&heap, eA);
	insert_max_heap(&heap, eB);
	insert_max_heap(&heap, eC);

	printf("\nStep2: preorder, print_heap �Լ� �׽�Ʈ\n");
	preorder(&heap, 1);
	printf("\n\n");
	print_heap(&heap);
	e4 = delete_max_heap(&heap);
	printf("\n%d ����: ��Ʈ�� ������\n", e4.key);
	print_heap(&heap);

	printf("\nStep3: find �Լ� �׽�Ʈ\n");
	printf("ã�� key �Է�(-1 for exit):");
	scanf("%d", &key);
	while (key != -1) {
		if ((index = find(&heap, 1, key)) == 0)
			printf("%d �� ����\n", key);
		else
			printf("%d �� [%d]�� ����\n", key, index);
		printf("ã�� key �Է�(-1 for exit):");
		scanf("%d", &key);
	}

	printf("\nStep4: print_sorted_value �Լ� �׽�Ʈ\n");
	print_sorted_value(heap);

	printf("\nStep5: modify_priority �Լ� �׽�Ʈ\n");
	printf("�ٲ� key �Է�(-1 for exit):");
	scanf("%d", &oldKey);
	while (oldKey != -1) {
		printf("�� key �Է�:");
		scanf("%d", &newKey);
		modify_priority(&heap, oldKey, newKey);
		print_heap(&heap);
		printf("�ٲ� key �Է�(-1 for exit):");
		scanf("%d", &oldKey);
	}
}