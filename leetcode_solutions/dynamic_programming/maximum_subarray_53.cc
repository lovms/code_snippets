/*
 * 关键在于“连续”子数组，子数组长度可以从1...一直到整个数组长度，存在很显然的子问题。
 *
 *
 * 官方题解中有“分而治之”的解法，涉及工程中实际应用以及“线段树”！！！值得去看一看
 */

#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int result = 0;
        //result = method_v1(nums); // 超时
        result = method_v2(nums);

        return result;
    }

    /*
     * 我直接定义子问题就是不同长度的连续子数组，长度为n的子数组和，依赖长度为n-1的子数组的和。
     * 很朴素的思想，但超时了，因为实际上遍历了所有的子数组情况O(n^2)的复杂度。
     *
     * 应该需要一些剪枝，这种状态定义的情形下，感觉不好剪枝
     *
     * =======================================================================================
     * 我感觉我这里的想法，和官方题解中的“线段树”解法有点向！！！
     * =======================================================================================
     */
    int method_v1(vector<int>& nums) {
        vector<int> dp(nums.size(), 0);
        int globalMax = -10e+5;
        for (int i = 0; i < nums.size(); ++i) {
            dp[i] = nums[i];
            if (dp[i] > globalMax) {
                globalMax = dp[i];
            }
        }
        for (int step = 2; step <= nums.size(); ++step) {
            for (int i = nums.size() - 1; i >= step-1; --i) {
                dp[i] = dp[i-1] + nums[i];
                //std::cout << "step|" << step << ", i|" << i << ", dp[i]|" << dp[i] << std::endl;
                if (dp[i] > globalMax) {
                    globalMax = dp[i];
                }
            }
        }
        return globalMax;
    }

    /*
     * 线性dp，定义子问题: nums[0 ... i], 状态为：以i结尾的最大子数组和
     *
     * 这样定义的根据是，题目要求子数组要连续，所以状态转移的条件其实就是在原数组中要连续！！！
     * 故状态中要强调"以i元素结尾"的子数组和。
     *
     * =======================================================================================
     * 对比method_v1中定义子问题的方法，我再次有感触，定义状态规划子问题时，往往并不是按照求解
     * 目标的字面意思，去定义直接的子问题。
     * 而是要找到问题的结构来定义子问题，比如这里因为连续，所以定义线性的动态规划问题。
     * 至于状态，需要根据状态转移的条件 + 最终的目标一起来设计！！！
     * =======================================================================================
     */
    int method_v2(vector<int>& nums) {
        vector<int> dp(nums.size(), 0);
        dp[0] = nums[0];
        int globalMax = dp[0];

        for (int i = 1; i < nums.size(); ++i) {
            dp[i] = std::max(dp[i-1]+nums[i], nums[i]);
            if (globalMax < dp[i]) {
                globalMax = dp[i];
            }
        }
        return globalMax;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {-2,1,-3,4,-1,2,1,-5,4};
    //vector<int> nums = {5,4,-1,7,8};
    std::cout << sol.maxSubArray(nums) << std::endl;
    return 0;
}
