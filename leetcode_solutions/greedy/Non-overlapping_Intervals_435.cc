/*
 *
 * 两种解法：
 * 
 * 解法一：贪心
 * 因为，区间重叠需要是对相邻（包含）的区间进行考察，所以按照左边界对区间进行升序排序，
 * 然后就可以根据 pre[1] > next[0] 判断pre和next相邻的区间重合了，并且如果pre和next区间没有重合
 * 我们也可以判断 next+1区间和pre也不会重合了。
 *
 * 如果发生重合，就是需要删除区间的时机，关键在于保留哪个区间，贪心的思路，就是保留右边界更小的那个区间！！！
 * 为什么？因为显然如果保留右边界较大的那个区间可以算出最优解，那么保留较小的那个肯定也可以啊，因为之后的区间重合，
 * 是拿这个保留下的区间的右边界和下一个区间的左边界去比较的，故保留区间的右边界越小则越能减小与后续区间重合的可能。
 *
 *
 * 解法二：
 * 在解法一的解题思路中，对区间按照左边界升序排列后，我们会明显感觉到，区间重合往往在相邻区间，很容易存在马尔科夫性，
 * 所以有用dp去求解的条件。
 *
 * 本题很明显的“线性dp”。
 *
 *  下面这段写的不对！！！！！==================================
 * 定义子问题：dp[i] 是对intervals[1 ... i] 确定保留第i个区间时需要删除的最小区间数，那对intervals[ 1 ... (i+1)]问题来说，
 * 此时并不能只考察第i个区间和i+1个区间是否重合，而写出下面的状态转移方程：        
 *           |- dp[i]  if i+1和i不重合
 * dp[i+1] = |
 *           |_ dp[i]+1  if i+1和i重合，删除i
 *
 * 
 * 这是不对的！！！
 * 原因是第dp[i]定义的状态就是保留i，所以如果要并且只删除第i个区间，依次类推，第i+1个区间也可能和第i-1个区间重合，那就要把第i-1个
 * 区间也删除掉，才能保留下来第i+1个区间，所以，状态转移方程是：
 *
 *
 *
 */
#include <iostream>
#include <vector>
using std::vector;

class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {

		std::sort(intervals.begin(), intervals.end(), [](vector<int>& a, vector<int>& b) {
				    if (a[0] < b[0]) {
					    return true;
					} else if (a[0] == b[0]) {
					    return a[1] < b[1];
					} 
					return false;
				});

		int pre = 0;
		int next = 1;
		int count = 0;
	    while (next < intervals.size()) {
			if (intervals[pre][1] > intervals[next][0]) { // intersect or overlap
				++count;
				if (intervals[pre][1] > intervals[next][1]) {
					pre = next;
				}
			} else {
				pre = next;
			}
			++next;
		}

		return count;
    }
};

int main() {
	Solution sol;
	//vector<vector<int>> intervals = {{1,2},{2,3},{3,4},{1,3}};
	vector<vector<int>> intervals = {{1,2},{1,2},{1,2}};
	//vector<vector<int>> intervals = {{-52,31},{-73,-26},{82,97},{-65,-11},{-62,-49},{95,99},{58,95},{-31,49},{66,98},{-63,2},{30,47},{-40,-26}};
	std::cout << sol.eraseOverlapIntervals(intervals) << std::endl;
	return 0;
}
