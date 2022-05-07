/*
 * 本题和53题“最大连续子数组和”很像，但由于乘法的特殊性，定义状态时不仅要考虑子问题中的最大值，
 *
 * 也需要考虑子问题中最小值！！！ 因为，负数 x 负数 = 正数
 */

#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        vector<int> dpMax(nums.size(), 0);
        vector<int> dpMin(nums.size(), -1000);

        dpMax[0] = nums[0];
        dpMin[0] = nums[0];

        int globalMax = nums[0];

        for (int i = 1; i < nums.size(); ++i) {
            dpMax[i] = std::max(dpMax[i-1] * nums[i], dpMin[i-1] * nums[i]);
            dpMax[i] = std::max(dpMax[i], nums[i]);

            dpMin[i] = std::min(dpMax[i-1] * nums[i], dpMin[i-1] * nums[i]);
            dpMin[i] = std::min(dpMin[i], nums[i]);

            if (dpMax[i] > globalMax) {
                globalMax = dpMax[i];
            }

        }

        return globalMax;

    }
};

int main() {
    Solution sol;
    //vector<int> nums = {2,3,-2,4}; // 6
    vector<int> nums = {-2,0,-1}; // 0

    std::cout << sol.maxProduct(nums) << std::endl;
    return 0;
}
