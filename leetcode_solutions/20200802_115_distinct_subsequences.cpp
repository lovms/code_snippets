//Given a string S and a string T, count the number of distinct subsequences of S which equals T.
//
//A subsequence of a string is a new string which is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (ie, "ACE" is a subsequence of "ABCDE" while "AEC" is not).
//
//It's guaranteed the answer fits on a 32-bit signed integer.
//
//Example 1:
//
//Input: S = "rabbbit", T = "rabbit"
//Output: 3
//Explanation:
//As shown below, there are 3 ways you can generate "rabbit" from S.
//(The caret symbol ^ means the chosen letters)
//
//rabbbit
//^^^^ ^^
//rabbbit
//^^ ^^^^
//rabbbit
//^^^ ^^^
//Example 2:
//
//Input: S = "babgbag", T = "bag"
//Output: 5
//Explanation:
//As shown below, there are 5 ways you can generate "bag" from S.
//(The caret symbol ^ means the chosen letters)
//
//babgbag
//^^ ^
//babgbag
//^^    ^
//babgbag
//^    ^^
//babgbag
//  ^  ^^
//babgbag
//    ^^^
//
//来源：力扣（LeetCode）
//链接：https://leetcode-cn.com/problems/distinct-subsequences
//著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
#include <iostream>
#include <string>

using std::string;
// Solution 1: recursively compare substring 
//class Solution {
//public:
//	Solution() : _count(0) {}
//
//	void match(string& s, string& t, int i, int j) {
//		if (i >= s.size() || j >= t.size()) {
//			return;
//		}
//		if (s[i] == t[j]) {
//			if (j == t.size()-1) {
//				_count += 1;
//			}
//			match(s, t, i+1, j+1);
//		}
//	    match(s, t, i+1, j);
//	}
//    int numDistinct(string s, string t) {
//		match(s, t, 0, 0);
//		return _count;
//    }
//
//private:
//	int _count;
//};

#include <vector>
using std::vector;
class Solution {
public:
	int numDistinct(string s, string t) {
		if (s == t) {
			return 1;
		}
		if (s.size() < t.size() || t.size() == 0) {
			return 0;
		}
		std::vector<unsigned int> comb(t.size(), 0);

		for (int i = 0; i < s.size(); ++i) {
			for (int j = t.size()-1; j >= 0; --j) {
				if (s[i] == t[j]) {
					if (j == 0) {
						comb[j]++;
					} else {
						comb[j] += comb[j-1]; 
					}
				}
			}
		}

		return comb[comb.size()-1];
	}
};

int main() {
	std::string s = "rabbbit"; 
	std::string t = "rabbit";
    
	//std::string s = "babgbag";
	//std::string t = "bag";
	Solution sol;
	std::cout << sol.numDistinct(s, t) << std::endl;
	return 0;
}
