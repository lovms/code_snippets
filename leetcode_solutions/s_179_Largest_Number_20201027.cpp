//Given a list of non-negative integers nums, arrange them such that they form the largest number.
//
//Note: The result may be very large, so you need to return a string instead of an integer.
//
// 
//
//Example 1:
//
//Input: nums = [10,2]
//Output: "210"
//Example 2:
//
//Input: nums = [3,30,34,5,9]
//Output: "9534330"
//Example 3:
//
//Input: nums = [1]
//Output: "1"
//Example 4:
//
//Input: nums = [10]
//Output: "10"
// 
//
//Constraints:
//
//1 <= nums.length <= 100
//0 <= nums[i] <= 10^9
//
//来源：力扣（LeetCode）
//链接：https://leetcode-cn.com/problems/largest-number
//著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
//













#include <iostream>
#include <algorithm>
#include <string>

using std::string;
using std::vector;

struct PaddingNum {
	int pn;
	int origin;
	int bits;
};

bool compare(const PaddingNum& a, const PaddingNum& b) {
	if ((a.bits < b.bits && a.pn!=0 && a.pn+(b.pn%a.pn)==b.pn) ||
		(a.bits > b.bits && b.pn!=0 && b.pn+(a.pn%b.pn)==a.pn)) {
		string xa = std::to_string(a.origin);
		string xb = std::to_string(b.origin);
		string x = xa + xb;
		string y = xb + xa;
		std::cout << x << " | " << y << std::endl;
		for (int i = 0; i < x.size(); ++i) {
			if (x[i] > y[i]) {
				return true;
			} else if (x[i] < y[i]) {
				return false;
			}
		}
		std::cout << "mark" << std::endl;
		return true; 
	}
	return a.pn > b.pn;
};

class Solution {
public:
    string largestNumber(vector<int>& nums) {
        if (nums.size() == 0) {
            return "";
        }

		const int fullLength = 9;
		std::vector<PaddingNum> arr(nums.size(), PaddingNum());
		for (int i = 0; i < nums.size(); i++) {
			int bits = ceil(log(nums[i])/log(10));
			if (nums[i] == pow(10, bits)) {
				bits++;
			}
			arr[i].origin = nums[i];
			arr[i].pn = nums[i] * pow(10,(fullLength - bits));
			arr[i].bits = bits;
		}

		std::sort(arr.begin(), arr.end(), compare);

		std::string result;
		for (auto const &v: arr) {
			result += std::to_string(v.origin);
			std::cout << v.origin << ", " << v.pn << std::endl;
		}
		return result;
    }
};

int main() {
	Solution s;
	//std::vector<int> nums = {432,43243};
	//std::vector<int> nums = {11311, 113};
	//std::vector<int> nums = {3,30,34,5,9};
	//std::vector<int> nums = {10,2};
	//std::vector<int> nums = {8308,8308,830};
	std::vector<int> nums = {1,2,3,4,5,6,7,8,9,0};
	std::cout << s.largestNumber(nums) << std::endl;
	return 0;
}
