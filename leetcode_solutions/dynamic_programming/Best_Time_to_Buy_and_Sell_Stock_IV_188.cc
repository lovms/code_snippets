/*
 * 相比于III，本题将交易次数设置成了变量，因此，状态总数由 3*2 增加到 (k+1)*2了
 * 状态转移公式就2个：
 *
 * dp_k_0[i] = max(dp_k_0[i-1], dp_k-1_1[i-1] + prices[i])
 *
 * dp_k_1[i] = max(dp_k_1[i-1], dp_k-1_0[i-1] - prices[i])
 *
 * 如果不实用滚动数组技巧，那么需要（k+1)*2个数组，或者是三维数组 #days * (k+1) * 2
 *
 * 1）注意dp_0_0和 dp_k_1这两个状态其实是无用的，最终要看状态 dp_k_0[i]
 * 2) 同样需要注意状态初始化
 */
#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        if (k == 0 || prices.size() <= 1) {
            return 0;
        }
        vector<vector<int>> dp(k+1, vector<int>(2, 0));

        for (int i = 0; i < k; ++i) {
            dp[i][0] = 0;
            dp[i][1] = -prices[0];
        }

        for (int i = 1; i < prices.size(); ++i) {
            for (int p = 0; p <= k; ++p) {
                if (p>0) {
                    dp[p][0] = std::max(dp[p][0], dp[p-1][1] + prices[i]);
                }

                if (p < k) {
                    dp[p][1] = std::max(dp[p][1], dp[p][0] - prices[i]);
                }
            }
        }

        return dp[k][0];
    }
};

int main() {
    Solution sol;
    /*
    vector<int> prices = {2,4,1};
    int k = 2;
    */

    vector<int> prices = {3,2,6,5,0,3};
    int k = 2;

    std::cout << sol.maxProfit(k, prices) << std::endl;
    return 0;
}



//============================================================================================================
// 以下是我之前AC的结果，那时动态规划方法没有搞得太明白，实际上还是记忆化搜索的方法……我只记得当时写的很痛苦。
//
// 记忆化搜索的方法不好写，代码较复杂，写的不好容易出错，还容易超时，放在下面，供对比 (当时的想法还没写完……)
//
// 记忆化搜索方法要把握亮点：
// 1）需要遍历所有i-th天买入且j-th天卖出的情况，本题额外需要考虑交易数限制小于k；
// 2）重复计算的部分是： 对于所有在第j-th天卖出的情况，maxProfitOf(p, days[1+j ... n]) 都是重复的，不需要每次都计算，
//    其中p是剩余的可交易次数。
//============================================================================================================
/*
 * 这是一个系列，系列最初形态是有一次买卖。
 * 但本题已经可以允许多次买卖了，因此 
 */
#include <vector>
#include <iostream>
using std::vector;
class Solution {
public:
	Solution() : _maxProfit(0), _optK(-1)  {}
    int maxProfit(int k, vector<int>& prices) {
		int days = prices.size();
		vector<vector<int>> possibleProfit(days, vector<int>(days, 0));
		vector<vector<int>> maxProfits(k+1, vector<int>(days, -1));  // k * days

		for (int i = 0; i < days-1; ++i) {
			for (int j = i+1; j < days; ++j) {
				possibleProfit[i][j] = prices[j] - prices[i];
			}
		}

		for (int i = 0; i < possibleProfit.size(); ++i) {
			for (int j = 0; j < possibleProfit[0].size(); ++j) {
				std::cout << possibleProfit[i][j] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;

		int step = 0;
		int begin = 0;
		return runStockTrading(k, days, step, begin, maxProfits, possibleProfit);
    }
	int runStockTrading(int k, int days, int step, int begin, vector<vector<int>>& maxProfits, vector<vector<int>>& possibleProfit) {
		std::cout << "Debug 1: remain_steps:" << k-step << ", start_day:" << begin << std::endl;
		if (step >= k || begin >= days) {  // use up steps or days, then return 0
			return 0;
		}
		if (maxProfits[k-step][begin] != -1) {
			return maxProfits[k-step][begin];
		}

		int row = begin;
		if (row >= possibleProfit.size()) {
			return 0;
		}

		int cols = possibleProfit[0].size();
		int curMax = 0;
		int tmpProfit = 0;
		for (int j = row+1; j < cols; ++j) {
			if (possibleProfit[row][j] > 0) {
			    tmpProfit = possibleProfit[row][j] + runStockTrading(k, days, step+1, j+1, maxProfits, possibleProfit);
				if (tmpProfit > curMax) {
					curMax = tmpProfit;
				}
			}
		}
		//skip the $(begin) day without trade
		tmpProfit = runStockTrading(k, days, step, 1+begin, maxProfits, possibleProfit);
		if (tmpProfit > curMax) {
			curMax = tmpProfit;
		}

		maxProfits[k-step][begin] = curMax;
		std::cout << "Debug 2: remain_steps:" << k-step << ", start_day:" << begin << ", maxProfit: " << curMax << std::endl;
		return curMax;
	}

private:
	int _maxProfit;
	int _optK;
};

int main() {
	Solution sol;
	/* Input: k = 2, prices = [2,4,1]
     * Output: 2
	 * Explanation: Buy on day 1 (price = 2) and sell on day 2 (price = 4), profit = 4-2 = 2.
	 */

	/*
	int k = 2;
	vector<int> prices = {2,4,1};
	*/

	/* Input: k = 2, prices = [3,2,6,5,0,3]
     * Output: 7
     * Explanation: Buy on day 2 (price = 2) and sell on day 3 (price = 6), profit = 6-2 = 4. Then buy on day 5 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
	 */

	/*
	int k = 2;
	vector<int> prices= {3,2,6,5,0,3};
	*/

	/* Input: k = 2, prices = [3,3,5,0,0,3,1,4]
	 * Output: 6
	 */

	int k = 2;
	vector<int> prices = {3,3,5,0,0,3,1,4};

	std::cout << sol.maxProfit(k, prices) << std::endl;
	return 0;
}
