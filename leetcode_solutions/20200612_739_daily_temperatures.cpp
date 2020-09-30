//Given a list of daily temperatures T, return a list such that, for each day in the input, tells you how many days you would have to wait until a warmer temperature. If there is no future day for which this is possible, put 0 instead.
//
//For example, given the list of temperatures T = [73, 74, 75, 71, 69, 72, 76, 73], your output should be [1, 1, 4, 2, 1, 1, 0, 0].
//
//Note: The length of temperatures will be in the range [1, 30000]. Each temperature will be an integer in the range [30, 100].
//

#include <iostream>
#include <vector>
using std::vector;

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& T) {
		const int upperBound = 100;
		const int lowerBound = 30;
        vector<vector<int>> record(upperBound - lowerBound + 1, vector<int>());
		//vector<int> stat(upperBound-lowerBound+1, 0);
		vector<int> waitingDays(T.size());

		for (int i = 0; i < T.size(); ++i) {
			record[T[i]-lowerBound].push_back(i);
			for (int j = 0; j < T[i]-lowerBound; ++j) {
				for (auto d : record[j]) {
					waitingDays[d] = i - d;
				}
				record[j].clear();
			}
		}

		return waitingDays;
    }
};

int main() {
	vector<int> T = {73, 74, 75, 71, 69, 72, 76, 73};
    Solution sol;
	vector<int> result = sol.dailyTemperatures(T);

	for (auto d : result) {
		std::cout << d << " ";
	}
	std::cout << std::endl;
	return 0;
}
