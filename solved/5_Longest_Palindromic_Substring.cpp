/*************************************************
 * @Description: 5th problem in leetcode.
 * @Author: yuanquan
 * @Email: yuanquan2011@qq.com
 * @Date: 2019-12-13 11:16:50
 * @LastEditors: yuanquan
 * @LastEditTime: 2021-07-04 14:20:45
 * @Copyright: Copyright (c) 2019 Supcon
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

string longestPalindrome(string s) {
	int start = 0, end = 0, sLen = s.length();
	if(sLen <= 1)return s;
	for(int i=0; i < sLen; ++i)
	{
		// sub start: i-j
		// sub end: j+i
		int j = 1;
		for(j=1; i-j>=0 && j+i<=sLen; ++j)
		{
			if(s[i-j] == s[j+i])
			{
				if(2*j > end - start)
				{
					start = i - j;
					end = i + j;
				}
			}
			else
			{
				break;
			}
		}


		// sub start: i-j
		// sub end: i+j+1
		if(i+1<sLen && s[i]==s[i+1])
		{
			if(1 > end - start)
			{
				start = i;
				end = i + 1;
			}
			for(j=1; i-j>=0 && j+i+1<sLen; ++j)
			{
				if(s[i-j]==s[j+i+1])
				{
					if(2*j + 1 > end - start)
					{
						start = i - j;
						end = i + j + 1;
					}
				}
				else
				{
					break;	
				}
			}
		}
	}

	return s.substr(start, end-start+1);
}

int main(void)
{
	string s = "ccc";
	cout << longestPalindrome(s) << endl;
	return 0;
}

