//Given an array of characters chars, compress it using the following algorithm:
//
//Begin with an empty string s. For each group of consecutive repeating characters in chars:
//
//If the group's length is 1, append the character to s.
//Otherwise, append the character followed by the group's length.
//The compressed string s should not be returned separately, but instead be stored in the input character array chars. Note that group lengths that are 10 or longer will be split into multiple characters in chars.
//
//After you are done modifying the input array, return the new length of the array.
//
// 
//Follow up:
//Could you solve it using only O(1) extra space?
//
// 
//
//Example 1:
//
//Input: chars = ["a","a","b","b","c","c","c"]
//Output: Return 6, and the first 6 characters of the input array should be: ["a","2","b","2","c","3"]
//Explanation: The groups are "aa", "bb", and "ccc". This compresses to "a2b2c3".
//Example 2:
//
//Input: chars = ["a"]
//Output: Return 1, and the first character of the input array should be: ["a"]
//Explanation: The only group is "a", which remains uncompressed since it's a single character.
//Example 3:
//
//Input: chars = ["a","b","b","b","b","b","b","b","b","b","b","b","b"]
//Output: Return 4, and the first 4 characters of the input array should be: ["a","b","1","2"].
//Explanation: The groups are "a" and "bbbbbbbbbbbb". This compresses to "ab12".
//Example 4:
//
//Input: chars = ["a","a","a","b","b","a","a"]
//Output: Return 6, and the first 6 characters of the input array should be: ["a","3","b","2","a","2"].
//Explanation: The groups are "aaa", "bb", and "aa". This compresses to "a3b2a2". Note that each group is independent even if two groups have the same character.
// 
//
//Constraints:
//
//1 <= chars.length <= 2000
//chars[i] is a lower-case English letter, upper-case English letter, digit, or symbol.
//
//来源：力扣（LeetCode）
//链接：https://leetcode-cn.com/problems/string-compression
//著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

// ******* Idea & Tips *******
// 1. 不太清楚这题考查什么点。题目需要理解清楚，
//     a. 压缩字符串的结果是要in-place修改原数组的；
//     b. 只有连续一个的字符，不用追加长度
// 2. 题目要求O(1)的空间复杂度，所以，只使用了几个变量
// 3. 字符连续个数interger -> string，这里偷懒了，直接用std::to_string了。
//
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

class Solution {
public:
    int compress(vector<char>& chars) {
		int len = 0;
		int count = 0;
		char cur = '\0';
		for (int i = 0; i < chars.size(); ++i) {
			if (cur == chars[i]) {
				count++;
			} else {
				if (cur == '\0') {
					count = 1;
					cur = chars[i];
					continue;
				} else {
					chars[len++] = cur;
					cur = chars[i];
					if (count > 1) {
						string lenString = std::to_string(count);
						for (int j = 0; j < lenString.size(); ++j) {
							chars[len++] = lenString[j];
						}
					}
					count = 1;
				}
			}
		}

		if (count > 0) {
			chars[len++] = cur;
			if (count > 1) {
				string lenString = std::to_string(count);
				for (int j = 0; j < lenString.size(); ++j) {
					chars[len++] = lenString[j];
				}
			}
		}

		for (auto &ch : chars) {
			std::cout << ch << " ";
		}
		std::cout << std::endl;
		return len;
    }
};

int main() {
	Solution s;
	//vector<char> chars = {'a','a','b','b','c','c','c'};
	//vector<char> chars = {'a'};
	//vector<char> chars = {'a','b','b','b','b','b','b','b','b','b','b','b','b'};
	vector<char> chars = {'a','a','a','b','b','a','a'};

	std::cout << s.compress(chars) << std::endl;
	return 0;
}
