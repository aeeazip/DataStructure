#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode {
	element data;
	struct ListNode* link;
} ListNode;

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

int keyCount(ListNode* head, element key)
{
	ListNode* temp;
	int count = 0;

	for (temp = head; temp != NULL; temp = temp->link) {
		if (temp->data == key)
			count++;
	}
	return count;
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
	printf("%d\n", keyCount(list, key));
}