#include <stdio.h> 
#include <stdlib.h> 
// 1) typedef으로 구조체 타입 Score 정의
typedef struct {
	int midterm;
	int final;
}Score;
void printScore(Score* p) //2) 
{
	printf("중간고사 성적은 %d\n", p->midterm);
	printf("학기말고사 성적은 %d\n", p->final);
}
Score* biggerScore(Score* p1, Score* p2) //3) 
{
	int score1 = p1->midterm + p1->final;
	int score2 = p2->midterm + p2->final;

	if (score1 >= score2)
		return p1;
	else
		return p2;
}
Score* totalScore(Score* p1, Score* p2) //4) 
{
	Score* p = (Score*)malloc(sizeof(Score));

	p->midterm = p1->midterm + p2->midterm;
	p->final = p1->final + p2->final;

	return p;
}
Score* createScore(int m, int f) //5) 
{
	Score* p = (Score*)malloc(sizeof(Score));

	p->midterm = m;
	p->final = f;

	return p;
}
int main(void) {
	Score s1, s2; // 포인터 p1, p2대신에 구조체변수 s1,s2
	Score* p3;

	s1.midterm = 50;
	s1.final = 100;
	s2.midterm = 70;
	s2.final = 70;

	printScore(&s1);
	printScore(&s2);
	printf("-----------------------------\n");
	printf("둘중 성적이 좋은 점수:\n");
	printScore(biggerScore(&s1, &s2));
	printf("-----------------------------\n");
	printf("두 성적의 총 합:\n");
	printScore(totalScore(&s1, &s2));
	printf("-----------------------------\n");
	p3 = createScore(100, 100);
	printScore(p3);
}