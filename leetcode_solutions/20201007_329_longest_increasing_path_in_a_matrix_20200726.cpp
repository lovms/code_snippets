//Given an integer matrix, find the length of the longest increasing path.
//
//From each cell, you can either move to four directions: left, right, up or down. You may NOT move diagonally or move outside of the boundary (i.e. wrap-around is not allowed).
//
//Example 1:
//
//Input: nums = 
//[
//  [9,9,4],
//  [6,6,8],
//  [2,1,1]
//] 
//Output: 4 
//Explanation: The longest increasing path is [1, 2, 6, 9].
//Example 2:
//
//Input: nums = 
//[
//  [3,4,5],
//  [3,2,6],
//  [2,2,1]
//] 
//Output: 4 
//Explanation: The longest increasing path is [3, 4, 5, 6]. Moving diagonally is not allowed.
//
//来源：力扣（LeetCode）
//链接：https://leetcode-cn.com/problems/longest-increasing-path-in-a-matrix
//著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>

using std::vector;
using std::string;
using std::ifstream;

class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
		if (matrix.size() == 0) {
			return 0;
		}
        vector<vector<int>> pathLen(matrix.size(), vector<int>(matrix[0].size(), 0));

        int steps = matrix.size() * matrix[0].size();
        int longestPath = 0;
		bool change = false;
        while (steps > 0) {
			change = false;
            for (int i = 0; i < matrix.size(); i++) {
                for (int j = 0; j < matrix[i].size(); j++) {
                    int path = 0;
                    if (j-1>=0 &&   // number on the left
                        matrix[i][j-1] < matrix[i][j]) {
                        if (pathLen[i][j] < pathLen[i][j-1]+1) {
                            pathLen[i][j] = pathLen[i][j-1]+1;
							change = true;
                        }
                    }
                    if (j+1 < matrix[i].size() && // number on the right
                        matrix[i][j+1] < matrix[i][j]) {
                        if (pathLen[i][j] < pathLen[i][j+1]+1) {
                            pathLen[i][j] = pathLen[i][j+1]+1;
							change = true;
                        }
                    }

                    if (i-1>=0 && //number on the top
                        matrix[i-1][j] < matrix[i][j]) {
                        if (pathLen[i][j] < pathLen[i-1][j]+1) {
                            pathLen[i][j] = pathLen[i-1][j]+1;
							change = true;
                        }
                    }

                    if (i+1<matrix.size() &&
                        matrix[i+1][j] < matrix[i][j]) {
                        if (pathLen[i][j] < pathLen[i+1][j]+1) {
                            pathLen[i][j] = pathLen[i+1][j]+1;
							change = true;
                        }
                    }

                    if (pathLen[i][j] > longestPath) {
                        longestPath = pathLen[i][j];
                    }
                }
            }

			// Get convergence when no change happens in an iteration
			// Important for early stopping, otherwise it's easy to get overtime!
			if (!change) {
				break;
			}
            steps--;
        }

        return longestPath+1;
    }
};

int main() {
    Solution s;

    vector<vector<int>> matrix;

    std::ifstream inf;
    inf.open("./input3");
    if (inf.is_open()) {
        std::stringstream ssm;
        string line;
        int row;
        while (std::getline(inf, line)) {
            ssm.clear();
            ssm << line;
            //std::cout << "mark1: " << line << std::endl;
            vector<int> tmp;
            int p;
            while (ssm >> p) {
                //std::cout << "mark2: " << p << std::endl;
                tmp.push_back(p);
            }
            matrix.push_back(tmp);
        }
    }

    for (auto& row:matrix) {
        for (auto& v: row) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }

    std::cout << s.longestIncreasingPath(matrix) << std::endl;
    return 0;
}
