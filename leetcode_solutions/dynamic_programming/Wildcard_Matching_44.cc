/*
 * 本题和最长公共子串那道题很像，子问题都是：s[i ... n]和p[j ... m]
 *
 * dp[i][j] 表示上述子问题的匹配结果：是(1)否(-1)匹配
 *
 * 按照p[j]有三种状态转移：
 * 1）p[j] == '?': dp[i][j] = dp[i+1][j+1];
 * 2) p[j] != '*' && != '?': 
 *    --a-- dp[i][j] = dp[i+1][j+1] if s[i]==p[j]
 *    --b-- dp[i][j] = -1 if s[i]!=p[j]
 * 3) p[j] == '*':      //这是最复杂的一个状态转移，*可以匹配空，也可以匹配剩余的全部s子串，所以需要探索多种可能
 *       dp[i][j] = max(dp[t][j+1]),   i <= t <= n+1   「t=i时，对应匹配空；t=n+1时，对应匹配剩余所有子串」
 *
 *
 * 另外，具体实现中的关键点就是对于初始状态处理，分别是i >= n+1，或者 j >= n+1
 * 特别需要注意, 如果s已经匹配完，但p还有剩余子串的情形，只有当p的剩余子串全是‘*’时，匹配才能成功。
 * 当然实现上，也可以放到p[j]==‘*’的分支中处理，总之，需要注意边界状况的处理！！！
 */
#include <iostream>
#include <vector>
#include <string>

using std::string;
using std::vector;

typedef vector<vector<int>> DDA;
class Solution {
public:
    bool isMatch(string s, string p) {
		DDA dp(s.size()+1, vector<int>(p.size()+1, 0));

		return (match(s, 0, p, 0, dp) > 0);

    }

	int match(string& s, int i, string& p, int j, DDA& dp) {
		//std::cout << "entry: i|" << i << ", j" << j << std::endl;
		
		if (i >= s.size()) {
			// 处理边界情况，字符串已经匹配完了，但reg正则还有，
			// 不过当reg正则剩余的子串都是*时，还是可以匹配成功的
			// 所以这个点千万得记着。
			bool allStars = true;
			while (j < p.size()) {
				if (p[j++] != '*') {
					allStars = false;
					break;
				}
			}
		    //std::cout << "mark1: i|" << i << ", j" << j << "| " << (allStars ? 1 : -1) << std::endl;
			return (allStars ? 1 : -1);
		} else {
			// 字符串还没有匹配完，但reg正则已经用完了，肯定无法匹配
			if (j >= p.size()) {
		        //std::cout << "mark2: i|" << i << ", j" << j << "| " << -1 << std::endl;
				return -1;
			}
		}
		if (dp[i][j] != 0) {
			//std::cout << "mark3: i|" << i << ", j" << j << "| " << dp[i][j] << std::endl;
			return dp[i][j];
		}

		if (p[j] == '?') {
			dp[i][j] = match(s, 1+i, p, 1+j, dp);
			//std::cout << "mark4: i|" << i << ", j" << j << "| " << dp[i][j] << std::endl;
		} else if (p[j] != '*') {
			if (s[i] == p[j]) {
				dp[i][j] = match(s, 1+i, p, 1+j, dp);
			} else {
				dp[i][j] = -1;
			}
			//std::cout << "mark5: i|" << i << ", j" << j << "| " << dp[i][j] << std::endl;
		} else {
			// p[j] == '*'
			dp[i][j] = -1;
			for (int t = i; t <= s.size(); ++t) {
				if (match(s, t, p, 1+j, dp) > 0) {
					dp[i][j] = 1;
					break;
				}
			}
			//std::cout << "mark6: i|" << i << ", j" << j << "| " << dp[i][j] << std::endl;
		}
		return dp[i][j];
	}
};

int main() {
	Solution sol;
	/*
	string s = "cb";
	string p = "?a";
	*/
	/*
	string s = "mississippi";
    string p = "m??*ss*?i*pi";
	*/
	string s = "aa";
	string p = "*";
	if (sol.isMatch(s, p)) {
		std::cout << "Yes! " << s << " matches " << p << std::endl;
	}
	return 0;
}
