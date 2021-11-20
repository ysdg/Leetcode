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

ListNode* swapPairs(ListNode* head) {
	if(!head || !(head->next)) return head;

	auto next = head->next;
	head->next = swapPairs(next->next);
	next->next = head;
	return next;

	// auto first = head;
	// auto second = head->next;

	// first->next = swapPairs(second->next);
	// second->next = first;

	// return second;

	// auto newHead = second;
	// first->next = second->next;
	// second->next = first;

	// while ((first->next) && (first->next->next))
	// {
	// 	head = first;
	// 	second = first->next->next;
	// 	first = first->next;

	// 	first->next = second->next;
	// 	second->next = first;
	// 	head->next = second;
	// }
	// return newHead;
}

int main(void)
{
	ListNode* list1 = CreateList({1, 2, 3, 4});
	ListNode* kl = swapPairs(list1);
	while (kl != nullptr)
	{
		std::cout << kl->val << std::endl;
		kl = kl->next;
	}
}
