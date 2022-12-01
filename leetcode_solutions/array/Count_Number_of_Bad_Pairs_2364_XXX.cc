/**
 * 这道题最终还是没想出来，虽然已经很接近了。
 * 题目要求找出 nums[j] - nums[i] != j - i, i<j的bad pair对数，当然这
 * 等价于找nums[j] - nums[i] = j-i的good pair对数，最后使用所有的pair对数减去good pair对数即可。
 *
 * 一开始O(n^2)的逐个对比的办法肯定超时，
 * 我一直在想的是对 nums[i]和 nums[i-1]能给后续的 nums[i] 和 nums[j]的对比带来什么信息么？想了半天也确认是没有的。
 * 也就是说每个pair的对比都是相互之间独立的（基本确定不是要用DP去求解了），那肯定要找到一个trick了。
 *
 * 1） 我一开始想的是对于 nums[i]来说，它在之后的位置上合适的数是可以算出来的 nums[j] 应该等于 g(i,j)=nums[i] + (j-i)，
 *     保存g(i,j)会很多，所以，可以保存上下界，超过上下界的数就不用比了，一定没有good pairs了。
 *
 * 2）然后我其实已经在想着要用map来保存g(i,j)了，然后 直接查询 nums[j]在map中有多少个即可。但有个关键的问题我没有解决：
 *    g(i,j)随着j的变化需要不断的变化！也就是我的map内容需要每次都全量更新一遍，那还是O(n^2)的！到这里我就看答案了……
 *
 * 最后发现，只要变换下公式， nums[j] - nums[i] = j - i等价于 nums[j] - j = nums[i] -i，所以map中并不需要存储g(i,j)而是存储
 * h(i) = nums[i] - i 就可以了 T_T
 * 
 * 唉，一道并不难的题，说明我思维还是比较僵化的!!!
 */

#include <iostream>
#include <vector>
#include <unordered_map>

using std::vector;
using std::unordered_map;

class Solution {
public:
    long long countBadPairs(vector<int>& nums) {
		if (nums.size() <= 1) return 0;
		unordered_map<int, int> prefix_map;
		long long count = 0;
		for (int i = 0 ; i < nums.size(); ++i) {
			std::cout << "i|" << i
				<< ", num|" << nums[i]
				<< ", lb|" << lower_bound
				<< ", ub|" << upper_bound << std::endl;
			if (nums[i] < lower_bound || nums[i] > upper_bound) {
				lower_bound = std::min(lower_bound+1, nums[i]);
				upper_bound = std::max(upper_bound+1, nums[i]);
				skip_count++;
				continue;
			}
			lower_bound = std::min(lower_bound+1, nums[i]);
			upper_bound = std::max(upper_bound+1, nums[i]);

			for (int j = 0; j <= i-1; ++j) {
				if (nums[j] - nums[i] != j - i) {
					count++;
				}
			}
		}

		std::cout << "skipped: " << skip_count << std::endl;
		return count;
    }
};

int main() {
	Solution sol;
	//vector<int> nums = {4,1,3,3};
	//vector<int> nums = {1,2,3,4,5};
	vector<int> nums = {48569,79564,76555,84731,98050,46924,28289,42472,49729,73560,81191,94767,5709,22438,29288,71494,90448,69312,35656,65335,74917,87270,62056,45168,19295,57243,86973,11463,99973,33181,93574,14390,69626,48378,69204,99712,66140,25214,60384,89263,69963,57029,76743,65494,93501,72282,86038,51600,6836,1256,64105,42382,81051,68794,36382,63317,21843,1637,87871,27337,19846,691,61121,30852,65896,16799,91259,71586,25429,66183,44698,76718,84590,4802,80708,83988,61631,96419,8483,23602,66579,63905,25871,28640,74684,60854,53211,37969,49288,48337,1802,74390,29837,19082,56793,72051,18543,51141,73960,97693,97879,81287,54348,33838,34348,98087,28246,47656,11400,4638,66569,62453,10985,89857,64870,39604,91341,49223,43655,17610,9076,14738,80742,23504,55567,77815,1046,31617,48053,70865,27076,30672,53606,6180,98362,5351,79480,22118,45028,58491,40131,28793,6544,12927,68813,11012};
	std::cout << sol.countBadPairs(nums) << std::endl;
	return 0;
}
