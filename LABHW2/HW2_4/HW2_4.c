#define _CRT_SECURE_NO_WARNINGS
#define MAX_STRING 100
#include <stdio.h>
#include <stdlib.h>

typedef char element;
typedef struct {
	int top;
	element data[MAX_STRING];
}StackType;

void init_stack(StackType* s) {
	s->top = -1;
}

int is_empty(StackType* s) {
	return (s->top == -1);
}

int is_full(StackType* s) {
	return (s->top == MAX_STRING - 1);
}

void push(StackType* s, char c) {
	if (is_full(s))
		printf("���� ��ȭ ����\n");
	else
		s->data[++(s->top)] = c;
}

element pop(StackType* s) {
	if (is_empty(s))
		printf("���� ���� ����\n");
	else
		return s->data[(s->top)--];
}

int palindrome(char str[]) //������ 1 �ƴϸ� 0����
{
	StackType s; // �迭�� ����� ���, ���Ḯ��Ʈ�� ����ϸ� LinkedStackType s; 
	int i;// �ʿ��� ������ ���� 

	init_stack(&s); // ���� �ʱ�ȭ �Լ�

	for (i = 0; str[i] != '\0'; i++) //str �� ���ڵ��� ���ÿ� �ִ´� 
		push(&s, str[i]);

	for (i = 0; str[i] != '\0'; i++) //���ÿ��� �ϳ��� ���鼭 str �� ���ڵ�� ���ʷ� �� 
		if (str[i] != pop(&s))
			return 0;
	return 1;
}

int main(void)
{
	char word[MAX_STRING];
	printf("Enter a word to check palindrome: ");
	scanf("%s", word);
	if (palindrome(word))
		printf("palindrome �Դϴ�.\n");
	else
		printf("palindrome �� �ƴմϴ�.\n");
}