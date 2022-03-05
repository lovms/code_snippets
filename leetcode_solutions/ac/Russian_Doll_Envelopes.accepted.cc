/* 
 * 本题的关键按照长宽对envelopes进行降序排列！
 * 我们从较小的信封开始，计算每个信封可以进行Russian Doll的最多的信封个数
 * 这里存在的最优子结构是，当我们知道envelopes[i]可以套装的最多的信封个数maxRussianDoll[i]后，
 * 对于任何排序在它前面的信封j，如果j可以装下i,那么 maxRussianDoll[j] = 1 + maxRussianDoll[i]
 *
 * 时间复杂度是 n^2的
 */
#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
	struct Envelope {
		int width;
		int height;
		Envelope() : width(0), height(0) {}
		Envelope(int w, int h):
			width(w), height(h) {}
		/*
		bool operator() (Envelope& a, Envelope& b) {
			if (a.width > b.width) {
				return true;
			} else if (a.width == b.width && a.height > b.height) {
				return true;
			}
			return false;
		}
		*/
	};

    int maxEnvelopes(vector<vector<int>>& envelopes) {
		vector<Envelope> env(envelopes.size(), Envelope());
		for (int i = 0; i < envelopes.size(); ++i) {
			env[i].width = envelopes[i][0];
			env[i].height = envelopes[i][1];
		}

		std::sort(env.begin(), env.end(), [](Envelope& a, Envelope& b) -> bool { 
				if (a.width > b.width) { 
				    return true;
				} else if (a.width == b.width && a.height > b.height) {
					return true;
				}
				return false; 
				});

		/*
		for (auto const & v : env) {
			std::cout << "(" << v.width << ", " << v.height << ")" << std::endl;
		}
		*/

		vector<int> maxRecord(env.size()+1, 1);
		return runRussianDoll(env, maxRecord);
    }

	int runRussianDoll(vector<Envelope>& env, vector<int>& maxRecord) {
		int maxRD = 1;
		for (int i = env.size()-1; i >= 0; --i) {
			if (i == env.size()-1) {
				maxRecord[i] = 1;
				continue;
			}

			int tmp = 0;
			for (int j = i+1; j < env.size(); ++j) {
				if (env[i].width > env[j].width && env[i].height > env[j].height) {
					tmp = 1 + maxRecord[j];
					if (tmp > maxRecord[i]) {
						maxRecord[i] = tmp;
					}
				}
			}
			if (maxRecord[i] > maxRD) {
				maxRD = maxRecord[i];
			}
			//std::cout << "(" << env[i].width << ", " << env[i].height << ") : " << maxRecord[i] << std::endl;
		}
		return maxRD;
	}

};

int main() {
	Solution sol;
	vector<vector<int>> envelopes;
    /* Input: envelopes = [[5,4],[6,4],[6,7],[2,3]]
     * Output: 3
     * Explanation: The maximum number of envelopes you can Russian doll is 3 ([2,3] => [5,4] => [6,7]).
     */

	/*
	vector<int> e1 = {5,4};
	vector<int> e2 = {6,4};
	vector<int> e3 = {6,7};
	vector<int> e4 = {2,3};

	envelopes.push_back(e1);
	envelopes.push_back(e2);
	envelopes.push_back(e3);
	envelopes.push_back(e4);
	*/
    /* Input: envelopes = [[1,1],[1,1],[1,1]]
     * Output: 1
     */

	/*
	vector<int> e1 = {1,1};
	envelopes.push_back(e1);
	envelopes.push_back(e1);
	envelopes.push_back(e1);
	*/

	/* Input: envelopes = [[10,8],[1,12],[6,15],[2,18]];
	 * Output: 2
	 */

	vector<int> e1 = {10, 8};
	vector<int> e2 = {1, 12};
	vector<int> e3 = {6, 15};
	vector<int> e4 = {2, 18};
	envelopes.push_back(e1);
	envelopes.push_back(e2);
	envelopes.push_back(e3);
	envelopes.push_back(e4);
	std::cout << sol.maxEnvelopes(envelopes) << std::endl;
    return 0;
}
