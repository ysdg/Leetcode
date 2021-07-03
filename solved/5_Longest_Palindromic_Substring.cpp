/*************************************************
 * @Description: 5th problem in leetcode.
 * @Author: yuanquan
 * @Email: yuanquan2011@qq.com
 * @Date: 2019-12-13 11:16:50
 * @LastEditors: yuanquan
 * @LastEditTime: 2020-01-20 16:08:36
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
	for(int i=0; i < sLen; i++)
	{
		for(int endTmp=sLen-1; i <= endTmp; endTmp--)
		{
			int endTTmp = endTmp;
			for(int startTmp=i; startTmp < endTTmp; startTmp++, endTTmp--)
			{
				if(s.at(startTmp) != s.at(endTTmp)){break;}
				else if(startTmp == endTTmp || (startTmp+1 == endTTmp) || startTmp+2==endTTmp)
				{
					if(end-start < endTmp -i)
					{
						start = i;
						end = endTmp;
					}
				}
			}
		}
	}
	return s.substr(start, end-start+1);
}

int main(void)
{
	string s = "abacab";
	cout << longestPalindrome(s) << endl;
	return 0;
}

