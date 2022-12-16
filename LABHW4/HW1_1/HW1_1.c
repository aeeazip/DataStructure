#include <stdio.h>
#include <stdlib.h>
#define MAX_LIST_SIZE 5
typedef int element;
typedef struct {
	element array[MAX_LIST_SIZE];
	int size;
}ArrayListType;

void init(ArrayListType* L) {
	L->size = 0;
}

int is_empty(ArrayListType* L) {
	return (L->size == 0);
}

int is_full(ArrayListType* L) {
	return (L->size == MAX_LIST_SIZE);
}

void insert(ArrayListType *L, int pos, element item) {
	if (!is_full(L) && pos >= 0 && pos <= L->size) {
		for (int i = L->size - 1; i >= pos; i--)
			L->array[i + 1] = L->array[i];
		L->array[pos] = item;
		L->size++;
		return;
	}
	if (is_full(L))
		printf("����Ʈ�� �����÷ο�\n");
}

void print_list(ArrayListType* L) {
	for (int i = 0; i < L->size; i++)
		printf("%d->", L->array[i]);
	printf("����Ʈ��\n");
}

void clear(ArrayListType* L) {
	for (int i = 0; i < L->size; i++)
		L->array[i] = "\0";
	init(L);
}

void insert_last(ArrayListType* L, element item) {
	if (L->size < MAX_LIST_SIZE) {
		L->array[(L->size)++] = item;
		return;
	}
	if (is_full(L))
		printf("����Ʈ�� �����÷ο�\n");
}

void delete(ArrayListType* L, int pos) {
	if (!is_empty(L) && pos >= 0 && pos < L->size) {
		for (int i = pos + 1; i < L->size; i++)
			L->array[i-1] = L->array[i];
		L->size--;
	}
}

void insert_first(ArrayListType* L, element item) {
	if (!is_full(L) && L->size < MAX_LIST_SIZE) {
		for (int i = L->size - 1; i >= 0; i--)
			L->array[i + 1] = L->array[i];
		L->array[0] = item;
		L->size++;
		return;
	}
	if (is_full(L))
		printf("����Ʈ�� �����÷ο�\n");
}

int get_length(ArrayListType* L) {
	return L->size;
}

element get_entry(ArrayListType* L, int pos) {
	if (pos >= 0 && pos < L->size)
		return L->array[pos];
	else
		printf("��ġ����\n");
}

void replace(ArrayListType* L, int pos, element item) {
	if (pos >= 0 && pos < L->size) 
		L->array[pos] = item;
} 

int is_in_list(ArrayListType* L, element item) {
	for (int i = 0; i < L->size; i++) {
		if (L->array[i] == item)
			return 1;
	}
	return 0;
}

void delete_by_key(ArrayListType* L, element key) {
	int i, j;
	
	for (i = 0; i < L->size; i++) {
		if (L->array[i] == key) {
			for (j = i + 1; i < L->size; i++)
				L->array[j - 1] = L->array[j];
			return;
		}
	}
	printf("�����Ϸ��� key�� %d�� ����Ʈ�� �����ϴ�\n", key);
}

int main(void)
{
	ArrayListType list1;
	init(&list1);
	insert(&list1, 0, 20);
	insert(&list1, 0, 10); print_list(&list1);
	clear(&list1); print_list(&list1);
	insert_last(&list1, 90); print_list(&list1);
	insert(&list1, 0, 30);
	insert(&list1, 0, 20);
	insert(&list1, 0, 10); print_list(&list1);
	delete(&list1, 2); print_list(&list1);
	printf("\n-�� ���Ĵ� HW1_1���� �߰��� �Լ��� �׽�Ʈ-\n");
	insert_first(&list1, 9); print_list(&list1);
	insert_last(&list1, 99); print_list(&list1); // �߿���˿����˿� ���� �߻�~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// ���� ����Ʈ�� �� ��(ũ�� 5��) �����̹Ƿ� �� �׸��� �� �߰��ϸ� "����Ʈ �����÷ο�"�� ����Ѵ�.
	insert_first(&list1, 1); print_list(&list1);
	printf("���̴� %d\n", get_length(&list1));
	printf("3��° ����Ÿ�� %d\n", get_entry(&list1, 2));
	replace(&list1, 3, 40); print_list(&list1);
	printf("20�� ����Ʈ�� %s\n", is_in_list(&list1, 20) ? "�ֽ��ϴ�" : "�����ϴ�");
	printf("22�� ����Ʈ�� %s\n", is_in_list(&list1, 22) ? "�ֽ��ϴ�" : "�����ϴ�");
	delete_by_key(&list1, 20); print_list(&list1);
	delete_by_key(&list1, 22); print_list(&list1);
}