#include <stdio.h>
#include <stdlib.h>

/*
给你两个 非空 的链表，表示两个非负的整数。它们每位数字都是按照 逆序 的方式存储的，并且每个节点只能存储 一位 数字。

请你将两个数相加，并以相同形式返回一个表示和的链表。

你可以假设除了数字 0 之外，这两个数都不会以 0 开头。
示例 1：
输入：l1 = [2,4,3], l2 = [5,6,4]
输出：[7,0,8]
解释：342 + 465 = 807

示例 2：
输入：l1 = [0], l2 = [0]
输出：[0]

示例 3：
输入：l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
输出：[8,9,9,9,0,0,0,1]
*/

struct ListNode {
	int val;
	struct ListNode* next;
};

/*
	思路1：
		因为逆序，所以链表同一结点的数字可以直接相加
		从头开始遍历，
			若两个链表的该节点非空，则记录下两个节点的和并取余，并记录下进制数，
			若其中一个链表的节点为空，则记该空节点的值为0，求和取余，记录下进制数，
			若两个链表的节点都为空，则跳出遍历
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
	思路2：
		同样从两条链表头开始遍历
			对两个节点求和取余，计算进制数
			但其中某条链表遍历完后，衔接上另一条没遍历完的链表
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
* 摘抄Leecode官方4ms答案
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
*	摘抄Leecode官方0ms答案
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