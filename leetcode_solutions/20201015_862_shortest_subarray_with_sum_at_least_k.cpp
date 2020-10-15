//Return the length of the shortest, non-empty, contiguous subarray of A with sum at least K.
//
//If there is no non-empty subarray with sum at least K, return -1.
//
// 
//
//Example 1:
//
//Input: A = [1], K = 1
//Output: 1
//Example 2:
//
//Input: A = [1,2], K = 4
//Output: -1
//Example 3:
//
//Input: A = [2,-1,2], K = 3
//Output: 3
// 
//
//Note:
//
//1 <= A.length <= 50000
//-10 ^ 5 <= A[i] <= 10 ^ 5
//1 <= K <= 10 ^ 9
//
//来源：力扣（LeetCode）
//链接：https://leetcode-cn.com/problems/shortest-subarray-with-sum-at-least-k
//著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
//
// ******* Idea & Tips *******
// 1. 一开始我的思路比较直接或者说暴力，按照step=1...ArraySize，计算所有连续子数组
//    的和，当遇见第一个满足和不小于K的子数组时停止，O(N^2)的时间复杂度，O(N)的空间
//    复杂度。这种迭代计算也比较好理解，但是显然没有什么信息可以被继承以加以利用；
//    提交后超时，也是情理之中的。
// 2. 之后，我直觉地转变了思路，快速计算任一连续子数组和，可以通过计算前缀和，假设
//    前缀和数组为P，P[j]-P[i]就是子数组{A[i+1], A[i+2], ..., A[j]}的和，为了便于计算，
//    前缀和数组的第一个元素应该是0。
//    改变子数组和的方式，不是目的，我的脑海中希望通过寻找某种可以继承的信息，以便
//    通过剪枝来减少计算量……不幸的是，我没想对，我找到如果A[i]<0，以A[i]开始或结尾的
//    子数组都不会是最短的，即便它们的和大于小于K。
//    此后，我绞尽脑汁，试图从原数组中寻找到某种判断条件，可以减少计算……
// 3. 无奈之下，我参考来官方解答，但我没有看完，我立马意识到，线索应该在前缀和数组P中，
//    而不是原数组A中，我顺着这个思路继续思考，终于完成解题，时间和空间复杂度都是O(N)的。
//
//    1）首先使用双端队列deque来表示P;
//    2) 对于A[i]计算P[i]，P[i]比P[i-µ]要小，那么，由于对于之后的任意的元素j，子数组
//       {i+1, ..., j}的和:P[j]-P[j]都比{i-µ+1, ..., j}的和：P[j]-P[i-µ]要大，且更短！
//    3）对于{i, i+1, ..., j}的连续子数组而言，如果它的和大于或等于K，那么该子数组的
//       子数组也可能大于或等于K，且更短！！！
//    
//    基于原则2),我们遍历原数组A，计算前缀和时，就会和P的front和end保存的前缀和都比较下，
//    如果比当前计算的前缀和大，那么都抛弃掉……这样的迭代操作，确保了前缀和队列P中，前缀和
//    是`单调递增`的！！！（这个地方是本题解的核心，必须仔细理解，简单却不容易总结出来）
//
//    同时，也容易理解，P中保存的前缀和的index并不是连续的，因此index也需要保存下来！
//
//    基于原则3），当我们更新了前缀和队列P时，如果子序列的和>= K，我们需要从P的front端开始，
//    寻找更短的符合条件的子数组。
//
// 4. 其实，本题中，如何剪枝这块，我陷入到判断条件的找寻中了，总结来看，就是不能被局部的信息
//    所限制，应该紧紧依据前缀和，着眼于子数组和的计算：P[j]-P[i]，就是要让P[i]越小越可能满足
//    和>= K这一点深入思考。

#include <iostream>
#include <vector>
#include <deque>

using std::vector;

class Solution {
public:
	struct Prefix {
		int index;
		int sum;
	};
    int shortestSubarray(vector<int>& A, int K) {
		if (A.size() <= 0) {
			return -1;
		}
		int shortestLen = A.size() + 1;

		std::deque<Prefix> B;
		Prefix zero;
		zero.index = -1;
		zero.sum = 0;
		B.push_back(zero);
		int sum = 0;
		for (int i = 0; i < A.size(); ++i) {
			if (A[i] >= K) {
				return 1;
			}
			sum += A[i];


			// 通过和头部以及尾部的前缀和循环比较大小，
			// 保证deque中的前缀和是单调递增的
			while (B.size() > 0 && B.front().sum > sum) {
				B.pop_front();
			}

			while (B.size() > 0 && B.back().sum > sum) {
				B.pop_back();
			}

			// 寻找到最短的满足条件的连续序列
			// 因为第一个达标的序列并不一定是最短的
			while (B.size() > 0 && sum - B.front().sum >= K) {
				if (i-B.front().index < shortestLen) {
				    shortestLen = i-B.front().index;
				}
				B.pop_front();
			}

			Prefix tmp;
			tmp.index = i;
			tmp.sum = sum;
			B.push_back(tmp);
		}

		if (shortestLen <= A.size()) {
			return shortestLen;
		}
		return -1;
    }
};

int main() {
	//vector<int> A = {-47,45,92,86,17,-22,77,62,-1,42 };
    //int K = 180;
	//vector<int> A = {2,-1,2};
	//int K = 3;
	vector<int> A = {1};
	int K = 1;
	Solution s;
	std::cout << s.shortestSubarray(A, K) << std::endl;
	return 0;
}
