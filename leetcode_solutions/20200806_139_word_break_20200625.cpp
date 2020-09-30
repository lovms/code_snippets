//Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, determine if s can be segmented into a space-separated sequence of one or more dictionary words.
//
//Note:
//
//The same word in the dictionary may be reused multiple times in the segmentation.
//You may assume the dictionary does not contain duplicate words.
//Example 1:
//
//Input: s = "leetcode", wordDict = ["leet", "code"]
//Output: true
//Explanation: Return true because "leetcode" can be segmented as "leet code".
//Example 2:
//
//Input: s = "applepenapple", wordDict = ["apple", "pen"]
//Output: true
//Explanation: Return true because "applepenapple" can be segmented as "apple pen apple".
//             Note that you are allowed to reuse a dictionary word.
//Example 3:
//
//Input: s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
//Output: false
//
//来源：力扣（LeetCode）
//链接：https://leetcode-cn.com/problems/word-break
//著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。





















































#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <stack>

using std::string;
using std::vector;
using std::unordered_map;
using std::cout;
using std::endl;

class Solution {
public:
	bool breakRoutine(string& s, int i, unordered_map<string, bool>& vocab, vector<bool>& record) {
		cout << "debug: " << i << "|" << s.size() << endl;
		if (i == s.size()) {
			return true;
		}

		for (int k = 1; k <= s.size() - i; k++) {
			if (i == 8) {
				cout << "debug1: " << k << " | " << s.substr(i, k) << endl;
			}
			if (vocab[s.substr(i, k)] && record[i+k] != false) {
			    cout << i << "|" << k << " -> " << s.substr(i,k) << std::endl;
				if (breakRoutine(s, i+k, vocab, record)) {
					cout << "debug2: " << i << "|" << k << endl;
					return true;
				} else {
					record[i+k] = false;
				}
			}
		}

		return false;
	}

    bool wordBreak(string s, vector<string>& wordDict) {
	    vector<bool> record(s.size()+1, true);
		unordered_map<string, bool> vocab;
		for (auto const &word : wordDict) {
			vocab.emplace(word, true);
		}

		return breakRoutine(s, 0, vocab, record);

    }
};

int main() {
	Solution sol;
	//string s = "applepenapple";
	//vector<string> wordDict = {"apple", "pen"};
	//string s = "catsandog"; 
	//vector<string> wordDict = {"cats", "dog", "sand", "and", "cat"};

	string s = "leetcode"; 
	vector<string> wordDict = {"leet", "code"};

	if (sol.wordBreak(s, wordDict)) {
		cout << "true" << endl;
	} else  {
	    cout << "false" << endl;
	}
	return 0;
}
