//Given a binary tree, write a function to get the maximum width of the given tree. The maximum width of a tree is the maximum width among all levels.
//
//The width of one level is defined as the length between the end-nodes (the leftmost and right most non-null nodes in the level, where the null nodes between the end-nodes are also counted into the length calculation.
//
//It is guaranteed that the answer will in the range of 32-bit signed integer.
//
//Example 1:
//
//Input: 
//
//           1
//         /   \
//        3     2
//       / \     \  
//      5   3     9 
//
//Output: 4
//Explanation: The maximum width existing in the third level with the length 4 (5,3,null,9).
//Example 2:
//
//Input: 
//
//          1
//         /  
//        3    
//       / \       
//      5   3     
//
//Output: 2
//Explanation: The maximum width existing in the third level with the length 2 (5,3).
//Example 3:
//
//Input: 
//
//          1
//         / \
//        3   2 
//       /        
//      5      
//
//Output: 2
//Explanation: The maximum width existing in the second level with the length 2 (3,2).
//Example 4:
//
//Input: 
//
//          1
//         / \
//        3   2
//       /     \  
//      5       9 
//     /         \
//    6           7
//Output: 8
//Explanation:The maximum width existing in the fourth level with the length 8 (6,null,null,null,null,null,null,7).
// 
//
//Constraints:
//
//The given binary tree will have between 1 and 3000 nodes.
//
//来源：力扣（LeetCode）
//链接：https://leetcode-cn.com/problems/maximum-width-of-binary-tree
//著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。


// 思路:
// 1. 本题中首先要理解定义的层宽，实际上是给定数每层
// 的最左端，最右端的节点，以及其在对应的满二叉树上的序号的差值！！
// 
// 2. 这和一般的将"每层的非空节点数目定义成层宽"是不一样的。
//
// 3. 需要注意的是，题目中保证了层宽是32位的整数，但是对应的满二叉数的
// 序号肯定就超过了32位了，这个地方一开始我就没注意，导致提交没过。
// 换成unsigned long long就可以了。(第0层的层宽为1，第i层层宽为2^i，
// i最大32，32层满二叉树节点总共有2^0+2^1+...+2^31 = (2^32-1)，所以
// 64位整数肯定是够的）
#include <utility>
#include <queue>
#include <vector>
#include <iostream>

using std::queue;
using std::pair;
using std::vector;
/**
 * Definition for a binary tree node.*/
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
/* */
class Solution {
public:
    int widthOfBinaryTree(TreeNode* root) {
		if (root == nullptr) {
			return 0;
		}
		if (root->left == nullptr && root->right == nullptr) {
			return 1;
		}

		queue<pair<TreeNode*, unsigned long long> > layers;
        layers.emplace(root, 1);
		int layerSize = 1;
		unsigned long long maxWidth = 1;
		unsigned long long first = 0;
		unsigned long long last = 0;
		while (!layers.empty()) {
			layerSize = layers.size();
			for (int i = 0; i < layerSize; ++i) {
				TreeNode* cur = std::get<0>(layers.front());
				unsigned long long seq = std::get<1>(layers.front());
				layers.pop();
				if (cur->left != nullptr) {
					layers.emplace(cur->left, 2*seq);
				} 
				if (cur->right != nullptr) {
					layers.emplace(cur->right, 2*seq+1);
				}
				if (i == 0) {
					first = seq; 
				}
				if (i == layerSize-1) {
					last = seq;
				}

			}

			if (last - first + 1 > maxWidth) {
				maxWidth = last - first + 1;
			}
		}
		return maxWidth;
    }

};

class BinaryTree {
public:
	BinaryTree() : root(nullptr) {}
	void buildTree(vector<int>& nums) {
		// node starts from index of 1
		// nums[0] should always be -1 !!!!
		tree.resize(nums.size(), nullptr);
		for (int i = nums.size()-1; i > 0; --i) {
			if (nums[i] != -1) {
				tree[i] = new TreeNode(nums[i]);
				if (2*i < nums.size()) {
					tree[i]->left = tree[2*i];
				} 
				if (2*i+1 < nums.size()) {
					tree[i]->right = tree[2*i+1];
				}
			}
		}
		root = tree[1];
	}

	void destroyTree() {
		for (int i = 1; i < tree.size(); ++i) {
			if (tree[i] != nullptr) {
				delete tree[i];
			}
		}
	}

public:
	TreeNode* root;
	vector<TreeNode*> tree;
};

int main() {
	//vector<int> nums = {-1,1,3,2,5,3,-1,9};
	//vector<int> nums = {-1,1,3,-1,5,3};
	//vector<int> nums = {-1,1,3,2,5,-1};
	vector<int> nums = {-1,1,2,-1};
	BinaryTree bt;
	bt.buildTree(nums);

	Solution s;
	std::cout << s.widthOfBinaryTree(bt.root) << std::endl;

	bt.destroyTree();
	return 0;
}
