// 本题
//
//
//
/*
639. Decode Ways II
A message containing letters from A-Z can be encoded into numbers using the following mapping:

'A' -> "1"
'B' -> "2"
...
'Z' -> "26"
To decode an encoded message, all the digits must be grouped then mapped back into letters using the reverse of the mapping above (there may be multiple ways). For example, "11106" can be mapped into:

"AAJF" with the grouping (1 1 10 6)
"KJF" with the grouping (11 10 6)
Note that the grouping (1 11 06) is invalid because "06" cannot be mapped into 'F' since "6" is different from "06".

In addition to the mapping above, an encoded message may contain the '*' character, which can represent any digit from '1' to '9' ('0' is excluded). For example, the encoded message "1*" may represent any of the encoded messages "11", "12", "13", "14", "15", "16", "17", "18", or "19". Decoding "1*" is equivalent to decoding any of the encoded messages it can represent.

Given a string s consisting of digits and '*' characters, return the number of ways to decode it.

Since the answer may be very large, return it modulo 10^9 + 7.

 

Example 1:

Input: s = "*"
Output: 9
Explanation: The encoded message can represent any of the encoded messages "1", "2", "3", "4", "5", "6", "7", "8", or "9".
Each of these can be decoded to the strings "A", "B", "C", "D", "E", "F", "G", "H", and "I" respectively.
Hence, there are a total of 9 ways to decode "*".
Example 2:

Input: s = "1*"
Output: 18
Explanation: The encoded message can represent any of the encoded messages "11", "12", "13", "14", "15", "16", "17", "18", or "19".
Each of these encoded messages have 2 ways to be decoded (e.g. "11" can be decoded to "AA" or "K").
Hence, there are a total of 9 * 2 = 18 ways to decode "1*".
Example 3:

Input: s = "2*"
Output: 15
Explanation: The encoded message can represent any of the encoded messages "21", "22", "23", "24", "25", "26", "27", "28", or "29".
"21", "22", "23", "24", "25", and "26" have 2 ways of being decoded, but "27", "28", and "29" only have 1 way.
Hence, there are a total of (6 * 2) + (3 * 1) = 12 + 3 = 15 ways to decode "2*".
 

Constraints:

1 <= s.length <= 105
s[i] is a digit or '*'.
*/

#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

class Solution {
public:
    int numDecodings(string s) {
		vector<unsigned long long> record(s.size()+1, 0);
		record[0] = 1;

		const unsigned long long modulus  = 1e+9 + 7;
		for (int i = 1; i <= s.size(); ++i) {
			int j = i-1;
			// decode s[j] seperately
			if (s[j] == '*') {
				record[i] += (record[i-1]*9) % modulus;
			} else if (s[j] != '0') {
				record[i] += record[i-1]; // *1
			}
			record[i] %= modulus;

			if (j == 0) {
				continue;
			}
			unsigned long long record_i_2 = i-2 >= 0 ? record[i-2] : 1;
			// decode s[j-1,j] together
			if (s[j-1] == '0') {
				continue;
			} else if (s[j-1]=='*') {
				//enuerate valid codes
				if (s[j] == '*') {
					record[i] += (15 * record_i_2) % modulus; // 11~19; 21~26
				} else {
					record[i] += record_i_2; //1*10 + s[j]-'0'
					int t = 2*10 + (s[j]-'0');
					if (t <= 26) {
						record[i] += record_i_2;
					}
				}

			} else if (s[j-1] == '1') {
				if (s[j] == '*') {
					record[i] += (9 * record_i_2) % modulus; // 11~19
				} else {
					record[i] += record_i_2;
				}
			} else if (s[j-1] == '2') {
				if (s[j] == '*') {
					record[i] += (6 * record_i_2) % modulus; // 21~26
				} else {
					int t = 2*10 + s[j]-'0';
					if (t <= 26) {
						record[i] += record_i_2;
					}
				}
			}
			record[i] %= modulus;
		}

		return record[s.size()];
    }

};

int main() {
	Solution sol;
	//std::string s = "204";
	//std::string s = "*********";
	std::string s = "7*9*3*6*3*0*5*4*9*7*3*7*1*8*3*2*0*0*6*";  //result: 196465252
	std::cout << sol.numDecodings(s) << std::endl;
	return 0;
}
