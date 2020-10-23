//Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the two sorted arrays.
//
//Follow up: The overall run time complexity should be O(log (m+n)).
//
// 
//
//Example 1:
//
//Input: nums1 = [1,3], nums2 = [2]
//Output: 2.00000
//Explanation: merged array = [1,2,3] and median is 2.
//Example 2:
//
//Input: nums1 = [1,2], nums2 = [3,4]
//Output: 2.50000
//Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.
//Example 3:
//
//Input: nums1 = [0,0], nums2 = [0,0]
//Output: 0.00000
//Example 4:
//
//Input: nums1 = [], nums2 = [1]
//Output: 1.00000
//Example 5:
//
//Input: nums1 = [2], nums2 = []
//Output: 2.00000
// 
//
//Constraints:
//
//nums1.length == m
//nums2.length == n
//0 <= m <= 1000
//0 <= n <= 1000
//1 <= m + n <= 2000
//-106 <= nums1[i], nums2[i] <= 106
//
//来源：力扣（LeetCode）
//链接：https://leetcode-cn.com/problems/median-of-two-sorted-arrays
//著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
	double biBinarySearch(vector<int>& nums1, int ai, int aj,
			              vector<int>& nums2, int bi, int bj, int median) {
        // 一下的写法中，nums1和nums2是对称的，所以，判断逻辑写了两遍，可以写的更简洁。
        
        // 判断结束的条件有两个 aj < 0 或者 ai > aj (nums同理),
        // 两种结束条件下，median的计算方式是不同的，这是最难的部分！
		if (aj < 0 && median-1 < nums2.size()) {
			return nums2[median-1];
		}
		
		if (ai > aj) {
			int t = median - ai -1;
			return nums2[t];
		}
		if (bj < 0 && median-1 < nums1.size()) {
			
			return nums1[median-1];
		}

		if (bi > bj) {
			int t = median - bi -1;
			return nums1[t];
		}

		int ap = 0;
		int tmp = aj - ai + 1;
		if (tmp % 2 == 0) {
            ap = tmp / 2;
		} else {
			ap = (1 + tmp) / 2;
		}
		ap += ai - 1;

		int bp = 0;
		tmp = bj - bi + 1;
		if (tmp % 2 == 0) {
			bp = tmp/2;
		} else {
			bp = (1 + tmp) / 2;
		}
		bp += bi - 1;

		if (nums1[ap] > nums2[bp]) {
		    int ap_global = ap + bp+2;
			if (ap_global == median) {
				return biBinarySearch(nums1, ai, aj, nums2, bi+1, bj, median);
			} else if (ap_global < median) {
				return biBinarySearch(nums1, ai, aj, nums2, bp+1, bj, median);
			} else {
				return biBinarySearch(nums1, ai, ap-1, nums2, bi, bj, median);
			}
		} else {
			int bp_global = bp + ap + 2;
			if (bp_global == median) {
				return biBinarySearch(nums1, ai+1, aj, nums2, bi, bj, median);
			} else if (bp_global < median) {
				return biBinarySearch(nums1, ap+1, aj, nums2, bi, bj, median);
			} else {
				return biBinarySearch(nums1, ai, aj, nums2, bi, bp-1, median);
			}
		}

		return -1;
	}

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
		int median = 0;
		if (nums1.size() == 0) {
			if (nums2.size() % 2 == 0) {
				median = nums2.size() / 2;
				return (nums2[median-1] + nums2[median]) / 2.0;
			} else {
				median = (1+nums2.size())/2;
				return nums2[median-1];
			}
		}
		if (nums2.size() == 0) {
			if (nums1.size() % 2 == 0) {
				median = nums1.size() / 2;
				return (nums1[median-1] + nums1[median]) / 2.0;
			} else {
				median = (1+nums1.size())/2;
				return nums1[median-1];
			}
		}

		int sumSize = nums1.size() + nums2.size();

		if (sumSize % 2 == 0) {
			// even
			median = sumSize / 2;
		    double ml = biBinarySearch(nums1, 0, nums1.size()-1, nums2, 0, nums2.size()-1, median);
			double mh = biBinarySearch(nums1, 0, nums1.size()-1, nums2, 0, nums2.size()-1, median+1);

			return (ml+mh)/2;

		} else {
			median = (sumSize + 1) / 2;
		    return biBinarySearch(nums1, 0, nums1.size()-1, nums2, 0, nums2.size()-1, median);

		}

		return 0;
    }
};

int main() {
	Solution s;
	vector<int> nums1 = {1,2};
	vector<int> nums2 = {3,4};

	std::cout << s.findMedianSortedArrays(nums1, nums2) << std::endl;
	return 0;
}
