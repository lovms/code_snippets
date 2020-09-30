//Given two binary strings, return their sum (also a binary string).
//
//The input strings are both non-empty and contains only characters 1 or 0.
//
//Example 1:
//
//Input: a = "11", b = "1"
//Output: "100"
//Example 2:
//
//Input: a = "1010", b = "1011"
//Output: "10101"
// 
//
//Constraints:
//
//Each string consists only of '0' or '1' characters.
//1 <= a.length, b.length <= 10^4
//Each string is either "0" or doesn't contain any leading zero.
//
//来源：力扣（LeetCode）
//链接：https://leetcode-cn.com/problems/add-binary
//著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

#include <iostream>
#include <vector>
#include <string>

using std::string;
using std::vector;
using std::endl;
using std::cout;

class Solution {
public:
    string addBinary(string a, string b) {
		if (a == "0" && b == "0") {
			return "0";
		}
		int carryOutBit = 0;

		if (a.size() < b.size()) {
			string tmp = a;
			a = b;
			b = tmp;
		}

		size_t sz = a.size() + 1;
		string result(sz, '0');
	    for (int i = a.size()-1, j = b.size()-1; i >= 0; i--, j--) {
			if (j >= 0) {
				result[i+1] = ((a[i]-48) ^ (b[j]-48)) ^ carryOutBit + 48;
				carryOutBit = ((a[i]-48) | carryOutBit) &  ((b[j]-48) | carryOutBit) & ((a[i]-48) | (b[j]-48));
				//cout << "X:" << i << ":" << j << "|" << result[i+1] << "," << carryOutBit << endl;
			} else {
				result[i+1] = (a[i]-48) ^ carryOutBit + 48;
				carryOutBit = (a[i]-48) & carryOutBit;
				//cout << "Y:" << i << ":" << j << "|" << result[i+1] << "," << carryOutBit << endl;
			}
		}
		result[0] = carryOutBit + 48;

		return result.substr(result.find('1'));
	}
};

int main() {
	Solution sol;
	//string a = "11", b = "1";
    //string a = "1010", b = "1011";
	string a = "100", b = "110010";
	cout << sol.addBinary(a, b) << endl;
	return 0;
}
