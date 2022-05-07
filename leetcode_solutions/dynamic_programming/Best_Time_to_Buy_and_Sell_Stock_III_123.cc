/*
 * 动态规划方法解题。状态与这个系列的II相比，状态变多了，状态描述：在一天的交易完成后，由“已经交易的次数”和“当前是否持有股票”来决定状态；
 * (这里交易过一次就是买卖一次的意思)。故每一天交易结束后共有3 * 2 = 6种状态。具体来看下：
 *
 *-------------------------------------------------------
 * 已经交易的次数    |    是否持有股票  |  状态数组
 *-------------------------------------------------------
 *        0          |         0        |    dp0_0 (X)
 *        0          |         1        |    dp0_1
 *-------------------------------------------------------
 *        1          |         0        |    dp1_0
 *        1          |         1        |    dp1_1
 *-------------------------------------------------------
 *        2          |         0        |    dp2_0
 *        2          |         1        |    dp2_1 (X)
 *-------------------------------------------------------
 *
 * 上述表格定义了具体的状态，由于每天都由这6种状态，所以需要使用6个数组，但状态dp0_0由于不需要任何动作、dp2_1不能再进行交易了，所以都没有意义！
 * 剩下状态的转移公式为：
 *
 * dp0_1[i] = max(dp0_1[i-1], -prices[i])    // -prices[i]就是当天买入了股票，或者不作任何动作维持之前买入的状态
 * dp1_0[i] = max(dp1_0[i-1], dp0_1[i-1] + prices[i])   // 维持之前的状态，或者将之前买入的股票卖出，故+prices[i]
 * dp1_1[i] = max(dp1_1[i-1], dp1_0[i-1] - prices[i])   // 维持之前的状态，或者买入股票
 * dp2_0[i] = max(dp2_0[i-1], dp1_1[i-1] + prices[i])   // 维持之前的状态，或者卖出股票
 *
 * 我的写法使用了滚动数组的技巧，因此只用了几个变量代替数组了，但要注意由于状态之间的依赖关系dp0_1 <- dp1_0 <- dp1_1 <- dp2_0，
 * 所以更新变量时应该从右往左更新！！！
 *
 *
 * 最后，还是要强调下DP方法的状态初始化问题！！！ 一定不能随意的将dp数组或者变量都初始化为0！！！
 * 本题中，初始状态从第1天开始的，那么就要在第1天交易完之后，定义各种状态，作为初始状态定义。
 */

#include <iostream>
#include <vector>

using std::vector;
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        // 第0位用于状态初始化
        int dp0_1 = -prices[0];
        int dp1_0 = 0, dp1_1 = -prices[0];

        int localMax = 0;
        for (int i = 1; i < prices.size(); ++i) {  //遍历从第1位开始
            if (dp1_1 + prices[i] > localMax) {  //localMax其实就对应状态dp2_0，可以写成：localMax = std::max(localMax, dp1_1 + prices[i])
                localMax = dp1_1 + prices[i];
            }
            dp1_1 = std::max(dp1_1, dp1_0 - prices[i]);
            dp1_0 = std::max(dp1_0, dp0_1 + prices[i]);
            dp0_1 = std::max(dp0_1, -prices[i]);

            //std::cout << "i: " << i << ",dp0_1: " << dp0_1 << "| dp1_0: " << dp1_0 << "| dp1_1: " << dp1_1 << "| localMax: " << localMax << std::endl;
        }

        return localMax;
    }

};

int main() {
    Solution sol;
    //vector<int> prices = {3,3,5,0,0,3,1,4}; // 6
    //vector<int> prices = {1,2,3,4,5}; // 4
    //vector<int> prices = {7,6,4,3,1};
    vector<int> prices = {3,2,6,5,0,3};

    std::cout << sol.maxProfit(prices) << std::endl;
    return 0;
}
