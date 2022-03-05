/**
 * 本题我使用了非常简单的DFS+记忆搜索，并且使用前缀和来加速。
 * 虽然通过了，但时间和空间效率上都不太好其实。
 *
 * 需要注意的地方是，本题需要打印出subarrays 的起始index，
 * 路径输出与DFS的过程一般都是相反的，通过判断某个subarray的sum是否正好在路径上。
 * 特别容易犯错的情况是，如果最后k个数字正好是最后一个subarray，那么需要单独判断。
 * 同时索引的边界条件需要特别注意，我一开始提交的时候，多次遇到了heap-buffer overflow
 * 的错误。
 */
/*
689. Maximum Sum of 3 Non-Overlapping Subarrays
Given an integer array nums and an integer k, find three non-overlapping subarrays of length k with maximum sum and return them.

Return the result as a list of indices representing the starting position of each interval (0-indexed). If there are multiple answers, return the lexicographically smallest one.

 

Example 1:

Input: nums = [1,2,1,2,6,7,5,1], k = 2
Output: [0,3,5]
Explanation: Subarrays [1, 2], [2, 6], [7, 5] correspond to the starting indices [0, 3, 5].
We could have also taken [2, 1], but an answer of [1, 3, 5] would be lexicographically larger.
Example 2:

Input: nums = [1,2,1,2,1,2,1,2,1], k = 2
Output: [0,2,4]
 

Constraints:

1 <= nums.length <= 2 * 104
1 <= nums[i] < 216
1 <= k <= floor(nums.length / 3)
*/

#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        vector<int> result;
        if (k >= nums.size()) {
            return result;
        }

		vector<int> prefixSum(nums.size(), 0);
		prefixSum[0] = nums[0];
		for (int i = 1; i < nums.size(); ++i) {
			prefixSum[i] = prefixSum[i-1] + nums[i];
		}

		/*
		for (auto& sum : prefixSum) {
			std::cout << sum << std::endl;
		}
		*/

		int MAX = 0; // num sequense is non-negative
		int count = 3;
		vector<vector<int>> remainMax(nums.size(), vector<int>(count+1, 0));
		subMax(remainMax, prefixSum, 0, count, k);

		std::cout << remainMax[0][count] << std::endl;

		findPath(remainMax, prefixSum, k, result);
		for (auto i : result) {
			std::cout << i << " ";
		}
		std::cout << std::endl;
		return result;

    }

	int subMax(vector<vector<int>>& remainMax, vector<int>& prefixSum, int start, int count, int k) {
		//if (count <= 0 || start > remainMax.size()-k || start > remainMax.size()-1) {
		if (count <= 0 || start > remainMax.size()-k) {
			return 0;
		}
		if (remainMax[start][count] > 0) {
			return remainMax[start][count];
		}
		int subSeqSum = start!=0 ?  (prefixSum[start+k-1]-prefixSum[start-1]) : prefixSum[start+k-1];
		remainMax[start][count] = std::max(subSeqSum + subMax(remainMax, prefixSum, start+k, count-1, k),
				                           subMax(remainMax, prefixSum, start+1, count, k));

		return remainMax[start][count];
	}

	void findPath(const vector<vector<int>>& remainMax, 
			const vector<int>& prefixSum, int k, vector<int>& result) {
		int count = 3;
		int n = 0;
		while (count > 0 && n+k < remainMax.size()) {
			int subSum = n!=0 ? (prefixSum[n+k-1]-prefixSum[n-1]) : prefixSum[n+k-1];
			if (remainMax[n][count] == subSum + remainMax[n+k][count-1]) {
				result.emplace_back(n);
				n += k;
				--count;
			} else {
				++n;
			}
		}
		if (count > 0) {  // last k numbers consists of the last sub sequence
			result.emplace_back(n);
		}
	}
};

int main() {
	Solution sol;
	//vector<int> nums = {1,2,1,2,6,7,5,1};
	//vector<int> nums = {1,2,1,2,1,2,1,2,1};
	int k = 2;
    vector<int> nums = {7,13,20,19,19,2,10,1,1,19};
	k = 3;
	sol.maxSumOfThreeSubarrays(nums, k);
	return 0;
}
