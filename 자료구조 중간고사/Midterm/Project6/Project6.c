#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
} TreeNode;

typedef struct { // 이렇게 제시하나 학생들은 다르게 해도 괜찮음
	TreeNode* NodePt;
	int rightPrint; // 오른쪽 자식 출력했으면 1, 아니면 0 
} element;

typedef struct StackNode {
	element data;
	struct StackNode* link;
} StackNode;

typedef struct {
	StackNode* top;
} LinkedStackType;

void init(LinkedStackType* s) // 변경하지 말라.
{
	s->top = NULL;
}

int is_empty(LinkedStackType* s) // 변경하지 말라.
{
	return (s->top == NULL);
}

// 포화 상태 검출 함수
int is_full(LinkedStackType* s) // 변경하지 말라.
{
	return 0;
}
// 삽입 함수
void push(LinkedStackType* s, element item) // 변경하지 말라.
{
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	temp->data = item;
	temp->link = s->top;
	s->top = temp;
}
// 삭제 함수
element pop(LinkedStackType* s) // 변경하지 말라.
{
	if (is_empty(s)) {
		fprintf(stderr, "스택이 비어있음\n");
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
element peek(LinkedStackType* s) // 변경하지 말라.
{
	if (is_empty(s)) {
		fprintf(stderr, "스택이 비어있음\n");
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

			//현재 노드를 2번 입력
			push(s, item);
			push(s, item);

			//왼쪽 노드로 이동
			root = root->left;
		}

		if (!is_empty(s))
		{
			root = pop(s).NodePt;

			//현재 노드의 첫번째 방문일때, 오른쪽으로 이동
			if (!is_empty(s) && root == peek(s).NodePt)
				root = root->right;
			//현재 노드를 두번째 방문 했을때 출력한다.
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

TreeNode* insert_node(TreeNode* root, int data)  // 변경하지 말라. 
												 // 아직 배우지 않았으나 어떤 규칙으로 트리에 노드를 삽입한다.
{
	TreeNode* p, * t; // p는 부모노드, t는 현재노드 
	TreeNode* n;	    // n은 새로운 노드

	t = root;
	p = NULL;

	// 탐색을 먼저 수행, 반복을 이용해서 search(위의 search함수 참조)
	while (t != NULL) { // 현재노드가 NULL이 될때까지
		 // if( data == t->data ) return root;
		p = t; // 현재노드를 부모노드로 하고
			// 현재노드를 전진
		if (data < t->data)
			t = t->left;
		else
			t = t->right;
	}
	// data가 트리 안에 없으므로 삽입 가능
	n = (TreeNode*)malloc(sizeof(TreeNode));
	//if (n == NULL) return;
	// 데이터 복사
	n->data = data;
	n->left = n->right = NULL;

	// 부모 노드와 링크 연결
	if (p != NULL)
		if (data < p->data)
			p->left = n;
		else
			p->right = n;
	else // 애초에 트리가 비어있었으면
		root = n;
	return root;
}

int main(void)
{
	LinkedStackType s;
	int n;
	TreeNode* root;
	init(&s);

	// (B) 연습을 위한 트리
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
	// (프로스쿨 사용을 위한 설명)
	// (A)부분으로 표시된 아래의 6줄은 프로스쿨에 올릴때 주석처리를 삭제해주세요.트리를 만들기 위한 부분입니다.
	/*(A)
	root = NULL;
	scanf("%d", &n);
	while (n != -1) {
		root = insert_node(root, n);
		scanf("%d", &n);
	} */

	//printf("후위 순회=");
	postorder_iter(&s, root); printf("\n");
	return 0;
}

/*
Q. 후위순회 반복문으로 작성하기

문제: (트리)반복적후위순회(난이도 상)

이번에는 후위순회를 반복적인 방법으로 구현하는 문제이다

재귀가 아닌 반복적방법으로 후위순회를 구현하는
postorder_iter 함수를 작성하라.

주의사항 및 힌트

반복적전위순회 구현하는 문제는 수업에서 다루었던 반복적중위순회를 조금 변경하면 되었다. 그러나 이 반복적후위순회는 조금 더 생각을 해야한다.
재귀를 사용하여 반복적으로 함수를 구현하지 않으면 0점 처리함
실행예 1(주어진 main함수에서 (A)부분을 주석처리했을때 (B)부분에서 주어진 초기화 대로 트리가 만들어지면)
1 4 16 25 20 15 <- 출력: 후위순회한 결과

실행예 2(주어진 main함수에서 (A)부분을 주석 취소 했을때)
20 10 30 5 15 25 35 -1 <- 입력: -1이 나올때까지 트리를 만드는 노드 삽입.
(아직 수업에서 배우지 않았지만 주어진 insert_node를 사용하면
20
/ \
10 30
/ \ / \
5 15 25 35
5 15 10 25 35 30 20 <- 출력: 후위 순회 결과
*/