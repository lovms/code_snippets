#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using std::vector;
using std::string;
using std::unordered_map;

class Solution {
public:
    int maxCoins(vector<int>& nums) {
		int n = nums.size();
		vector<int> numbers;
		numbers.push_back(1);
		numbers.insert(numbers.end(), nums.begin(), nums.end());
		numbers.push_back(1);
		int sz = numbers.size();
		vector<vector<int>> dp(sz, vector<int>(sz, 0));

		for (int step = 1; step <= n; ++step) {
			for (int i = 0; i+step+1 < sz; ++i) {
				int j = i+step+1;
				for (int k = i+1; k <= i+step; ++k) {
				    int coins = dp[i][k] + numbers[i]*numbers[k]*numbers[j] + dp[k][j];      // (i, k, i+step+1)
					if (coins > dp[i][j]) {
						dp[i][j] = coins;
					}
				}
			}
		}
		return dp[0][sz-1];
    }
};

int main () {
	Solution sol;
	/* Input: nums = [3,1,5,8]
     * Output: 167
	 * Explanation:
	 * nums = [3,1,5,8] --> [3,5,8] --> [3,8] --> [8] --> []
	 * coins =  3*1*5    +   3*5*8   +  1*3*8  + 1*8*1 = 167
	 */
    //vector<int> nums = {3,1,5,8};
	//vector<int> nums = {3,1,5,9,7,8};
	//vector<int> nums = {7,9,8,0,7,1,3,5,5,2,3};
	vector<int> nums = {8,2,6,8,9,8,1,4,1,5,3,0,7,7,0,4,2,2,5,5};
	std::cout << sol.maxCoins(nums) << std::endl;

	return 0;
}
