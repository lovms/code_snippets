//Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.
//
//Example 1:
//
//Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
//Output: true
//Example 2:
//
//Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
//Output: false
//
//来源：力扣（LeetCode）
//链接：https://leetcode-cn.com/problems/interleaving-string
//著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::cout;
using std::string;
using std::endl;

class Solution {
public:
	bool judge(string& s1, string& s2, string &s3, vector<vector<int>>& info,
			   int p1, int p2) {
		if (p1 == s1.size()) {
			if (s3.substr(p1+p2) == s2.substr(p2)) {
				info[p1][p2] = 1;
				return true;
			} else {
				info[p1][p2] = -1;
				return false;
			}
		}
		if (p2 == s2.size()) {
			if (s3.substr(p1+p2) == s1.substr(p1)) {
				info[p1][p2] = 1;
				return true;
			} else {
				info[p1][p2] = -1;
				return false;
			}
		}
        
		if (s1[p1] != s3[p1+p2] && s2[p2] != s3[p1+p2]) {
			info[p1][p2] = -1;
			return false;
		}

		if (s1[p1] == s3[p1+p2]) {
			if (info[p1+1][p2] == 0) {
				if (judge(s1, s2, s3, info, p1+1, p2)) {
					info[p1+1][p2] = 1;
				} else {
					info[p1+1][p2] = -1;
				}
			}
		}
		if (s2[p2] == s3[p1+p2]) {
			if (info[p1][p2+1] == 0) {
				if (judge(s1, s2, s3, info, p1, p2+1)) {
					info[p1][p2+1] = 1;
				} else {
					info[p1][p2+1] = -1;
				}
			}
		}

		return (info[p1+1][p2]==1) || (info[p1][p2+1]==1);
	}

    bool isInterleave(string s1, string s2, string s3) {
		if (s1.size() + s2.size() != s3.size()) {
			return false;
		}
		int p1 = 0;
		int p2 = 0;
		vector<vector<int>> info(s1.size()+1, vector<int>(s2.size()+1, 0));

		bool res = judge(s1, s2, s3, info, p1, p2);
		for (auto row : info) {
			for (auto i : row) {
				cout << i << " ";
			}
			cout << endl;
		}
		return res;
    }

};

int main() {
    string s1 =	"aabcc";
	string s2 = "dbbca";
	string s3 = "aadbbcbcac";
	//string s3 = "aadbbbaccc";
	//string s3 = "aaba";

	Solution sol;
	if (sol.isInterleave(s1, s2, s3)) {
		cout << "yes\n";
	} else {
		cout << "no\n";
	}
	return 0;
}
