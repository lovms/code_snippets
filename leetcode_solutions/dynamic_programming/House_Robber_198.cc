#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.size() == 1) {
            return nums[0];
        } else if (nums.size() == 2) {
            return std::max(nums[0], nums[1]);
        }
        vector<int> dp(nums.size(), 0);

        dp[0] = nums[0];
        dp[1] = std::max(nums[0], nums[1]);
        for (int i = 2; i < nums.size(); ++i) {
            dp[i] = std::max(nums[i] + dp[i-2], dp[i-1]);
        }

        return dp[nums.size()-1];
    }
};

int main() {
    Solution sol;
    //vector<int> nums = {1,2,3,1};
    //vector<int> nums = {2, 7, 9, 3, 1};
    vector<int> nums = {2, 1, 1, 2};
    std::cout << sol.rob(nums) << std::endl;
    return 0;
}
