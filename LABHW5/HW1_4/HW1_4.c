#include <stdio.h>
#include <stdlib.h>
typedef int element;
typedef struct ListNode { // ��� Ÿ��
	element data;
	struct ListNode* link;
} ListNode;

void print_list(ListNode* head) // Ʋ��(�����ؾ�)
{
	ListNode* p;
	if (head == NULL) return;
	if (head->link == head) {
		printf("%d->����Ʈ�� ��\n", head->data);
		return;
	}

	p = head->link;
	do {
		printf("%d->", p->data);
		p = p->link;
	} while (p != head);
	printf("%d->����Ʈ�� ��", p->data); // ������ ��� ���
	printf("\n");
}

ListNode* insert_first(ListNode* head, element data)
{
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	node->data = data;
	if (head == NULL) {
		head = node;
		node->link = head;
	}
	else {
		node->link = head->link; // (1) 
		head->link = node; // (2) 
	}
	return head; // ����� ��� �����͸� ��ȯ�Ѵ�. 
} 

ListNode* insert_last(ListNode* head, element data)
{
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	node->data = data;

	if (head == NULL) {
		head = node;
		node->link = head;
	}
	else {
		node->link = head->link;
		head->link = node;
		head = node;
	}
	return head; // ����� ��� �����͸� ��ȯ�Ѵ�
}

ListNode* delete_first(ListNode* head)
{
	ListNode* temp;
	if (head == NULL) {
		printf("����Ʈ�� ��� ������ ����\n");
		return NULL;
	}
	else if (head->link == head) {
		free(head);
		head = NULL;
	}
	else {
		temp = head->link;
		head->link = temp->link;
		return head;
	}
}

ListNode* delete_last(ListNode* head)
{
	ListNode* temp = head->link;
	if (head == NULL) {
		printf("����Ʈ�� ��� ������ ����\n");
		return NULL;
	}
	else if (head->link == head) {
		free(head);
		head = NULL;
	}
	else {
		while (temp->link != head)
			temp = temp->link;
		temp->link = head->link;
		head = temp;
	}
	return head;
}

ListNode* search(ListNode* head, element data)
{
	ListNode* temp = head;

	do {
		if (temp->data == data)
			return temp;
		temp = temp->link;
	} while (temp != head);
	return NULL;
}

int get_size(ListNode* head)
{
	ListNode* temp = head->link;
	int size = 0;

	if (head == NULL)
		return 0;

	while (temp != head) {
		size++;
		temp = temp->link;
	}
	return size + 1;
}


// ���� ���� ����Ʈ �׽�Ʈ ���α׷�
int main(void)
{
	ListNode* head = NULL;
	// list = 10->20->30->40
	head = insert_last(head, 20); 
	print_list(head); //20->

	head = insert_last(head, 30);
	print_list(head); //20-> 30

	head = insert_last(head, 40);
	print_list(head);//20-> 30-> 40

	head = insert_first(head, 10);
	print_list(head); //10-> 20-> 30-> 40

	head = delete_first(head);
	print_list(head);//20-> 30-> 40

	head = delete_last(head);
	print_list(head);//20-> 30

	printf("����Ʈ�� ���̴� %d\n", get_size(head));

	ListNode* s = (ListNode*)malloc(sizeof(ListNode));
	s = search(head, 30);

	if (s == NULL)
		printf("Ž������ �������� �ʽ��ϴ�\n");
	else
		printf("Ž������ %d\n", s->data);
	return 0;
}
