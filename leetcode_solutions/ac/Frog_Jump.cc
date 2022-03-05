#include <iostream>
#include <vector>
#include <unordered_map>
using std::vector;
using std::unordered_map;
class Solution {
public:
    bool canCross(vector<int>& stones) {
		int sz = stones.size();
		vector<vector<int>> simulator(sz, vector<int>(sz, -1));

		simulator[0][1] = 1;
		unordered_map<int, int> lastStep;

		for (int i = 1; i < sz; ++i) {

			lastStep.clear();
			for (int xi = 0; xi < i; ++xi) {
				if (simulator[xi][i] != -1) {
					if (i == sz-1) {
						return true;
					}
					int t = simulator[xi][i];
					lastStep[t-1] = 1;
					lastStep[t] = 1;
					lastStep[t+1] = 1;
				}
			}

			for (int j = i+1; j < sz; ++j) {
				int stepNeeded = stones[j] - stones[i];
				if (lastStep.find(stepNeeded) != lastStep.end()) {
					simulator[i][j] = stepNeeded;
				}
			}
		}

		for (int i = 0; i < sz; ++i) {
			for (int j = 0; j < sz; ++j) {
				std::cout << simulator[i][j] << " ";
			}
			std::cout << std::endl;
		}


		return false;

    }
};

int main() {
	Solution sol;
	/*
	Input: stones = [0,1,3,5,6,8,12,17]
	Output: true
	Explanation: The frog can jump to the last stone by jumping 1 unit to the 2nd stone, then 2 units to the 3rd stone, then 2 units to the 4th stone, then 3 units to the 6th stone, 4 units to the 7th stone, and 5 units to the 8th stone.
	*/

	//vector<int> stones= {0,1,3,5,6,8,12,17};
	/*
	Input: stones = [0,1,2,3,4,8,9,11]
	Output: false
	Explanation: There is no way to jump to the last stone as the gap between the 5th and 6th stone is too large.
	*/
	vector<int> stones = {0,1,2,3,4,8,9,11};

	if (sol.canCross(stones)) {
		std::cout << "true\n";
	} else {
		std::cout << "false\n";
	}
	return 0;
}
