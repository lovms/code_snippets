/*
 * 本题暴力枚举的方法是超时的，对于m*n的矩阵而言，复杂度为O(m^2 * n^2)。
 *
 * 计算子矩阵的元素和，基本上都要使用前缀和来避免重复累加计算，这个是基本的算法素养，无须多言！
 *
 * 本题优化的思路，基于对一维问题的考察，即找到一个数组的连续子数组的最大不超过K的和。
 *
 * 基于前缀和的计算，当我们考察第j个元素的前缀和sum_i时，我们希望在它之前的前缀和中找到最小的sum_j,
 * 满足 j < i，并且 sum_i - sum_j <=K。因此，如果通过遍历来找到这个sum_j，时间复杂度其实还是O(n)或者O(m) （取决于限定上下界还是左右界）
 * 所以，问题的关键在于将 {sum_0, sum_1, ..., sum_i-1} 维护成一个有序数组，从而可以利用二分查找在O(logn)的时间内找到！！！
 *
 * 下面的实现中，我直接用遍历方法，没有维护有序数组，也是AC了！！！但我觉得，时间复杂度并没有降低，可能是线性时间减少了？？
 */
#include <iostream>
#include <vector>
#define S_INT_MIN 0x80000000
using std::vector;

class Solution {
public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
		int rows = matrix.size();
		if (rows <=0 ) {
			return 0;
		}
		int cols = matrix[0].size();
		vector<vector<int>> cumulatedSum(rows, vector<int>(cols, 0));
        for (int j = 0; j < cols; j++) {
			for (int i = 0; i < rows; i++) {
				if (i==0) {
					cumulatedSum[0][j] = matrix[0][j];
				} else {
					cumulatedSum[i][j] = cumulatedSum[i-1][j] + matrix[i][j];
				}
			}
		}

		/*
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				std::cout << cumulatedSum[i][j] << " ";
			}
			std::cout << std::endl;
		}
		*/

		int max = 0x80000000;
		int lowerBound = 0;
		int colSum = 0;
		int rowSum = 0;
		vector<int> presum;
		for (int i = 0; i < rows; i++) {
			for (int row_step = 0; i+row_step <rows; ++ row_step) {
				rowSum = 0;
				presum.push_back(rowSum);
				for (int j = 0; j < cols; j++) {
					if (i == 0) {
						colSum = cumulatedSum[row_step][j];
					} else {
						colSum = cumulatedSum[i+row_step][j] - cumulatedSum[i-1][j];
					}

					rowSum = rowSum + colSum;
					//std::cout << "mark1: (rowSum:" << rowSum << "), (colSum:" << colSum  << ")" << std::endl;
					int lowerBound = rowSum - k;
					int preMin = 0x7FFFFFFF;
					for (int k = 0; k < presum.size(); k++) {
						if (presum[k] >= lowerBound && presum[k] < preMin) {
							preMin = presum[k];
						}
					}
					//std::cout << "debug1: i:" << i << ", row_step: " << row_step << ", col: " << j << ", pre: " << preMin << ", now: " << rowSum << ", lowerBound: " << lowerBound << std::endl;
					if (rowSum == k) {
						return k;
					} 
					if (preMin!=0x7FFFFFFF && rowSum - preMin > max) {
						max = rowSum - preMin;
						//std::cout << "debug2: " << max << std::endl;
					}

					presum.emplace_back(rowSum);
				}
			    presum.clear();
			}

		}

		return max;
    }
 
};

int main() {
	Solution sol;
	vector<vector<int>> matrix;
	/*
	 * Input: matrix = [[1,0,1],[0,-2,3]], k = 2
	 * Output: 2
	 * Explanation: Because the sum of the blue rectangle [[0, 1], [-2, 3]] is 2, and 2 is the max number no larger than k (k = 2).
	 */

	/*
	vector<int> row1 = {1,0,1};
	vector<int> row2 = {0,-2,3};
	matrix.push_back(row1);
	matrix.push_back(row2);
	int k = 2;
	*/

	/*
	 * Input: matrix = [[2,2,-1]], k = 3
	 * Output: 3
	 */

	vector<int> row1 = {2,2,-1};
	matrix.push_back(row1);
    int k = 0;

	/*
	 * case 3: 
	 * output: 2
	 */

	/*
	vector<int> row1 = {5,-4,-3,4};
	vector<int> row2 = {-3,-4,4,5};
	vector<int> row3 = {5,1,5,-4};
	matrix.push_back(row1);
	matrix.push_back(row2);
	matrix.push_back(row3);
    int k = 3;
	*/
	std::cout << sol.maxSumSubmatrix(matrix, k) << std::endl;
	return 0;
}
