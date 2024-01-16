#include <stdio.h>
#include <stdlib.h>

/*
�������� �ǿ� ��������ʾ�����Ǹ�������������ÿλ���ֶ��ǰ��� ���� �ķ�ʽ�洢�ģ�����ÿ���ڵ�ֻ�ܴ洢 һλ ���֡�

���㽫��������ӣ�������ͬ��ʽ����һ����ʾ�͵�����

����Լ���������� 0 ֮�⣬���������������� 0 ��ͷ��
ʾ�� 1��
���룺l1 = [2,4,3], l2 = [5,6,4]
�����[7,0,8]
���ͣ�342 + 465 = 807

ʾ�� 2��
���룺l1 = [0], l2 = [0]
�����[0]

ʾ�� 3��
���룺l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
�����[8,9,9,9,0,0,0,1]
*/

struct ListNode {
	int val;
	struct ListNode* next;
};

/*
	˼·1��
		��Ϊ������������ͬһ�������ֿ���ֱ�����
		��ͷ��ʼ������
			����������ĸýڵ�ǿգ����¼�������ڵ�ĺͲ�ȡ�࣬����¼�½�������
			������һ������Ľڵ�Ϊ�գ���Ǹÿսڵ��ֵΪ0�����ȡ�࣬��¼�½�������
			����������Ľڵ㶼Ϊ�գ�����������
	12ms
*/
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
	struct ListNode* head = NULL, *tail = NULL;
	int n1, n2, carry=0, sum;
	while (l1 || l2) {
		n1 = l1 ? l1->val : 0;
		n2 = l2 ? l2->val : 0;
		sum = n1 + n2 + carry;
		if (!head) {
			head = tail = (struct ListNode*)malloc(sizeof(struct ListNode));
		}
		else {
			tail->next = (struct ListNode*)malloc(sizeof(struct ListNode));
			tail = tail -> next;
		}
		tail->next = NULL;
		tail->val = sum % 10;
		carry = sum / 10;
		if (l1) {
			l1 = l1->next;
		}
		if (l2) {
			l2 = l2->next;
		}
	}
	if (carry > 0) {
		tail->next = malloc(sizeof(struct ListNode));
		tail->next->val = carry;
		tail->next->next = NULL;
	}
	return head;
}

/*
	˼·2��
		ͬ������������ͷ��ʼ����
			�������ڵ����ȡ�࣬���������
			������ĳ�������������ν�����һ��û�����������
	8ms
*/

struct ListNode* addTwoNumbers2(struct ListNode* l1, struct ListNode* l2) {
	struct ListNode* head = l1, * tail = NULL;
	int carry = 0, sum;
	while (l1 && l2) {
		sum = l1->val + l2->val + carry;
		l1->val = sum % 10;
		carry = sum / 10;
		tail = l1;
		l1 = l1->next;
		l2 = l2->next;
	}
	if (!l1) {
		tail->next = l2;
	}
	while (carry > 0 && tail->next != NULL) {
		sum = tail->next->val + carry;
		tail->next->val = sum % 10;
		carry = sum / 10;
		tail = tail->next;
	}
	if (carry > 0) {
		tail->next = (struct ListNode*)malloc(sizeof(struct ListNode));
		tail->next->val = carry;
		tail->next->next = NULL;
	}
	return head;
}

/*
* ժ��Leecode�ٷ�4ms��
*/

struct ListNode* addTwoNumbers3(struct ListNode* l1, struct ListNode* l2) {
	int sum, carry = 0;
	struct ListNode* p, * head = NULL;
	while (l1 || l2 || carry) {
		sum = 0;
		if (l1) {
			sum += l1->val;
			l1 = l1->next;
		}
		if (l2) {
			sum += l2->val;
			l2 = l2->next;
		}
		sum += carry;
		if (sum >= 10) {
			carry = 1;
		}
		else {
			carry = 0;
		}
		if (!head) {
			head = p = malloc(sizeof(struct ListNode));
			p->val = sum % 10;
			p->next = NULL;
		}
		else {
			p->next = malloc(sizeof(struct ListNode));
			p->next->val = sum % 10;
			p = p->next;
			p->next = NULL;
		}
	}
	return head;
}

/*
*	ժ��Leecode�ٷ�0ms��
*/
struct ListNode* addTwoNumbers4(struct ListNode* l1, struct ListNode* l2) {
	struct ListNode* head = NULL, * tail = NULL;
	int carry = 0;
	while (l1 && l2)
	{
		struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
		newNode->val = (l1->val + l2->val + carry);
		carry = (newNode->val / 10);
		newNode->val %= 10;
		newNode->next = NULL;
		if (head)
		{
			tail->next = newNode;
			tail = newNode;
		}
		else
		{
			head = tail = newNode;
		}
		l1 = l1->next, l2 = l2->next;
	}
	printf("jnb!");
	while (l1)
	{
		l1->val = l1->val + carry;
		carry = (l1->val / 10);
		l1->val = l1->val % 10;
		tail->next = l1;
		tail = l1;
		l1 = l1->next;
		printf("??\n");
	}
	while (l2)
	{
		l2->val = l2->val + carry;
		carry = (l2->val / 10);
		l2->val = l2->val % 10;
		tail->next = l2;
		tail = l2;
		l2 = l2->next;
		printf("!!\n");
	}
	if (carry)
	{
		struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
		newNode->val = 1;
		newNode->next = NULL;
		tail->next = newNode;
		tail = newNode;
	}
	printf("www!\n");
	return head;
}


struct ListNode* createList(int* a, int len) {
	struct ListNode* p = NULL, * head = NULL;
	for (int i = 0; i < len; i++) {
		if (!head) {
			head = p = (struct ListNode*)malloc(sizeof(struct ListNode));
			p->next = NULL;
			p->val = a[i];
		}
		else {
			p->next = (struct ListNode*)malloc(sizeof(struct ListNode));
			p->next->next = NULL;
			p->next->val = a[i];
			p = p->next;
		}
	}
	return head;
}

int main() {
	struct ListNode* l1 = NULL, *l2 = NULL, * l3 = NULL;
	int a1[] = { 9,9,9,9,9,9,9 };
	int a2[] = { 9,9,9,9 };
	l1 = createList(a1, sizeof(a1) / sizeof(int));
	l2 = createList(a2, sizeof(a2) / sizeof(int));
	l3 = addTwoNumbers2(l1, l2);
	while (l3) {
		printf("%d,", l3->val);
		l3 = l3->next;
		if (!l3) {
			printf("\b");
		}
	}
	return 0;
}