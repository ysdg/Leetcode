/*************************************************
 * @Description: file content
 * @Author: yuanquan
 * @Email: yuanquan2011@qq.com
 * @Date: 2021-05-17 21:20:13
 * @LastEditors: yuanquan
 * @LastEditTime: 2021-05-25 23:14:13
 * @copyright: Copyright (c) yuanquan
 *************************************************/
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

bool isValid(string s) {
	vector<char> toMatch;

	for(const auto& c : s)
	{
		switch (c)
		{
		case '(':	toMatch.push_back(')');	break;
		case '[':	toMatch.push_back(']');	break;
		case '{':	toMatch.push_back('}');	break;
		
		case ')':	
		case ']':	
		case '}':	
			if(!toMatch.empty() && *toMatch.rbegin() == c)
			{
				toMatch.pop_back();
				continue;
			}
			return false;
		break;

		default:	return false;			break;
		}
	}

	return toMatch.empty();
}

int main(void)
{
	std::cout << "Is Valid: " << isValid("}") << std::endl;
}
