//say you have an array for which the ith element is the price of a given stock on day i.
//
//If you were only permitted to complete at most one transaction (i.e., buy one and sell one share of the stock), design an algorithm to find the maximum profit.
//
//Note that you cannot sell a stock before you buy one.
//
//Example 1:
//
//Input: [7,1,5,3,6,4]
//Output: 5
//Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
//             Not 7-1 = 6, as selling price needs to be larger than buying price.
//Example 2:
//
//Input: [7,6,4,3,1]
//Output: 0
//Explanation: In this case, no transaction is done, i.e. max profit = 0.
//
//来源：力扣（LeetCode）
//链接：https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock
//著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
//

// 解题思路：
// 这种题目显然不能暴力求解，buy和sell，因为都只能操作一次，
// 也就限定了利润求解针对任一一个pair，满足：
// buy的价格越低利润越大！！！
// 所以遍历数组的过程中，一边求解profit，一边寻找最低的buy价格。
#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
		if (prices.size() < 2) {
			return 0;
		}

		int buy = prices[0];
		int sell = 0;
		int profit = 0;

		for (auto p: prices) {
			sell = p;
			if (sell - buy > profit) {
				profit = sell - buy;
			}

			if (p < buy) { // buy价格越低，profit才可能越大
				buy = p;
			}
		}

		return profit;
    }
};

int main() {
	Solution s;
	vector<int> prices = {7,6,4,3,1};
	std::cout << s.maxProfit(prices) << std::endl;
	return 0;
}
