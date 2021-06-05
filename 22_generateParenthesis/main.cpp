/*************************************************
 * @Description: file content
 * @Author: yuanquan
 * @Email: yuanquan2011@qq.com
 * @Date: 2021-05-17 21:20:13
 * @LastEditors: yuanquan
 * @LastEditTime: 2021-06-05 15:06:04
 * @copyright: Copyright (c) yuanquan
 *************************************************/
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <math.h>

using namespace std;

void generate(vector<string>& v, string s, int l, int r, int n)
{
	if(l > n || r > n || r > l) return;
	if(l==n && r==n) 
	{
		v.emplace_back(move(s)); 
		return;
	}
	
	generate(v, s + '(', l+1, r, n);
	generate(v, s + ')', l, r+1, n);
}

vector<string> generateParenthesis(int n) 
{
	vector<string> v;
	generate(v, "", 0, 0, n);
	return v;
}

int main(void)
{
	for(const auto& i : generateParenthesis(3))
	{
		std::cout << i << std::endl;
	}
}
