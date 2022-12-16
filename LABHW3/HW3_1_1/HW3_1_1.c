#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define MAX_QUEUE_SIZE 3

typedef struct {
	char name[10];
}element;

typedef struct {
	int front, rear;
	element data[MAX_QUEUE_SIZE];
}QueueType;

void init(QueueType* q) {
	q->front = q->rear = 0;
}

int is_empty(QueueType* q) {
	return (q->front == q->rear);
}

int is_full(QueueType* q) {
	return (q->front == (q->rear + 1) % MAX_QUEUE_SIZE);
}

void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void enqueue(QueueType* q, element e) {
	if (is_full(q))
		error("ť�� ��ȭ�����Դϴ�");
	else {
		q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
		q->data[q->rear] = e;
	}
}

element dequeue(QueueType* q) {
	if(is_empty(q))
		error("ť�� ��������Դϴ�");
	else {
		q->front = (q->front + 1) % MAX_QUEUE_SIZE;
		return q->data[q->front];
	}
}

int get_count(QueueType* q) {
	if (is_empty(q))
		return 0;
	else if (is_full(q))
		return MAX_QUEUE_SIZE - 1;
	else {
		if ((q->rear - q->front) >= 0)
			return (q->rear - q->front);
		else
			return (MAX_QUEUE_SIZE + q->rear - q->front);
	}
}

void print_queue(QueueType* q) {
	int i = q->front + 1;

	if (!is_empty(q)) {
		do {
			if (i == MAX_QUEUE_SIZE)
				i = 0;

			printf("%s ", q->data[i].name);
			i++;
		} while (i <= q->rear);
	}
	printf("\n");
}

int main(void)
{
	QueueType manQ;
	QueueType womanQ;
	element newPerson;
	init(&manQ);
	init(&womanQ);

	char ch, gender;
	printf("���� �ּ� ���α׷��Դϴ�.\n");
	do{
		printf("i<nsert, ���Է�>, c<heck, ����� üũ>, q<uit>:");
		scanf("%c", &ch);

		if (ch == 'i') {
			printf("�̸��� �Է�:");
			scanf("%s", newPerson.name);
			while (getchar() != '\n');
			printf("������ �Է�<m or f>:");
			scanf("%c", &gender);

			if (gender == 'm') {
				if (is_empty(&womanQ)) {
					printf("���� ����ڰ� �����ϴ�. ");

					if (is_full(&manQ))
						printf("����ڰ� ��á���� ���ȸ�� �̿�\n");
					else {
						printf("��ٷ��ֽʽÿ�.\n");
						enqueue(&manQ, newPerson);
					}
				}
				else
					printf("Ŀ���� ź���߽��ϴ�! %s�� %s\n", dequeue(&womanQ).name, newPerson.name);

			}
			else {
				if (is_empty(&manQ)) {
					printf("���� ����ڰ� �����ϴ�. ");

					if (is_full(&womanQ))
						printf("����ڰ� ��á���� ���ȸ�� �̿�\n");
					else {
						printf("��ٷ��ֽʽÿ�.\n");
						enqueue(&womanQ, newPerson);
					}
				}
				else
					printf("Ŀ���� ź���߽��ϴ�! %s�� %s\n", newPerson.name, dequeue(&manQ).name);
			}
		}
		else if (ch == 'c') {
			printf("���� ����� %d��: ", get_count(&manQ));
			print_queue(&manQ);
			printf("���� ����� %d��: ", get_count(&womanQ));
			print_queue(&womanQ);
		}
		while (getchar() != '\n');
	} while (ch!='q');
}