/*
 * 本题需要找到多个股票买卖的时间对，所以，我这里显示地使用了双层循环。
 * 并且通过倒序遍历days数组，来计算子问题的买卖股票最高利润，从而避免重复计算。
 *
 * 这里有个非常需要注意的实现细节，就是我在循环内部使用了prices[j] <= pricies[i]就过滤无效计算！
 * 这样会导致内部循环最终的结果为0，当这个子问题不存在最佳买卖时间（如：{5,0,3}, 在5时买入，卖出无法获得正向收益）。
 * 但这里有个基本的常识，就是dp[i] >= dp[i+1], 即我不在第i天进行交易的这种状态下，至少可以获得dp[i+1]的利润，
 * 因此在内层循环初始化localMax时需要使用dp[i+1]来初始化！！！ (上述例子中dp[1]=3, 因此dp[0]至少是3)
 *
 * 【*** 看过题解过后，我发现我并没有用动态规划来解题，本质上还是记忆化搜索的方式，因为实际上我是遍历了所有买入、卖出的情况，
 *   只不过通过保存计算过的状态来减少计算而已! 我解法的时间复杂度是O(n^2)的，动态规划可以降低到O(n)*** 】
 *
 *
 * 最开始我是通过findSubMax这种递归+记忆搜索的方式来遍历所有的情况，但由于在prices[j] < prices[i]这块
 * 实现的不好，所以超时了，因为我这里的实现方式，是必须在i-th day买入，所以如果在i-th卖出，其实模拟了（覆盖了）
 * 第i天不进行交易的状态。故无法使用prices[j] == prices[i]来跳过无效的交易，从而导致大量的时间浪费，在提交时，
 * 最后一个例子就存在大量这种连续多天股票价格一样的情形，递归的效率特别慢…… 对比AC的解法，其实就差在这块了。
 *
 */

#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() <= 1) {
            return 0;
        }

        vector<int> dp(prices.size(), -1);

        dp.back() = 0;
        int globalMax = 0;
        for (int i = prices.size()-2; i >= 0; --i) { // buy stock on the i-th day
            int localMax = dp[i+1]; // Attention!!! dp[i] >= dp[i+1], so we must initilize dp[i] with dp[i+1] instead of 0
            for (int j = i+1; j < prices.size(); ++j) { // and sell it on the  j-th day
                if (prices[j] <= prices[i]) {
                    continue;
                }
                int tmpProfit = prices[j] - prices[i];
                if (1+j < prices.size()) {
                    tmpProfit += dp[1+j];
                }
                if (tmpProfit > localMax) {
                    localMax = tmpProfit;
                }
            }
            dp[i] = localMax;
            //std::cout << "debug: i|" << i << ", localMax|" << localMax << std::endl;
            if (localMax > globalMax) {
                globalMax = localMax;
            }
        }

        return globalMax;


        //return findSubMax(prices, 0, dp);
    }

    /*
     * 这种解法超时
     */
    int findSubMax(vector<int>& prices, int i, vector<int>& dp) {
        std::cout << "debug: i: " << i << std::endl;
        if (i >= prices.size()) {
            return 0;
        } else if (i == prices.size()-1) {
            return 0;
        } else if (i == prices.size()-2) {
            return std::max(0, prices.back() - prices[prices.size()-2]);
        }

        if (dp[i] != -1) {
            return dp[i];
        }

        // buy stock on the ith day
        int localMax = 0;
        for (int j = i; j < prices.size(); ++j) {
            if (prices[j] <= prices[i]) {
                continue;
            }
            int tmpProfit = prices[j] - prices[i] + findSubMax(prices, j+1, dp);
            if (tmpProfit > localMax) {
                localMax = tmpProfit;
            }
        }

        dp[i] = localMax;
        return dp[i];
    }
};

int main() {
    //vector<int> prices = {3,4,1,5,3,3,12};  // 14
    //vector<int> prices = {7,1,5,3,6,4}; // 7
    //vector<int> prices = {1,2,3,4,5}; // 4
    //vector<int> prices = {7,6,4,3,1}; // 0
    //vector<int> prices = {7,1,5,3,6,4};
    vector<int> prices = {3,2,6,5,0,3}; // 7

    Solution sol;
    std::cout << sol.maxProfit(prices) << std::endl;
    return 0;
}
