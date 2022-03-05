/*
 * 下面的实现超时了，
 * 大致的思路是对每一个为'0'的元素，对其上下左右分割成4个子矩阵，然后递归分割求解，
 * 如果子矩阵不包含'0'元素（提前遍历保存所有'0'元素坐标），则直接计算矩阵面积返回。
 * 递归分割矩阵，会产生很多公共的子矩阵，因此，使用表存储已经计算过的子矩阵。
 *
 * 该思路非常朴素和直接，因为问题要求的矩阵面积（只包含'1')，所以，遇到'0'元素都不去
 * 考虑，因而考虑的部分就是把这个点扣除的上下左右4个子矩阵了。
 *
 * 超时我认为有两个原因:
 * 1) 如果原矩阵中包含的'0'元素很多，那分割产生的子矩阵过多，递归也会很深；
 * 2) 判断一个子矩阵是否包含'0'元素不是一件容易的事情，遍历判读所有'0'元素耗时；
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
	struct Point {
		int a;
		int b;
		Point() {
			a = 0;
			b = 0;
		}
		Point(int pa, int pb) :
			a(pa), b(pb) {}
	};

    int maximalRectangle(vector<vector<char>>& matrix) {
		if (matrix.size() == 0) {
			return 0;
		}
		vector<Point> zeroPoints;
		int rows = matrix.size();
		int cols = matrix[0].size();
		for (int i = 0; i < rows; ++i)
			for (int j = 0; j < cols; ++j) {
				if (matrix[i][j] == '0') {
					zeroPoints.emplace_back(i, j);
				}
			}
	    
		unordered_map<string, int> rectangleMaxInnerArea;

		Point upLeft(0, 0);
		Point downRight(rows-1, cols-1);

		int res = findMaxRect(upLeft, downRight, zeroPoints, rectangleMaxInnerArea);

		return res;
    }

	bool checkPointInclusion(const Point& upLeft, const Point& downRight, const Point& zp) {
		if ((zp.a >= upLeft.a && zp.a <= downRight.a) &&
			(zp.b >= upLeft.b && zp.b <= downRight.b)) {
			return true;
		}

		return false;
	}

	int findMaxRect(Point& upLeft, Point& downRight, 
			        vector<Point>& zeroPoints,
					unordered_map<string, int>& rectangleMaxInnerArea) {
		string recSign = std::to_string(upLeft.a) + "_" + std::to_string(upLeft.b) + "_" +
			             std::to_string(downRight.a) + "_" + std::to_string(downRight.b);
		auto area = rectangleMaxInnerArea.find(recSign);
		if (area != rectangleMaxInnerArea.end()) {
			return area->second;
		}

		int recArea =  (downRight.a - upLeft.a + 1) * (downRight.b - upLeft.b + 1);
		if (recArea < globalMaxRec) {
			return 0;
		}
		int maxRec = 0;
		for (auto const& zp : zeroPoints) {
			if (checkPointInclusion(upLeft, downRight, zp)) {
				int upRec, downRec, leftRec, rightRec = 0;
				if (zp.a > upLeft.a) {
					Point tp(zp.a-1, downRight.b);
					upRec = findMaxRect(upLeft, tp, zeroPoints, rectangleMaxInnerArea);
					maxRec = maxRec < upRec ? upRec : maxRec;
				}
				if (zp.a < downRight.a) {
					Point tp(zp.a+1, upLeft.b);
					downRec = findMaxRect(tp, downRight, zeroPoints, rectangleMaxInnerArea);
					maxRec = maxRec < downRec ? downRec : maxRec;
				}
				if (zp.b > upLeft.b) {
					Point tp(downRight.a, zp.b-1);
					leftRec = findMaxRect(upLeft, tp, zeroPoints, rectangleMaxInnerArea);
					maxRec = maxRec < leftRec ? leftRec : maxRec;
				}
				if (zp.b < downRight.b) {
					Point tp(upLeft.a, zp.b+1);
					rightRec = findMaxRect(tp, downRight, zeroPoints, rectangleMaxInnerArea);
					maxRec = maxRec < rightRec ? rightRec : maxRec;
				}
				rectangleMaxInnerArea[recSign] = maxRec;
				if (maxRec > globalMaxRec) {
					globalMaxRec = maxRec;
				}
					      
				return maxRec;
			}
		}
		maxRec= recArea;
		rectangleMaxInnerArea[recSign] = maxRec;
		if (maxRec > globalMaxRec) {
			globalMaxRec = maxRec;
		}
		return maxRec;
	}
private:
	int globalMaxRec;

};

int main () {
	//Input: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
    //Output: 6
	
	vector<vector<char>> matrix(4, vector<char>(5, '1'));
	matrix[0][1] = '0';
	matrix[0][3] = '0';
	matrix[0][4] = '0';
	matrix[1][1] = '0';
	matrix[3][1] = '0';
	matrix[3][2] = '0';
	matrix[3][4] = '0';

	//vector<vector<char>> matrix(1, vector<char>(2, '0'));
	Solution sol;
	std::cout << sol.maximalRectangle(matrix) << std::endl;


	return 0;
}
