/*
 * 本题简单想一下就会发现存在大量的重复子问题，似乎也比较好用dp来求解。
 *
 * 我一开始想到的子问题划分是通过连接任意两个不相邻的节点，从而得到2个互不相关的多边形子问题。
 * 父问题的解可以通过所有划分的2个子问题的各自的最优（最小）解相加求得。这种简单的想法背后存在
 * 的主要问题是：随着子问题的划分不断递进，子问题会很难描述。
 *
 * 实际上如果使用区间dp的思想去思考，就会产生一种更加合理的划分。
 *
 * 划分子问题最终需要有利于求解父问题，更广泛的思考之后，这是个区间dp的问题，子问题由一组相邻的若干条边
 * 组成：i,i+1,...,j，然后i和j是确定连接的边，每次从 i < k < j中选择一个顶点组成三角形，同时将问题划分成
 *
 * i,...,k和 k,...,j两个子问题。
 *
 * 假设dp[i][j]就是 上述父问题的最小三角划分多边形的最小值，那么描述上面过程的动态方程就是：
 * dp[i][j] = Min_k( dp[i][k] + v[i]*v[k]*v[j] + dp[k][j] ), i < k <j
 *
 *
 * 另外，我这里的实现还是查表法的实现。 bottomUpDp则是自下而上的实现方法，需要注意为了能够组成三角形，
 * 这里step的最小值就是2。自下而上方法最重要的就是dp矩阵的初始化，初始化稍有差池，结果肯定不对了。
 */
#include <iostream>
#include <vector>

#define MAX_INT 0x7FFFFFFF

using std::vector;
class Solution {
public:
    int minScoreTriangulation(vector<int>& values) {
		/*自上而下查表法*/
		/*
		vector<vector<int>> dp(values.size(), vector<int>(values.size(), 0));
		triangulation(values, 0, values.size()-1, dp);
		return dp[0][values.size()-1];
		*/

		/*自下而上*/
		return bottomUpDp(values);
    }

	int triangulation(vector<int>& values, int i, int j, vector<vector<int>>& dp) {
		if (j - i < 2) {
			// adjacent nodes
			return 0;
		}
		if (dp[i][j] != 0) {
			//std::cout << "mark1: i|" << i << ", j|" << j << " --> " << dp[i][j] << std::endl;
			return dp[i][j];
		}

		if (j-i == 2) {
			dp[i][j] = values[i] * values[i+1] * values[i+2];
			//std::cout << "mark2: i|" << i << ", j|" << j << " --> " << dp[i][j] << std::endl;
			return dp[i][j];
		}
		int localMin = 1e+7;
		int twoTimes = values[i] * values[j];
		for (int k = i+1; k < j ; ++k) {
			int tmpResult = twoTimes * values[k] + triangulation(values, i, k, dp) + triangulation(values, k, j, dp);
			//std::cout << "debug: i|" << i << ", j|" << j << ", k|" << k << " --> " << tmpResult << std::endl;
			if (tmpResult < localMin) {
				localMin = tmpResult;
			}
		}
		//std::cout << "mark3: i|" << i << ", j|" << j << " --> " << dp[i][j] << std::endl;
		dp[i][j] = localMin;
		return dp[i][j];
	}

	/*自底向上的dp*/
	int bottomUpDp(vector<int>&values) {
		int n = values.size();
		vector<vector<int>> dp(n, vector<int>(n, 0));
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j)
				dp[i][j] = MAX_INT;
			if (i < n-1) {
		        dp[i][i+1] = 0;
			}
			dp[i][i] = 0;
        }

		int j = 0;
		for (int step = 2; step <= n-1; ++step) {
			for (int i = 0; i < n; ++i) {
                j = i+step;
				if (j >= n) continue;
				for (int k = i+1; k < j; ++k) { // i < k < j
					dp[i][j] = std::min(dp[i][j], dp[i][k] + values[i]*values[k]*values[j] + dp[k][j]);

				}
			}
		}
		return dp[0][n-1];
	}

};

int main() {
	Solution sol;
	//vector<int> values = {1,2,3};
	//vector<int> values = {3,7,4,5};
	vector<int> values = {1,3,1,4,1,5};
	std::cout << sol.minScoreTriangulation(values) << std::endl;
	return 0;
}
