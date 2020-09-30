//Write a function to find the longest common prefix string amongst an array of strings.
//
//If there is no common prefix, return an empty string "".
//
//Example 1:
//
//Input: ["flower","flow","flight"]
//Output: "fl"
//Example 2:
//
//Input: ["dog","racecar","car"]
//Output: ""
//Explanation: There is no common prefix among the input strings.
//Note:
//
//All given inputs are in lowercase letters a-z.
//
//来源：力扣（LeetCode）
//链接：https://leetcode-cn.com/problems/longest-common-prefix
//著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;
using std::string;

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
		if (strs.size() <= 0) {
			return "";
		}
		int j = strs[0].size(); // max common prefix length
		for (int i = 1; i < strs.size(); ++i) {
			int length = std::min(j, int(std::max(int(strs[i-1].size()), int(strs[i].size()))));
			for (j = 0; j < length; ++j) {
				if (strs[i-1][j] != strs[i][j]) {
					break;
				}
			}
			if (j == 0) {
				return "";
			}
		}

		return strs[0].substr(0,j);
    }
};

int main() {
	Solution sol;
	vector<string> strs = {"flower","flow","flight"};
	cout << sol.longestCommonPrefix(strs) << endl;
	return 0;
}
