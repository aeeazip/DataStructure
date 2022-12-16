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

// key�� ���� Ž�� Ʈ�� root�� �����Ѵ�. 
TreeNode* insert_node(TreeNode* root, element key) // �������� ����
{
    TreeNode* p, * t; // p�� �θ���, t�� ������ 
    TreeNode* n;        // n�� ���ο� ���

    t = root;
    p = NULL;

    // Ž���� ���� ����, �ݺ��� �̿��ؼ� search(���� search�Լ� ����)
    while (t != NULL) { // �����尡 NULL�� �ɶ�����
         //if( key == t->key ) return root; (A)-1: ���� key�� �ִ� ��� �Լ��� ������ �κ��� �ּ�ó����
        p = t; // �����带 �θ���� �ϰ�
            // �����带 ����
        if (key <= t->data) // (A)-2: ���� �۰ų� ���� ��� �������� �̵�
            t = t->left;
        else
            t = t->right;
    }

    n = (TreeNode*)malloc(sizeof(TreeNode));
    if (n == NULL) exit(1);
    // ������ ����
    n->data = key;
    n->left = n->right = NULL;

    // �θ� ���� ��ũ ����
    if (p != NULL)
        if (key <= p->data)
            p->left = n;
        else
            p->right = n;
    else // ���ʿ� Ʈ���� ����־�����
        root = n;

    return root;
}

int getKeyCount(TreeNode* node, int key) // �ڵ� �ۼ�
{
    // ������ �˳��ϰ� ������ �����Ͽ����� �Ϻδ� ä���� �ʾƵ� �ȴ�
    // �� �ٿ� ���� ������ �־ �ȴ�.
    // ��: int temp; if (a > b) return a; else return b;
    int count = 0;
   
    if (node != NULL) {
        if (node->data == key)
            count = 1 + getKeyCount(node->left, key) + getKeyCount(node->right, key);
        else
            count = getKeyCount(node->left, key) + getKeyCount(node->right, key);
    }
    return count;

}
int main(void) // �������� ����
{
    int n;
    int key;

    TreeNode* root = NULL;

    // (A) �Էºκ�
    scanf("%d", &n);
    while (n != -1) {
        root = insert_node(root, n);
        scanf("%d", &n);
    }
    //printCheck(root); Ʈ��üũ�� ���� �ӽ÷� ����� ��

    scanf("%d", &key);
    printf("%d\n", getKeyCount(root, key));
}