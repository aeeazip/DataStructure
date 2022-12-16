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
		printf("������ �׸��� �����ϴ�.\n");
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

	if (head == NULL) // ��尡 ����ִ� ���
		printf("������ �׸��� �����ϴ�.\n");
	
	if (head->link == NULL) { // ��尡 �ϳ��� ���
		free(head);
		head = NULL;
	}
	else { // ��尡 2�� �̻��� ���
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
		printf("������ �� �����ϴ�\n");

	if (pos == 0)
		head = delete_first(head);
	else {
		while (i != pos) {
			i++;
			pre = p;
			p = p->link;
		}

		if (pos == get_length(head) - 1)  // ��尡 �� �̻��̸鼭 pos=����-1
			head = delete_last(head);
		else {  // ��尡 �� �̻��̸鼭 pos=�߰�
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
		printf("������ �� �����ϴ�\n");
	else {
		while (p != NULL) {
			if (p->data == key)
				break;
			i++;
			p = p->link;
		}

		if (i == 0) // key���� ����� ù ��° ���� ���
			head = delete_first(head);
		else if (i == get_length(head) - 1) // key���� ����� ������ ���� ���
			head = delete_last(head);
		else // key���� ����� �߰����� ���
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
		printf("pos ���� ����\n");

	if (pos == 0)
		head = insert_first(head, value);
	else if (pos == get_length(head)) // ������� �ʰ� pos=����
		head = insert_last(head, value);
	else { // ������� �ʰ� pos=�߰�
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
	//list1 = 30->20->10->�� �����. �̶� 10, 20, 30�� ������ ��带 �����Ѵ�. 
	list1 = insert_first(list1, 10);
	list1 = insert_first(list1, 20);
	list1 = insert_first(list1, 30);

	// list1�� ��� 
	printf("list1 = ");
	print_list(list1);

	//list1�� �� �� ��带 �����Ѵ� ��, list1 = 20->30-> 
	list1 = delete_first(list1);

	// list1�� ��� 
	print_list(list1);

	//list2 = 11->22->33->44->�� �����. �̶� 11, 22, 33, 44�� ������ ��带 �����Ѵ�. 
	list2 = insert_last(list2, 11);
	list2 = insert_last(list2, 22);
	list2 = insert_last(list2, 33);
	list2 = insert_last(list2, 44);

	// list2�� ��� 
	print_list(list2);

	// list2�� �� �� ��带 �����Ѵ�. ��, list2 = 11->22->33-> 
	list2 = delete_last(list2);

	// list2�� ��� 
	print_list(list2);

	//list2�� �������� �ٲ� ����Ʈ�� list3�� ����Ű�� �Ѵ�. list3 = 33->22->11->�� �����. 
	list3 = reverse(list2);

	//list3�� ����Ѵ�. 
	print_list(list3);

	// list1 = 20->30->33->22->11->�� �����. ��, list1�� list3�� ���ļ� list1�� ����Ű�� �Ѵ�. 
	list1 = concat(list1, list3);

	//list1�� ����Ѵ�.
	print_list(list1);

	if (is_in_list(list1, 20))
		printf("list1�� 20�� �ֽ��ϴ�\n");
	else
		printf("list1�� 20�� �����ϴ�\n");

	printf("list1�� ���̴� %d\n", get_length(list1));
	printf("list1�� ������ %d\n", get_total(list1));

	printf("pos = 1�� ����� data�� %d\n", get_entry(list1, 1));
	
	list1 = delete_by_key(list1, 33); // Test list1 ù����, �߰�����, ������ ���� �� �غ���
	print_list(list1);

	list1 = insert_pos(list1, 3, 50); // Test list1 ù����, �߰�����, ������ ���� �� �غ���
	print_list(list1);

	list1 = delete_pos(list1, 2);
	print_list(list1);
}