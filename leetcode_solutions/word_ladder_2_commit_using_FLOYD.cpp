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

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::cout;
using std::endl;

class Solution {
public:
	Solution() : MAX_LEN(10000) {}
	uint16_t isNeighbor(const string& str1, const string& str2) {
		if (str1.size() != str2.size()) {
			return XINFINITY;
		}
		int count = 0;
		for (int i = 0; i < str1.size(); i++) {
			count += (str1[i] == str2[i] ? 0 : 1);
		}
		if (count <= 1) {
			return 1;
		}
		return XINFINITY;
	}

	int build(vector<string>& vocab, uint16_t * transformation_graph) {
		if (transformation_graph == NULL) {
			return 0;
		}
		for (int i = 0; i < vocab.size(); ++i) {
			for (int j = 0; j < vocab.size(); ++j) {
				transformation_graph[i*MAX_LEN + j] = XINFINITY;
			}
			transformation_graph[i*MAX_LEN+i] = 0;
		}
		for (int i = 0; i < vocab.size(); ++i) {
			for (int j = i+1; j < vocab.size(); ++j) {
				transformation_graph[i*MAX_LEN+j] = isNeighbor(vocab[i], vocab[j]);
				transformation_graph[j*MAX_LEN+i] = transformation_graph[i*MAX_LEN+j];
			}
		}

		/*
		for (int i = 0; i < vocab.size(); ++i) {
			for (int j = 0; j < vocab.size(); ++j) {
				cout << transformation_graph[i*MAX_LEN + j] << " ";
			}
			cout << endl;
		}
		*/

		return 0;
	}

	void findShortestPaths(uint16_t * transformation_graph, int size) {
		for (int k = 0; k < size; ++k)
			for (int i = 0; i < size; ++i)
				for (int j = 0; j <size; ++j) {
					if (transformation_graph[i*MAX_LEN+k] < XINFINITY && 
							transformation_graph[k*MAX_LEN+j] < XINFINITY &&
							transformation_graph[i*MAX_LEN+j] > transformation_graph[i*MAX_LEN+k] + transformation_graph[k*MAX_LEN+j]) {
						transformation_graph[i*MAX_LEN+j] = transformation_graph[i*MAX_LEN+k] + transformation_graph[k*MAX_LEN+j];
					}
				}
	}

	void printPath(string& startWord, uint16_t * transformation_graph, vector<string>& vocab, int i, int j, vector<string>& path, const int originalPathLen,
                   vector<vector<string>>& paths) {
		if (i >= vocab.size() || j >= vocab.size()) {
			return;
		}

		if (i == j) {
			if (path.size()-2 < originalPathLen) {
				return;
			}
            paths.push_back(path);
            /*
			cout << startWord;
			for (auto& word : path)
				cout << " " << word;
			cout << endl;
            */
			return;
		}

		for (int k = 0; k < vocab.size(); ++k) {
			if ( k!=i && transformation_graph[i*MAX_LEN+k] + transformation_graph[k*MAX_LEN+j] == transformation_graph[i*MAX_LEN+j]) {
				//cout << "mark: " << i << " " << vocab[k] << endl;
				path.push_back(vocab[k]);
				printPath(startWord, transformation_graph, vocab, k, j, path, originalPathLen, paths);
				path.pop_back();
			}
		}
	}

	void getWordTransformation(uint16_t* transformation_graph, string& beginWord, string& endWord, vector<string>& vocab, vector<int>& index, int&endIndex) {
		for (int i = 0; i < vocab.size(); ++i) {
			if (vocab[i] == endWord) {
				endIndex = i;
				break;
			}
		}
		if (endIndex == -1) {
			return;
		}
		uint16_t minPathLen = XINFINITY;
		for (int i = 0; i < vocab.size(); ++i) {
			if (1 == isNeighbor(vocab[i], beginWord)) {
				if (transformation_graph[i*MAX_LEN+endIndex] < minPathLen) {
					index.clear();
					minPathLen = transformation_graph[i*MAX_LEN+endIndex]; 
					index.push_back(i);
				} else if (transformation_graph[i*MAX_LEN+endIndex] == minPathLen) {
					index.push_back(i);
				}
			}
		}
	}

    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        vector<vector<string>> paths;
        int MAX_LEN = wordList.size();
		uint16_t* transformation_graph = new uint16_t[MAX_LEN*MAX_LEN];
        build(wordList, transformation_graph);
        findShortestPaths(transformation_graph, wordList.size());
		vector<int> index;
		int endIndex = -1;
		getWordTransformation(transformation_graph, beginWord, endWord, wordList, index, endIndex);
		if (endIndex == -1) {
			return paths;
		}

        vector<string> path;
		for (auto ind : index) {
			int originalPathLen = transformation_graph[ind*MAX_LEN + endIndex];
			//cout << "mark2: " << ind << " " << originalPathLen << endl;
			if (originalPathLen < XINFINITY) {
				path.clear();
				path.push_back(beginWord);
				path.push_back(wordList[ind]);
				printPath(beginWord, transformation_graph, wordList, ind, endIndex, path, originalPathLen, paths); 
			}
		}

		delete[] transformation_graph;
        return paths; 
    }
    
public:
	int MAX_LEN;
	const uint16_t XINFINITY = 9999;
};

int main() {
	vector<string> vocab = {"hot","dot","dog","lot","log","cog"};

	string query = "hit";
	string endWord = "cog";

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
