/*
 * 本题可以用树形dp求解。
 *
 * 子问题分析：对于以节点i为root的子树，dp[i]是以i为端点（路径的起点或终点）最大路径值，
 *
 * 存在以节点i为端点的三条路径: 
 * --> dp[root->left] + value(i)   // i和它左子树相连的路径, 注意dp的定义，dp[root->left]所表示的路径一定是以root->left为端点的，所以dp[root->left]和value[i]一定是能组成新的路径！！
 * --> dp[root->right] + value(i)  // i和它右子树相连的路径
 * --> value[i]单独   //千万不要忘记了！！！ 如果 dp[root->left] <=0 并且 dp[root->right] <=0, 那么value[i]一定比上面两条路径大的
 *
 * 存在以节点i为中间节点的两条路径：
 * -->  dp[root->left] + value[i] + dp[root->right]
 * -->  value[parent of i] + dp[i]  //上升到父亲问题了,实际上包含多条路径的比较
 *
 *  因为是树形dp，使用递归实现是比较方便的，可以看到上面4条路径是在子问题中比较出来最优的。
 *  递归函数dp()返回的就是 dp[i]。
 *
 */

#include <iostream>
#include <vector>
#include <cassert>

using std::vector;
struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(): val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left,TreeNode* right): val(x), left(left), right(right) {}
};

class Solution {
public:
	Solution(): _globalMax(-(3e+8)) {}
    int maxPathSum(TreeNode* root) {
		dp(root);

		return _globalMax;

    }

	int dp(TreeNode* root) {
		if (root == nullptr) {
			return 0;
		}

		if (_globalMax < root->val) { // path only consists of the root node
			_globalMax = root->val;
		}

		int leftSubTreeMax = root->val + dp(root->left);   // val + dp[i->left]
		int rightSubTreeMax = root->val + dp(root->right); // val + dp[i->right]
		std::cout << "mark1 val|" << root->val << ", left|" << leftSubTreeMax << ", right|" << rightSubTreeMax << std::endl;

		int crossRootPath = leftSubTreeMax + rightSubTreeMax - root->val;  // dp[i->left] + val + dp[i->right]
		if (crossRootPath > _globalMax) {
			_globalMax = crossRootPath;
		}

		if (leftSubTreeMax > _globalMax) {
			_globalMax = leftSubTreeMax;
		}

		if (rightSubTreeMax > _globalMax) {
			_globalMax = rightSubTreeMax;
		}

		return std::max(root->val, std::max(leftSubTreeMax, rightSubTreeMax));  // dp[i]
	}

private:
    int _globalMax;
};

void buildTree(vector<TreeNode*>& myTree, vector<int>& values) {
	assert(myTree.size() == values.size());
	for (int i = values.size()-1; i >= 0; --i) {
		if (values[i] <= -10000) {
			continue;
		}
		myTree[i] = new TreeNode(values[i]);
		if (2*i+1 < myTree.size()) {
			myTree[i]->left = myTree[2*i+1];
		}
		if (2*i+2 < myTree.size()) {
			myTree[i]->right = myTree[2*i+2];
		}
	}
}

void destroy(TreeNode* root) {
	if (root == nullptr) {
		return;
	}
	destroy(root->left);
	destroy(root->right);
	delete root;
}

int main() {
	Solution sol;
	//vector<int> values = {-10,9,20,-10000,-10000,15,7};
	//vector<int> values = {2,1,3};
	//vector<int> values = {2, -1, -2}; // 2
	vector<int> values = {9, 6, -3, -10000, -10000, -6, 2, -10000, -10000, -10000, -10000, -10000, -10000, 2, -10000,
	                      -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000,
	                      -6, -6};  // 16
	vector<TreeNode*> myTree(values.size(), nullptr);
	buildTree(myTree, values);
	std::cout << sol.maxPathSum(myTree[0]) << std::endl;
	destroy(myTree[0]);
	return 0;
}
