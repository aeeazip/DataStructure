#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STRING 100
typedef struct {
	int id;
	char name[MAX_STRING];
	char tel[MAX_STRING];
	char dept[MAX_STRING];
} element;

typedef struct TreeNode {
	element data;
	struct TreeNode* left, * right;
} TreeNode;

TreeNode* new_node( int id, char name[], char tel[], char dept[]) {
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->data.id = id;
	strcpy(temp->data.name, name);
	strcpy(temp->data.tel, tel);
	strcpy(temp->data.dept, dept);
	temp->left = temp->right = NULL;
	return temp;
}

TreeNode* insert(TreeNode* node, int id, char name[], char tel[], char dept[]) {
	if (node == NULL)
		return new_node(id, name, tel, dept);

	if (node->data.id > id)
		node->left = insert(node->left, id, name, tel, dept);
	else if (node->data.id < id)
		node->right = insert(node->right, id, name, tel, dept);

	return node;
}

TreeNode* min_value_node(TreeNode* node) {
	TreeNode* temp = node;
	while (temp->left != NULL)
		temp = temp->left;
	return temp;
}

TreeNode* delete(TreeNode* node, int id) {
	int found = 0;

	if (node == NULL) {
		printf("id�� %d�� �л��� �����ϴ�.\n", id);
		return node;
	}

	if (node->data.id > id)
		node->left = delete(node->left, id);
	else if (node->data.id < id)
		node->right = delete(node->right, id);
	else {
		if (node->left == NULL) {
			TreeNode* temp = node->right;
			free(node);
			return temp;
		}
		else if (node->right == NULL) {
			TreeNode* temp = node->left;
			free(node);
			return temp;
		}
		TreeNode* temp = min_value_node(node->right);
		node->data = temp->data;
		node->right = delete(node->right, temp->data.id);
	}
	return node;
}

void search(TreeNode* node, int id) {
	if (node == NULL) {
		printf("id�� %d�� �л��� �����ϴ�.\n", id);
		return;
	}

	if (node->data.id == id) {
		printf("-------------------------------------\n");
		printf("�й�: %d\n", node->data.id);
		printf("�̸�: %s\n", node->data.name);
		printf("��ȭ��ȣ: %s\n", node->data.tel);
		printf("�а�: %s\n", node->data.dept);
		return;
	}
	else if (node->data.id > id)
		return search(node->left, id);
	else
		return search(node->right, id);
}

void print(TreeNode* node) {
	if (node != NULL) {
		print(node->left);
		printf("-------------------------------------\n");
		printf("�й�: %d\n", node->data.id);
		printf("�̸�: %s\n", node->data.name);
		printf("��ȭ��ȣ: %s\n", node->data.tel);
		printf("�а�: %s\n", node->data.dept);
		print(node->right);
	}
}

int count(TreeNode* node) {
	if (node == NULL)
		return 0;
	else
		return 1 + count(node->left) + count(node->right);
}

int main(void) {
	TreeNode* root = NULL;

	int id;
	char name[MAX_STRING];
	char tel[MAX_STRING];
	char dept[MAX_STRING];
	char c;

	do {
		printf("Enter i(nsert), d(elete), s(earch), p(rint), c(ount), q(uit):");
		scanf_s("%c", &c);

		if (c == 'i') {
			printf("�й��Է�:");
			scanf("%d", &id);
			printf("�̸� �Է�:");
			scanf("%s", name);
			printf("��ȭ��ȣ �Է�:");
			scanf("%s", tel);
			printf("�а� �Է�:");
			scanf("%s", dept);

			root = insert(root, id, name, tel, dept);
		}
		else if (c == 'd') {
			printf("������ �й� �Է�:");
			scanf_s("%d", &id);
			root = delete(root, id);
		}
		else if (c == 's') {
			printf("Ž���� �й� �Է�:");
			scanf_s("%d", &id);
			search(root, id);
		}
		else if (c == 'p') {
			printf("�л� ���� �й� �� ���\n");
			print(root);
		}
		else if (c == 'c')
			printf("���� ����� �л��� �� ���� %d\n", count(root));
		while (getchar() != '\n');
	} while (c != 'q');
}