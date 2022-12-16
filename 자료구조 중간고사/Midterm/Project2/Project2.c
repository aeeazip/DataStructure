#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
typedef int element;
typedef struct ListNode {
	element data;
	struct ListNode* link;
} ListNode;

void display(ListNode* head) //변경하지 말라
{
	ListNode* p = head;
	while (p != NULL) {
		printf("%d->", p->data);
		p = p->link;
	}
	printf("NULL\n");
}

ListNode* insert_last(ListNode* head, int value) // 변경하지 말라
{

	ListNode* temp = head;
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = NULL;

	if (head == NULL) // 공백 리스트이면
		head = p;
	else {
		while (temp->link != 0)
			temp = temp->link;

		temp->link = p;
	}
	return head;
}

ListNode* insert_sorted(ListNode* head, int value)
{
	ListNode* temp, * pre = NULL;
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = NULL;

	if (head == NULL) head = p;
	else if (p->data <= head->data) {
		p->link = head;
		head = p;
	}
	else {
		for (temp = head; temp != NULL; temp = temp->link) {
			if (p->data <= temp->data)
				break;
			pre = temp;
		}

		p->link = temp;
		pre->link = p;
	}

	return head;
}

int main(void) // 변경하지 말라
{
	ListNode* list = NULL;
	int n, key;

	scanf("%d", &n);
	while (n != -1) {
		list = insert_last(list, n);
		scanf("%d", &n);
	}
	scanf("%d", &key);
	list = insert_sorted(list, key);
	display(list);
}