/*
 * 本题类似在二维空间上的路径寻优，将每个矩阵位置看作一个节点N,
 * 那么最优子结构可以如下定义：
 * 1) N(i-1,j) 可以向下移动到 N(i,j);
 * 2) 如果知道 N(i,j)位置所需的最小能量为 minHP; 那么 N(i-1, j)位置通过向下移动，所需的最小能量 则 为 max(1, minHP - lostHP(i, j));
 *    并且不需要知道 N(i-1, j)后续移动到终点的具体路径！！！
 * 
 * 根据最优子结构，可知，我们需要从终点开始往起点来递归迭代。
 *
 * 这里面有两处细节需要特别注意：
 * 1）从终点往起始点移动的路径有很多条，对于某个节点N(i,j)，虽然一步之内，只有 N(i+1,j)以及N(i, j+1)两个节点可以作为其后续路径节点,
 *    但经过N（i，j)实际上的路径却有很多条，因此，我们需要记录下到达N(i,j)所需最小的能量需求，否则，递归遍历可以提前结束了，否则会超时！
 * 2) 要时刻记住，任一时刻，knight所需的能量必须>=1
 */
#include <vector>
#include <iostream>
using std::vector;
#define MAX_INT 0x7FFFFFFF
class Solution {
public:
	Solution() : _maxInt(MAX_INT), _minimumHP(MAX_INT) {}
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
		int rows = dungeon.size();
		int cols = dungeon[0].size();
		vector<vector<int>> liveBar(rows, vector<int>(cols, _maxInt));

		moveBack(rows-1, cols-1, 1, liveBar, dungeon);
		return _minimumHP;
    }

	void moveBack(int r, int cl, int mHp, vector<vector<int>>& liveBar, vector<vector<int>> &dungeon) {
		int hp = mHp - dungeon[r][cl];
		//hp = hp <= 0 ? 1 : hp;  // hp must be at least 1 at any time, otherwise the knight would be dead immediately
		hp = std::max(1, hp);
		if (hp < liveBar[r][cl]) {
		    liveBar[r][cl] = hp;
		} else {
		    return;
		}
		std::cout << "Debug: " << r << "|" << cl << ", " << hp << std::endl;
		if (r == 0 && cl == 0) {
			if (_minimumHP > hp) {
				_minimumHP = hp;
				return;
			}
		}
		if (r-1>=0) {
			// up
			moveBack(r-1, cl, hp, liveBar, dungeon);
		} 

		if (cl-1>=0) {
			// to left
			moveBack(r, cl-1, hp, liveBar, dungeon);
		}
	}

private:
	int _minimumHP;
	const int _maxInt;
};

int main() {
	Solution sol;
	vector<vector<int>> dungeon;
	/* Input: dungeon = [[-2,-3,3],[-5,-10,1],[10,30,-5]]
     * Output: 7
     * Explanation: The initial health of the knight must be at least 7 if he follows the optimal path: RIGHT-> RIGHT -> DOWN -> DOWN.
	 */

	/*
	vector<int> t1 ={-2,-3,3};
	dungeon.push_back(t1);
	vector<int> t2 ={-5,-10,1};
	dungeon.push_back(t2);
	vector<int> t3 ={10,30,-5};
	dungeon.push_back(t3);
	*/
	/* Input: dungeon = [[0]]
     * Output: 1
	 */

	//vector<int> t = {0};
	//dungeon.push_back(t);
	
	/* Input: dungeon = [[-1,1]]
	 * Output: 2
	 */
    vector<int> t = {-1, 1};
	dungeon.push_back(t);
	std::cout << sol.calculateMinimumHP(dungeon) << std::endl;
	return 0;
}
