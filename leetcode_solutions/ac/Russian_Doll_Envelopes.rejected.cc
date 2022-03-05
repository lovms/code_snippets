/*
 * 本题是超时的解法。非常暴力！
 * 考虑的是所有的信封套装组合，时间复杂度其实是 2^n的。
 * 因为在runRussianDoll的核心代码段中，每个信封考虑两种情况，包含还是不包含。
 * 虽然使用了记录表的方式省去了一些计算，但指数级的复杂度还是避免不了超时。
 *
 * 实际上，这种暴力算法没有考虑这里存在的最优子结构，即如果知道了较小信封的maxRussianDoll可以套装的更小的信封个数，
 * 那么对于比它大的信封的套装个数，可以基于该较小信封的maxRussianDoll来计算了，而不用去重复考虑更小的信封了。
 * 详细的解释见accepted版本
 *
 * 总之，这里不能将去除重复计算，就当作使用动态规划的标志，毕竟还需要考虑最优子结构，显然，保存一些
 * 子组合的maxRussianDoll虽然减少计算，但子组合不是最优子结构！！！！
 */
#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
	Solution(): _globalMax(0) {}
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

		vector<int> maxRecord(env.size()+1, -1);
		return runRussianDoll(env, maxRecord, 0, -1);
    }

	int runRussianDoll(vector<Envelope>& env, vector<int>& maxRecord, int  cur, int last) {
		if (cur >= env.size()) {
			return 0;
		}
		if (maxRecord[cur] != -1) {
			return maxRecord[cur];
		} 
		int tmpInclude = 0;
		int tmpExclude = 0;
		if (last==-1 || env[cur].width < env[last].width && env[cur].height < env[last].height) {
			tmpInclude = 1 + runRussianDoll(env, maxRecord, cur+1, cur);
		}
		tmpExclude = runRussianDoll(env, maxRecord, cur+1, last);
		return tmpInclude>tmpExclude ? tmpInclude : tmpExclude;
	}

private:
	int _globalMax;

};

int main() {
	Solution sol;
	vector<vector<int>> envelopes;
    /* Input: envelopes = [[5,4],[6,4],[6,7],[2,3]]
     * Output: 3
     * Explanation: The maximum number of envelopes you can Russian doll is 3 ([2,3] => [5,4] => [6,7]).
     */

	vector<int> e1 = {5,4};
	vector<int> e2 = {6,4};
	vector<int> e3 = {6,7};
	vector<int> e4 = {2,3};

	envelopes.push_back(e1);
	envelopes.push_back(e2);
	envelopes.push_back(e3);
	envelopes.push_back(e4);
    /* Input: envelopes = [[1,1],[1,1],[1,1]]
     * Output: 1
     */

	/*
	vector<int> e1 = {1,1};
	envelopes.push_back(e1);
	envelopes.push_back(e1);
	envelopes.push_back(e1);
	*/
	std::cout << sol.maxEnvelopes(envelopes) << std::endl;
    return 0;
}
