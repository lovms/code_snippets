/*
 * 下述实现基于一个超时的版本Maximal_Rectangle.rejected.cc 重新思考得来
 *
 * 原来的想法是围绕'0'元素，将矩阵分割成上下左右4个子矩阵进行递归超时，子问题太多不好优化。
 *
 *
 * 该问题要求包含'1'元素的矩形的面积，观察发现是一个局部问题。直觉上，对于任何包含'1'元素
 * 的区域，我们只要知道'0'元素的位置，就可以在局部范围内求解问题。
 *
 * 因此，我们将问题改成：求解元素'1'为右下角的矩形的最大面积，
 * 所以，我们需要先计算每个'1'元素上下最近的非'0'长度，可以通过行遍历、列遍历来实现。
 *
 * 基于上述基本信息，就可以进行局部求解，需要注意计算顺序，对于任一个'1'元素，从右往左，
 * 或者从下到上来遍历计算。从右往左遍历，需要记下最大的垂直方向的边长；
 * 从下到上遍历时，需要记下最大的水平方向的边长。
 */

#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <unordered_map>

using std::vector;
using std::tuple;
using std::unordered_map;
using std::string;
typedef tuple<int, int> Point;

class Solution {
public:
	Solution(): globalMaxRec(0) {}
	struct Side {
		int toLeft;
		int toUp;
		int area;
		Side() {
			toLeft = 0;
			toUp = 0;
			area = 0;
		}
	};

    int maximalRectangle(vector<vector<char>>& matrix) {
		if (matrix.size() == 0) {
			return 0;
		}
		int rows = matrix.size();
		int cols = matrix[0].size();

		vector<vector<Side>> distance(rows, vector<Side>(cols, Side()));

		// calc side distance to the left and to the up
        for (int i = 0; i < rows; ++i) {
		    int zeroIndex = -1;
			for (int j = 0; j < cols; ++j) {
		        if (matrix[i][j] == '0') {
				    zeroIndex = j;
				}
				distance[i][j].toLeft = j - zeroIndex;
			}
		}

		for (int j = 0; j < cols; ++j) {
		    int zeroIndex = -1;
			for (int i = 0; i < rows; ++i) {
			    if (matrix[i][j] == '0') {
				    zeroIndex = i;
				}
				distance[i][j].toUp = i - zeroIndex;
			}
		}

		//
		int maxArea = 0;
		int curArea = 0;
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				if (distance[i][j].toLeft * distance[i][j].toUp < globalMaxRec) {
					//pruning
					continue;
				}
				if (distance[i][j].toLeft  > distance[i][j].toUp) {
					maxArea = 0;
					int leftDis = distance[i][j].toLeft;
					for (int u = 0; u < distance[i][j].toUp; ++u) {
						if (distance[i-u][j].toLeft < leftDis) {
							leftDis = distance[i-u][j].toLeft;
						}
						curArea = leftDis * (u+1);
						if (curArea > maxArea) {
							maxArea = curArea;
						}
					}
				} else {
					maxArea = 0;
					int upDis = distance[i][j].toUp;
					for (int l = 0; l < distance[i][j].toLeft; ++l) {
						if (distance[i][j-l].toUp < upDis) {
							upDis = distance[i][j-l].toUp;
						}
						curArea = upDis * (l+1);
						if (curArea > maxArea) {
							maxArea = curArea;
						}
					}
				}
				if (globalMaxRec < maxArea) {
					globalMaxRec = maxArea;
				}
			}
		}
		return globalMaxRec;
    }

private:
	int globalMaxRec;

};

int main () {
	//Input: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
    //Output: 6
	
	/*
	vector<vector<char>> matrix(4, vector<char>(5, '1'));
	matrix[0][1] = '0';
	matrix[0][3] = '0';
	matrix[0][4] = '0';
	matrix[1][1] = '0';
	matrix[3][1] = '0';
	matrix[3][2] = '0';
	matrix[3][4] = '0';
	*/

	vector<vector<char>> matrix(1, vector<char>(1, '1'));
	Solution sol;
	std::cout << sol.maximalRectangle(matrix) << std::endl;

	return 0;
}
