/*
-1�� ���ö����� �Ϸ��� ������ �о� *��*�� ���ʷ� �־ ���Ḯ��Ʈ�� �����
key ���� ������ ���� ��
�� key ���� ���Ḯ��Ʈ���� ������ ������ ���Ḯ��Ʈ�� ����ϴ� ���α׷��� �ۼ��϶�.

���࿹ #1
10 20 30 40 50 -1 : �Ϸ��� ���� �Է�
30 : key �Է�
50->40->30->20->10->����Ʈ�� : ���� ���Ḯ��Ʈ ���
50->40->20->10->����Ʈ�� : key 30�� ������ ���� ���Ḯ��Ʈ ���

���࿹ #1
10 20 30 40 50 -1 : �Ϸ��� ���� �Է�
70 : key �Է�
50->40->30->20->10->����Ʈ�� : ���� ���Ḯ��Ʈ ���
50->40->30->20->10->����Ʈ�� : key 70�� ������ ��(�����Ƿ� ������ �Ͼ�� ����)�� ���Ḯ��Ʈ ���
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_LIST_SIZE 10 	// ����Ʈ�� �ִ�ũ��

typedef int element;			// �׸��� ����
typedef struct {
	element array[MAX_LIST_SIZE];	  // �迭 ����
	int size;		  // ���� ����Ʈ�� ����� �׸���� ����
} ArrayListType;

// ���� ó�� �Լ�
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// ����Ʈ �ʱ�ȭ �Լ�
void init(ArrayListType* L)
{
	L->size = 0;
}

// ����Ʈ�� ��� ������ 1�� ��ȯ
// �׷��� ������ 0�� ��ȯ
int is_empty(ArrayListType* L)
{
	return L->size == 0;
}

// ����Ʈ�� ���� �� ������ 1�� ��ȯ
// �׷��� ������ 1�� ��ȯ
int is_full(ArrayListType* L)
{
	return L->size == MAX_LIST_SIZE;
}

element get_entry(ArrayListType* L, int pos)
{
	if (pos < 0 || pos >= L->size)
		error("��ġ ����");
	return L->array[pos];
}

// ����Ʈ ���
void print_list(ArrayListType* L)
{
	int i;
	for (i = 0; i < L->size; i++)
		printf("%d->", L->array[i]);
	printf("����Ʈ��\n");
}


//------------------------------------------------
void clear(ArrayListType* L)
{
	L->size = 0;
}

void insert_first(ArrayListType* L, element item)
{
	int i;
	if (is_full(L))
		printf("����Ʈ �����÷ο�\n");
	else {
		for (i = L->size - 1; i >= 0; i--)
			L->array[i + 1] = L->array[i];
		L->array[0] = item;
		L->size++;
	}
}

// �ڵ� �ۼ� �κ�
void delete_by_key(ArrayListType* L, element key)
{
	int i, key_index = -1;

	for (i = 0; i < L->size; i++) {
		if (key == L->array[i]) {
			key_index = i;
			break;
		}
	}

	if (key_index != -1) {
		for (i = key_index + 1; i < L->size; i++) 
			L->array[i - 1] = L->array[i];
		L->size--;
	}
}


int main(void)
{
	ArrayListType list1;
	int n, key;

	init(&list1);
	scanf("%d", &n);
	while (n != -1) {
		insert_first(&list1, n);
		scanf("%d", &n);
	}
	scanf("%d", &key);
	print_list(&list1);
	delete_by_key(&list1, key);
	print_list(&list1);
}