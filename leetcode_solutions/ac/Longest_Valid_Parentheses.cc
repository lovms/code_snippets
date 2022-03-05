#include <iostream>
#include <string>

using std::string;

class Solution {
public:
    int longestValidParentheses(string s) {
		if (s.empty()) {
			return 0;
		}
		bool changeFlag = true;
		while (changeFlag) {
			changeFlag = false;
			for (int i = 0; i < s.size(); ++i) {
				if (s[i] == '(') {
					for (int j = i+1; j < s.size(); ++j) {
						if (s[j] == '+') {
							continue;
						} else if (s[j] == ')') {
							s[i] = '+';
							s[j] = '+';
							i = j;
							changeFlag = true;
							break;
						} else {
							break;
						}
					}
				}
			}
		}

		std::cout << "debug info: " << s << std::endl;
		int count = 0;
		int max_count = 0;
		for (int i = 0; i < s.size(); ++i) {
			if (s[i] == '+') {
				++count;
			} else {
				if (max_count < count) {
					max_count = count;
				}
				count = 0;
			}
		}
		return max_count > count? max_count:count;
    }
};

int main() {
	Solution sol;
	string s = "";
	while (std::cin >> s) {
	    std::cout << "longest length: " << sol.longestValidParentheses(s) << std::endl;
	}
	return 0;
}
