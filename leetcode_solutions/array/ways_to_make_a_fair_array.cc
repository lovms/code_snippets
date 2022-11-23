/**
 * 因为`只能删掉一个数，所以index的变化只会有一次`，而且删除第i位置上的数，
 * index奇偶性发生改变的只有其右侧的所有数！！！所以，我们可以预先计算每个位置
 * 的左右两侧的奇数以及偶数位置的前缀和，这样就有
 *
 * 1）如果位置i是奇数：
 *    则删除nums[i]后的奇数和等于 Left_Odd_Sum + Right_Even_Sum，因为i右侧
 *    原先偶数index上的数都变成奇数index上了；
 * 2）如果位置i是偶数：
 *    则删除nums[i]后的偶数和= Left_Even_Sum + Right_Odd_Sum;
 *
 * 坑：
 * 1） 返回的是总共有多少种删除的方式，看清题目；
 * 2）如果nums长度为1，返回1；
 * 3）局部变量一定要初始化，否则提交和本地的初始化策略不同，结果不同，这里卡了好几次；
 *
 * 遗留：
 * 虽然思路很简单，但实现并不简洁，我实现的比较粗暴, 无论时间和空间上都有优化的空间
 *
 * 题解中"正负交替前缀和"非常的简洁，值得学习：https://leetcode.cn/problems/ways-to-make-a-fair-array/solutions/493715/shuang-bai-zheng-fu-jiao-ti-qian-zhui-he-by-letian/
 */

#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
	struct SideSum {
		unsigned int odd_sum;
		unsigned int even_sum;
		SideSum(): odd_sum(0), even_sum(0) {}
	};

    int waysToMakeFair(vector<int>& nums) {
		if (nums.size() == 1) return 1;
		if (nums.size() <= 2) return 0;
		vector<SideSum> from_left(nums.size(), SideSum());
		//from_left.reserve(nums.size());    // 要初始化，不能仅分配大小; 否则提交后运行的结果会于本地运行的不同
		vector<SideSum> from_right(nums.size(), SideSum());
		//from_right.reserve(nums.size());

		for (int i = 0; i < nums.size(); ++i) {
			if ((i&1) == 1) {  // odd
				if (i > 0) {
				    from_left[i].odd_sum = nums[i] + from_left[i-1].odd_sum;
				    from_left[i].even_sum = from_left[i-1].even_sum;
				} else {
					from_left[i].odd_sum = nums[i];
				}
			} else {
				if (i > 0) {
				    from_left[i].even_sum = nums[i] + from_left[i-1].even_sum;
				    from_left[i].odd_sum = from_left[i-1].odd_sum;
				} else {
					from_left[i].even_sum = nums[i];
				}
			}
		}

		for (int i = nums.size()-1; i >= 0; --i) {
			if ((i&1) == 1) {
				if (i < nums.size()-1) {
				    from_right[i].odd_sum = nums[i] + from_right[i+1].odd_sum;
					from_right[i].even_sum = from_right[i+1].even_sum;
				} else {
					from_right[i].odd_sum = nums[i];
				}
			} else {
				if (i < nums.size()-1) {
				    from_right[i].even_sum = nums[i] + from_right[i+1].even_sum;
					from_right[i].odd_sum = from_right[i+1].odd_sum;
				} else {
					from_right[i].even_sum = nums[i];
				}
			}
		}

		unsigned int odd_sum_without_i = 0;  // notice that all numbers are not less than 1. (>=1)
		unsigned int even_sum_without_i = 0;
		int valid_delete_nums = 0;
		for (int i = 0; i < nums.size(); ++i) {
			if ((i&1) == 1) {
				// i 右侧的原先偶数index都变成了奇数index
				odd_sum_without_i = (from_left[i].odd_sum - nums[i]) + from_right[i].even_sum;
				// i 左侧的原先奇数index都变成了偶数index
				even_sum_without_i = from_left[i].even_sum + (from_right[i].odd_sum - nums[i]);
			} else {
				odd_sum_without_i = from_left[i].odd_sum + (from_right[i].even_sum - nums[i]);
				even_sum_without_i = (from_left[i].even_sum - nums[i]) + from_right[i].odd_sum;
			}

			if (odd_sum_without_i == even_sum_without_i) {
				valid_delete_nums++;
			}
		}
		return valid_delete_nums;
    }
};

int main() {
	Solution sol;
	vector<int> nums = {2,1,6,4};
	//vector<int> nums = {6,1,7,4,1};
	std::cout << "delete: " << sol.waysToMakeFair(nums) << std::endl;
	return 0;
}
