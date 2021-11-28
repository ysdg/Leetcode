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
#include <gtest/gtest.h>
#include <boost/array.hpp>
#include <tuple>

using namespace std;
using namespace boost;
using namespace testing;

int removeElement(vector<int>& nums, int val) {
	int len = 0;
	for(int i=0; i < nums.size(); ++i)
	{
		if(nums[i] != val)
		{
			nums[len] = nums[i];
			++len;
		}
	}
	return len;
}

TEST(removeDuplicatesTest, test)
{
	using TestData = tuple<vector<int>, int, vector<int>>;
	vector<TestData> datas{
		make_tuple(vector<int>{3,2,2,3}, 3, vector<int>{2, 2}),
		make_tuple(vector<int>{0, 1, 2, 2, 3, 0, 4, 2}, 2, vector<int>{0, 1, 3, 0, 4}),

	};
	for(auto& dat : datas)
	{
		auto& nums = get<0>(dat);
		auto& val = get<1>(dat);
		auto& result = get<2>(dat);
		nums.resize(removeElement(nums, val));
		sort(result.begin(), result.end());
		sort(nums.begin(), nums.end());
		EXPECT_EQ(result, nums);
	}
}

