#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 10
#define MAX_STRING 100 // 추가

typedef struct { // 문제를 풀기위해 수정하였다
    char name[MAX_STRING];
    int age;
} element;

typedef struct {
    element  queue[MAX_QUEUE_SIZE];
    int  front, rear;
} QueueType;
//
void error(char* message) // 변경하지 말라
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}
// 초기화 함수
void init(QueueType* q) // 변경하지 말라
{
    q->front = q->rear = 0;
}
// 공백 상태 검출 함수
int is_empty(QueueType* q) // 변경하지 말라
{
    return (q->front == q->rear);
}
// 포화 상태 검출 함수
int is_full(QueueType* q) // 변경하지 말라
{
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
// 삽입 함수
void enqueue(QueueType* q, element item) // 변경하지 말라
{
    if (is_full(q))
        error("큐가 포화상태입니다");
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->queue[q->rear] = item;
}
// 삭제 함수
element dequeue(QueueType* q) // 변경하지 말라
{
    //if (is_empty(q))
        //error("큐가 공백상태입니다");
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->queue[q->front];
}

void print_queue(QueueType* q) // 이 함수를 작성
{
    int i = q->front;

    if (!is_empty(q)) {
        do {
            i = (i + 1) % MAX_QUEUE_SIZE;
            printf("%s ", q->queue[i].name);
            if (i == q->rear)
                break;
        } while (i != q->front);
    }
    printf("end\n");
}

int main(void)
{
    QueueType AQ, BQ;
    int n;
    element ele, eleA, eleB;
    init(&AQ);
    init(&BQ);

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s %d", ele.name, &ele.age);
        enqueue(&AQ, ele);
    }
    for (int i = 0; i < n; i++) {
        scanf("%s %d", ele.name, &ele.age);
        enqueue(&BQ, ele);
    }

    // 이하 코드 작성
    
    for (int i = 0; i < n; i++) {
        eleA = dequeue(&AQ);
        eleB = dequeue(&BQ);

        if (eleA.age <= eleB.age) {
            printf("%s %d\n", eleA.name, eleA.age);
            enqueue(&BQ, eleB);
        }
        else {
            printf("%s %d\n", eleB.name, eleB.age);
            enqueue(&AQ, eleA);
        }
    }

    // 게임이 끝난후 AQ와 BQ를 출력
    print_queue(&AQ);
    print_queue(&BQ);
}