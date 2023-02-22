/**
 * Version1 超时、Version2 过了、Version3重写的更清楚些
 **/
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <fstream>

using std::vector;
using std::queue;
using std::unordered_map;


/**
 * Version1
 */
class Solution {
public:
    int maximumInvitations(vector<int>& favorite) {
		int max = 0;
		vector<int> pre(favorite.size(), -1);
		for (int i = 0; i < favorite.size(); ++i) {
			int res = check_invitation(i, favorite, pre);
			max = std::max(max, res);
			//std::cout << "debug1 : i-" << i << ", res-" << res << std::endl;
		}

		std::cout << "print pre: ";
		for (auto p : pre) {
			std::cout << p << " ";
		}
		std::cout << std::endl;

		int j = 0;
		int res = 0;
		for (int i = 0; i < favorite.size(); ++i) {
			if (i == favorite[favorite[i]]) {
				j = favorite[i];
				//std::cout << "friends: " << i << " | " << j << std::endl;
				res += pre[i] + pre[j] + 2;
			}
		}
		max = std::max(max, res/2);
		return max;
    }

	int check_invitation(int start, vector<int>& favorite, vector<int>& pre) {
		//queue<int> circle;
		unordered_map<int, int> invited;

		int step = 1;
		invited.emplace(start, step);
		//circle.push(start);

		int i = -1;  // pre employee index
		int j = start;
		while (invited.find(favorite[j]) == invited.end()) {
			if (step-1 <= pre[j]) { 
				/* 剪枝：按照喜爱关系走到节点i的step
				 *       还不如之前的step大，可能是重复遍历，
				 *       也不会获得更大的环，所以提前停止
				 */
				return 0;
			}
			std::cout << "start from: " << start
				<< " go through " << j << " at steps " << step - 1 << std::endl;
			if (favorite[j] != i && step-1 > pre[j]) {
				pre[j] = step-1;
			} 
			step++;
			invited.emplace(favorite[j], step);

			i = j;
			j = favorite[j];
		}

		return invited[j] - invited[favorite[j]] + 1;
	}
};


int main() {
	Solution sol;
	//vector<int> favorite = {2,2,1,2};
	//vector<int> favorite = {3,0,1,4,1};
	//vector<int> favorite = {1,2,0};
	//vector<int> favorite = {1,0,0,2,1,6,5};
	vector<int> favorite = {5,13,3,14,1,1,13,13,14,10,5,13,3,14,2};
	std::cout << sol.maximumInvitations(favorite) << std::endl;
	return 0;
}

/** 
 * Version2 
 **/
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <fstream>
#include <string>

using std::vector;
using std::queue;
using std::unordered_map;

class Solution {
public:
	int max_;
	Solution(): max_(0) {}

    int maximumInvitations(vector<int>& favorite) {
		int max = 0;

		unordered_map<int, vector<int>> next;

		int j = 0;
		for (int i = 0; i < favorite.size(); ++i) {
            j = favorite[i];
			next[j].emplace_back(i);
		}

		vector<int> step(favorite.size(), -1);

		unordered_map<int, int> invited;
		for (int i = 0; i < step.size(); ++i) {
			step[i] = travel(favorite, i, next, invited, step, 1);
		}

		int res = 0;
		for (int i = 0; i < favorite.size(); ++i) {
			if (i == favorite[ favorite[i] ]) {
				res += step[i] + step[favorite[i]];
			}
		}
		res = res/2;
		if (max_ < res) {
			max_ = res;
		}
		return max_;
    }

	int travel(vector<int>& favorite, int cur, unordered_map<int, vector<int>>& next,
			unordered_map<int, int>& invited, vector<int>& step, int deep) {

		//std::cout << "debug: cur: " << cur << ", deep: " << deep << std::endl;
		if (step[cur] != -1) {
		    //std::cout << "X__X: cur: " << cur << ", step: " << step[cur] << std::endl;
			return step[cur];
		}
		if (next.find(cur) == next.end()) {
			step[cur] = 1;
			return 1;
		}

		int longest = 0;
		invited.emplace(cur, deep);
		for (auto n : next[cur]) {
			if (invited.find(n) != invited.end() && invited[n] != -1) {
				if (max_ < deep) {
					max_ = deep;
				}
				continue;
			}

			if (favorite[cur] == n) {  // bi-connected nodes
			    continue;
			}

			int res = travel(favorite, n, next, invited, step, deep+1);
			if (res > longest) {
				longest = res;
			}
		}
		invited[cur] = -1;
		step[cur] = 1 + longest;

		//std::cout << "mark: cur| " << cur << ", step: " << step[cur] << std::endl;

		return step[cur];
	}

};

void read_input(const std::string& filename, vector<int>& out) {
	std::ifstream in(filename, std::ios_base::in);
	std::string str = "";
	std::getline(in, str);
	std::cout << str << std::endl;

	std::size_t i = str.find("[");
	str = str.substr(i+1);

	while ((i=str.find(",")) != std::string::npos) {
		auto num = str.substr(0, i);
		out.emplace_back(std::stoi(num));
		str = str.substr(i+1);
	}

}

int main() {
	Solution sol;
	//vector<int> favorite;
	//read_input("./1", favorite);
	//std::cout << "employees number: " << favorite.size() << std::endl;
	//vector<int> favorite = {2,2,1,2};
	//vector<int> favorite = {3,0,1,4,1};
	vector<int> favorite = {1,2,0};
	//vector<int> favorite = {1,0,0,2,1,6,5};
	//vector<int> favorite = {1,0,1,2,3,4};
	//vector<int> favorite = {1,0,3,2,5,6,7,4,9,8,11,10,11,12,10}; // 11
	//vector<int> favorite = {6,4,4,5,0,3,3}; // 6
	std::cout << sol.maximumInvitations(favorite) << std::endl;
	return 0;
}



