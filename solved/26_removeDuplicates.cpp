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

int removeDuplicates(vector<int>& nums) {
	if(nums.size() <= 1)  return nums.size();

	int i = 0, j = 1;
	for(int j=1; j < nums.size(); ++j)
	{
		if(nums[i] != nums[j])
		{
			++i;
			nums[i] = nums[j];
		}
	}
	return i + 1;
}

int main(void)
{
	vector<int> v{1, 1, 2, 3, 3, 4};
	auto len = removeDuplicates(v);
	for(auto i=0; i < len; ++i)
	{
		cout << v[i] << ", ";
	}
	cout << endl;
}
