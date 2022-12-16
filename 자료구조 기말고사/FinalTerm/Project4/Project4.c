#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200
#define TRUE 1
#define FALSE 0

typedef struct {
	int key;
} element;

typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;

// 초기화 함수
void init(HeapType* h) // 변경하지 말라
{
	h->heap_size = 0;
}

// 현재 요소의 개수가 heap_size인 히프 h에 item을 삽입한다.
// 삽입 함수
void insert_max_heap(HeapType* h, element item) // 변경하지 말라
{
	int i;
	i = ++(h->heap_size);

	//  트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
	while ((i != 1) && (item.key > h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;     // 새로운 노드를 삽입
}

// 삭제 함수
element delete_max_heap(HeapType* h) // 변경하지 말라
{
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// 현재 노드의 자식노드중 더 작은 자식노드를 찾는다.
		if ((child < h->heap_size) &&
			(h->heap[child].key) < h->heap[child + 1].key)
			child++;
		if (temp.key >= h->heap[child].key) break;
		// 한단계 아래로 이동
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

int calcMax(int a, int b) // 변경하지 말라
{
	if (a >= b)
		return a;
	else
		return b;
}
// find
int find(HeapType* h, int root, int key) // 변경하지 말라
{
	if (h->heap_size < root)
		return 0;
	if (h->heap[root].key == key)
		return root;
	else if (h->heap[root].key < key)
		return 0;
	else
		return calcMax(find(h, root * 2, key), find(h, root * 2 + 1, key));
}

void delete_heap_by_key(HeapType* h, int oldkey) // 코드 작성
{
	int i;

	for (i = 0; i < h->heap_size; i++) {
		if (h->heap[i].key == oldkey) {
			int parent, child;
			element item, temp;
			
			item = h->heap[i];
			temp = h->heap[ ] // 서브트리에서 마지막 노드의 인덱스
			parent = i;
			child = i * 2;

			while (child <= h->heap_size) {
				if ((child < h->heap_size) && (h->heap[child].key < h->heap[child + 1].key))
					child++;

				if(te)

			}
		}
	}
}
void print_heap(HeapType* h) // 변경하지 말라
{
	int s, i;

	for (s = 1; s <= h->heap_size; s *= 2) {	// s = 1, 2, 4, 8, ...
		for (i = s; i < s * 2 && i <= h->heap_size; i++) 	// e.g., when s = 4, i = 4, 5, 6, 7
			printf("%d ", h->heap[i]);
		printf("\n");
	}
}

int main(void) // 변경하지 말라
{
	element ele;
	int index;
	int key;
	HeapType heap;	// 히프 생성

	init(&heap);		// 초기화
	scanf("%d", &key);
	while (key != -1) {
		ele.key = key;
		insert_max_heap(&heap, ele);
		scanf("%d", &key);
	}
	print_heap(&heap);

	scanf("%d", &key);
	delete_heap_by_key(&heap, key);
	print_heap(&heap);
}