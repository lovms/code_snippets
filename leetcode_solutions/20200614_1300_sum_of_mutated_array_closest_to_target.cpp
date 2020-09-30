//Given an integer array arr and a target value target, return the integer value such that when we change all the integers larger than value in the given array to be equal to value, the sum of the array gets as close as possible (in absolute difference) to target.
//
//In case of a tie, return the minimum such integer.
//
//Notice that the answer is not neccesarilly a number from arr.
//
// 
//
//Example 1:
//
//Input: arr = [4,9,3], target = 10
//Output: 3
//Explanation: When using 3 arr converts to [3, 3, 3] which sums 9 and that's the optimal answer.
//Example 2:
//
//Input: arr = [2,3,5], target = 10
//Output: 5
//Example 3:
//
//Input: arr = [60864,25176,27249,21296,20204], target = 56803
//Output: 11361
// 
//
//Constraints:
//
//1 <= arr.length <= 10^4
//1 <= arr[i], target <= 10^5
//
//来源：力扣（LeetCode）
//链接：https://leetcode-cn.com/problems/sum-of-mutated-array-closest-to-target
//著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using std::cout;
using std::endl;
using std::vector;

class Solution {
public:
    int findBestValue(vector<int>& arr, int target) {
        int lowBound0 = 0;  // 上一个元素计算的highBound
		int lowBound1 = 0;
        int highBound = 0;
        std::sort(arr.begin(), arr.end());

		// 处理第一个元素之前的特殊情形
        highBound = arr.size() * (arr[0]-1);
		if (target == highBound) {
			return (arr[0]-1);
		}
        if (target > 0 && target < highBound) {
            int value = target / arr.size();
            if (std::abs(int(value*arr.size() - target)) <= std::abs(int((value+1)*arr.size() - target))) {
                return value;
			} else {
                return value+1;
			}
		}

		// 处理第一个元素至倒数第二个元素
		lowBound0 = highBound;
       
        int cumulated = 0;
        int mutatedNums = 0;
        for (int i = 0; i < arr.size()-1; i++) {
            cumulated += arr[i];
            mutatedNums = arr.size() - i - 1;
            lowBound1 = cumulated + arr[i] * mutatedNums;
            highBound = cumulated + (arr[i+1]-1) * mutatedNums;
			// lowBound0 ~ lowBound1
			if (target > lowBound0 && target < lowBound1) {
				if (std::abs(lowBound0 - target) <= std::abs(lowBound1 - target)) {
					return (arr[i]-1);
				} else {
					return arr[i];
				}
			}
			// lowBound1 ~ highBound
            if (target ==  lowBound1) {
                return arr[i];
			} else if (target == highBound) {
                return arr[i+1]-1;
			} else if (target > lowBound1 && target < highBound) {
				int value = (target-cumulated) / mutatedNums;
				if (std::abs(cumulated+value*mutatedNums - target) <= std::abs(cumulated+(value+1)*mutatedNums - target)) {
					return value;
				} else {
					return value+1;
				}
			}
			lowBound0 = highBound;
 
		}

		// 处理最后一个元素的特殊情形
		lowBound1 = cumulated + arr[arr.size() - 1];

		if (target < lowBound1) {
			if (std::abs(lowBound0 - target) <= std::abs(lowBound1 - target)) {
				return (arr[arr.size()-1]-1);
			} else {
				return arr[arr.size() - 1];
			}
		} else {
			return arr[arr.size() - 1];
		}

    }
};

int main() {
	vector<int> arr = {60864,25176,27249,21296,20204};
	int target = 56803;
	Solution sol;
	cout << sol.findBestValue(arr, target) << endl;

	return 0;
}
