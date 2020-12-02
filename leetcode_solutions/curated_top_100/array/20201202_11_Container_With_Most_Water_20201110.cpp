//Given n non-negative integers a1, a2, ..., an , where each represents a point at coordinate (i, ai). n vertical lines are drawn such that the two endpoints of the line i is at (i, ai) and (i, 0). Find two lines, which, together with the x-axis forms a container, such that the container contains the most water.
//
//Notice that you may not slant the container.
//
// 
//
//Example 1:
//
//
//Input: height = [1,8,6,2,5,4,8,3,7]
//Output: 49
//Explanation: The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. In this case, the max area of water (blue section) the container can contain is 49.
//Example 2:
//
//Input: height = [1,1]
//Output: 1
//Example 3:
//
//Input: height = [4,3,2,1,4]
//Output: 16
//Example 4:
//
//Input: height = [1,2,1]
//Output: 2
// 
//
//Constraints:
//
//n = height.length
//2 <= n <= 3 * 104
//0 <= height[i] <= 3 * 104

// 思路：
// 1. 如果需要暴力比较所有的containers，那么需要1*2*3*4*...*(n-1)
// 2. 考虑第0条垂直边，当它和第j条边组成container时，并且满足
//    height[0] < height[j]时，对于任意第i条边(i<j)，都不会比<0,j>
//    组成的container面积大了，因为高度不会大于height[0]了，但底会一直变短
#include <iostream>
#include <vector>
using std::vector;
class Solution {
public:
        int longerSide(int i, int j) {
                return (i<j ? i : j);
        }

    int maxArea(vector<int>& height) {
                if (height.size() == 2) {
                        return longerSide(height[0], height[1]);
                }

                int left  = 0;
                int right = height.size() - 1;

        int maxArea = (right - left) * longerSide(height[left], height[right]);
                int i = left;
                int j = right;
                std::cout << "start: " << i << "," << j << std::endl;

                int curArea = 0;
                while (i < j) {
                        if (height[i] <= height[j]) {
                                i++;
                                curArea = (j-i) * longerSide(height[i], height[j]);
                                std::cout << "mark1: " << i << ", " << j << " |" << curArea << std::endl;
                                if (curArea > maxArea) {
                                        maxArea = curArea;
                                }
                        }
                        if (height[i] > height[j]) {
                                j--;
                                curArea = (j-i) * longerSide(height[i], height[j]);
                                std::cout << i << ", " << j << " |" << curArea << std::endl;
                                if (curArea > maxArea) {
                                        maxArea = curArea;
                                }
                        }
                }
                return maxArea;
    }
};

int main() {
        Test t;
        //vector<int> height = {1,8,6,2,5,4,8,3,7};
        //vector<int> height = {4,3,2,1,4};
        vector<int> height = {1,1};
        std::cout << t.maxArea(height) << std::endl;
        return 0;
}
