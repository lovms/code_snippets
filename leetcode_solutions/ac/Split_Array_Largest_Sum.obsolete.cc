#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
    int splitArray(vector<int>& nums, int m) {
		int sz = nums.size();
		vector<int> cumulatedSum(sz, 0);
		cumulatedSum[0] = nums[0];
		std::cout << "cumulated Sum: ";
		for (int i = 1; i < sz; ++i) {
			cumulatedSum[i] = cumulatedSum[i-1] + nums[i];
			std::cout << cumulatedSum[i] << " ";
		}
		std::cout << std::endl;

		int miniMaxSum = 0;
		int intervalSum = 0;
		vector<int> cutPoints(m-1, 0);
		for (int i = 0; i < m-1; ++i) {
			cutPoints[i] = i;
		}
		for (int i = 0; i < m; ++i) {
			if (i == 0) {
				intervalSum = cumulatedSum[cutPoints[i]];
			} else if (i == m-1) {
				intervalSum = cumulatedSum[sz-1] - cumulatedSum[cutPoints[i]];
			} else {
			    intervalSum = cumulatedSum[cutPoints[i]] - cumulatedSum[cutPoints[i-1]];
			}
			if (intervalSum > miniMaxSum) {
				miniMaxSum = intervalSum;
			}
		}
		std::cout << "Debug1: " << miniMaxSum << std::endl;

		m -= 1;
		bool changed = true;
		int splitIndex = m-1;
		while (changed) {
			changed = false;
			int cutPoint = cutPoints[splitIndex];
			std::cout << "Debug2: splitIndex|" << splitIndex << ", cutPoint|" << cutPoint << std::endl;
			if ((splitIndex+1 < m && cutPoint + 1 < cutPoints[splitIndex+1]) ||
				cutPoint + 1 <= nums.size() - 2) { // empty split is not allowed

				// check right
				if (splitIndex==m-1) {
					intervalSum = cumulatedSum[sz-1] - cumulatedSum[cutPoint+1];
				} else {
					intervalSum = cumulatedSum[cutPoints[splitIndex+1]] - cumulatedSum[cutPoint+1];
			    }
				if (intervalSum > miniMaxSum) {
					continue;
				}
				std::cout << "Debug3: check right: "  << intervalSum << std::endl;
				// check left
				if (splitIndex == 0) {
					intervalSum = cumulatedSum[cutPoint+1];
				} else {
					intervalSum = cumulatedSum[cutPoint+1] - cumulatedSum[cutPoints[splitIndex-1]];
				}
				if (intervalSum > miniMaxSum) {
					continue;
				}
				std::cout << "Debug3: check left: "  << intervalSum << std::endl;
				cutPoints[splitIndex] += 1; // shift split to the right for one step
				changed = true;
			} else {
				continue;
			}

			if (splitIndex == 0) {
				splitIndex = m - 1;
			} else {
				splitIndex -= 1;
			}
		}

		return miniMaxSum;

    }
};
int main() {
	Solution sol;
	/*
	Input: nums = [7,2,5,10,8], m = 2
	Output: 18
	Explanation:
	There are four ways to split nums into two subarrays.
	The best way is to split it into [7,2,5] and [10,8],
	where the largest sum among the two subarrays is only 18.
	*/

	vector<int> nums = {7,2,5,10,8};
	int m = 2;
	/*
	Input: nums = [1,2,3,4,5], m = 2
	Output: 9
	Example 3:
	*/

	/*
	Input: nums = [1,4,4], m = 3
	Output: 4
	*/

	std::cout << sol.splitArray(nums, m) << std::endl;
	return 0;
}
