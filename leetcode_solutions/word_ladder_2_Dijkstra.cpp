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

struct Node {
    int index;
    int dist;
    Node(int i, int d): index(i), dist(d) {}
};
struct GreaterThanByDist {
    bool operator() (const Node& a, const Node& b) {
        return a.dist > b.dist;
    }
};
template<typename T>
class custom_priority_queue : public std::priority_queue<T, std::vector<T>, GreaterThanByDist>
{
  public:

      bool remove(const int index) {
        auto it = std::find_if(this->c.begin(), this->c.end(),
                [&] (T const&p) {return p.index==index;});
        if (it != this->c.end()) {
            this->c.erase(it);
            std::make_heap(this->c.begin(), this->c.end(), this->comp);
            return true;
       }
       else {
        return false;
       }
 }
};

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
        if (count == 1) {
            return 1;
        }
        return XINFINITY;
    }

    int build(vector<string>& vocab, uint16_t * transformation_graph) {
        if (transformation_graph == NULL) {
            return 0;
        }
        std::unordered_map<string, int> wordSet;
        for (int i = 0; i < vocab.size(); ++i) {
            wordSet[vocab[i]] = i;
            for (int j = 0; j < vocab.size(); ++j) {
                transformation_graph[i*MAX_LEN + j] = XINFINITY;
            }
            transformation_graph[i*MAX_LEN+i] = 0;
        }
		string t = "";
		int k = -1;
        for (int i = 0; i < vocab.size(); ++i) {
			for (int j = 0; j <vocab[i].size(); j++) {
				t = vocab[i];
				for (char c : chars) {
					t[j] = c;
					if (t!=vocab[i] && wordSet.find(t) != wordSet.end()) {
						k = wordSet[t];
						transformation_graph[i*MAX_LEN+k] = 1;
						transformation_graph[k*MAX_LEN+i] = 1;
					}
				}
            }
        }

        return 0;
    }

    /* Dijkstra's algo using binary-heap as an implemention of a priority-queue */
    void findShortestPaths(uint16_t * transformation_graph, int size, int endW, vector<int>& sDist, vector<vector<int>>& preNodes) {
        for (int i = 0; i < preNodes.size(); i++) {
            preNodes[i].clear();
        }

        custom_priority_queue<Node> minHeap;
        sDist[endW] = 0;

        std::set<int> visitedWs;
        minHeap.emplace(endW, 0);
        while (!minHeap.empty()) {
            int cur = minHeap.top().index;
            visitedWs.insert(cur);
            minHeap.pop();

            for (int i = 0; i < sDist.size(); i++) {
                if (visitedWs.find(i) != visitedWs.end()) {
                    continue;
                }
                if (transformation_graph[cur*MAX_LEN+i] < XINFINITY) { // nodes adjcent to the `cur`
                    if (sDist[i] > sDist[cur] + transformation_graph[cur*MAX_LEN+i]) {
                        preNodes[i].clear();
                        preNodes[i].push_back(cur);
                        sDist[i] = sDist[cur] + transformation_graph[cur*MAX_LEN+i];
                    } else if (sDist[i] == sDist[cur] + transformation_graph[cur*MAX_LEN+i]) {
                        preNodes[i].push_back(cur);
                    }
                    minHeap.remove(i);
                    minHeap.emplace(i, sDist[i]);
                }
            }
        }
        return;
    }

    void myPrint(string& beginWord, std::vector<int>& sPath, int pre, vector<vector<int>>& preNodes, vector<vector<string>>& paths, vector<string>& wordList) {
        if (pre == -1) {
            vector<string> path;
            path.push_back(beginWord);
            for (auto x = sPath.begin(); x != sPath.end(); x++) {
                path.push_back(wordList[*x]);
            }
            paths.push_back(path);
            return;
        }
        sPath.push_back(pre);
        if (preNodes[pre].size() > 0) {
            for (auto n : preNodes[pre]) {
                myPrint(beginWord, sPath, n, preNodes, paths, wordList);
            }
        } else {
            myPrint(beginWord, sPath, -1, preNodes, paths, wordList);
        }
        sPath.pop_back();
    }

    void printPath(string& beginWord, int endW, vector<string>& wordList, vector<vector<int>>& preNodes, vector<vector<string>>& paths) {
        std::vector<int> sPath;
        int i = endW;
        myPrint(beginWord, sPath, i, preNodes, paths, wordList);
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
                index.push_back(i);
            }
        }
    }

    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        vector<vector<string>> paths;
        MAX_LEN = wordList.size();
        uint16_t* transformation_graph = new uint16_t[MAX_LEN*MAX_LEN];
        build(wordList, transformation_graph);
        vector<int> index;
        int endIndex = -1;
        getWordTransformation(transformation_graph, beginWord, endWord, wordList, index, endIndex);
        if (endIndex == -1 || index.size() <= 0) {
            return paths;
        }

        vector<vector<int>> preNodes(wordList.size(), vector<int>());
        vector<int> sDist(preNodes.size(), XINFINITY);
    	findShortestPaths(transformation_graph, wordList.size(), endIndex, sDist, preNodes);

		int minimum = XINFINITY;
		for (auto i : index) {
			if (sDist[i] < minimum) {
				minimum = sDist[i];
			}
		}

		for (auto i : index) {
			if (sDist[i] == minimum) {
				printPath(beginWord, i, wordList, preNodes, paths);
			}
		}


        delete[] transformation_graph;
        return paths;
    }

public:
    size_t MAX_LEN;
    const uint16_t XINFINITY = 9999;
    const string chars = "qwertyuiopasdfghjklzxcvbnm";
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
