#define _CRT_SECURE_NO_WARNINGS
#define MAX_STACK_SIZE 3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef int element;
typedef struct StackNode{
	element data;
	struct StackNode* link;
}StackNode;

typedef struct {
	StackNode* top;
}LinkedStackType;

void init_stack(LinkedStackType* s) {
	s->top = NULL;
}

int is_empty(LinkedStackType* s) {
	return (s->top == NULL);
}

int is_full(LinkedStackType* s) {
	return 0;
}

void push(LinkedStackType* s, element item) {
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	temp->data = item;

	temp->link = s->top;
	s->top = temp;
}

element pop(LinkedStackType* s) {
	StackNode* temp = s->top;
	element data;

	if(is_empty(s))
		printf("스택 공백 에러\n");
	else {
		s->top = temp->link;
		data = temp->data;
		free(temp);
		return data;
	}
}

element peek(LinkedStackType* s) {
	if (is_empty(s))
		printf("스택 공백 에러\n");
	else 
		return s->top->data;
}

void stack_print(LinkedStackType* s) {
	StackNode *temp;
	if (is_empty(s))
		printf("<empty>\n");
	else {
		for (temp = s->top; temp != NULL; temp = temp->link) {
			if(temp==s->top)
				printf("%d <- top\n", temp->data);
			else
				printf("%d\n", temp->data);
		}
	}
	printf("--\n");
}

int main() {
	LinkedStackType s;

	init_stack(&s);
	stack_print(&s);

	push(&s, 10);
	stack_print(&s);
	push(&s, 20);
	stack_print(&s);
	push(&s, 30);
	stack_print(&s);
	push(&s, 40);
	stack_print(&s);
	pop(&s);
	stack_print(&s);
	push(&s, 50);
	stack_print(&s);
	pop(&s);
	stack_print(&s);
	pop(&s);
	stack_print(&s);
	pop(&s);
	stack_print(&s);
}