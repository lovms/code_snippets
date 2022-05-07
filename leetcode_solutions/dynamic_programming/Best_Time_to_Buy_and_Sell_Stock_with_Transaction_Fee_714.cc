/* 
 * 和系列II相比，增加了交易费，只需要在状态转移公式中，在买入股票时将交易费减去就可以了。
 *
 * 核心还是理解这里的状态和子问题，子问题定义为: days[0 ... i]交易完成后能够获取的最大利润。
 *
 * 但对于子问题，需要根据交易完成后“是否持有股票”定义两种状态，因为days[0 ... i, i+1]需要依赖days[0 ... i]
 * 子问题在两种不同状态下的最优解，来作比较。（所以，我们可以看到定义好子问题，有时候我们定义的dp状态未必就对应子问题的最优解，因为也需要对解决上层问题有用的“中间状态”!!!）
 *
 * 动作有三种：啥也不做、买入股票、卖出股票
 */

#include <iostream>
#include <vector>
using std::vector;

class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        if (prices.size() <= 1) {
            return 0;
        }

        vector<int> dp0(prices.size(), 0);
        vector<int> dp1(prices.size(), 0);

        dp0[0] = 0;
        dp1[0] = -prices[0];  //刚进入股市，只能花钱买股票

        for (int i = 1; i < prices.size(); ++i) {
            dp0[i] = std::max(dp0[i-1], dp1[i-1] + prices[i] - fee);
            dp1[i] = std::max(dp1[i-1], dp0[i-1] - prices[i]);
        }

        return dp0[prices.size()-1];
    }
};

int main() {
    Solution sol;
    
    vector<int> prices = {1,3,2,8,4,9};
    int fee = 2;
    /*
    vector<int> prices = {1,3,7,5,10,3};
    int fee = 3;
    */

    std::cout << sol.maxProfit(prices, fee) << std::endl;
    return 0;
}
