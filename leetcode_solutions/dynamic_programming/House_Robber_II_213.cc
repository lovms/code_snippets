/*
 * 对比198来看这道题会更容易理解，这道题依然是线性dp。
 * 所有的屋子组成了个环形，与198不同的点，只是第0位和第n-1位的屋子，它们会互相影响；
 * 其他位置的屋子和198对比起来没有不同。
 *
 * 但由于n-1位的屋子会受0位屋子是否被盗影响，因此，第0位屋子是否被盗就要添加到状态中！！
 *
 * 本题中使用两个dp数组，就是为了区分第0位屋子是否被盗的两种状态。
 *
 * 所以，环形只是增加了dp的状态数，但没有改变线性dp的本质。
 *
 */
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

        vector<int> dp0(nums.size(), 0);
        vector<int> dp1(nums.size(), 0);

        dp0[0] = 0;
        dp0[1] = nums[1];
        dp1[0] = nums[0];
        dp1[1] = nums[0];
        for (int i = 2; i < nums.size(); ++i) {
            if (i == nums.size() - 1) {
                dp0[i] = std::max(nums[i] + dp0[i-2], dp0[i-1]);
                dp1[i] = dp1[i-1];
            } else {
                dp0[i] = std::max(nums[i] + dp0[i-2], dp0[i-1]);
                dp1[i] = std::max(nums[i] + dp1[i-2], dp1[i-1]);
            }
        }

        int n = nums.size() - 1;
        return std::max(dp0[n], dp1[n]);
    }
};

int main() {
    Solution sol;
    //vector<int> nums = {2, 3, 2};
    vector<int> nums = {1, 2, 3, 1};
    std::cout << sol.rob(nums) << std::endl;
    return 0;
}
