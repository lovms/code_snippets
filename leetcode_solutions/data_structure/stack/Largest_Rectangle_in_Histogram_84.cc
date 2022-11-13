/* 
 * 一开始觉得应该用dp来解决，但真到写状态转移方程时，
 * 才发现不能用dp求解，假设dp[i][j]表示下标从i到j这段
 * histogram的最大rectangle面积。 但dp[i][j]并不能通过
 * 子问题直接解决，比如 dp[i-1][j]或者dp[i][j-1]或者任何在
 * i到j之间的histgram的最大rectangle面积来直接求得。
 * 因为histogram(i...j)组成的矩形，底边是j-i，高则是
 * min(histogram(i...j)), 从dp[i-1][j] 去求解 dp[i][j]时，
 * 可能histogram(i...k)正好能组成一个矩形，这就需要去比较
 * dp[i-1][j]和这个矩形面积的大小了，显然只有dp[i-1][j]和知道
 * min(histogram(i...j))都是不够的，都不能立即找到k。
 * 简单来说，从马尔可夫链的角度去看这个问题，就是dp需要记录的信息
 * 不只有子问题的解，甚至包含子问题的一些其他信息或者所有信息，显然
 * 这样的情况下，公共子问题意义不大，因为子问题的解无法直接推导出父问题的解！！！
 *
 * 但如果从左至右去看这个问题时，当histogram[i] < histogram[i-1]时，那么
 * histogram(i-1 ... n)能组成的矩形的面积最大也不会超过 histogram(i...n)能够
 * 组成的最大矩形面积的，也就是说，histogram(i)的信息就可以丢弃了。
 *
 * 通过stack可以很好的捕捉这种性质，即从左至右遍历histogram(0 ... n)，当遍历到
 * histogram(i)时，stack中只能保留比它小的histogram(k) < histogram(i), 0<=k <i,
 * 这里面其实隐含着，虽然histogram(k)比histogram(i)小，但它组成矩形的底边比从i开始
 * 组成的矩形的底边天然是要长的。所以比histogram(i)小的heights不能丢弃，同时histogram(k)
 * 的位置k和高度height[k]都是要保存在stack中的。
 *
 * 总结：
 * 1) 从左到右遍历heights
 *    a. 如果stack为空，则直接进栈；
 *    b. 如果stack中top的高度比当前大，则计算top能组成的最大矩形面积（底边长度：左起堆栈中下一个height的index+1，右则到当前height的左边)，循环直到top的高度比当前高度小，或者堆栈空了，然后将当前height入堆栈；
 *    c. 如果stack中top的高度比当前小，直接入堆栈；
 * 2) 上述遍历完之后，堆栈中的高度是单调增的，
 *    因此，要通过出栈的顺序挨个计算每个height的最大矩形面积即可，同1）中类似，每个矩形的底边长度的左边界，就是下一位(先入栈）的index+1。
 *    但此时，所有的右边界都是n了。
 *
 * 其实，我们通过堆栈操作，将参差不齐的histogram中局部的矩形计算完，剩下单调递增的heights，然后一并计算，包含了所有的情况。
 *
 * 难得我一次提交就通过了^_^
 */

#include <iostream>
#include <stack>
#include <vector>

using std::stack;
using std::vector;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
		int n = heights.size();
		std::stack<Hist> preh;

		int maxArea = 0;
		for (int i = 0; i < heights.size(); ++i) {
			if (preh.empty()) {
				if (maxArea < heights[i]) {
					maxArea = heights[i];
				}
				preh.push(Hist(i, heights[i]));
				continue;
			}

			auto t = preh.top();
			while (heights[i] < t.height) {
				preh.pop();
				int a = preh.empty() ? 0 : preh.top().index+1;  // pop出的这个height能组成最大矩形的左边界

				int area = (i-a) * t.height;
				if (area > maxArea) {
					maxArea = area;
				}

				if (preh.empty()) {
					break;
				}
				t = preh.top();
			}

			preh.push(Hist(i, heights[i]));
		}

		// stack中只剩下单调递增的heights了
		int b = n;
		if (!preh.empty()) {
			b = preh.top().index + 1;
		}

		while (!preh.empty()) {
			auto t = preh.top();
			preh.pop();

			int a = preh.empty() ? 0 : preh.top().index + 1;

			int area = (b - a) * t.height;
			if (area > maxArea) {
				maxArea = area;
			}
		}

		return maxArea;
    }

private:
	struct Hist {
		int index = 0;
		int height = 0;

		Hist(int i, int h):
			index(i), height(h) {}
	};
};

int main() {
	Solution sol;
    //vector<int> heights = {2,1,5,6,2,3};
    //vector<int> heights = {3,2,1,3,2,4,3};
    vector<int> heights = {3};
	std::cout << "Max Rectangle Area: " << sol.largestRectangleArea(heights) << std::endl;
	return 0;
}
