/*************************************************
 * @Description: file content
 * @Author: yuanquan
 * @Email: yuanquan2011@qq.com
 * @Date: 2021-05-16 20:55:36
 * @LastEditors: yuanquan
 * @LastEditTime: 2021-05-16 21:28:12
 * @copyright: Copyright (c) yuanquan
 *************************************************/
#include <string>
#include <vector>
#include <math.h>
#include <algorithm>
#include <iostream>

using namespace std;

vector<string> letterCombinations(string digits) {
	static vector<vector<string>> Num2Letter{
		{"a", "b", "c"},
		{"d", "e", "f"},
		{"g", "h", "i"},
		{"j", "k", "l"},
		{"m", "n", "o"},
		{"p", "q", "r", "s"},
		{"t", "u", "v"},
		{"w", "x", "y", "z"},
	};

	vector<string> out;
	// out.reserve(pow(3, digits.size()));

	for(const auto& num : digits)
	{
		auto i = (uint32_t)(num-'2');

		if(out.empty())
		{
			out = Num2Letter[i];
			continue;
		}

		vector<string> tmp;
		for(const auto& s : out)
		{
			for(const auto& letter : Num2Letter[i])
			{
				tmp.push_back(s + letter);
			}
		}
		swap(out, tmp);
	}
	return out;
}

int main(void)
{
	auto digits = "23";
	auto strs = letterCombinations(digits);
	for(const auto& s : strs)
	{
		cout << s << endl;
	}
}
