#include <stdio.h>
#include <stdlib.h>
typedef int element;
typedef struct ListNode {
	element data;
	struct ListNode* link;
}ListNode;

ListNode* insert_first(ListNode* head, int value) {
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;

	p->link = head;
	head = p;
	return head;
}

void print_list(ListNode* head) {
	ListNode* p = head;

	for (p = head; p != NULL; p = p->link)
		printf("%d->", p->data);
	printf("\n");
}

ListNode* delete_first(ListNode* head) {
	ListNode* removed = head;
	
	if (head == NULL)
		printf("삭제할 항목이 없습니다.\n");
	else {
		head = removed->link;
		free(removed);
		return head;
	}
}

ListNode* insert_last(ListNode* head, int value) {
	ListNode* temp = head;
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = NULL;

	if (head == NULL)
		head = p;
	else {
		while (temp->link != NULL)
			temp = temp->link;
		temp->link = p;
	}
	return head;
}

ListNode* delete_last(ListNode* head) {
	ListNode *temp = head;
	ListNode* prevTemp = NULL;

	if (head == NULL) // 노드가 비어있는 경우
		printf("삭제할 항목이 없습니다.\n");
	
	if (head->link == NULL) { // 노드가 하나인 경우
		free(head);
		head = NULL;
	}
	else { // 노드가 2개 이상인 경우
		while (temp->link != NULL) {
			prevTemp = temp;
			temp = temp->link;
		}
		prevTemp->link = NULL;
		free(temp);
	}
	return head;
}

ListNode* reverse(ListNode* head) {
	ListNode* p, * q, * r;
	p = head;
	q = NULL;

	while (p!=NULL) {
		r = q;
		q = p;
		p = p->link;
		q->link = r;
	}
	return q;
}

ListNode* concat(ListNode* list1, ListNode* list2) {
	ListNode *p = list1;
	
	if (list1 == NULL)
		return list2;
	else if (list2 == NULL)
		return list1;
	else {
		while (p->link != NULL)
			p = p->link;
		p->link = list2;
		return list1;
	}
}

int is_in_list(ListNode* head, element item) {
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));

	for (p = head; p != NULL; p = p->link) {
		if (item == p->data)
			return 1;
	}
	return 0;
}

int get_length(ListNode* head) {
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	int i = 0;

	for (p = head; p != NULL; p = p->link)
		i++;
	return i;
}

int get_total(ListNode* head) {
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	int total = 0;

	for (p = head; p != NULL; p = p->link)
		total += p->data;
	return total;
}

element get_entry(ListNode* head, int pos) {
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	int i = 0;

	for (p = head; p != NULL; p = p->link) {
		if (i == pos)
			return p->data;
		i++;
	}
}

ListNode* delete_pos(ListNode* head, int pos) {
	ListNode* p = head;
	ListNode* pre = NULL;
	int i = 0;

	if (pos<0 || pos>=get_length(head) || head == NULL)
		printf("삭제할 수 없습니다\n");

	if (pos == 0)
		head = delete_first(head);
	else {
		while (i != pos) {
			i++;
			pre = p;
			p = p->link;
		}

		if (pos == get_length(head) - 1)  // 노드가 둘 이상이면서 pos=길이-1
			head = delete_last(head);
		else {  // 노드가 둘 이상이면서 pos=중간
			pre->link = p->link;
			free(p);
		}
	}
	return head;
}

ListNode* delete_by_key(ListNode* head, int key) {
	ListNode* p = head;
	int i = 0;

	if (!is_in_list(head, key) || head==NULL)
		printf("삭제할 수 없습니다\n");
	else {
		while (p != NULL) {
			if (p->data == key)
				break;
			i++;
			p = p->link;
		}

		if (i == 0) // key값이 노드의 첫 번째 값인 경우
			head = delete_first(head);
		else if (i == get_length(head) - 1) // key값이 노드의 마지막 값인 경우
			head = delete_last(head);
		else // key값이 노드의 중간값인 경우
			head = delete_pos(head, i);
	}
	return head;
}

ListNode* insert_pos(ListNode* head, int pos, element value) {
	ListNode* temp = head;
	ListNode* pre = NULL;
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	
	if (pos<0 || pos>get_length(head))
		printf("pos 범위 오류\n");

	if (pos == 0)
		head = insert_first(head, value);
	else if (pos == get_length(head)) // 비어있지 않고 pos=길이
		head = insert_last(head, value);
	else { // 비어있지 않고 pos=중간
		int i = 0;
		while (i != pos) {
			i++;
			pre = temp;
			temp = temp->link;
		}
		p->link = temp;
		pre->link = p;
	}
	return head;
}

int main(void)
{
	ListNode* list1 = NULL, * list2 = NULL, * list3;
	//list1 = 30->20->10->를 만든다. 이때 10, 20, 30의 순으로 노드를 삽입한다. 
	list1 = insert_first(list1, 10);
	list1 = insert_first(list1, 20);
	list1 = insert_first(list1, 30);

	// list1을 출력 
	printf("list1 = ");
	print_list(list1);

	//list1의 맨 앞 노드를 삭제한다 즉, list1 = 20->30-> 
	list1 = delete_first(list1);

	// list1을 출력 
	print_list(list1);

	//list2 = 11->22->33->44->를 만든다. 이때 11, 22, 33, 44의 순으로 노드를 삽입한다. 
	list2 = insert_last(list2, 11);
	list2 = insert_last(list2, 22);
	list2 = insert_last(list2, 33);
	list2 = insert_last(list2, 44);

	// list2를 출력 
	print_list(list2);

	// list2의 맨 뒤 노드를 삭제한다. 즉, list2 = 11->22->33-> 
	list2 = delete_last(list2);

	// list2를 출력 
	print_list(list2);

	//list2를 역순으로 바꾼 리스트를 list3가 가리키게 한다. list3 = 33->22->11->를 만든다. 
	list3 = reverse(list2);

	//list3를 출력한다. 
	print_list(list3);

	// list1 = 20->30->33->22->11->를 만든다. 즉, list1과 list3를 합쳐서 list1이 가리키게 한다. 
	list1 = concat(list1, list3);

	//list1을 출력한다.
	print_list(list1);

	if (is_in_list(list1, 20))
		printf("list1에 20이 있습니다\n");
	else
		printf("list1에 20이 없습니다\n");

	printf("list1의 길이는 %d\n", get_length(list1));
	printf("list1의 총합은 %d\n", get_total(list1));

	printf("pos = 1인 노드의 data는 %d\n", get_entry(list1, 1));
	
	list1 = delete_by_key(list1, 33); // Test list1 첫원소, 중간원소, 마지막 원소 다 해보기
	print_list(list1);

	list1 = insert_pos(list1, 3, 50); // Test list1 첫원소, 중간원소, 마지막 원소 다 해보기
	print_list(list1);

	list1 = delete_pos(list1, 2);
	print_list(list1);
}