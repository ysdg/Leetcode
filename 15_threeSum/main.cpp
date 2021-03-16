/*************************************************
 * @Description: file content
 * @Author: yuanquan
 * @Email: yuanquan2011@qq.com
 * @Date: 2021-03-09 19:41:30
 * @LastEditors: yuanquan
 * @LastEditTime: 2021-03-15 22:33:24
 * @copyright: Copyright (c) yuanquan
 *************************************************/
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> threeSum(vector<int>& nums) {
	vector<vector<int>> v;

	sort(nums.begin(), nums.end());
	int size = nums.size();

	for(int i=0; i < size; i++)
	{
		if(i > 0 && nums[i]==nums[i-1]) continue;
		for(int j=i+1, k=size-1; j < k;)
		{
			auto sum = nums[i] + nums[j] + nums[k];
			if(sum > 0)
			{
				--k;
			}
			else if(sum < 0)
			{
				++j;
			}
			else
			{
				vector<int> onev{nums[i], nums[j], nums[k]};
				sort(onev.begin(), onev.end());
				v.emplace_back(move(onev));
				++j;
				--k;
				while (j < k && nums[j]==nums[j-1])
				{
					++j;
				}
				while (j < k && nums[k]==nums[k+1])
				{
					--k;
				}
			}
		}
	}

	return move(v);
}
}

int main(void)
{
	vector<int> nums{-1,0,1,2,-1,-4};
	
	const auto& numsV = threeSum(nums);
	for(const auto& v : numsV)
	{
		for(auto n : v)
		{
			cout << n << " ";
		}
		cout << endl;
	}
}

// int rowNum{};

// Fruit2Data dataOut;

// cin>>noskipws;
// cin >> rowNum;
// set<int> indexSet;
// while(1)
// {
// 	string fruit;
// 	int personIndex{};
// 	int weight{};
// 	cin >> fruit >> personIndex >> weight;
// 	if(fruit.empty()) break;
	
// 	dataOut[fruit][weight].insert(personIndex);
	
// 	indexSet.insert(personIndex);
// 	if(indexSet.size()==rowNum) break;
// }

// for(const auto& fruitData : dataOut)
// {
// 	for(const auto& weight2Index : fruitData.second)
// 	{
// 		for(const auto& personIndex : weight2Index.second)
// 		{
// 			cout << fruitData.first << " " << personIndex << " " << weight2Index.first << endl;
// 		}
// 	}
// }