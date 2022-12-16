#include <stdio.h> 
void print_fact_exp(int n)
{ 
	if (n == 0 || n == 1)
		printf("1");
	else {
		printf("%d * ", n);
		return print_fact_exp(n - 1);
	}
}
int main(void)
{
	int n;
	printf("Enter a number:");
	scanf_s("%d", &n);
	printf("%d! = ", n);
	print_fact_exp(n);
	printf("\n");
}