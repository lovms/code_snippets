/**
 * 本题的BST定义正好符合“中序遍历”结果升序，所以实现上以类似递归式的中序遍历：
 * 1）isBST(root->left)
 * 2) checkOrder: leftMax <  root->val < rightMin;
 * 3) isBST(root->right)
 * 对于每个节点，考察其左右子树是否是BST，如果是则获取其权重加和；
 * 如果左子树是BST，则应该返回其最右侧节点，实际上就是左子树的最小值；
 * 如果右子树是BST，则应该返回其最左侧节点，实际上就是右子树的最大值；
 */

#include <iostream>
#include <queue>
#include <unordered_map>
/**
 * Definition for a binary tree node.
 */
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
using Q=std::queue<TreeNode*>;

class Solution {
public:
	Solution(): _maxSum(0) {}
    int maxSumBST(TreeNode* root) {
		int sum = 0;
		int a, b = 0;
		isBST(root, sum, a, b);
		return _maxSum;
    }

	bool isBST(TreeNode* root, int& sum, int& minV, int& maxV) {
		auto checkOrder = [] (TreeNode* root, int lVal, int rVal) {
			if (root == nullptr) return true;
			if (root->left != nullptr) {
				if (lVal >= root->val) {
				    return false;
				}
			}
			if (root->right != nullptr) {
				if (rVal <= root->val) {
					return false;
				}
			}
			return true;
		};

		if (root == nullptr) {
			sum = 0;
			return true;
		}
		int lSum = 0;
		int rSum = 0;
		int lMin = 999999, lMax = -999999;
		int rMin = 999999, rMax = -999999;
		bool checkLeftSub = isBST(root->left, lSum, lMin, lMax);
		bool checkRightSub = isBST(root->right, rSum, rMin, rMax);

		minV = std::min(root->val, lMin);
		minV = std::min(minV, rMin);

		maxV = std::max(root->val, lMax);
		maxV = std::max(maxV, rMax);

		/*
		std::cout << "Debug: val: " << root->val << ",minV: " << minV << "; maxV: " << maxV
			      << ";lMin: " << lMin << ";lMax: " << lMax
				  << ";rMin: " << rMin << ";rMax: " << rMax << std::endl;
		*/
	    if (checkLeftSub && checkOrder(root, lMax, rMin) && checkRightSub) {
			sum = lSum + root->val + rSum;
			if (sum > _maxSum) {
				_maxSum = sum;
			}
			return true;
		}
		return false;
	}

private:
	int _maxSum;
};

void buildTree(std::vector<int>& tree, TreeNode** root) {
	Q nodes;
	*root = new TreeNode(tree[0]);
	if ((*root) == nullptr) {
		std::cout << "Debug: XXX  null " << std::endl;
	}
	nodes.push(*root);
	int i = -1;
	while (!nodes.empty()) {
		TreeNode* cur = nodes.front();
		i++;
		std::cout << "Debug: build on ith node: " << i << "," << cur->val << std::endl;
		if (2*i+1 < tree.size() && tree[2*i+1] < 999999) {
			cur->left = new TreeNode(tree[2*i+1]);
			nodes.push(cur->left);
		} else {
		    cur->left = nullptr;
		}
		if (2*i+2 < tree.size() && tree[2*i+2] < 999999) {
			cur->right = new TreeNode(tree[2*i+2]);
			nodes.push(cur->right);
		} else {
		    cur->right = nullptr;
	    }
		nodes.pop();
	}

}

void printTree(TreeNode* root) {
	if (root == nullptr) {
		return;
	}
	printTree(root->left);
	std::cout << root-> val << ";";
	printTree(root->right);
}

void destroyTree(TreeNode* root) {
}

int main() {
	std::vector<int> tree = {1,4,3,2,4,2,5,999999,999999,999999,999999,999999,999999,4,6};
	//std::vector<int> tree = {4,3,999999,1,2};
	//std::vector<int> tree = {-4, -2, -5};
	//std::vector<int> tree = {1,999999,10,-5,20};
	TreeNode* root = nullptr;
	buildTree(tree, &root);
	std::cout << "Debug: finish to build tree" << std::endl;
	printTree(root);
	//std::cout << "root-left: " << root->left->val << " # root-right" << root->right->val << std::endl; 
	std::cout << "\n---------------------------------" << std::endl;
	Solution sol;
	int res = sol.maxSumBST(root);
	std::cout << "Result: " << res << std::endl;
    return 0;
}
