#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using std::vector;
using std::unordered_map;
using std::queue;

class Test {
public:
	int run(vector<int>& input) {
		vector<int> dp(input.size(), 1);

		for (int i = 1; i < input.size(); ++i) {
			for (int j = 0; j < i; ++j) {
				if (input[i] > input[j]) {
					if (dp[j] + 1 > dp[i]) {
						dp[i] = dp[j];
					}
				}
			}
		}
		return dp[input.size()-1];
	}

};

int main() {
	Test t;
	vector<int> input = {10, 9, 2,5,3,7,101,18};
	std::cout << t.run(input) << std::endl;
	return 0;
}

