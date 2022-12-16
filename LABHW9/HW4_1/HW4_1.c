#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define TRUE 1
#define FALSE 0
#define MAX_TREE_SIZE 20
int i = 0;
typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
} TreeNode;
// root
// 15
// 4 15
// 15 16 25
//
//root2
//15
//4 15
//15 16 25
//28
TreeNode n1 = { 15, NULL, NULL };
TreeNode n2 = { 4, &n1, NULL };
TreeNode n3 = { 16, NULL, NULL };
TreeNode n4 = { 25, NULL, NULL };
TreeNode n5 = { 15, &n3, &n4 };
TreeNode n6 = { 15, &n2, &n5 };
TreeNode* root = &n6;
TreeNode m1 = { 15, NULL, NULL };
TreeNode m2 = { 4, &n1, NULL };
TreeNode m3 = { 16, NULL, NULL };
TreeNode m7 = { 28, NULL, NULL }; // �߰�
TreeNode m4 = { 25, NULL, &m7 }; // ����
TreeNode m5 = { 15, &m3, &m4 };
TreeNode m6 = { 15, &m2, &m5 };
TreeNode* root2 = &m6;

//p281 Quiz 01
int get_nonleaf_count(TreeNode* node) { //��ܸ� ����� ����
	int count = 0;

	if (node != NULL) {
		if (node->left != NULL && node->right != NULL)
			count = get_nonleaf_count(node->left) + get_nonleaf_count(node->right) + 1;
		else if (node->left != NULL && node->right == NULL)
			count = get_nonleaf_count(node->left) + get_nonleaf_count(node->right) + 1;
		else if (node->right != NULL && node->left == NULL)
			count = get_nonleaf_count(node->left) + get_nonleaf_count(node->right) + 1;
		else
			count = get_nonleaf_count(node->left) + get_nonleaf_count(node->right);
	}
	return count;
}

int get_node_count(TreeNode* t) {
	int count = 0;

	if (t != NULL) 
		count = get_node_count(t->left) + get_node_count(t->right) + 1;
	return count;
}

//p281 Quiz 02
int equal(TreeNode* t1, TreeNode* t2) { //����� �������� ��
	if(t1==NULL && t2==NULL)
		return 1;
	else if (t1 != NULL && t2 != NULL) {
		if (equal(t1->left, t2->left)) {
			if (equal(t1->right, t2->right)) {
				if (t1->data == t2->data)
					return 1;
			}
		}
	}
	return 0;
}

//p308 #25
int get_oneleaf_count(TreeNode* node) { //�ڽ��� �ϳ��� ����� ���� ��ȯ
	int count = 0;

	if (node != NULL) {
		if (node->left != NULL && node->right == NULL)
			count = get_oneleaf_count(node->left) + get_oneleaf_count(node->right) + 1;
		else if (node->right != NULL && node->left == NULL)
			count = get_oneleaf_count(node->left) + get_oneleaf_count(node->right) + 1;
		else
			count = get_oneleaf_count(node->left) + get_oneleaf_count(node->right);
	}
	return count;
}

//p308 #26
int get_twoleaf_count(TreeNode* node) { 
	int count = 0;
	if (node != NULL) {
		if (node->left != NULL && node->right != NULL)
			count = get_twoleaf_count(node->left) + get_twoleaf_count(node->right) + 1;
		else
			count = get_twoleaf_count(node->left) + get_twoleaf_count(node->right);
	}
	return count;
}
//p308 #27
int get_max(TreeNode* node) { //�ִ밪 ��ȯ
	int max, left, right, root;

	if (node == NULL)
		return 0;
	else {
		root = node->data;
		left = get_max(node->left);
		right = get_max(node->right);

		if (left > right)
			max = left;
		else max = right;

		if (max < root)
			max = root;
	}
	return max;
}

int get_min(TreeNode* node) { //�ּҰ� ��ȯ
	int min, left, right, root;

	if (node == NULL)
		return 99999999;
	else{
		root = node->data;
		left = get_min(node->left);
		right = get_min(node->right);

		if (left > right)
			min = right;
		else min = left;

		if (min > root)
			min = root;
	}
	return min;
}

//p308 #30
void node_increase(TreeNode* node) { //����Ʈ�� ��� ���� 1�� ����
	if (node != NULL) {
		node->data++;
		node_increase(node->left);
		node_increase(node->right);
	}
}

void preorder(TreeNode* root) // p271 �ڵ� ����
{
	if (root != NULL) {
		printf("%d ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

int search(TreeNode* root, int key, TreeNode* result[]) {// ���� Ʈ������ �־��� key ���� ���� ������ ��� ã�� �װ͵��� �ּҰ��� result �迭�� �����ϰ� �ش� ����� ������ ��ȯ
	int count = 0;

	if (root != NULL) {
		if (root->data == key) {
			result[i++] = root;
			count = 1 + search(root->left, key, result) + search(root->right, key, result);
		}
		else
			count = search(root->left, key, result) + search(root->right, key, result);
	}
	return count;
} 

TreeNode* copy(TreeNode* root) { // �־��� ���� Ʈ���� ������ ���ο� Ʈ���� ��ȯ
	TreeNode* new = (TreeNode*)malloc(sizeof(TreeNode));

	if (root == NULL)
		return NULL;
	else {
		new->data = root->data;
		new->left = copy(root->left);
		new->right = copy(root->right);
	}
	return new;
} 

int main(void)
{
	TreeNode* result[MAX_TREE_SIZE];
	TreeNode* clone;
	int i, num;

	printf("��)\n");
	printf("Ʈ�� root �� ��ܸ������ ������ %d.\n", get_nonleaf_count(root));
	printf("Ʈ�� root2 �� ��ܸ������ ������ %d.\n", get_nonleaf_count(root2));
	printf("Ʈ�� root �� �ڽ��� �ϳ��� �ִ� ����� ������ %d.\n", get_oneleaf_count(root));
	printf("Ʈ�� root2 �� �ڽ��� �ϳ��� �ִ� ����� ������ %d.\n", get_oneleaf_count(root2));
	printf("Ʈ�� root �� �ڽ��� ���� �ִ� ����� ������ %d.\n", get_twoleaf_count(root));
	printf("Ʈ�� root2 �� �ڽ��� ���� �ִ� ����� ������ %d.\n", get_twoleaf_count(root2));
	printf("Ʈ�� root ���� ���� ū ���� %d.\n", get_max(root));
	printf("Ʈ�� root2 ���� ���� ū ���� %d.\n", get_max(root2));
	printf("Ʈ�� root ���� ���� ���� ���� %d.\n", get_min(root));
	printf("Ʈ�� root2 ���� ���� ���� ���� %d.\n", get_min(root2));

	printf("\n��)\n");
	num = search(root, 15, result);
	for (i = 0; i < num; i++)
		printf("(0x%p, %d), ", result[i], result[i]->data);
	printf("\n");

	printf("\n��)\n");
	preorder(root);
	node_increase(root);
	printf("\n");
	preorder(root);
	printf("\n");
	printf("%s\n", equal(root, root) ? "����" : "�ٸ���");
	printf("%s\n", equal(root2, root2) ? "����" : "�ٸ���");
	printf("%s\n", equal(root, root2) ? "����" : "�ٸ���");
	
	printf("\n��)\n");
	clone = copy(root);
	preorder(root);
	printf("\n");
	preorder(clone);
	printf("\n");
}