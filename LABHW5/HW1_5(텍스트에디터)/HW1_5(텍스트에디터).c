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

void display_te(ListNode* head) // text editor 를 위해 변경 // 2)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	int i = 1;

	printf("----------text edited----------\n");
	for (p = head; p != NULL; p = p->link) 
		printf("(%d) %s", i++, p->data.line);
}

void display_te_pos(ListNode* head, int pos) // text editor 를 위해 변경 // 2)
{
	ListNode* p = head;
	int i = 0;

	if (pos<0 || pos>=get_length(head)) // pos범위 오류
		printf("출력할 수 없습니다.\n");
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
		printf("pos 범위 오류\n");
		return NULL;
	}
	if (pos == 0)
		head = insert_first(head, new);
	else if (pos == get_length(head)) // 비어있지 않고 pos=길이
		head = insert_last(head, new);
	else { // 비어있지 않고 pos=중간
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
		printf("삭제할 항목이 없습니다.\n");
	else {
		head = removed->link;
		free(removed);
		return head;
	}
}

ListNode* delete_last(ListNode* head) {
	ListNode* temp = head;
	ListNode* prevTemp = NULL;

	if (head == NULL) // 노드가 비어있는 경우
		printf("삭제할 항목이 없습니다.\n");

	if (head->link == NULL) { // 노드가 하나인 경우
		free(head);
		head = NULL;
	}
	else { // 노드가 2개 이상인 경우
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
		printf("삭제할 수 없습니다\n");

	if (pos == 0)
		head = delete_first(head);
	else {
		while (i != pos) {
			i++;
			pre = p;
			p = p->link;
		}

		if (pos == get_length(head) - 1)  // 노드가 둘 이상이면서 pos=길이-1
			head = delete_last(head);
		else {  // 노드가 둘 이상이면서 pos=중간
			pre->link = p->link;
			free(p);
		}
	}
	return head;
}

// 나머지 함수들 정의를 그대로 여기에 
char askChoice(void) {
	char choice;
	printf("------------------------------\n"); 
	printf("a: 텍스트 끝에 라인 추가\n"); 
	printf("i: 라인 번호로 라인 추가\n"); 
	printf("d: 라인 번호로 라인 삭제\n"); 
	printf("v: 라인 번호로 해당 라인 출력\n"); 
	printf("p: 전체 텍스트 출력\n"); 
	printf("q: 끝\n");
	printf("메뉴 선택:"); 
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
			printf("텍스트 끝에 삽입할 라인: ");
			while (getchar() != '\n');
			fgets(newElement.line, MAX_CHAR_PER_LINE, stdin);
			list = insert_last(list, newElement);
			display_te(list);
			break;
		case 'i':
			printf("삽입할 라인 번호: ");
			scanf("%d", &lineNb);
			printf("삽입할 라인: ");
			while (getchar() != '\n');
			fgets(newElement.line, MAX_CHAR_PER_LINE, stdin);
			list = insert_pos(list, newElement, lineNb - 1);
			display_te(list);
			break;
		case 'd':
			printf("삭제할 라인 번호: ");
			scanf("%d", &lineNb);
			while (getchar() != '\n');
			list = delete_pos(list, lineNb - 1);
			display_te(list);
			break;
		case 'v':
			printf("출력할 라인 번호: ");
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