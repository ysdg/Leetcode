/*************************************************
 * @Description: file content
 * @Author: yuanquan
 * @Email: yuanquan2011@qq.com
 * @Date: 2021-05-17 21:20:13
 * @LastEditors: yuanquan
 * @LastEditTime: 2021-05-24 23:00:40
 * @copyright: Copyright (c) yuanquan
 *************************************************/
#include <iostream>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// int cur = 0;

// ListNode* removeNthFromEnd(ListNode* head, int n) {
	
// 	if(!head) return head;

// 	head->next = removeNthFromEnd(head->next, n);

// 	++cur;

// 	if(n==cur) return head->next;

// 	return head;
// }

ListNode* removeNthFromEnd(ListNode* head, int n) {
	ListNode* begin{head};
	ListNode* end{head};
	
	for(uint32_t i=0; i < n; ++i)
	{
		end = end->next;
		if(!end)
		{
			return head->next;
		}
	}

	while (end->next)
	{
		end = end->next;
		begin = begin->next;
	}
	begin->next = begin->next->next;

	return head;
}

int main(void)
{
	ListNode node4{4, nullptr};
	ListNode node3{3, &node4};
	ListNode node2{2, &node3};
	ListNode node1{1, &node2};

	auto node = removeNthFromEnd(&node1, 4);
	while (node)
	{
		std::cout << node->val << std::endl;
		node = node->next;
	}
}
