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

ListNode* mergeKLists(vector<ListNode*>& lists) {
	ListNode* kList(nullptr);
	ListNode* head(kList);
	while (true)
	{
		ListNode** minNode{nullptr};
		for(auto& list : lists)
		{
			if(list == nullptr) continue;
			if(!minNode)
			{
				minNode = &list;
				continue;
			}
			if((*minNode)->val >= list->val)
			{
				minNode = &list;
				continue;
			}
		}
		if(!minNode) break;

		if(!kList)
		{
			kList = *minNode;
			head = kList;
		}
		else
		{
			kList->next = *minNode;
			kList = kList->next;
		}
		*minNode = (*minNode)->next;
		kList->next = nullptr;
	}
	return head;
}

int main(void)
{
	ListNode* list1 = CreateList({1, 4, 5});
	ListNode* list2 = CreateList({1, 3, 4});
	ListNode* list3 = CreateList({2, 6});
	vector<ListNode*> vList{list1, list2, list3};
	ListNode* kl = mergeKLists(vList);
	while (kl != nullptr)
	{
		std::cout << kl->val << std::endl;
		kl = kl->next;
	}
}
