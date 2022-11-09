/* 和编辑距离的问题很像。
 *
 * 唯一的特殊点在于*，所以分成 '.' 和 正常英文字符两大情况来判断，
 * 其中再分别根据接下来一位是否是'*'来分类判断。
 *
 * 难点在于边界条件的考虑，我这里漏在2点：
 * 1）case: s="aab", p="c*a*b"; 这个case问题处在 'c*'如果不去匹配s中任何字符时，
 *    是不需要条件: s[i] == p[j] 的
 * 2）case: s="a", p="ab*";  当i=s.size()时，j是小于p.size()的，但因为"b*"可以匹配空
 *    进一步延伸"a*c*e*b*"这种也可以匹配空！所以，匹配结束也不能以i==s.size()来单独判定。
 *    匹配结束只能以pattern用完来判定。也就是说，即便i==s.size()了，如果 j < p.size()，那么
 *    还要继续匹配，只不过是剩余的pattern只能匹配空了，另外i是不能再移动了，这也就是为啥
 *    我的代码里很多涉及i+1的移动，都会有个i < s.size()的前置条件。
 *
 *
 * 总结一下：核心的坑：'a*'可以匹配空！！
 *
 * ----------------------------------------
 *  另外，与官方题解不同的是： (m = s.size(), n = p.size())
 *  我这里dp的子问题是从某个位置开始至字符串结尾，也即是考察 s[i ... m] 和 p[j ... n]是否匹配的问题,
 *  所以，最终结果是dp[0][0];
 *  而题解中，考察的子问题是 s[0 ... i] 和 p[0 ... j]，所以最终结果是dp[m][n], 可以思考下这块状态转移方程。
 *
 *  本质上，我理解之所以这两种子问题划分都可以求解，是以为本题中的匹配问题是对称的，也就是说
 *  从左到右匹配或者从由向左匹配，结果是一样的。
 *
 *  但我这种子问题划分不太好写成自下而上的迭代方式，更容易用查表法实现。
 */

#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;

class Solution {
public:
    bool isMatch(string s, string p) {
		vector<vector<int>> dp(s.size()+1, vector<int>(p.size()+1, -1));
		subMatch(s, 0, p, 0, dp);
		return (dp[0][0] == 1);
    }

	int subMatch(string& s, int i, string& p, int j, vector<vector<int>>& dp) {
		if (j == p.size()) {  // pattern用完了，匹配过程结束 
			if (i == s.size()) return 1;
			return 0;  // s remains
		}

		// 此处，可能出现 i==s.size()，但 j < p.size()的情况，所以涉及i的操作
		// 都需要 i < s.size()的前置条件。

		if (i < s.size() && dp[i][j] != -1) return dp[i][j];   // 查表
	
		if (p[j] == '.') {
			if (j+1 < p.size() && p[j+1] == '*') {  // '.*'
				return (dp[i][j] = ((i < s.size() && subMatch(s, i+1, p, j, dp)) ||   // '.*' matches the current char and tries to match more
					   subMatch(s, i, p, j+2, dp) ||   // '.*' matches zero char, so directly move on
					   (i < s.size() && subMatch(s, i+1, p, j+2, dp))));   // '.*' matches the last char and move on the next one
			}
			return (i<s.size() && (dp[i][j] = subMatch(s, i+1, p, j+1, dp)));     // '.'可以匹配任意字符
		} else if (p[j] != '*') { // lower case english letters
			if (j+1 < p.size() && p[j+1] == '*') {  // '{char}*'
				return (dp[i][j] = (i<s.size() && (s[i]==p[j] && subMatch(s, i+1, p, j, dp)) ||   // '{char}*' matches the current char and tries to match more
					   subMatch(s, i, p, j+2, dp) ||   // '{char}*' matches zero char，对应上面的case 1)的讨论
					   (i<s.size() && s[i]==p[j] && subMatch(s, i+1, p, j+2, dp))));   // '{char}*' matches the last char and move on the next one
			}
			if (i < s.size() && s[i] != p[j]) {  // 正常字符匹配, 没匹配上：失败
				return 0;
			}
			return (i<s.size() && (dp[i][j] = subMatch(s, i+1, p, j+1, dp)));    // 正常字符匹配，匹配上了：继续
		}
		return 0;
	}
};

int main() {
	Solution sol;
	//string s = "abcxefeeeb";
	//string p = "abc.*xe*b";
	string s = "aab";
	string p = "c*a*b";
	//string s = "a";
	//string p = "ab*";
	//string s = "abcaaaaaaabaabcabac";
	//string p = ".*ab.a.*a*a*.*b*b*";
	if (sol.isMatch(s, p)) {
		std::cout << "True Match: " << s << " | " << p << std::endl;
	} else {
		std::cout << "False Match: " << s << " | " << p << std::endl;
	}
	return 0;
}
