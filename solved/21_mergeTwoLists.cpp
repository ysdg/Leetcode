/*************************************************
 * @Description: file content
 * @Author: yuanquan
 * @Email: yuanquan2011@qq.com
 * @Date: 2021-05-17 21:20:13
 * @LastEditors: yuanquan
 * @LastEditTime: 2021-05-31 22:26:52
 * @copyright: Copyright (c) yuanquan
 *************************************************/
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) 
{
	if(!l1) return l2;
	if(!l2) return l1;

	if(l1->val < l2->val)
	{
		l1->next = mergeTwoLists(l1->next, l2);
		return l1;
	}
	else
	{
		l2->next = mergeTwoLists(l1, l2->next);
		return l2;
	}
}

// ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
// 	ListNode* head;

// 	if(l1 && l2)
// 	{
// 		if(l1->val < l2->val)
// 		{
// 			head = l1;
// 			l1 = l1->next;
// 		}
// 		else
// 		{
// 			head = l2;
// 			l2 = l2->next;
// 		}
// 	}
// 	else if(l1)
// 	{
// 		return l1;
// 	}
// 	else
// 	{
// 		return l2;
// 	}

// 	ListNode* nodeNow = head;
// 	while (l1 && l2)
// 	{
// 		if(l1->val < l2->val)
// 		{
// 			nodeNow->next = l1;
// 			nodeNow = nodeNow->next;
// 			l1 = l1->next;
// 		}
// 		else
// 		{
// 			nodeNow->next = l2;
// 			nodeNow = nodeNow->next;
// 			l2 = l2->next;
// 		}
// 	}
// 	nodeNow->next = l1 ? l1 : l2;
	
// 	return head;
// }

int main(void)
{
	ListNode node5(5, nullptr);
	ListNode node3(3, &node5);
	ListNode node1(1, &node3);

	ListNode node4(4, nullptr);
	ListNode node2(2, &node4);

	auto node = mergeTwoLists(&node1, &node2);
	while (node)
	{
		std::cout << node->val << std::endl;
		node = node->next;
	}
}
