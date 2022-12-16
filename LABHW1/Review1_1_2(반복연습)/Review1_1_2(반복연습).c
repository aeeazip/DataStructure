#include <stdio.h> 
#include <string.h> 
void reverse_string(char* str, int s, int e) {
	char c;

	while (e > s) {
		c = str[e];
		str[e] = str[s];
		str[s] = c;

		s++;
		e--;
	}
}
int main() {
	char str[100];
	printf("Enter any string:");
	scanf_s("%s", str, 100);
	reverse_string(str, 0, strlen(str) - 1);
	printf("\nReversed String is: %s", str);
	return 0;
}