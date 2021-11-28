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

int strStr(string haystack, string needle) {
	if(needle.empty()) return 0;

	for(int i=0; i < haystack.size(); ++i)
	{
		for(int j=0; j < needle.size(); ++j)
		{
			if(i + j >= haystack.size()) return -1;
			if(haystack[i + j] != needle[j]) break;
			if(j==needle.size()-1) return i;
		}
	}
	return -1;
}

TEST(strStrTest, all)
{
	using TestData = tuple<string, string, int>;
	vector<TestData> datas{
		make_tuple("hello", "ll", 2),
		make_tuple("aaaaa", "bba", -1),
		make_tuple("", "", 0),
	};

	for(auto& dat : datas)
	{
		auto [haystack, needle, position] = dat;
		EXPECT_EQ(position, strStr(haystack, needle)) << "str[" << haystack << "], sub str[" << needle << "]";
	}
}
