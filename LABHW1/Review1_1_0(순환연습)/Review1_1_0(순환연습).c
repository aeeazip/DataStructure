#include <stdio.h> 
#include <string.h> 
void print_reverse(char *str, int end) { 
	if (end == 0)
		printf("%c", str[0]);
	else {
		printf("%c", str[end]);
		return print_reverse(str, end - 1);
	}
} 
int main() {
	char str[100]; 
	printf("Enter any string:"); 
	scanf_s("%s", str, 100); 
	printf("Reversed String is: "); 
	print_reverse(str, strlen(str) - 1); // str과 마지막 인덱스를 매개변수로 
	return 0; 
}