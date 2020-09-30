//Given two words (beginWord and endWord), and a dictionary's word list, find all shortest transformation sequence(s) from beginWord to endWord, such that:
//
//Only one letter can be changed at a time
//Each transformed word must exist in the word list. Note that beginWord is not a transformed word.
//Note:
//
//Return an empty list if there is no such transformation sequence.
//All words have the same length.
//All words contain only lowercase alphabetic characters.
//You may assume no duplicates in the word list.
//You may assume beginWord and endWord are non-empty and are not the same.
//Example 1:
//
//Input:
//beginWord = "hit",
//endWord = "cog",
//wordList = ["hot","dot","dog","lot","log","cog"]
//
//Output:
//[
//  ["hit","hot","dot","dog","cog"],
//  ["hit","hot","lot","log","cog"]
//]
//Example 2:
//
//Input:
//beginWord = "hit"
//endWord = "cog"
//wordList = ["hot","dot","dog","lot","log"]
//
//Output: []
//
//Explanation: The endWord "cog" is not in wordList, therefore no possible transformation.
//

//https://zhuanlan.zhihu.com/p/30930884 单向BFS
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <unordered_map>

using std::string;
using std::vector;
using std::cout;
using std::endl;

class Solution {
private:
    bool isNeighbor(const string& str1, const string& str2) {
        if (str1.size() != str2.size()) {
            return 0;
        }
        int count = 0;
        for (int i = 0; i < str1.size(); i++) {
            count += (str1[i] == str2[i] ? 0 : 1);
        }

		return count==1;
    }

public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
		wordList.push_back(beginWord);
		//unordered_map<string ,int> word2Id;

		vector<vector<int>> adjacent_words(wordList.size(), vector<int>());
		int endWordIndex = -1;
		for (int i = 0; i < wordList.size(); ++i) {
			if (wordList[i] == endWord) {
				endWordIndex = i;
			}
			//word2Id[wordList[i]] = i;
			for (int j = i+1; j < wordList.size(); ++j) {
				if (isNeighbor(wordList[i], wordList[j])) {
					adjacent_words[i].push_back(j);
					adjacent_words[j].push_back(i);
				}
			}
		}
		vector<vector<string>> paths;
		if (endWordIndex == -1) {
			return paths;
		}
		std::queue<vector<int>> que;
		que.emplace(vector<int>(1, wordList.size()-1));
		vector<uint16_t> sDist(wordList.size(), XINFINITY);
		sDist[wordList.size()-1] = 0;
		cout << "begin debug\n";
		for (int k = 0; k < sDist.size(); ++k) {
			cout << wordList[k] << "|" << sDist[k] << endl;
		}
		cout << "end debug\n";
		while (!que.empty()) {
			vector<int>& prepath = que.front();
			int now = prepath.back();
			if (now == endWordIndex) {
				vector<string> tmp;
				for (auto i : prepath) {
					tmp.push_back(wordList[i]);
				}
				paths.push_back(tmp);
			} else {
				for (auto i : adjacent_words[now]) {
					if (wordList[now] == "bleat" &&
							wordList[i] == "bloat") {
						cout << "debug1: sDist[bloat]|" << sDist[i]
							 << ", sDist[bleat]|" << sDist[now] << endl;
					}
					if (sDist[i] >= sDist[now] + 1) {
						sDist[i] = sDist[now] + 1;
						vector<int> tmp(prepath);
						tmp.push_back(i);
						if (wordList[i] == "bloat") {
							for (auto k : tmp) {
								cout << wordList[k] << " ";
							}
							cout << endl;
						}
						que.push(tmp);
					}
				}
			}
			que.pop();
		}

        return paths;
    }

public:
    const uint16_t XINFINITY = (1<<16)-1;
};

int main() {
    //vector<string> vocab = {"hot","cog"};
	/*
    vector<string> vocab = {"hot","dot","dog","lot","log", "cog"};

    string query = "hot";
    string endWord = "cog";
	*/
	vector<string> vocab;
	string query;
	string endWord;
	std::ifstream inf;
	inf.open("./word_ladder_2_data");
	if (inf.is_open()) {
		std::getline(inf, query);
		std::getline(inf, endWord);
		std::cout << query << ";" << endWord << endl;
		string line;
		std::getline(inf, line);
		string st;
		while (line.find(",") != std::string::npos) {
			int i = line.find(",");
			vocab.push_back(line.substr(0, i));
			//std::cout << line.substr(0, i) << std::endl;
			line = line.substr(i+1);
		}
		//std::cout << line << endl;
		vocab.push_back(line);
	}

    Solution sol;
    vector<vector<string>> paths = sol.findLadders(query, endWord, vocab);

    for (auto& path : paths) {
        for (auto& node : path) {
            cout << node << " ";
        }
        cout << endl;
    }
    return 0;
}
