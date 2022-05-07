/*
 * 本题按照一种特殊的方式选择出一个数组，然后加和，最终目的是求出最小可能的和。
 *
 * 但重复的前缀和，非常符合dp求解的条件
 *
 * 我的解法时间和空间复杂度都为O(n^2)，但由于状态转移只发生在相邻的两层之间，
 * 因此，并不需要使用和原三角数组一样大小的空间来始终保存所有状态，而是可以用一个一维数组
 * 来保存状态转移时所需要的之前一层的状态即可，从而将空间复杂度降低到O(n)
 */

#include <iostream>
#include <vector>

using std::vector;
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        vector<vector<int>> dp;

        for (auto& layer : triangle) {
            dp.emplace_back(vector<int>(layer.size(), 0));
        }

        for (int i = 0; i < triangle.back().size(); ++i) {
            dp.back()[i] = triangle.back()[i];
        }

        /*
        std::cout << "====dp size:" << dp.size() << "\n";
        for (auto& layer: dp) {
            for (auto& e : layer) {
                std::cout << e << ",";
            }
            std::cout << std::endl;
        }
        */

        for (int layer = triangle.size()-2; layer >= 0; --layer) {
            for (int j = 0; j < triangle[layer].size(); ++j) {
                dp[layer][j] = triangle[layer][j] + std::min(dp[layer+1][j], dp[layer+1][j+1]);
            }
        }

        return dp[0][0];
    }
};

int main() {
    Solution sol;
    vector<vector<int>> triangle = {{2},{3,4},{6,5,7},{4,1,8,3}}; 
    //vector<vector<int>> triangle = {{-10}};
    std::cout << sol.minimumTotal(triangle) << std::endl;
    return 0;
}
