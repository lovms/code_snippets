/*
 * 本题说下我认为的3点思考关键点:
 * 1) 即便只有一个鸡蛋，本题也是有解的, 从第1层开始一层一层往上测试便可。所以当k=1时，minMove=n;
 *
 * 2) 一层层网上测试显然很低效，二分法一次就能减少一半的测试量！ 一般来讲，如果在第x>1层（共n层）测试，会有两种结果：
 *    --> 如果鸡蛋每碎，则在n-x层中，继续用k个鸡蛋测试，记作 dp(k, n-x)；
 *    --> 如果鸡蛋没有碎，则在x-1层中，继续用k-1个鸡蛋测试，记作 dp(k-1, x-1)；
 *    这里有个关键点，就是子问题只需要层高，并不在乎从哪一层开始，策略是一样的，这样上述状态转移到的子问题才能是重复子问题，
 *    因此使用dp求解才会更高效。
 *
 *    所以从[1...n] 用k个鸡蛋测试，和 从[ m ... m+n-1]用k个鸡蛋测试，策略是一样的。
 *
 * 3) 如果鸡蛋足够多，那二分法就是最优解，正因为鸡蛋不是无限多，所以最优点才可能不在二分点。
 *    直观上可以这样理解，如果层数是2*n+1, 第一层尝试在n+1层扔鸡蛋，后续的二个子问题的层高都是n，
 *    但显然dp(k-1, n)的鸡蛋比 dp(k, 2*n+1-(n_1)) = dp(k,n)的鸡蛋要少一个，所以前者很有可能move会更多！
 *    二分对两个子问题不是最公平的。
 *
 */
#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

typedef vector<vector<int>> DDA; // double-dimentional array

class Solution {
public:
    int superEggDrop(int k, int n) {
		DDA dp(k+1, vector<int>(n+1, 0));

		for (int i = 1; i <= k; ++i) {
			dp[i][1] = 1;
		}
		for (int j = 1; j <= n; ++j) {
			dp[1][j] = j;
		}

		int result = splitFind_v3(1, n, k, dp);
		return result;
    }

	/* 
	 * 解法二：
	 *
	 * 每一个区间的第一次尝试使用了二分查找在楼层firstTryFloor去提升效率，
	 * 但由于二分查找并不总是最优的，但如果存在更优的解，那么一定是小于firstTryFloor的！
	 * 所以从firstTryFoor-1层往下尝试，以便找到更优的解。这种线性的尝试导致效率非常低。
	 *
	 * 超时！
	 */
	int splitFind_v2(int low, int high, int k, DDA& dp) {
		if (high < low) return 0;
		int floors = high - low + 1;

		//std::cout << "mark1: low|" << low << ", high|" << high << ", k|" << k << std::endl;
		if (dp[k][floors] != 0) {
			//std::cout << "debug1 result: k|floors" << k << ", " << floors << " --> " << dp[k][floors] << std::endl;
			return dp[k][floors];
		}

		int firstTryFloor = (low + high) / 2; 
		int localMin = 1 + std::max(splitFind_v2(low, firstTryFloor-1, k-1, dp), splitFind_v2(firstTryFloor+1, high, k, dp));

		for (int iFloor = firstTryFloor-1; iFloor >= low; --iFloor) {
			int tmpResult = 1 + std::max(splitFind_v2(low, iFloor-1, k-1, dp), splitFind_v2(iFloor+1, high, k, dp));
			if (localMin < tmpResult) {
				break;
			}
			localMin = tmpResult;
		}
		dp[k][floors] = localMin;
		//std::cout << "mark3 result: " << localMin << std::endl;
		return localMin;
	}

	/*
	 * 解法三：
	 *
	 * 解法三我在思考中其实也考虑到，不过没有考虑得特别清楚。
	 * 当在状态dp(k, n)时尝试x层，之后分解成两个子问题：
	 * 1）如果鸡蛋碎了，则需要往更低的楼层找 T1 = dp(k-1, x-1)
	 * 2）如果鸡蛋没碎，则需要往更高的楼层找 T2 = dp(k, n-x)
	 *
	 * 为了提升效率，使用二分查找得到第一次尝试楼层：x = n/2,
	 * 但我们知道这未必是最优解，所以需要尝试其他楼层，但怎么找到
	 * 其他尝试楼层呢？？这是关键，我这块没搞清楚，所以解法二超时了，
	 *
	 * 但其实我们可以根据T1 和 T2的大小关系，来寻找其他可以尝试的楼层：
	 * 1）如果T1 > T2，说明低楼层需要花更多的步骤，我们需要把x定得更低点，
	 *    但多低呢，不能从x往下一个个尝试了，直接二分，所以第一次尝试楼层
	 *    应该是 x' = (x-1)/2;
	 * 2) 如果T1 < T2, 说明高楼层花了更多的步骤，我们需要把x定得更高点，
	 *    所以第一次尝试楼层改为 x' = (n-x)/2
	 * 
	 * 在看官方题解之前，我没搞清楚为啥这样做就能得到最优解，我有点担心，
	 * 所以，我使用了解法二。官方题解用将dp(k, n-x)单调增函数，dp(k-1, x-1)单调减函数
	 * 的交点位置即 T1=T2是理论最优解，对x是离散的情况，最优解应该在T1=T2附近。
	 *
	 * 所以，我们用这里用二分查找并不是超找一个数组中等于某个值的元素，而是在解决一个类似，
	 * 找到数组中的某个index，使得其分割的两个数组和最接近！其实也可以用二分查找！！！
	 *
	 * 所以，每次理解二分查找都有惊喜！！
	 *
	 *
	 */
	int splitFind_v3(int from, int to, int k, DDA& dp) {
		if (from > to) return 0;
		int floors = to - from + 1;
		if (dp[k][floors] != 0) {
			std::cout << "mark1: k|" << k << ", f|" << floors << " --> " << dp[k][floors] << std::endl;
			return dp[k][floors];
		}

		int high = to, low =from;
		int t1=0, t2=0;
		while (high >= low) {   //
			int median = (high + low) / 2;

			t1 = splitFind_v3(from, median-1, k-1, dp);
			t2 = splitFind_v3(median+1, to, k, dp);

			std::cout << "mark2: from|" << from << ", to|" << to << ", median|" << median << "--> " << "t1|t2: " << t1 << "|" << t2 << std::endl;
			std::cout << "mark3: low|" << low << ", high|" << high << std::endl;
			if (t1 < t2) {
				low = median + 1;
			} else if (t1 > t2) {
				high = median - 1;
			} else {
				break;
			}
		}

		dp[k][floors] = 1 + std::max(t1, t2);
		return dp[k][floors];
	}

};

int main() {
	Solution sol;
	//int k=2, n=6; //3
	//int k=3, n=14;
	//int k=8, n=10000;
	int k=2, n=10;
	std::cout << sol.superEggDrop(k, n) << std::endl;
	return 0;
}
