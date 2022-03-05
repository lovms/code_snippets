/*
 * 本题勉强通过，耗时是O(N^4)，虽然比指数复杂度强，但耗时上还得继续优化
 * 另外本题中有很多“数值计算”上的细节，稍微不注意就会溢出！！！要是手写本题的话，估计会场面会很难看。
 *
 * 周末继续优化，并总结细节点
 */
#include <iostream>
#include <vector>
#include <unordered_map>
using std::unordered_map;
using std::vector;
class Solution {
public:
	Solution() : _slice_sum(0) {}

    int numberOfArithmeticSlices(vector<int>& nums) {
		int sz = nums.size();
		vector<vector<long long>> diff(sz, vector<long long>(sz, 0));
        int maxNum = 0x80000000;
        int minNum = 0x7FFFFFFF;
		for (int i = 0; i < sz; ++i) {
            if (nums[i] > maxNum) {
                maxNum = nums[i];
            } 
            if (nums[i] < minNum) {
                minNum = nums[i];
            }
			for (int j = i+1; j < sz; ++j) {
				diff[i][j] = (long long)nums[j] - (long long)nums[i];
			}
		}
        if (maxNum == minNum) {
            return fastComb(nums.size());
        }

		for (int i = 0; i < sz-2; ++i) {
			for (int j = i+1; j < sz; ++j) {
				run(diff, j, sz, diff[i][j], 2);
			}
		}

		return _slice_sum;
    }

	void run(vector<vector<long long>> & diff, int next_row, int sz, long long step, int count) {
		if (count >= 3) {
			_slice_sum += 1;
		}
		bool flag = false;
	    for (int j = next_row+1; j < sz; ++j) {
		    if (diff[next_row][j] == step) {
				flag = true;
				run(diff, j, sz, step, count+1);
			}
		}
	}

	int count_comb(int count) {
		for (int i = 3; i <= count; ++i) {
			_slice_sum += count-i+1;
		}
		return 0;
	}

    int fastComb(int sz) {
		// C(n,0)=1
		// C(n,1)=n
		// C(n,2)=n*(n-1)/2
		// C(n,0) + C(n,1) + C(n,2) + ... + C(n,n)=2^n
		return (((unsigned long long)1<<sz) - 1 - sz - sz*(sz-1)/2);
	}

private:
	int _slice_sum;
};

int main() {
	Solution sol;
	/*
	 * Input: nums = [2,4,6,8,10]
     *Output: 7
	 *Explanation: All arithmetic subsequence slices are:
	 *[2,4,6]
	 *[4,6,8]
	 *[6,8,10]
	 *[2,4,6,8]
	 *[4,6,8,10]
	 *[2,4,6,8,10]
	 *[2,6,10]
	 */

	//vector<int> nums = {2,4,6,8,10};

	/*
	 * Input: nums = [7,7,7,7,7]
     * Output: 16
     * Explanation: Any subsequence of this array is arithmetic.
	 */
	//vector<int> nums = {7,7,7,7,7};

	//vector<int> nums = {2,4,6,6,6,8,10};
	//
	vector<int> nums = {0,2000000000,-294967296};
	//
	//vector<int> nums = {-2147483648,0,-2147483648};
	//vector<int> nums = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	//vector<int> nums = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	//vector<int> nums = {0,1,2,2,2};
	std::cout << sol.numberOfArithmeticSlices(nums) << std::endl;
	return 0;
}
