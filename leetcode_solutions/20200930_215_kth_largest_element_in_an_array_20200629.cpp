//Find the kth largest element in an unsorted array. Note that it is the kth largest element in the sorted order, not the kth distinct element.
//
//Example 1:
//
//Input: [3,2,1,5,6,4] and k = 2
//Output: 5
//Example 2:
//
//Input: [3,2,3,1,2,4,5,5,6] and k = 4
//Output: 4
//Note:
//You may assume k is always valid, 1 ≤ k ≤ array's length.
//
//来源：力扣（LeetCode）
//链接：https://leetcode-cn.com/problems/kth-largest-element-in-an-array
//著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:

	int qs(vector<int>& nums, int i, int j, int k) {
		if (i > j) {return 0;}
		else if (i==j) { return nums[i]; }

		int pivot = nums[i];
		int low = i + 1;
		int high = j;

		while ( low <= high) {
			while (low <= high && nums[low] >= pivot) {
				low++;
			}

			while (low <= high && nums[high] < pivot) {
				high--;
			}

			if (low < high) {
				int tmp = nums[high];
				nums[high] = nums[low];
				nums[low] = tmp;
			}
		}

		if (high != i) {
			int tmp = nums[high];
			nums[high] = nums[i];
			nums[i] = tmp;
		}

		if (high == k) {
			return nums[k];
		} else if (high < k) {
			return qs(nums, high+1, j, k);
		} else {
			return qs(nums, i, high-1, k);
		}

		return 0;
	}

    int findKthLargest(vector<int>& nums, int k) {
		k -= 1; //indexes of c++ vector starts from 0
		return qs(nums, 0, nums.size()-1, k);
    }
};

int main() {
	Solution s;
	vector<int> nums = {3,2,1,5,6,4};
	//vector<int> nums = {3,2,3,1,2,4,5,5,6};
	int k = 2;
	std::cout << s.findKthLargest(nums, k) << std::endl;

	return 0;
}
