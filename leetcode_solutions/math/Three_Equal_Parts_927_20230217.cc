/**
 * 因为是将0-1序列分成三段，每段表示的binary数字应该是一样的。
 * 
 * 由于编码是固定的，因此，可以比较容易获取的信息是：
 * 1）每段拥有的1的个数，所以总体1的个数必须%3=0；
 * 2）每段最后的tail zero的个数必须相同，可以通过统计第3分段的末尾0个数来获得；
 * 这里说的容易，是指时间复杂度较低。
 *
 * 明确以上两点，就可以确定有效的三段了，然后比较是否相等就可以。
 *
 * 整体时间复杂度是O(n)的，所以就AC了。似乎太简单了……
 *
 * 看了下题解，还有很多人想复杂了，数学题就是要找规律和技巧的。
 **/

#include <iostream>
#include <vector>
#include <string>

using std::string;
using std::vector;

class Solution {
public:
    vector<int> threeEqualParts(vector<int>& arr) {
		int ones = 0;
		int tail_zeros = 0;
		for (int i = arr.size()-1; i >= 0; --i) {
			if (arr[i] == 0 && i+tail_zeros == arr.size()-1) {
				tail_zeros++;
			}
			if (arr[i] == 1) {
				ones++;
			}
		}

		/*
		std::cout << "ones: " 
			<< ones 
			<< ",tail zeros: " << tail_zeros << std::endl;
			*/
		if (ones == 0) {
			return {0, int(arr.size()-1)};
		}
		if (ones % 3 != 0) {
			return {-1,-1};
		}

		int part1_left = 0;
		int part1_right = 0;
		int part2_left = 0;
		int part2_right = 0;
		int part3_left = 0;
		int part3_right = arr.size()-1;
		int cum = 0;
		for (int i = 0; i < arr.size(); ++i) {
			cum += arr[i];
			if (arr[i] == 1) {
				if (cum == 1) {
				    part1_left = i;
				}
				if (cum == ones/3) {
					part1_right = i;
				}
				if (cum == 1+ones/3) {
					part2_left = i;
				}
				if (cum == 2*ones/3) {
					part2_right = i;
				}
				if (cum == 2*ones/3+1) {
					part3_left = i;
				}
			}
		}

		/*
		std::cout << part1_left << ", "
			<< part1_right << "\n"
			<< part2_left << ", "
			<< part2_right << "\n"
			<< part3_left << ", "
			<< part3_right << std::endl;
		*/

		std::string str1 = "";
		std::string str2 = "";
		std::string str3 = "";
		for (int i = part1_left; i <= part1_right + tail_zeros; ++i) {
			str1 += std::to_string(arr[i]);
		}

		for (int i = part2_left; i <= part2_right + tail_zeros; ++i) {
			str2 += std::to_string(arr[i]);
		}

		for (int i = part3_left; i < arr.size(); ++i) {
			str3 += std::to_string(arr[i]);
		}

		/*
		std::cout << str1 << "\n"
			<< str2 << "\n"
			<< str3 << std::endl;
		*/
		if (str1 == str2 && str2 == str3) {
			return {part1_right+tail_zeros, part2_right+tail_zeros+1};
		}
	    return {-1, -1};
    }

};

int main() {
	Solution sol;
	//vector<int> arr = {1,1,0,0,1};
	vector<int> arr = {1,0,1,0,1};
	auto res = sol.threeEqualParts(arr);
	std::cout << "result: " << res[0] << ", " << res[1] << std::endl;
	return 0;
}
