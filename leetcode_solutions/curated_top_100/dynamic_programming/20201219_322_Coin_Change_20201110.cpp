//
//You are given coins of different denominations and a total amount of money amount. Write a function to compute the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.
//
//You may assume that you have an infinite number of each kind of coin.
//
// 
//
//Example 1:
//
//Input: coins = [1,2,5], amount = 11
//Output: 3
//Explanation: 11 = 5 + 5 + 1
//Example 2:
//
//Input: coins = [2], amount = 3
//Output: -1
//Example 3:
//
//Input: coins = [1], amount = 0
//Output: 0
//Example 4:
//
//Input: coins = [1], amount = 1
//Output: 1
//Example 5:
//
//Input: coins = [1], amount = 2
//Output: 2
// 
//
//Constraints:
//
//1 <= coins.length <= 12
//1 <= coins[i] <= 2^31 - 1
//0 <= amount <= 10^4

// 思路：
// 典型的背包问题，对于兑换值，每次选择一个coin进行兑换
// 然后就化解为子问题：amount - coin 如何兑换，
// 并且子问题可以共享，故可用动态规划去求解
//
// 需要特别注意的是，使用辅助数组时，需要先设定好初始值；
//
// 还有个需要做特殊处理的，是无法实现兑换的情形，需要做好
// 标记，这样之后遇到同样的子问题，不需要再次计算了！
#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
	void getChangeCoins(vector<int>& record, vector<int>& coins, int amount) {
		if (amount == 0) {
			return;
		}
		int remain = 0;
		int max = Maximum;
		for (auto & v : coins) {
			remain = amount - v;
			std::cout << "debug: " << amount << ", " << v << std::endl;
			if (remain < 0) {
				continue;
			}
			if (record[remain] ==  -1) {
				getChangeCoins(record, coins, remain);
			}

			if (record[remain] == Maximum) {
				continue;
			}
			if (record[remain] + 1 < max) {
				max = record[remain] + 1;
			}
		}

		record[amount] = max;
	}

    int coinChange(vector<int>& coins, int amount) {
		if (amount == 0) {
			return 0;
		}
		vector<int> record(amount+1, -1);
		record[0] = 0;
		for (auto & v: coins) {
			if (v < record.size()) 
				record[v] = 1;
		}
		

		getChangeCoins(record, coins, amount);

		return (record[amount] == Maximum ? -1 : record[amount]);
    }
public:
    const int Maximum = (unsigned int)(1<<31) - 1;
};


int main() {
	vector<int> nums = {186,419,83,408};
	int amount = 6249;
	Solution s;
	std::cout << s.coinChange(nums, amount) << std::endl;
	return 0;
}
