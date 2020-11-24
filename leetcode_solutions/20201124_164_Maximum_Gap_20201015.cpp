//Given an unsorted array, find the maximum difference between the successive elements in its sorted form.
//
//Return 0 if the array contains less than 2 elements.
//
//Example 1:
//
//Input: [3,6,9,1]
//Output: 3
//Explanation: The sorted form of the array is [1,3,6,9], either
//             (3,6) or (6,9) has the maximum difference 3.
//Example 2:
//
//Input: [10]
//Output: 0
//Explanation: The array contains less than 2 elements, therefore return 0.
//Note:
//
//You may assume all elements in the array are non-negative integers and fit in the 32-bit signed integer range.
//Try to solve it in linear time/space.
//
//
//来源：力扣（LeetCode）
//链接：https://leetcode-cn.com/problems/maximum-gap
//著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
//

#include <iostream>
#include <vector>

using std::vector;

// Method1 : quick sort
class Solution {
public:
    int maximumGap(vector<int>& nums) {
		if (nums.size() < 2) {
			return 0;
		}

		quickSort(nums, 0, nums.size()-1);
		for (auto v: nums) {
			std::cout << v << " ";
		}

		std::cout << std::endl;

		int max = 0;
		for (int i=1; i < nums.size(); i++) {
			if (nums[i] - nums[i-1] > max) {
				max = nums[i] - nums[i-1];
			}
		}
		return max;
        
    }

    void quickSort(vector<int>& nums, int i, int j) {
		if (i >= j) {
			return;
		}

		int pivot = nums[i];
		int low = i+1;
		int high = j;

		while (low <= high) {
			while (low <= high && nums[low] < pivot) {
				low++;
			}

			while (low <= high && nums[high] >= pivot) {
				high--;
			}

			if (low < high) {
				int tmp = nums[low];
				nums[low] = nums[high];
				nums[high] = tmp;
				low++;
				high--;
			}
	    }

		if (high > i) {
			int tmp = nums[high];
			nums[high] = pivot;
			nums[i]= tmp;
		}


		quickSort(nums, i, high-1);
		quickSort(nums, high+1, j);
	}
};

// Method 2: bucket sort
// 思路：对于n个大小位于[min, max]的数，如果这个n个数正好的等间距
//       分布的，那么意味着排好序后，任意相邻的两个数之间的差距是
//       一样的：(max-min)/n；实际上，只要有一个数不在等间距的位置
//       上，那么最大间距就会比 (max-min)/n 要大！！！
//
//       因此，借助桶排序，我们按照桶大小为(max-min)/n来将[min, max]
//       区间进行均匀分桶，每个桶内保存最小和最大值。由于桶内的间距
//       不会大于(max-min)/n，所以不需要考虑桶内的相邻数的间距！只要
//       考察桶间的相邻数间距，即bucket[i+1].min - bucket[i].max。
//
// 问题：1。如果要求有序数组相邻数的最小间距，该方法还可以用么？
//       2. 上述思路中的分桶方案，会不会由于max非常大，从而导致分桶
//          的数目太大，导致内存不够用？（虽然提交是通过了）有没有
//          优化分桶减少内存使用的方法？

class Solution {
public:
    int maximumGap(vector<int>& nums) {
		if (nums.size() < 2) {
				return 0;
		}

		int min = (unsigned int)(1<<31)-1;
		int max = 0;

		for (auto v : nums) {
				if (v < min) {
						min = v;
				}
				if (v > max) {
						max = v;
				}
		}

		float bucketSize = (float)(max - min) / nums.size();
		if (bucketSize == 0) {
				bucketSize = 1;
		}
		int bucketN = nums.size()+1;

		vector<Bucket> buckets(bucketN, Bucket());
		int bucketIndex = -1;
		for (auto v: nums) {
			bucketIndex = (v - min) / bucketSize;

			buckets[bucketIndex].count++;
			if (v < buckets[bucketIndex].min) {
					buckets[bucketIndex].min = v;
			}
			if (v > buckets[bucketIndex].max) {
					buckets[bucketIndex].max = v;
			}
		}

		// debug
		/*
		for (int i=0; i<buckets.size(); i++) {
				std::cout << i << " : " << buckets[i].min << "," << buckets[i].max << std::endl;
		}
		*/
		// end

		int maxGap = 0;
		for (int i = 0; i < bucketN-1; ++i) {
				if (buckets[i].count == 0) {
						continue;
				}
				if (buckets[i+1].count == 0) {
						buckets[i+1].count = 1;
						buckets[i+1].max = buckets[i].max;
				} else if (buckets[i+1].min - buckets[i].max > maxGap) {
						maxGap = buckets[i+1].min - buckets[i].max;
				}
		}
		return maxGap;

    }

};

int main() {
	Solution s;
	vector<int> nums = {10};

	std::cout << s.maximumGap(nums) << std::endl;
	return 0;
}
