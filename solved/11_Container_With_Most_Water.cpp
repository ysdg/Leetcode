/*************************************************
 * @Description: file content
 * @Author: yuanquan
 * @Email: yuanquan2011@qq.com
 * @Date: 2020-06-30 13:20:21
 * @LastEditors: yuanquan
 * @LastEditTime: 2020-07-08 21:57:56
 * @copyright: Copyright (c) yuanquan
 *************************************************/

#include "iostream"
#include "vector"

// Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.

// Example 1:
// Input: "babad"
// Output: "bab"
// Note: "aba" is also a valid answer.

// Example 2:
// Input: "cbbd"
// Output: "bb"

using namespace std;

int maxArea(vector<int>& height) {
	// int start, end, max=0;
	// for(start=0; start < height.size(); start++)
	// {
	// 	for(end=start+1; end < height.size(); end++)
	// 	{
	// 		int v = min(height[start], height[end]) * (end-start);
	// 		if(v > max)
	// 		{
	// 			max = v;
	// 		}
	// 	}
	// }
	// return max;
	
	int start=0, end=height.size()-1, m=0;
	while(start < end)
	{
		m = max(min(height[start], height[end]) * (end-start), m);
		if(height[start] > height[end]) end--;
		else start++;
	}
	return m;
}

int main(void)
{
	// string s = "abacab";
	// std::vector<int> h {1,8,6,2,5,4,8,3,7};
	// cout << maxArea(h) << endl;
	
	int16_t num16, result;
	uint8_t high, low;
	num16 = -2000;
	low = num16;
	high = num16 >> 8;
	cout << "high: " << high << "low: " << low << endl;

	result = (int16_t)(high << 8) + (int16_t)(low);
	cout << "result: " << result << endl;
	return 0;
}
