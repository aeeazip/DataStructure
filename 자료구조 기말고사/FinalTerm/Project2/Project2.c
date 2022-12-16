#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef int element;
typedef struct TreeNode {
    element data;
    struct TreeNode* left, * right;
} TreeNode;
// key를 이진 탐색 트리 root에 삽입한다. 

TreeNode* insert_node(TreeNode* root, element key) // 변경하지 말라
{
    TreeNode* p, * t; // p는 부모노드, t는 현재노드 
    TreeNode* n;        // n은 새로운 노드

    t = root;
    p = NULL;

    // 탐색을 먼저 수행, 반복을 이용해서 search(위의 search함수 참조)
    while (t != NULL) { // 현재노드가 NULL이 될때까지
         //if( key == t->key ) return root; (A)-1: 같은 key가 있는 경우 함수를 끝내는 부분을 주석처리함
        p = t; // 현재노드를 부모노드로 하고
            // 현재노드를 전진
        if (key <= t->data) // (A)-2: 값이 작거나 같은 경우 왼쪽으로 이동
            t = t->left;
        else
            t = t->right;
    }

    n = (TreeNode*)malloc(sizeof(TreeNode));
    if (n == NULL) exit(1);
    // 데이터 복사
    n->data = key;
    n->left = n->right = NULL;

    // 부모 노드와 링크 연결
    if (p != NULL)
        if (key <= p->data)
            p->left = n;
        else
            p->right = n;
    else // 애초에 트리가 비어있었으면
        root = n;

    return root;
}

void inorder(TreeNode* root) // 변경하지 마라
{
    if (root) {
        inorder(root->left);    // 왼쪽서브트리 순회
        printf("%d ", root->data);  // 노드 방문
        inorder(root->right);   // 오른쪽서브트리 순회
    }
}

void preorder(TreeNode* root)  // 변경하지 마라
{
    if (root) {
        printf("%d ", root->data);  // 노드 방문
        preorder(root->left);   // 왼쪽서브트리 순회
        preorder(root->right);  // 오른쪽서브트리 순회
    }
}
void printCheck(TreeNode* node) // 변경하지 마라
{
    preorder(node); printf("\n");
    inorder(node); printf("\n");
}

void replaceKeyValue(TreeNode* root, int oldKey, int newKey) // 코드 작성
{
    // 빈줄은 넉넉하게 여러개 제공하였으니 일부는 채우지 않아도 된다
    // 한 줄에 여러 문장을 넣어도 된다.
    // 예: int temp; if (a > b) return a; else return b;
    // 실행한 결괏값 50 30 10 30 99 99 70 60이(가) 
        //    기댓값 50 99 10 99 70 60와(과) 다릅니다.

    if (root != NULL) {
        if (root->data == oldKey) { //oldkey 제거
            root = insert_node(root, newKey);
            
        }

        if (root->data < oldKey) 
           return replaceKeyValue(root->right, oldKey, newKey);
        else if(root->data > oldKey)
            return replaceKeyValue(root->left, oldKey, newKey);
    }

}

int main(void) // 변경하지 마라
{
    int n;
    int oldKey, newKey;
    int key;

    TreeNode* root = NULL;

    scanf("%d", &n);
    while (n != -1) {
        root = insert_node(root, n);
        scanf("%d", &n);
    }
    // printCheck(root); 트리체크를 위해 임시로 사용할 수
    scanf("%d", &oldKey);
    scanf("%d", &newKey);
    replaceKeyValue(root, oldKey, newKey);
    printCheck(root);
}