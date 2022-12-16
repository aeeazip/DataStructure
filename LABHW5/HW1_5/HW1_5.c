#include <stdio.h>
#include <stdlib.h>
typedef int element;
typedef struct DListNode { // ���߿��� ��� Ÿ��
	element data;
	struct DListNode* llink;
	struct DListNode* rlink;
} DListNode;

// ���� ���� ����Ʈ�� �ʱ�ȭ
void init(DListNode* phead)
{
	phead->llink = phead;
	phead->rlink = phead;
}

// ���� ���� ����Ʈ�� ��带 ���
void print_dlist(DListNode* phead)
{
	DListNode* p;
	for (p = phead->rlink; p != phead; p = p->rlink) {
		printf("<-| |%d| |-> ", p->data);
	}
	printf("\n");
}

// ���ο� �����͸� ��� before�� �����ʿ� �����Ѵ�. 
void dinsert(DListNode *before, element data) 
{
	DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));
	newnode->data = data;

	newnode->llink = before;
	newnode->rlink = before->rlink;
	before->rlink->llink = newnode;
	before->rlink = newnode;
}

// ��� removed�� �����Ѵ�. 
void ddelete(DListNode* head, DListNode* removed) 
{
	if (removed == head) return;
	else {
		removed->llink->rlink = removed->rlink;
		removed->rlink->llink = removed->llink;
	}
}

// �������� ��ȸ�ϸ鼭 ����� ������ ���� ���
void print_reverse_dlist(DListNode* head) 
{
	DListNode* p = head;
	for (p = p->llink; p != head; p = p->llink) 
		printf("<-| |%d| |-> ", p->data);
	printf("\n");
}

// data �� ���� ��带 ã�Ƽ� ��ȯ�Ѵ�.
DListNode* search(DListNode* head, element data) 
{
	DListNode* p = head;
	for (p = p->rlink; p != head; p = p->rlink) {
		if (p->data == data)
			return p;
	}
	return NULL;
}

// ���� ���� ����Ʈ �׽�Ʈ ���α׷�
int main(void)
{
	DListNode* head = (DListNode*)malloc(sizeof(DListNode));
	init(head);
	printf("�߰� �ܰ�\n");

	// �� �տ� ��带 ����
	dinsert(head, 10);
	print_dlist(head); //10
	dinsert(head, 20);
	print_dlist(head); //20 10
	dinsert(head, 30);
	print_dlist(head); //30 20 10

	// �� �ڿ� ��带 �����Ϸ���?
	dinsert(head->llink, 40);
	print_dlist(head); //30 20 10 40

	// �������� ��ȸ�ϸ鼭 ����� ������ ���� ���
	print_reverse_dlist(head); //40 10 20 30
	
	printf("\n���� �ܰ�\n");
	// �� ���� ��带 ����
	ddelete(head, head->rlink);
	print_dlist(head); //20 10 40

	// �� ���� ��带 �����Ϸ���?
	ddelete(head, head->llink);
	print_dlist(head); //20 10 

	DListNode* s = (DListNode*)malloc(sizeof(DListNode));
	s = search(head, 20);

	if(s == NULL)
		printf("Ž������ �������� �ʽ��ϴ�\n");
	else
		printf("Ž������ %d\n", s->data);

	free(head);
	return 0;
}