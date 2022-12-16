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
TreeNode m7 = { 28, NULL, NULL }; // 추가
TreeNode m4 = { 25, NULL, &m7 }; // 변경
TreeNode m5 = { 15, &m3, &m4 };
TreeNode m6 = { 15, &m2, &m5 };
TreeNode* root2 = &m6;

//p281 Quiz 01
int get_nonleaf_count(TreeNode* node) { //비단말 노드의 개수
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
int equal(TreeNode* t1, TreeNode* t2) { //노드의 개수부터 비교
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
int get_oneleaf_count(TreeNode* node) { //자식이 하나인 노드의 개수 반환
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
int get_max(TreeNode* node) { //최대값 반환
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

int get_min(TreeNode* node) { //최소값 반환
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
void node_increase(TreeNode* node) { //이진트리 노드 값을 1씩 증가
	if (node != NULL) {
		node->data++;
		node_increase(node->left);
		node_increase(node->right);
	}
}

void preorder(TreeNode* root) // p271 코드 복사
{
	if (root != NULL) {
		printf("%d ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

int search(TreeNode* root, int key, TreeNode* result[]) {// 이진 트리에서 주어진 key 값을 갖는 노드들을 모두 찾아 그것들의 주소값을 result 배열에 저장하고 해당 노드의 갯수를 반환
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

TreeNode* copy(TreeNode* root) { // 주어진 이진 트리를 복제한 새로운 트리를 반환
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

	printf("가)\n");
	printf("트리 root 중 비단말노드의 개수는 %d.\n", get_nonleaf_count(root));
	printf("트리 root2 중 비단말노드의 개수는 %d.\n", get_nonleaf_count(root2));
	printf("트리 root 중 자식이 하나만 있는 노드의 개수는 %d.\n", get_oneleaf_count(root));
	printf("트리 root2 중 자식이 하나만 있는 노드의 개수는 %d.\n", get_oneleaf_count(root2));
	printf("트리 root 중 자식이 둘이 있는 노드의 개수는 %d.\n", get_twoleaf_count(root));
	printf("트리 root2 중 자식이 둘이 있는 노드의 개수는 %d.\n", get_twoleaf_count(root2));
	printf("트리 root 에서 가장 큰 수는 %d.\n", get_max(root));
	printf("트리 root2 에서 가장 큰 수는 %d.\n", get_max(root2));
	printf("트리 root 에서 가장 작은 수는 %d.\n", get_min(root));
	printf("트리 root2 에서 가장 작은 수는 %d.\n", get_min(root2));

	printf("\n나)\n");
	num = search(root, 15, result);
	for (i = 0; i < num; i++)
		printf("(0x%p, %d), ", result[i], result[i]->data);
	printf("\n");

	printf("\n다)\n");
	preorder(root);
	node_increase(root);
	printf("\n");
	preorder(root);
	printf("\n");
	printf("%s\n", equal(root, root) ? "같다" : "다르다");
	printf("%s\n", equal(root2, root2) ? "같다" : "다르다");
	printf("%s\n", equal(root, root2) ? "같다" : "다르다");
	
	printf("\n라)\n");
	clone = copy(root);
	preorder(root);
	printf("\n");
	preorder(clone);
	printf("\n");
}