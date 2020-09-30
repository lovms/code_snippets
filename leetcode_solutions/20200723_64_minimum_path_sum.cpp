//Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right which minimizes the sum of all numbers along its path.
//
//Note: You can only move either down or right at any point in time.
//
//Example:
//
//Input:
//[
//  [1,3,1],
//  [1,5,1],
//  [4,2,1]
//]
//Output: 7
//Explanation: Because the path 1→3→1→1→1 minimizes the sum.
//
//来源：力扣（LeetCode）
//链接：https://leetcode-cn.com/problems/minimum-path-sum
//著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

#include <iostream>
#include <string>
#include <vector>

using std::vector;

class Solution {
public:
	int searchPath(int i, int j, vector<vector<int>> & dist, vector<vector<int>>& grid) {
		std::cout << "debug2: i-j|" << i << "-" << j << std::endl;
		int row = dist.size();
		int col = dist[row-1].size();
		std::cout << "debug1: row " << row << ", col " << col << std::endl;
		if (i == row-1 && j == col-1) {
			std::cout << "debug3: " << grid[i][j] << std::endl;
			return grid[i][j];
		}

		if (dist[i][j] != 0) {
			return dist[i][j];
		}

		int l = 0x7FFFFFFF;
		int r = 0x7FFFFFFF;
		if (i+1 < row) {
			l = searchPath(i+1, j, dist, grid);
		} 
		if (j+1 < col) {
		    r = searchPath(i, j+1, dist, grid);
		}
		dist[i][j] = grid[i][j]+ std::min(l, r);
		return dist[i][j];
	}

    int minPathSum(vector<vector<int>>& grid) {
		vector<vector<int>> dist;
		for (auto & row : grid) {
			dist.push_back(vector<int>(row.size(), 0));
		}

		return searchPath(0, 0, dist, grid);

    }
};

int main() {
	Solution sol;
	vector<vector<int>> grid;
	grid.emplace_back(vector<int>({1}));
	//grid.emplace_back(vector<int>({1,5,1}));
	//grid.emplace_back(vector<int>({4,2,1}));
	std::cout << sol.minPathSum(grid) << std::endl;;
	return 0;
}
