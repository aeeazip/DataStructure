#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 3

typedef int element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
}StackType;

void init_stack(StackType* s) {// 스택 초기화 함수
	s->top = -1;
}

int is_empty(StackType* s) {// 공백 상태 검출 함수
	return (s->top==-1);
}

int is_full(StackType* s) {// 포화 상태 검출 함수
	return (s->top == MAX_STACK_SIZE - 1);
}

void stack_print(StackType* s) {// 스택 상태 출력
	int i;

	if (is_empty(s))
		printf("<empty>\n");
	else {
		for (i = s->top; i >= 0; i--) {
			if (i == s->top)
				printf("%d <- top\n", s->data[i]);
			else
				printf("%d\n", s->data[i]);
		}
	}
	printf("--\n");
}

void push(StackType* s, element item) {// 삽입 함수
	if (is_full(s)) 
		printf("스택 포화 에러\n");
	else
		s->data[++(s->top)] = item;
}

element pop(StackType* s) {// 삭제 함수
	if (is_empty(s)) 
		printf("스택 공백 에러\n");
	else
		return s->data[(s->top)--];
}

element peek(StackType* s) {// 피크 함수
	if (is_empty(s)) 
		printf("스택 공백 에러\n");
	else
		return s->data[(s->top)];
}

int main(void) {
	StackType s;

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