//uppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand. (i.e.,  [0,1,2,4,5,6,7] might become  [4,5,6,7,0,1,2]).
//
//Return the minimum element of this array.
//
// 
//
//Example 1:
//
//Input: nums = [3,4,5,1,2]
//Output: 1
//Example 2:
//
//Input: nums = [4,5,6,7,0,1,2]
//Output: 0
//Example 3:
//
//Input: nums = [1]
//Output: 1
// 
//
//Constraints:
//
//1 <= nums.length <= 5000
//-5000 <= nums[i] <= 5000
//All the integers of nums are unique.
//nums is sorted and rotated at some pivot.

// 比较简单的一道题
// 因为rotate操作，导致数组被分成两部分：
// 两部分内部都是升序的，因此只要通过
// nums[i] < nums[i+1] && nums[i] < nums[i-1]就
// 可以找到原序列最小值
//
// 但要注意细节
// 1. 数组长度为1
// 2. 数组长度为2
// 3. 正常数组首尾的数（在循环中处理不到)
#include <iostream>
#include <vector>

using std::vector;
class Solution {
public:
    int findMin(vector<int>& nums) {
		if (nums.size() == 1) {
			return nums[0];
		}
		if (nums.size() == 2) {
			return (nums[0] < nums[1] ? nums[0] : nums[1]);
		}
		for (int i = 1; i < nums.size()-1; ++i) {
			if (nums[i] < nums[i+1] && nums[i] < nums[i-1]) {
				return nums[i];
			}
		}
		return (nums[0] < nums[nums.size()-1] ? nums[0] : nums[nums.size()-1]);
    }
};

int main() {
	Solution s;
	//vector<int> nums = {4,5,6,7,0,1,2};
	vector<int> nums= {1};
	std::cout << s.findMin(nums) << std::endl;
	return 0;
}
