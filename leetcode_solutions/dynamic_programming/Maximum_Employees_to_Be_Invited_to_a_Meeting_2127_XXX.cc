#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using std::vector;
using std::queue;
using std::unordered_map;

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
