/**
 * 本题我思考了一下觉得一次遍历就可以了，每次只判断当前位置的字符是否合法即可。
 * 一共只需要判断（+|-、'e|E'、'.'、[0-9]、其他非法字符）这5种情况即可。
 * 有些判断需要全局信息，所以设置了hasE、hasDot来储存之前的字符中是否出现e或者.
 *
 * 本题的难点就是各种边界情况。但一般的情况是“出现在第一位”、“出现在最后一位”，
 * 其他的边界情况就需要一点点挖掘了，确实很难一次性搞定所有边界情况！！！
 *
 * bound conditons that I didn't take into consider: ".",  ".e1" , '+'
 *
 * "+"这个case需要特别说明下，这个case的特殊之处是 + 出现在了第一位，同时也出现在了最后一位
 * 判断时，要先判断是否出现在最后一位，其他情况下，+ 出现第一位都是正常的！
 */
#include <iostream>
#include <string>
#include <vector>

using std::string;

class Solution {
public:

	bool isDigit(char ch) {
		if (ch >= '0' && ch <= '9') {
			return true;
		}
		return false;
	}

    bool isNumber(string s) {
		int i = 0;
		bool hasE = false;
		bool hasDot = false;
		while (i < s.size()) {
			if (s[i] == '-' || s[i] == '+') {
				if (i+1 >= s.size()) { // end with '-' or '+'
					return false;
				}
				if (i == 0) {  // 1. at the first place BUT not end with '-' or '+'
					i++;
					continue;
				}
				if (s[i-1] == 'e') {  // 2. e+ or e-
					if (i+1 < s.size() && isDigit(s[i+1])) {
						i+=2;
						continue;
					}
				} else {
					return false;
				}
			} else if (s[i] == 'e' || s[i] == 'E') {
				if (i == 0) {
					return false;
				}
				if (i-1>=0 && (s[i-1] == '-' || s[i-1] == '+')) {  // Strings include (+e -e)  Are All UnValid.
					return false;
				}
				if (hasE) { // e already emerges
					return false;
				}
				if (i+1 >= s.size()) {   // end with e|E
					return false;
				}
				hasE = true;
			} else if (s[i] == '.') {
				if (hasDot) {
					return false;
				}

				if (hasE) {  // an integer is needed after 'E'
					return false;
				}

				if (i+1 < s.size() && s[i+1] == 'e') {
					if (i-1 < 0 || !isDigit(s[i-1])) {
						return false;
					}
				}

				if (i+1 >= s.size()) { // end with a dot
					if (i-1 < 0 || !isDigit(s[i-1])) {
						return false;
					}
				}

				hasDot = true;
			} else if (isDigit(s[i])) {
				i++;
				continue;
			} else {
				return false;
			}
			i++;
		}
		return true;
	}
};

int main() {
	Solution sol;
	std::vector<string> valid_numbers = {"2", "0089", "-0.1", "+3.14", "4.", "-.9", "2e10", "-90E3", "3e+7", "+6e-1", "53.5e93", "-123.456e789"};
	std::vector<string> unvalid_numbers = {"abc", "1a", "1e", "e3", "99e2.5", "--6", "-+3", "95a54e53", ".", ".e1", "+"};
	for (auto& n : unvalid_numbers) {
		if (sol.isNumber(n)) {
			std::cout << n << " is a valid number" << std::endl;
		} else {
			std::cout << n << " is NOT a valid number" << std::endl;
		}
	}

	return 0;
}
