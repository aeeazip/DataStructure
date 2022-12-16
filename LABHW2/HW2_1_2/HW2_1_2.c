// version 1
#define _CRT_SECURE_NO_WARNINGS
#define MAX_STACK_SIZE 3
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct {
	int num;
	char name[10];
}element;

typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
}StackType;

int is_empty(StackType* s) {
	return (s->top == -1);
}

int is_full(StackType* s) {
	return (s->top == MAX_STACK_SIZE - 1);
}

void stack_print(StackType* s) {
	int i;
	if (is_empty(s))
		printf("<empty>\n");
	else {
		for (i = s->top; i >= 0; i--) {
			if (i == s->top)
				printf("[%d, %s] <- top\n", s->data[i].num, s->data[i].name);
			else
				printf("[%d, %s]\n", s->data[i].num, s->data[i].name);
		}
	}
	printf("--\n");
}

void push(StackType* s, element item) {
	if (is_full(s))
		printf("스택 포화 에러\n");
	else
		s->data[++(s->top)] = item;
}

element pop(StackType* s) {
	if (is_empty(s))
		printf("스택 공백 에러\n");
	else
		return s->data[(s->top)--];
}

element peek(StackType* s) {
	if (is_empty(s))
		printf("스택 공백 에러\n");
	else
		return s->data[(s->top)];
}


void init(StackType* s) {
	s->top = -1;
}

int main() {
	StackType s;
	element e;

	init(&s);
	stack_print(&s);

	e.num = 10;
	strcpy(e.name, "ten");
	push(&s, e);
	stack_print(&s);

	e.num = 20;
	strcpy(e.name, "twenty");
	push(&s, e);
	stack_print(&s);

	e.num = 30;
	strcpy(e.name, "thirty");
	push(&s, e);
	stack_print(&s);

	e.num = 40;
	strcpy(e.name, "fourty");
	push(&s, e);
	stack_print(&s);

	pop(&s);
	stack_print(&s);

	e.num = 50;
	strcpy(e.name, "fifty");
	push(&s, e);
	stack_print(&s);

	pop(&s);
	stack_print(&s);

	pop(&s);
	stack_print(&s);

	pop(&s);
	stack_print(&s);
}

/* version 2

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 3

typedef struct {
	int data;
	char str[10];
}element;

element stack[MAX_STACK_SIZE]; 
int top = -1;

int is_empty() {// 공백 상태 검출 함수
	return (top == -1);
}

int is_full() {// 포화 상태 검출 함수
	return (top == MAX_STACK_SIZE - 1);
}

void stack_print() {// 스택 상태 출력
	int i;

	if (is_empty())
		printf("<empty>\n");
	else {
		for (i = top; i >= 0; i--) {
			if (i == top)
				printf("[%d, %s] <- top\n", stack[i].data, stack[i].str);
			else
				printf("[%d, %s]\n", stack[i].data, stack[i].str);
		}
	}
	printf("--\n");
}

void push(element item) {// 삽입 함수
	if (is_full())
		printf("스택 포화 에러\n");
	else
		stack[++top] = item;
}

element pop() {// 삭제 함수
	if (is_empty())
		printf("스택 공백 에러\n");
	else
		return stack[top--];
}

element peek() {// 피크 함수
	if (is_empty())
		printf("스택 공백 에러\n");
	else
		return stack[top];
}

int main(void) {
	element e;

	stack_print();

	e.data = 10;
	strcpy(e.str, "ten");
	push(e);
	stack_print();

	e.data = 20;
	strcpy(e.str, "twenty");
	push(e);
	stack_print();

	e.data = 30;
	strcpy(e.str, "thirty");
	push(e);
	stack_print();

	e.data = 40;
	strcpy(e.str, "fourty");
	push(e);
	stack_print();
	
	pop();
	stack_print();

	e.data = 50;
	strcpy(e.str, "fifty");
	push(e);
	stack_print();

	
	pop();
	stack_print();

	pop();
	stack_print();

	pop();
	stack_print();
}
*/
