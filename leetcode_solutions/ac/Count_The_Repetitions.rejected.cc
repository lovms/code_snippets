#include <iostream>
#include <unordered_map>

using std::string;
using std::unordered_map;
class Solution {
public:
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
		int p1 = 0;
		int len1 = s1.size() * n1;
		int base1 = s1.size();
		int p2 = 0;
		int base2 = s2.size();
		int pos = 0;
		while (p1 < len1) {
			if (s1[p1%base1] == s2[p2%base2]) {
				pos++;
				p1++;
				p2++;
			} else {
				p1++;
			}
		}

		return p2/(s2.size()*n2);
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

	/*
	string s1 = "acb";
	int n1 = 1;
	string s2 = "acb";
	int n2 = 1;
	*/

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

	string s1 = "phqghumeaylnlfdxfircvscxggbwkfnqduxwfnfozvsrtkjprepggxrpnrvystmwcysyycqpevikef";
	int n1 = 1000000;
	string s2 = "fmznimkkasvwsrenzkycxfxtlsgypsfad";
	int n2 = 333;
	std::cout << sol.getMaxRepetitions(s1, n1, s2, n2) << std::endl;
	return 0;
}
