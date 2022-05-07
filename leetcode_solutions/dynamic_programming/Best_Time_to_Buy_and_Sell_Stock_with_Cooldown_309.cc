/*
 * 本题在II的基础上，增加了个cooldown=1 day的条件，这里实际上是改变了状态转移的条件，并没有改变状态！！！
 *
 * 状态依然是“一天交易完后，是否持有股票”。
 *
 * 使用数组dp0和dp1分别表示两种状态，则
 * II中的状态转移公式为：
 * 1) dp0[i] = max(dp0[i-1], dp1[i-1] + prices[i])
 * 2) dp1[i] = max(dp1[i-1], dp0[i-1] - prices[i])
 *
 *
 * 本题中dp0的状态转移没有变化：保持昨天的状态，或者昨天持有股票则今天卖出。
 *
 * 但对于dp1，有个冷静期限制。dp0[i-1]包含了昨天卖出股票这种情况，这个情况是不能转移到dp1[i]的，
 * 其实，dp0[i-1]可以从两个状态转移而来：一是 dp0[i-2]，另一个是：dp1[i-2] + prices[i] 即i-2天持有股票，但i-1天卖出了。
 * 所以，我们只能从 dp0[i-2] -> dp0[i-1] -> dp1[i] 转移状态，所以修改下dp1的状态转移，如下：
 *
 * 2) dp1[i] = max(dp1[i-1], dp0[i-2] - prices[i])。
 *
 *
 * ==================================================================
 * 我从题解中看到，其实这个“是否处于冷静期”也可以用来改变状态的！！！
 *
 * ==================================================================
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

        vector<int> dp0(prices.size(), 0);
        vector<int> dp1(prices.size(), 0);
        dp0[0] = 0;
        dp1[0] = -prices[0];
        dp0[1] = std::max(dp0[0], dp1[0] + prices[1]);
        dp1[1] = std::max(dp1[0], dp0[0] - prices[1]);

        for (int i = 2; i < prices.size(); ++i) {
            dp0[i] = std::max(dp0[i-1], dp1[i-1] + prices[i]);
            dp1[i] = std::max(dp1[i-1], dp0[i-2] - prices[i]);
        }

        return dp0[prices.size()-1];
    }
};

int main() {
    Solution sol;
    //vector<int> prices = {1,2,3,0,2}; //3
    vector<int> prices = {1}; //3
    std::cout << sol.maxProfit(prices) << std::endl;
    return 0;
}
