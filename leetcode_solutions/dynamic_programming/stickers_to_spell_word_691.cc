/*
 * 状态压缩dp的典型题。
 *
 * 但其实，本题很想背包问题，只不过：1）背包容量无法用int表达；2）使用"物品”是无限的。
 *
 * 针对1）其实就需要使用“状态压缩”，或者我个人理解相当于“数字化”表达dp状态，其实即便不用数字化，直接用字符串去表达应该也可以。
 *
 * 我的写法还是偏向于背包的写法!!! 
 *
 * 另外，很多人其实使用了BFS或者DFS的解法，像官方题解其实就是DFS（所谓: 记忆化搜索）
 *
 *  这里似乎记忆化搜索的方法更好些，因为我使用背包的写法来写，只能选择自上而下的顺序来写dp，
 *  导致空间上不能使用滚动数组，空间上会有损，空间复杂度是( 2^m * n)，m是target长度，n是stickers的数目！
 *  
 *=======================================
 * 其实还有个很重要的优化点，就是减少不必要的冗余sticker！！！
 *
 * target是"thehat"，sticker1="try", sticker2="tie"
 *
 * sticker1中有效自负<t, 1>; 而sticker2中的有效字符是 <t,1>、<e, 1>
 * 
 * 因为本题只考虑最少的sticker数量，具体使用哪个sticker并不用关心，所以
 * 使用sticker1的有效字符，sticker2都有，所以没必要考虑sticker1，只需要考虑sticker2
 *
 * 因此，无论在dp或者dfs等方法前，去掉冗余sticker都可以大幅提升效率，虽然算法复杂度其实不会变，但n大概率会减小的。
 */
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using std::vector;
using std::string;
using std::unordered_map;

using DICT = unordered_map<char, int>;

#define DEBUG 0
#define PRINT() \
	(!DEBUG) ? (std::cout << "") : std::cout

class Solution {
public:
	Solution() : _FAIL_FLAG(0) {}

    int minStickers(vector<string>& stickers, string target) {
		_FAIL_FLAG = 1 + target.size();  //如果stickers能够拼成target，那么每张sticker即便只贡献target中一个字符，最差也只需要target.size()张stickers
		// 将string target转换成map，记录每个字符出现的次数
		DICT targetChars;
		for (auto const ch : target) {
			auto iter = targetChars.find(ch);
			if (iter != targetChars.end()) {
				iter->second++;
			} else {
				targetChars.emplace(ch, 1);
			}
		}

		// 将所有sticker上的string，转换成字符出现的次数的map，便于查询，
		// 同时丢弃掉无用的字符
		vector<DICT> stickersMap;
		auto countChars = [&targetChars] (const string& sticker, DICT& cmap) {
			for (auto ch : sticker) {
				if (targetChars.find(ch) != targetChars.end()) {
					auto iter = cmap.find(ch);
					if (iter != cmap.end()) {
						iter->second++;
					} else {
						cmap.emplace(ch, 1);
					}
				}
			}
		};
		for (auto & str : stickers) {
			DICT cmap;
			countChars(str, cmap);
			if (!cmap.empty()) {
				stickersMap.emplace_back(std::move(cmap));
			}
		}

		// sticker存在包含关系，将被包含的sticker去掉，从而极大的减少dp所有遍历的状态
		std::sort(stickersMap.begin(), stickersMap.end(), [] (DICT& a, DICT& b) {
				    return (a.size() < b.size() ? true : false);
				});
		vector<DICT> optimizedMap;
		// check if b includes a
		auto checkInclusion = [] (DICT& a, DICT& b) {
		    DICT::iterator iter;
			for (auto p : a) {
				iter = b.find(p.first);
				if (iter == b.end()) {
					return false;
				} else if (iter->second < p.second) {
					return false;
				}
			}
			return true;
		};
		for (int i = 0; i < stickersMap.size(); ++i) {
			bool inclusionByAnotherSticker = false;
			for (int j = stickersMap.size()-1; j > i; --j) {
				if (checkInclusion(stickersMap[i], stickersMap[j])) {
					inclusionByAnotherSticker = true;
					break;
				}
			}
			if (!inclusionByAnotherSticker) {
				optimizedMap.emplace_back(stickersMap[i]);
			}
		}
		std::swap(stickersMap, optimizedMap);

		/*
		for (auto const& cmap : stickersMap) {
			for (auto p : cmap) {
				std::cout << p.first << "|" << p.second << " ";
			}
			std::cout << std::endl;
		}
		std::cout << "===============================\n";
		*/

		// dp状态，target string每个字符都只有：被sticker上的字符消除或者还未被消除两种状态
		// 所以一共有2^m种状态，共需要m位bit。本题中m<=15，所以用int即可。
		int targetStatus = (1<<target.size()) - 1;

		PRINT() << "DEBUG1: targetStatus: " << targetStatus 
			      << "| stickers size: " << stickersMap.size() << std::endl;

		
		// dp状态数组
		vector<vector<int>> dp(targetStatus + 1, vector<int>(stickersMap.size(), -1));

		int result = run(target, targetStatus, dp, stickersMap, 0); 

		return (result < _FAIL_FLAG ? result : -1);
    }

	int run(const string& target, int targetStatus, vector<vector<int>>& dp, vector<DICT>& stickersMap, int i) {
		PRINT() << "DEBUG2 targetStatus: " << targetStatus
			      << "| i: " << i << std::endl;
		if (i >= stickersMap.size() && targetStatus != 0) {
			return _FAIL_FLAG;
		}
		if (targetStatus == 0) {
			return 0;
		}
		if (dp[targetStatus][i] != -1) {
			return dp[targetStatus][i];
		}
		DICT& cmap = stickersMap[i];
		int oriTargetStatus = targetStatus;
		int minNeedNum = _FAIL_FLAG;
		DICT::iterator iter;
		for (int x = 0; x <= target.size(); ++x) {   // 对于一个sticker，可能会使用0次或者多次
			if (x > 0) {
				DICT t(cmap);
				bool change = false;
				for (int k = 0; k < target.size(); ++k) {
					if ( ((1<<(target.size()-k-1)) & targetStatus) != 0 &&    // 通过状态bit判断target中某位字符是否还未被消除
						(iter=t.find(target[k])) != t.end() &&               // 判断stickersMap[i]中是否还有该字符
						iter->second > 0) {

						PRINT() << "[x=" << x << "] k: " << k  << "|bit: " << (1<<(target.size()-k-1)) << std::endl;
						targetStatus ^= 1<<(target.size()-k-1);   // 通过异或操作修改target状态
						t[target[k]]--;
						change = true;
					}
				}
				if (!change) {
					break;
				}
			}
			minNeedNum = std::min(minNeedNum, x+run(target, targetStatus, dp, stickersMap, i+1));
			PRINT() << "MARK: x|" << x << ", targetStatus|" << targetStatus << ", i+1|" << i+1 << ", min|" << minNeedNum << std::endl;
		}
		dp[oriTargetStatus][i] = minNeedNum;
		PRINT() << "DEBUG3 <targetStatus,i>: <" << oriTargetStatus << ", " << i << "> : " << minNeedNum << std::endl;
		return dp[oriTargetStatus][i];
	}

private:
	int _FAIL_FLAG;

};

int main() {
	Solution sol;
	/* 3
	vector<string> stickers = {"with","example","science"};
	string target = "thehat";
	*/
	/* -1
	vector<string> stickers = {"notice","possible"};
	string target = "basicbasic";
	*/

	/* 3
	vector<string> stickers = {"these","guess","about","garden","him"};
    string target = "atomher";
	*/

	/* 9 */
	vector<string> stickers = {"indicate","why","finger","star","unit","board","sister","danger","deal","bit","phrase","caught","if","other","water","huge","general","read","gold","shall","master","men","lay","party","grow","view","if","pull","together","head","thank","street","natural","pull","raise","cost","spoke","race","new","race","liquid","me","please","clear","could","reply","often","huge","old","nor"};
    string target = "fhhfiyfdcwbycma";

	std::cout << sol.minStickers(stickers, target) << std::endl;
	
	return 0;
}
