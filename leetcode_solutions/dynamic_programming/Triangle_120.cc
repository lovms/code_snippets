/*
 * 本题按照一种特殊的方式选择出一个数组，然后加和，最终目的是求出最大可能的和。
 *
 * 但重复的前缀和，非常符合dp求解的条件
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
