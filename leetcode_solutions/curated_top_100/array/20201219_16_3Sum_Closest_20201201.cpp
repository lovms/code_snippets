//Given an array nums of n integers and an integer target, find three integers in nums such that the sum is closest to target. Return the sum of the three integers. You may assume that each input would have exactly one solution.
//
// 
//
//Example 1:
//
//Input: nums = [-1,2,1,-4], target = 1
//Output: 2
//Explanation: The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
// 
//
//Constraints:
//
//3 <= nums.length <= 10^3
//-10^3 <= nums[i] <= 10^3
//-10^4 <= target <= 10^4
//
//来源：力扣（LeetCode）
//链接：https://leetcode-cn.com/problems/3sum-closest
//著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

// 思路：
// 1. 穷举遍历三个数的和，需要O(N^3)，复杂度较高
// 2. 排序是本题的关键，排序可以使得对和的判断有个方向，可以节省
//    掉对一些组合的考察
// 3. 外循环的想法，说固定第一个数，其实，这里包含选择这个数以及不选择这个数
//    两种情况;另外，内循环时，剩下的两个数都只考察i之后的数；这里其实相当于
//    对时间又做了一次优化。也就是说，当i=2时，剩下两个数都只要从j=3开始考虑了，
//    因为，三个数的组合包含i=0或者i=1的情形，之前已经考虑过了…… 这里啰嗦了点，
//    但对于理解为什么内循环index是从i+1开始的，非常重要…………
// 4. 另外，从动态规划的角度考虑，固定一个数i，然后问题就化解成两个子问题：
//    1）选择第i个数，然后考察 target-nums[i]，以及非i的其他数组；
//    2）不选择第i 个数，然后考察target，以及非i的其他数组；
//
//    虽然满足子问题形式，但这个问题不是动态规划问题，是因为，子问题不是公共的，
//    或者说，我们很难复用求解过的子问题
#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>  // for greater<int>() or less<int>()

using std::vector;

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
		std::sort(nums.begin(), nums.end(), std::less<int>()); // ascendent sort

		int closestT = (unsigned int)(1<<31)-1;
		int closestSum = 0;
		//std::cout << closestT << std::endl;

		for (int i = 0; i < nums.size(); ++i) {
			int pl = i+1;
			int pr = nums.size()-1;
			int sum = 0;
			while (pl < pr) {
				sum = nums[i] + nums[pl] + nums[pr];
				//std::cout << "debug1: " << sum << "," << closestT << std::endl;
				if (abs(sum-target) < closestT) {
					closestT = abs(sum-target);
					closestSum = sum;
				}
				if (sum > target) {
					pr--;
				} else if (sum == target) {
					return target;
				} else {
					pl++;
				};
			}

		}
		return closestSum;
    }
};

int main() {
	//vector<int> nums = {-1, 2, 1, -4};
	//int target = 1;
	vector<int> nums = {1,1,1,1};
	int target = 0;
	Solution s;
	std::cout << s.threeSumClosest(nums, target) << std::endl;
	return 0;
}
