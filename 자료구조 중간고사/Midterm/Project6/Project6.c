#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
} TreeNode;

typedef struct { // �̷��� �����ϳ� �л����� �ٸ��� �ص� ������
	TreeNode* NodePt;
	int rightPrint; // ������ �ڽ� ��������� 1, �ƴϸ� 0 
} element;

typedef struct StackNode {
	element data;
	struct StackNode* link;
} StackNode;

typedef struct {
	StackNode* top;
} LinkedStackType;

void init(LinkedStackType* s) // �������� ����.
{
	s->top = NULL;
}

int is_empty(LinkedStackType* s) // �������� ����.
{
	return (s->top == NULL);
}

// ��ȭ ���� ���� �Լ�
int is_full(LinkedStackType* s) // �������� ����.
{
	return 0;
}
// ���� �Լ�
void push(LinkedStackType* s, element item) // �������� ����.
{
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	temp->data = item;
	temp->link = s->top;
	s->top = temp;
}
// ���� �Լ�
element pop(LinkedStackType* s) // �������� ����.
{
	if (is_empty(s)) {
		fprintf(stderr, "������ �������\n");
		exit(1);
	}
	else {
		StackNode* temp = s->top;
		element data = temp->data;
		s->top = s->top->link;
		free(temp);
		return data;
	}
}
element peek(LinkedStackType* s) // �������� ����.
{
	if (is_empty(s)) {
		fprintf(stderr, "������ �������\n");
		exit(1);
	}
	else {
		return s->top->data;
	}
}

void postorder_iter(LinkedStackType* s, TreeNode* root)
{
	element item;
	while (1)

	{
		while (NULL != root)

		{
			item.NodePt = root;
			item.rightPrint = 0;

			//���� ��带 2�� �Է�
			push(s, item);
			push(s, item);

			//���� ���� �̵�
			root = root->left;
		}

		if (!is_empty(s))
		{
			root = pop(s).NodePt;

			//���� ����� ù��° �湮�϶�, ���������� �̵�
			if (!is_empty(s) && root == peek(s).NodePt)
				root = root->right;
			//���� ��带 �ι�° �湮 ������ ����Ѵ�.
			else

			{
				printf("%d ", root->data);
				root = NULL;
			}
		}
		else
			break;
	}
}

TreeNode* insert_node(TreeNode* root, int data)  // �������� ����. 
												 // ���� ����� �ʾ����� � ��Ģ���� Ʈ���� ��带 �����Ѵ�.
{
	TreeNode* p, * t; // p�� �θ���, t�� ������ 
	TreeNode* n;	    // n�� ���ο� ���

	t = root;
	p = NULL;

	// Ž���� ���� ����, �ݺ��� �̿��ؼ� search(���� search�Լ� ����)
	while (t != NULL) { // �����尡 NULL�� �ɶ�����
		 // if( data == t->data ) return root;
		p = t; // �����带 �θ���� �ϰ�
			// �����带 ����
		if (data < t->data)
			t = t->left;
		else
			t = t->right;
	}
	// data�� Ʈ�� �ȿ� �����Ƿ� ���� ����
	n = (TreeNode*)malloc(sizeof(TreeNode));
	//if (n == NULL) return;
	// ������ ����
	n->data = data;
	n->left = n->right = NULL;

	// �θ� ���� ��ũ ����
	if (p != NULL)
		if (data < p->data)
			p->left = n;
		else
			p->right = n;
	else // ���ʿ� Ʈ���� ����־�����
		root = n;
	return root;
}

int main(void)
{
	LinkedStackType s;
	int n;
	TreeNode* root;
	init(&s);

	// (B) ������ ���� Ʈ��
//          15
//	   4		 20
//    1	      16  25
	TreeNode n1 = { 1,  NULL, NULL };
	TreeNode n2 = { 4,  &n1,  NULL };
	TreeNode n3 = { 16, NULL, NULL };
	TreeNode n4 = { 25, NULL, NULL };
	TreeNode n5 = { 20, &n3,  &n4 };
	TreeNode n6 = { 15, &n2,  &n5 };
	root = &n6;
	// (���ν��� ����� ���� ����)
	// (A)�κ����� ǥ�õ� �Ʒ��� 6���� ���ν��� �ø��� �ּ�ó���� �������ּ���.Ʈ���� ����� ���� �κ��Դϴ�.
	/*(A)
	root = NULL;
	scanf("%d", &n);
	while (n != -1) {
		root = insert_node(root, n);
		scanf("%d", &n);
	} */

	//printf("���� ��ȸ=");
	postorder_iter(&s, root); printf("\n");
	return 0;
}

/*
Q. ������ȸ �ݺ������� �ۼ��ϱ�

����: (Ʈ��)�ݺ���������ȸ(���̵� ��)

�̹����� ������ȸ�� �ݺ����� ������� �����ϴ� �����̴�

��Ͱ� �ƴ� �ݺ���������� ������ȸ�� �����ϴ�
postorder_iter �Լ��� �ۼ��϶�.

���ǻ��� �� ��Ʈ

�ݺ���������ȸ �����ϴ� ������ �������� �ٷ���� �ݺ���������ȸ�� ���� �����ϸ� �Ǿ���. �׷��� �� �ݺ���������ȸ�� ���� �� ������ �ؾ��Ѵ�.
��͸� ����Ͽ� �ݺ������� �Լ��� �������� ������ 0�� ó����
���࿹ 1(�־��� main�Լ����� (A)�κ��� �ּ�ó�������� (B)�κп��� �־��� �ʱ�ȭ ��� Ʈ���� ���������)
1 4 16 25 20 15 <- ���: ������ȸ�� ���

���࿹ 2(�־��� main�Լ����� (A)�κ��� �ּ� ��� ������)
20 10 30 5 15 25 35 -1 <- �Է�: -1�� ���ö����� Ʈ���� ����� ��� ����.
(���� �������� ����� �ʾ����� �־��� insert_node�� ����ϸ�
20
/ \
10 30
/ \ / \
5 15 25 35
5 15 10 25 35 30 20 <- ���: ���� ��ȸ ���
*/