#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct TreeNode {
	element key;
	struct TreeNode* left, * right;
}TreeNode;

TreeNode* new_node(TreeNode* node, element key) {
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->key = key;
	temp->left = temp->right = NULL;
	return temp;
}

TreeNode* insert(TreeNode* node, element key) {
	if (node == NULL)
		return new_node(node, key);
	
	if (key < node->key)
		node->left = insert(node->left, key);
	else if (key > node->key)
		node->right = insert(node->right, key);

	return node;
}

TreeNode* min_value_node(TreeNode* node) {
	TreeNode* temp = node;

	while (temp->left != NULL)
		temp = temp->left;
	return temp;
}

TreeNode* delete(TreeNode* node, element key) {
	if (node == NULL)
		return node;

	if (key < node->key)
		node->left = delete(node->left, key);
	else if (key > node->key)
		node->right = delete(node->right, key);
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
		node->key = temp->key;
		node->right = delete(node->right, temp->key);
	}
	return node;
}

int search(TreeNode* node, element key) {
	if (node == NULL)
		return 0;

	if (node->key == key)
		return 1;
	else if (node->key > key)
		return search(node->left, key);
	else return search(node->right, key);
}

void print(TreeNode* node) { //preorder
	if (node != NULL) {
		printf("%d ", node->key);
		print(node->left);
		print(node->right);
	}
}

int height(TreeNode* node) {
	if (node == NULL)
		return 0;

	int left = height(node->left);
	int right = height(node->right);
	return 1 + (left > right ? left : right);
}

int count(TreeNode* node) {
	if (node == NULL)
		return 0;
	return 1 + count(node->left) + count(node->right);
}

int get_maximum(TreeNode* node) {
	while (node->right != NULL)
		node = node->right;
	return node->key;
}

int get_minimum(TreeNode* node) {
	while (node->left != NULL) 
		node = node->left;
	return node->key;
}

int main(void) {
	TreeNode* root = NULL;
	char c;
	element n;

	do {
		printf("Enter i(nsert),d(elete),s(earch),p(rint),h(eight),c(ount),m(ax),n(min),q(uit):");
		scanf_s("%c", &c);
		
		if (c == 'i') {
			printf("삽입할 key값 입력:");
			scanf_s("%d", &n);
			root = insert(root, n);
		}
		else if (c == 'd') {
			printf("삭제할 key값 입력:");
			scanf_s("%d", &n);
			root = delete(root, n);
		}
		else if (c == 's') {
			printf("탐색할 key값 입력:");
			scanf_s("%d", &n);
			if (search(root, n))
				printf("있음\n");
			else
				printf("없음\n");
		}
		else if (c == 'p') {
			print(root);
			printf("\n");
		}
		else if (c == 'h')
			printf("트리의 높이는 %d\n", height(root));
		else if (c == 'c')
			printf("노드의 개수는 %d\n", count(root));
		else if (c == 'm')
			printf("가장 큰 값은 %d\n", get_maximum(root));
		else if (c == 'n')
			printf("가장 작은 값은 %d\n", get_minimum(root));
		while (getchar() != '\n');
	} while (c != 'q');

}