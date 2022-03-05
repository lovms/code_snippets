/*
 * 本题无法用DP求解。
 *
 * 见过相似的题目：给定一个数组，找到最大的连续子数组的和。
 * 这个问题只要保证子数组的和是单调递增就可以了，因此满足最优子结构。
 *
 * 但本题中由于限制了子矩阵的最大和不能超过K。因此，我想了半天，
 * 也没想到最优子结构，其实是不存在！！！
 *
 * 下方的求解是暴力求解，超时了，复杂度是O(n^4)的，定义所有的子矩阵。
 * 看评论，有说将vector换成数组就能过，但这样过显然白花时间去思考这道题了。
 *
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
        for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				if (j==0) {
					cumulatedSum[i][0] = matrix[i][0];
				} else {
					cumulatedSum[i][j] = cumulatedSum[i][j-1] + matrix[i][j];
				}
			}
		}

		for (int i=1; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				cumulatedSum[i][j] += cumulatedSum[i-1][j];
			}
		}

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				std::cout << cumulatedSum[i][j] << " ";
			}
			std::cout << std::endl;
		}

		int max = 0x80000000;
		for (int i = 0; i < rows; i++) {
			for (int row_step = 0; i+row_step <rows; ++ row_step) {
				for (int j = 0; j < cols; j++) {
					for (int col_step = 0; j+col_step < cols; ++col_step) {
						int rectangleSum = cumulatedSum[i+row_step][j+col_step];
						if (j-1 >= 0) {
							rectangleSum -= cumulatedSum[i+row_step][j-1];
						}
						if (i-1 >= 0) {
							rectangleSum -= cumulatedSum[i-1][j+col_step];
						}
						if (i-1 >= 0 && j-1 >= 0) {
							rectangleSum += cumulatedSum[i-1][j-1];
						}
						//std::cout << "debug1: (i,j,i+row_step, j+col_step) " << i << ", " <<  j << ", " << i+row_step << ", " << j+col_step << " | " << rectangleSum << std::endl;
						if (i==1 && j==0 && i+row_step==2 && j+col_step==2) {
							std::cout << "debug2: " << cumulatedSum[i+row_step][j+col_step] << "\t"
								                    << cumulatedSum[i-1][j+col_step] << std::endl;
						}
						if (rectangleSum <= k && rectangleSum > max) {
							max = rectangleSum;
						}
					}
				}
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

	/*
	vector<int> row1 = {2,2,-1};
	matrix.push_back(row1);
	int k = 3;
	*/

	/*
	 * case 3:
	 */

	vector<int> row1 = {5,-4,-3,4};
	vector<int> row2 = {-3,-4,4,5};
	vector<int> row3 = {5,1,5,-4};
	matrix.push_back(row1);
	matrix.push_back(row2);
	matrix.push_back(row3);
    int k = 8;
	std::cout << sol.maxSumSubmatrix(matrix, k) << std::endl;
	return 0;
}
