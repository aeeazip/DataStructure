#include <stdio.h> 
#include <string.h> 
void reverse_string(char *str, int s, int e) {
	//str ���� ������ �ʰ� ��ü�� �����ϱ�
	char c;
	if (e <= s)
		return;
	else {
		c = str[e];
		str[e] = str[s];
		str[s] = c;
		return reverse_string(str, s + 1, e - 1);
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
