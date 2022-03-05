/*
 * 本题的思路其实挺简单的，就是拿词典去连续的字符串中匹配词，
 * 匹配上之后，则循环对后续的子字符串重复上述步骤。
 *
 * 因为，本题允许重复使用词典中的word，所以实现起来更简单。
 *
 * 直观上来看，上述算法存在共享子结构，但我没有记表法来提升性能，居然也accepted了。
 * 后续看看能否进一步优化时间？？？！！！
 */
#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {

		vector<string> sentence;

		findWordBreak(s, 0, wordDict, sentence);

		return _allSentences;
    }

    void findWordBreak(string& s, int beg, vector<string>& wordDict, vector<string>& sentence) {
        if (beg == s.size()) {
			//completely match
			string s = generateSentence(sentence);
			_allSentences.emplace_back(s);
		}
		for (auto &word : wordDict) {
			if (word.size() + beg <= s.size() && s.substr(beg, word.size()) == word) {
				sentence.emplace_back(word);
				findWordBreak(s, beg+word.size(), wordDict, sentence);
				sentence.pop_back();
			}
		}
	}

	string generateSentence(vector<string>& sentence) {
		string res = "";
		for (int i = 0; i < sentence.size(); ++i) {
			if (i != 0) {
				res += " " + sentence[i];
			} else {
				res = sentence[0];
			}
		}
		return res;
	}

	private:
        vector<string> _allSentences;
};

int main() {
	Solution sol;
	/* 
	 * Input: s = "catsanddog", wordDict = ["cat","cats","and","sand","dog"]
     *  Output: ["cats and dog","cat sand dog"]
	*/
	//string s= "catsanddog";
	//vector<string> wordDict = {"cat","cats","and","sand","dog"};


	/*
	 * Input: s = "pineapplepenapple", wordDict = ["apple","pen","applepen","pine","pineapple"]
     * Output: ["pine apple pen apple","pineapple pen apple","pine applepen apple"]
     * Explanation: Note that you are allowed to reuse a dictionary word.
	 */
	//string s = "pineapplepenapple";
	//vector<string> wordDict = {"apple","pen","applepen","pine","pineapple"};
	/*
	 * Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
     * Output: []
	 */
	string s = "catsandog";
	vector<string> wordDict = {"cats","dog","sand","and","cat"};

	// test
	vector<string> res = sol.wordBreak(s, wordDict);
	for (auto &sent : res) {
		std::cout << sent << std::endl;
	}
	return 0;
}
