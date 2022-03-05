//假设词典长度为N，如果要对每个单词检测，它是否能由其他单词拼接成，涉及多次匹配，而每次匹配都是O(N)的(一个个试），
//假设单词的平均长度是M，那么对一个单词的检查，都需要O(MN)。故所有单词都检查一遍，时间复杂度是O（NM*N)。
//
//Trie树就是用来进行单词匹配的（不需要完全匹配，否则直接hash更快），比如前缀匹配，因此使用Trie树可以将单次匹配
//的时间复杂度从 O(N) 降低至 O(M)。
//
// 另外，判断单词是否可以由其他单词拼接得到的这个检查过程，其实就是DFS搜索，不同于传统DFS，是因为上述检查过程是个
// 图，而不是树，因为一个前缀可能有多种匹配方式！…… DFS搜索就必须要标识出访问过的节点，以免重复访问，但本题中如果
// 真要标识出访问过的节点，与传统的DFS相比要更加困难，因为不是树（后续补充描述下这里）
//
// 由于这里我们只需要判断是否能拼接成功，而不需要保存所有的拼接方式，因此，简单的将访问过的位置保存下来，后续就不用访问了!
// 这个visited_pos很重要，否则就会超时!
//
// 最终的时间复杂度应该是O(MM*N)，由于Trie树的使用，实际当中常数因子会更小，速度更快，当然应该还有优化空间，我提交的
// 办法时间上表现并不优秀！
#include <iostream>
#include <unordered_set>
#include <vector>
#include <string>
#include <stack>


using std::vector;
using std::string;
using std::unordered_set;
using std::stack;
using std::pair;

#define ALPHABET_SIZE 26

struct Node {
	vector<struct Node*> children;
	bool isEndOfWord;
	Node() : isEndOfWord(false) {
		children.insert(children.begin(), ALPHABET_SIZE, nullptr);
	}
};

class Trie {
public:
	Trie() : root(nullptr) {}

	void buildPrefixTree(vector<string> wordDict) {
		root = new Node();
		for (auto const& word : wordDict) {
			if (word == "") continue;
			insert(word);
		}
	}

	void insert(const string& word) {
		if (root == nullptr) {
			root = new Node();
		}
		Node *cur = root;
		for (int i = 0; i < word.size(); ++i) {
			if (cur->children[word[i]-'a'] == nullptr) {
				cur->children[word[i]-'a'] = new Node();
			}
			cur = cur->children[word[i]-'a'];

			if (i==word.size()-1) {
				cur->isEndOfWord = true;
			}

		}
	}

	bool isInTheDict(const string& token) {
		if (root == nullptr) {
			return false;
		}
		Node* cur = root;
		for (int i = 0; i < token.size(); ++i) {
			if (cur->children[token[i]-'a'] == nullptr) {
				//std::cout << "mark1: " << i << "|" << token[i] << std::endl;
				return false;
			} else if (i==token.size()-1) {
				//std::cout << "mark3: " << i << "|" << token[i] << std::endl;
				if (cur->children[token[i]-'a']->isEndOfWord == true) {
					return true;
				}
			} else {
				//std::cout << "mark2: " << i << "|" << token[i] << std::endl;
			    cur = cur->children[token[i]-'a'];
			}
		}
		return false;
	}

	void prefixFind(const string& token, int p, stack<int>& pos, unordered_set<int>& visited_pos) {
		if (root == nullptr) {
			return;
		}
		Node* cur = root;
		int start = p;
		for (; p < token.size(); ++p) {
			if (cur->children[token[p]-'a'] == nullptr) {
			
                break;
			} else if (cur->children[token[p]-'a']->isEndOfWord == true) {
				if (p-start!=token.size()-1 && visited_pos.find(p) == visited_pos.end()) {
				    pos.push(p);
					visited_pos.emplace(p);  //we should always avoid visited node in DFS
                }
			}
			cur = cur->children[token[p]-'a'];
		}
	}

	void printTrie() {
	}

    ~Trie() {
		if (root != nullptr) {
			destroy(root);
		}
	}

private:


	void destroy(struct Node* nd) {
		if (nd != nullptr) {
			for (auto child : nd->children) {
				destroy(child);
			}
		}
		delete(nd);
	}



	struct Node *root;
};

class Solution {
public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
		Trie t;
		t.buildPrefixTree(words);

		vector<string> result;


		for (auto const& word : words) {
		    visited_pos.clear();
			if (match(t, word, 0)) {
				//std::cout << "Debug3: " << word << std::endl;
				result.push_back(word);
			}
		}
		return result;
    }

	bool match(Trie& t, const string& word, int p) {
		stack<int> pos;
		t.prefixFind(word, p, pos, visited_pos);
		while (!pos.empty()) {
			auto& cur = pos.top();
			//std::cout << "Debug1: " << word << "|" << cur << "|" << word.size()-1<< std::endl;
			if (cur == word.size()-1) {
			    //std::cout << "Debug2: " << word << "|" << cur << std::endl;
				return true;
			}
			pos.pop();
			if (match(t, word, cur+1)) {
				return true;
			}
		}
		return false;
	}

private:
	unordered_set<int> visited_pos;
	int _minLen;
};

int main() {
	Solution s;
	vector<string> words = {"cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"};

	vector<string> result = s.findAllConcatenatedWordsInADict(words);
	for(auto const& token : result) {
		std::cout << token << std::endl;
	}
	return 0;
}
