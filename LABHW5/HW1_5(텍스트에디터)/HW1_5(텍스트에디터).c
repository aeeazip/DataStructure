#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h>
#define MAX_CHAR_PER_LINE 100 

// 1)
typedef struct { 
	char line[MAX_CHAR_PER_LINE];
} element;

typedef struct ListNode {
	element data;
	struct ListNode* link;
} ListNode;

void display_te(ListNode* head) // text editor �� ���� ���� // 2)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	int i = 1;

	printf("----------text edited----------\n");
	for (p = head; p != NULL; p = p->link) 
		printf("(%d) %s", i++, p->data.line);
}

void display_te_pos(ListNode* head, int pos) // text editor �� ���� ���� // 2)
{
	ListNode* p = head;
	int i = 0;

	if (pos<0 || pos>=get_length(head)) // pos���� ����
		printf("����� �� �����ϴ�.\n");
	else {
		while (i!=pos) {
			i++;
			p = p->link;
		}
		printf("(%d) %s", pos + 1, p->data.line);
	}
}

int get_length(ListNode* head) {
	ListNode* p = head;

	int size = 0;
	while (p != NULL) {
		size++;
		p = p->link;
	}
	return size;
}

ListNode* insert_first(ListNode* head, element new) {
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = new;

	p->link = head;
	head = p;
	return head;
}

ListNode* insert_last(ListNode *head, element new)
{
	ListNode* temp = head;
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = new;
	p->link = NULL;

	if (head == NULL)
		head = p;
	else {
		while (temp->link != NULL)
			temp = temp->link;
		temp->link = p;
	}
	return head;
}

ListNode* insert_pos(ListNode* head, element new, int pos) {
	ListNode* temp = head;
	ListNode* pre = NULL;
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = new;

	if (pos<0 || pos>get_length(head)) {
		printf("pos ���� ����\n");
		return NULL;
	}
	if (pos == 0)
		head = insert_first(head, new);
	else if (pos == get_length(head)) // ������� �ʰ� pos=����
		head = insert_last(head, new);
	else { // ������� �ʰ� pos=�߰�
		int i = 0;
		while (i != pos) {
			i++;
			pre = temp;
			temp = temp->link;
		}
		p->link = temp;
		pre->link = p;
	}
	return head;
}

ListNode* delete_first(ListNode* head) {
	ListNode* removed = head;

	if (head == NULL)
		printf("������ �׸��� �����ϴ�.\n");
	else {
		head = removed->link;
		free(removed);
		return head;
	}
}

ListNode* delete_last(ListNode* head) {
	ListNode* temp = head;
	ListNode* prevTemp = NULL;

	if (head == NULL) // ��尡 ����ִ� ���
		printf("������ �׸��� �����ϴ�.\n");

	if (head->link == NULL) { // ��尡 �ϳ��� ���
		free(head);
		head = NULL;
	}
	else { // ��尡 2�� �̻��� ���
		while (temp->link != NULL) {
			prevTemp = temp;
			temp = temp->link;
		}
		prevTemp->link = NULL;
		free(temp);
	}
	return head;
}


ListNode* delete_pos(ListNode* head, int pos) {
	ListNode* p = head;
	ListNode* pre = NULL;
	int i = 0;

	if (pos < 0 || pos >= get_length(head) || head == NULL)
		printf("������ �� �����ϴ�\n");

	if (pos == 0)
		head = delete_first(head);
	else {
		while (i != pos) {
			i++;
			pre = p;
			p = p->link;
		}

		if (pos == get_length(head) - 1)  // ��尡 �� �̻��̸鼭 pos=����-1
			head = delete_last(head);
		else {  // ��尡 �� �̻��̸鼭 pos=�߰�
			pre->link = p->link;
			free(p);
		}
	}
	return head;
}

// ������ �Լ��� ���Ǹ� �״�� ���⿡ 
char askChoice(void) {
	char choice;
	printf("------------------------------\n"); 
	printf("a: �ؽ�Ʈ ���� ���� �߰�\n"); 
	printf("i: ���� ��ȣ�� ���� �߰�\n"); 
	printf("d: ���� ��ȣ�� ���� ����\n"); 
	printf("v: ���� ��ȣ�� �ش� ���� ���\n"); 
	printf("p: ��ü �ؽ�Ʈ ���\n"); 
	printf("q: ��\n");
	printf("�޴� ����:"); 
	scanf("%c", &choice);
	return choice;
}

int main(void) // 3) 
{
	ListNode* list = NULL;
	char choice;
	int lineNb;
	element newElement;

	while ((choice = askChoice()) != 'q') {
		switch (choice) {
		case 'a':
			printf("�ؽ�Ʈ ���� ������ ����: ");
			while (getchar() != '\n');
			fgets(newElement.line, MAX_CHAR_PER_LINE, stdin);
			list = insert_last(list, newElement);
			display_te(list);
			break;
		case 'i':
			printf("������ ���� ��ȣ: ");
			scanf("%d", &lineNb);
			printf("������ ����: ");
			while (getchar() != '\n');
			fgets(newElement.line, MAX_CHAR_PER_LINE, stdin);
			list = insert_pos(list, newElement, lineNb - 1);
			display_te(list);
			break;
		case 'd':
			printf("������ ���� ��ȣ: ");
			scanf("%d", &lineNb);
			while (getchar() != '\n');
			list = delete_pos(list, lineNb - 1);
			display_te(list);
			break;
		case 'v':
			printf("����� ���� ��ȣ: ");
			scanf("%d", &lineNb);
			while (getchar() != '\n');
			display_te_pos(list, lineNb - 1);
			break;
		case 'p':
			while (getchar() != '\n');
			display_te(list);
		}
		fflush(stdin);
	}
}