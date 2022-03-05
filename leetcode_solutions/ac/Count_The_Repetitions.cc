#include <iostream>
#include <unordered_map>
#include <string>
using std::string;
using std::unordered_map;
class Solution {
public:
	struct Rec {
		int jump;
		int num;
	};

    int getMaxRepetitions(string s1, int n1, string s2, int n2) {

		unordered_map<int, Rec> extraNMap;
	    for (int i = s1.size()-1; i >= 0; i--) {
			if (s1[i] == s2[0]) {
				int extraN = doOneMatch(s1, s2, i);
				int nextPos = i + extraN;
				int matchNum = 1;
				unordered_map<int, Rec>::iterator itr = extraNMap.find(nextPos);
				while (itr!=extraNMap.end() && nextPos+itr->second.jump < s1.size()) {
					extraN += itr->second.jump;
					matchNum += itr->second.num;

					nextPos += itr->second.jump;
					itr = extraNMap.find(nextPos);
				}
				Rec t;
				t.jump = extraN;
				t.num = matchNum;
				extraNMap.emplace(i, t);
			}
		}

		/*
		for (int i = 0; i < s1.size(); ++i) {
			if (s1[i] == s2[0]) {
				int extraN = doOneMatch(s1, s2, i);
				Rec t;
				t.jump = extraN;
				t.num = 1;
				extraNMap.emplace(i, t);
			}
		}
		*/

		/*
		for (auto const& v : extraNMap) {
			std::cout << "debug1: " << v.first << "\t" << v.second.jump << "|" << v.second.num  << std::endl;
		}
		*/
		
		int p1 = 0;
		int len1 = s1.size() * n1;
		int p2 = 0;
		int m = 0;
		while (p1 < len1) {
			if (s1[p1%s1.size()] == s2[0]) {
				//std::cout << "debug2: p1:" << p1  << std::endl;
				int _p1 = p1%s1.size();
				p1 += extraNMap[_p1].jump;
				p2 = 0;
				m += extraNMap[_p1].num;

			} else {
				p1++;
			}
		}
		if (p1 > len1) {
			m -= 1;
		}

		//std::cout << "result: " << m << "|" << n2 << "==> " <<  m/n2 << std::endl;
		return m/n2;
    }

	int doOneMatch(string& s1, string& s2, int s1_begin) {
	    int p1 = s1_begin;
		int p2 = 0;
		while (p2 < s2.size()) {
		    if (s1[p1%s1.size()] == s2[p2]) {
			    p1++;
				p2++;
			} else {
				p1++;
			}
		}

		return p1-s1_begin;
	}

};

int main() {
	Solution sol;
	/*
	 * Input: s1 = "acb", n1 = 4, s2 = "ab", n2 = 2
     * Output: 2
	 */

	/*
	string s1 = "acb";
	int n1 = 4;
	string s2 = "ab";
	int n2 = 2;
	*/
	/* 
	 * Input: s1 = "acb", n1 = 1, s2 = "acb", n2 = 1
	 * Output: 1
	 */

	string s1 = "acb";
	int n1 = 1;
	string s2 = "acb";
	int n2 = 1;

	/*
	 * case 3:
	 */
	//string s1="aaa"; int n1 =3; string s2="aa"; int n2=1;
	/*
	 * case 4:
	 */
	/*
	string s1="phqghumeaylnlfdxfircvscxggbwkfnqduxwfnfozvsrtkjprepggxrpnrvystmwcysyycqpevikeffmznimkkasvwsrenzkycxf";
	int n1 = 100000;
	string s2="xtlsgypsfadpooefxzbcoejuvpvaboygpoeylfpbnpljvrvipyamyehwqnqrqpmxujjloovaowuxwhmsncbxcoksfzkvatxdknly";
	int n2 = 1;
	*/

	/*
	 * case 5:
	 */

	/*
	string s1 = "phqghumeaylnlfdxfircvscxggbwkfnqduxwfnfozvsrtkjprepggxrpnrvystmwcysyycqpevikef";
	int n1 = 1000000;
	string s2 = "fmznimkkasvwsrenzkycxfxtlsgypsfad";
	int n2 = 333;
	*/

	/*
	 * case 6:
	 */
	/*
	string s1 = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
	std::cout << "mark: " << s1.size() << std::endl;
    int n1 = 1000000;
    string s2 = "a";
    int n2 = 1;
	*/
	std::cout << sol.getMaxRepetitions(s1, n1, s2, n2) << std::endl;
	return 0;
}
