#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct DlistNode {
	element data;
	struct DlistNode* llink;
	struct DlistNode* rlink;
} DlistNode;

void init(DlistNode* phead) // 변경하지 말라
{
	phead->llink = phead;
	phead->rlink = phead;
}

void display(DlistNode* phead) // 변경하지 말라
{
	DlistNode* p;
	for (p = phead->rlink; p != phead; p = p->rlink) {
		printf("%d->", p->data);
	}
	printf("NULL\n");
}
// 노드 new_node를 노드 before의 오른쪽에 삽입한다.
void dinsert_node(DlistNode* before, element data) // 변경하지 말라
{
	DlistNode* new_node;
	new_node = (DlistNode*)malloc(sizeof(DlistNode));
	new_node->data = data;

	new_node->llink = before;
	new_node->rlink = before->rlink;
	before->rlink->llink = new_node;
	before->rlink = new_node;
}

void ddelete(DlistNode* phead, DlistNode* removed) // 변경하지 말라
{
	if (removed == phead) return;
	removed->llink->rlink = removed->rlink;
	removed->rlink->llink = removed->llink;
	free(removed);
}
void delete_by_key(DlistNode* phead, int key)
{
	DlistNode* temp=phead->rlink;

	do {
		if (key == temp->data) {
			temp->rlink->llink = temp->llink;
			temp->llink->rlink = temp->rlink;
		}
		temp = temp->rlink;
	} while (temp != phead);
}

int main(void) // 변경하지 말라
{
	DlistNode head_node;
	int n, key;
	init(&head_node);
	scanf("%d", &n);
	while (n != -1) {
		dinsert_node(head_node.llink, n);
		scanf("%d", &n);
	}
	scanf("%d", &key);
	//display(&head_node);
	delete_by_key(&head_node, key);
	display(&head_node);
}