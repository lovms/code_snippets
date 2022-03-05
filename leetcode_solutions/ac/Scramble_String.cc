/*
 * 本题一开始看我有点懵，感觉特别复杂，但是之后一想又觉得其实很直白。
 * 解决问题的关键在于，题目中字符串的变换，最复杂的就是“交换”操作，
 * 使得将字符串分割的操作，可以将字符串分割成两块独立的substr，从而，
 * 产生了最优子结构，只要substr满足scramble变换，那么原来的str也可以!
 *
 * 虽然解决了本题，但是效率不佳，后续还可以看看怎么优化？？？！！
 */
#include <iostream>
#include <unordered_map>
#include <string>
#include <cstddef>

using std::to_string;
using std::unordered_map;
using std::string;
class Solution {
public:
    bool isScramble(string s1, string s2) {
		if (s1 == s2) {
			return true;
		}

		unordered_map<string, int> subsegment;


		return segCheck(s1, s2, 0, 0, s1.size(), subsegment);
    }

	bool segCheck(string& s1, string& s2, int s1b, int s2b, int len, unordered_map<string, int>& subsegment) {
		//std::cout << "Debug: " << s1b << "|" << s2b << "|" << len << ", " << s1.substr(s1b, len) << "|" << s2.substr(s2b, len) << std::endl;
		if (len==1) {
			if (s1[s1b] == s2[s2b]) {
				return true;
			} else {
				return false;
			}
		}
		string segKey = s1.substr(s1b, len) + "_" + s2.substr(s2b, len);
		auto res = subsegment.find(segKey);
		if (res != subsegment.end()) {
			return res->second;
		}
		for (int i = 1; i < len; ++i) {
			if (segCheck(s1, s2, s1b, s2b, i, subsegment) && segCheck(s1, s2, s1b+i, s2b+i, len - i, subsegment)) {
				subsegment[segKey] = true;
				return true;
			} else if (segCheck(s1, s2, s1b, s2b+len-i, i, subsegment) && segCheck(s1, s2, s1b+i, s2b, len - i, subsegment)) {
				subsegment[segKey] = true;
				return true;
			}
		}
		subsegment[segKey] = false;
		return false;
	}
	
};

int main() {
	Solution sol;
	//string s1 = "great";
	//string s2 = "rgeat";
	string s1 = "abcde";
	string s2 = "caebd";
	//string s1 = "abc";
	//string s2 = "bca";
	if (sol.isScramble(s1, s2)) {
		std::cout << s1 << " can scramble to " << s2 << std::endl;
	}
	
	return 0;
}
