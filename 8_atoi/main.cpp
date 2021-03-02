/*************************************************
 * @Description: 5th problem in leetcode.
 * @Author: yuanquan
 * @Email: yuanquan2011@qq.com
 * @Date: 2019-12-13 11:16:50
 * @LastEditors: yuanquan
 * @LastEditTime: 2021-02-28 23:52:10
 * @Copyright: Copyright (c) 2019 Supcon
 *************************************************/
#include "iostream"
#include "vector"

using namespace std;

int myAtoi(string str) {
	int numOut{0};
	bool isPositive{true};
	bool isNum{false};
	for(std::size_t i=0; i < str.size(); i++)
	{
		char c = str[i];
		
		if(!isNum)
		{
			if(c == ' ') continue;
			if(c == '-') 
			{
				isPositive = !isPositive;
				continue;
			}
		}
		
		if(c >= '0' && c <= '9')
		{
			isNum = true;
			
			long numCheck = (long)numOut * 10 + (c - '0');
			if((numCheck > 2147483647 - static_cast<int>(isPositive)))
			{
				numOut = 2147483647 - static_cast<int>(isPositive);
				break;
			}
				
			numOut = numOut * 10 + (c - '0');
		}
		else
		{
			break;
		}
	}
	return numOut * (isPositive ? 1 : -1);
}

int main(void)
{
	string s = "-42";
	cout << myAtoi(s) << endl;
	return 0;
}

