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

// 10: b1010, 3: b0011
int divide(int dividend, int divisor) {
	if(dividend == 0) return 0;
	if(divisor == INT32_MIN) 
	{
		if(dividend == INT32_MIN)return 1;
		else return 0;
	}
	if(dividend == INT32_MIN && divisor == -1) return INT32_MAX;
	if(dividend == INT32_MIN && divisor == 1) return INT32_MIN;

	bool isPositive = (dividend > 0 && divisor > 0) || (dividend < 0 && divisor < 0);
	
	int result = 0;
	if(divisor < 0) divisor = -divisor;
	if(dividend == INT32_MIN)
	{
		++result;
		dividend += divisor;
	}
	if(dividend < 0) dividend = -dividend;
	for(int i=31; i >= 0; --i)
	{
		if((dividend >> i) >= divisor)
		{
			dividend -= (divisor << i);
			result += (1 << i);
		}
	}
	if(isPositive) return result;
	else return -result;
}

TEST(divideTest, all)
{
	using TestData = tuple<int, int, int>;
	vector<TestData> datas{
		make_tuple(10, 3, 3),
		make_tuple(7, -3, -2),
		make_tuple(0, 1, 0),
		make_tuple(1, 1, 1),
		make_tuple(INT32_MIN, -1, INT32_MAX),
		make_tuple(INT32_MIN, INT32_MIN, 1),
	};

	for(auto& dat : datas)
	{
		auto [dividend, divisor, result] = dat;
		EXPECT_EQ(result, divide(dividend, divisor)) << dividend << "/" << divisor;
	}
}
