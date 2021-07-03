/*************************************************
 * @Description: file content
 * @Author: yuanquan
 * @Email: yuanquan2011@qq.com
 * @Date: 2021-03-09 19:41:30
 * @LastEditors: yuanquan
 * @LastEditTime: 2021-03-15 21:50:36
 * @copyright: Copyright (c) yuanquan
 *************************************************/
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int threeSumClosest(vector<int>& nums, int target) {
	int closestSum = nums[0] + nums[1] + nums[2];

	sort(nums.begin(), nums.end());
	for(size_t i=0; i < nums.size(); ++i)
	{
		for(size_t j=i+1, k=nums.size()-1; j < k; )
		{
			int sum = nums[i] + nums[j] + nums[k];

			if(abs(sum-target) <= abs(closestSum-target)) 
			{
				closestSum = sum;
			}
			
			if(sum > target)
			{
				--k;
			}
			else if(sum < target)
			{
				++j;
			}
			else
			{
				return target;
			}
		}
	}
	return closestSum;
}

int main(void)
{
	vector<int> nums{-1,2,1,-4};
	int target = 1;

	cout << "Closest three sum: " << threeSumClosest(nums, target) << endl;
}