//Given an array A of positive integers, A[i] represents the value of the i-th sightseeing spot, and two sightseeing spots i and j have distance j - i between them.
//
//The score of a pair (i < j) of sightseeing spots is (A[i] + A[j] + i - j) : the sum of the values of the sightseeing spots, minus the distance between them.
//
//Return the maximum score of a pair of sightseeing spots.
//
// 
//
//Example 1:
//
//Input: [8,1,5,2,6]
//Output: 11
//Explanation: i = 0, j = 2, A[i] + A[j] + i - j = 8 + 5 + 0 - 2 = 11
// 
//
//Note:
//
//2 <= A.length <= 50000
//1 <= A[i] <= 1000
//
//来源：力扣（LeetCode）
//链接：https://leetcode-cn.com/problems/best-sightseeing-pair
//著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

class Solution {
public:
    int maxScoreSightseeingPair(vector<int>& A) {
		if (A.size() < 2) return 0;
		if (A.size() == 2) return (A[0] + A[1] - 1);
		vector<int> hatA(A.size(), 0);
		for (int i = 0; i < A.size(); ++i) {
			hatA[i] = A[i] - i;
			cout << A[i] << ":" << i << ":" << hatA[i] << endl;
		}
		cout << endl;

		vector<int> maxE(A.size(), 0);
		int max = -100000;
		int maxIndex = 0;
		for (int i = hatA.size() - 1; i > 0; i--) {
			if (hatA[i] > max) {
				max = hatA[i];
				maxIndex = i;
				maxE[i-1] = i;
			} else {
				maxE[i-1] = maxIndex;
			}
		}
		for (auto m : maxE) 
			cout << m << " ";
		cout << endl;

		int sum = 0;
		max = -100000;
		for (int i = 0; i < hatA.size()-1; ++i) {
			sum = A[i] + hatA[maxE[i]] + i;
			cout << i << ":" << sum << endl;
			if (sum > max) {
				max = sum;
			}
		}
		return max;
    }
};

int main() {
	Solution sol;
	//vector<int> A = {1,3,5};
	vector<int> A = {8,1,5,2,6};
	cout << sol.maxScoreSightseeingPair(A) << endl;
	return 0;
}
