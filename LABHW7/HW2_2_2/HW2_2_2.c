#define _CRT_SECURE_NO_WARNINGS
#define MAX_STACK_SIZE 3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct StackNode {
	int data;
	char name[10];
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

void push(LinkedStackType* s, int data, char str[]) {
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	temp->data = data;
	strcpy(temp->name, str);

	temp->link = s->top;
	s->top = temp;
}

StackNode* pop(LinkedStackType* s) {
	StackNode* temp = s->top;
	
	if(is_empty(s))
		printf("스택 공백 에러\n");
	else {
		s->top = temp->link;
		free(temp);
		return s->top;
	}
}

StackNode* peek(LinkedStackType* s) {
	if (is_empty(s))
		printf("스택 공백 에러\n");
	else
		return s->top;
}

void stack_print (LinkedStackType* s) {
	StackNode* temp;
	if (is_empty(s))
		printf("<empty>\n");
	else {
		for (temp = s->top; temp != NULL; temp = temp->link) {
			if (temp==s->top)
				printf("[%d, %s] <- top\n", temp->data,temp->name);
			else
				printf("[%d, %s]\n", temp->data, temp->name);
		}
	}
	printf("--\n");
}

int main(void) {
	LinkedStackType* s = (LinkedStackType*)malloc(sizeof(LinkedStackType));

	init_stack(s);
	stack_print(s);

	push(s, 10, "ten");
	stack_print(s);

	push(s, 20, "twenty");
	stack_print(s);

	push(s, 30, "thirty");
	stack_print(s);

	push(s, 40, "fourty");
	stack_print(s);

	pop(s);
	stack_print(s);

	push(s, 50, "fifty");
	stack_print(s);


	pop(s);
	stack_print(s);

	pop(s);
	stack_print(s);

	pop(s);
	stack_print(s);
}