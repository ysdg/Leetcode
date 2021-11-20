/*************************************************
 * @Description: file content
 * @Author: yuanquan
 * @Email: yuanquan2011@qq.com
 * @Date: 2021-05-17 21:20:13
 * @LastEditors: yuanquan
 * @LastEditTime: 2021-07-24 12:20:47
 * @copyright: Copyright (c) yuanquan
 *************************************************/
#include <iostream>
#include <vector>
#include <set>
#include <string>

using namespace std;

// Definition for singly-linked list.
struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* CreateList(vector<int> vec)
{
	ListNode* list{nullptr};
	ListNode* head = list;
	for(const auto node : vec)
	{
		if(!list)
		{
			list = new ListNode{node};
			head = list;
		}
		else
		{
			list->next = new ListNode{node};
			list = list->next;
		}
	}
	return head;
}

// Recursion
ListNode* reverseKGroup(ListNode* head, int k) {
	if(k <= 1) return head;

	ListNode* nextHead = head;
	for(auto len=k; len > 0; --len)
	{
		if(!nextHead) return head;
		nextHead = nextHead->next;
	}

	ListNode* first = head;
	ListNode* second = head->next;

	// reverse follow nodes
	head->next = reverseKGroup(nextHead, k);

	// reverse current k nodes
	for(auto i=1; i < k; ++i)
	{
		ListNode* next = second->next;
		second->next = first;

		first = second;
		second = next;
	}
	return first;
}

/* 
// Iteration
bool isLenEnough(ListNode* h, int k)
{
	for(auto len=k; len > 0; --len)
	{
		if(!h) return false;
		h = h->next;
	}
	return true;
};
ListNode* reverseKGroup(ListNode* head, int k) {
	if(k <= 1) return head;

	ListNode* headOut = head;
	ListNode* hair{nullptr};
	if(isLenEnough(head, k))
	{
		ListNode* first = head;
		ListNode* second = head->next;
		// reverse current k nodes
		for(int j=1; j < k; ++j)
		{
			ListNode* tmp = second->next;
			second->next = first;

			first = second;
			second = tmp;
		}
		hair = head;
		hair->next = first;
		head->next = second;
		head = second;
		headOut = first;
	}
	else
	{
		return head;
	}

	while (isLenEnough(head, k))
	{
		ListNode* first = head;
		ListNode* second = head->next;
		// reverse current k nodes
		for(int j=1; j < k; ++j)
		{
			ListNode* tmp = second->next;
			second->next = first;

			first = second;
			second = tmp;
		}
		hair->next = first;
		hair = head;
		head->next = second;
		head = second;
	}
	return headOut;
} */
int main(void)
{
	ListNode* list1 = CreateList({1, 2, 3, 4, 5});
	ListNode* kl = reverseKGroup(list1, 3);
	while (kl != nullptr)
	{
		cout << kl->val << ", ";
		kl = kl->next;
	}
	cout << endl;
}
