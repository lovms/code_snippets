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
