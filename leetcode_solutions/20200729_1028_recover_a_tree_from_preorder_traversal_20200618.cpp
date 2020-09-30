//We run a preorder depth first search on the root of a binary tree.
//
//At each node in this traversal, we output D dashes (where D is the depth of this node), then we output the value of this node.  (If the depth of a node is D, the depth of its immediate child is D+1.  The depth of the root node is 0.)
//
//If a node has only one child, that child is guaranteed to be the left child.
//
//Given the output S of this traversal, recover the tree and return its root.
//
// 
//
//Example 1:
//
//
//
//Input: "1-2--3--4-5--6--7"
//Output: [1,2,5,3,4,6,7]
//Example 2:
//
//
//
//Input: "1-2--3---4-5--6---7"
//Output: [1,2,5,3,null,6,null,4,null,7]
// 
//
//Example 3:
//
//
//
//Input: "1-401--349---90--88"
//Output: [1,401,null,349,88,90]
// 
//
//Note:
//
//The number of nodes in the original tree is between 1 and 1000.
//Each node will have a value between 1 and 10^9.
//
//来源：力扣（LeetCode）
//链接：https://leetcode-cn.com/problems/recover-a-tree-from-preorder-traversal
//著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>

using std::cout;
using std::vector;
using std::string;
using std::endl;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* recoverFromPreorder(string S) {
		S = S + "-";  // use as a sentinel of ending
		std::stack<TreeNode*> roots;
		int s, e = 0;
		int value = -1;
		int last_layer = 0;
		int layer = 0;
		bool flag = true; // true when deal with a value
		TreeNode* the_root = nullptr;
		for (int i = 0; i < S.size(); i++) {
			if (S[i] == '-') {
				if (flag) {
    				value = std::stoi(S.substr(s, e-s));
					std::cout << value << " ; " << layer << " ; " << last_layer << std::endl;
    				TreeNode *x = new TreeNode(value);
    				//x.val = value;
					if (roots.empty()) {
						the_root = x;
						roots.push(x);
						last_layer = 0;
					} else {
						// 
						if (layer > last_layer) {
							TreeNode * my_root = roots.top();
							my_root->left = x;
							roots.push(x);
							last_layer = layer;
							std::cout << "add: " << value << " to " << my_root->val << std::endl;
						} else if (layer == last_layer) {
							roots.pop();
							TreeNode *my_root = roots.top();
							my_root->right = x;
							roots.push(x);
							std::cout << "add: " << value << " to " << my_root->val << std::endl;
						} else {
            				while (layer <= last_layer) {
            					roots.pop();
            					last_layer--;
            				}
							TreeNode *my_root = roots.top();
							my_root->right = x;
							roots.push(x);
        					last_layer = layer;
							std::cout << "add: " << value << " to " << my_root->val << std::endl;
						}
					}
    				layer = 1;
    				flag = false;
				} else {
					layer++;
				}
			} else {
				if (!flag) {
					s = i;
					e = s+1;
					flag = true;
				} else {
					e++;
				}
			}
		}

		return the_root;
    }
};

void doLayerWiseTraversalAnddestroyTheTree(TreeNode* root) {
	std::vector<TreeNode*> nodes;
	std::queue<TreeNode*> q;
	q.push(root);
	while (!q.empty()) {
		TreeNode* n = q.front();
		if (n == nullptr) {
			std::cout << "null" << ",";
			q.pop();
		} else {
			nodes.push_back(n);
			q.pop();
			std::cout << n->val << ",";
			if (n->left != nullptr) {
				q.push(n->left);
			} else if (n->right != nullptr) {
				q.push(nullptr);
			}
			if (n->right != nullptr) {
				q.push(n->right);
			} else if (n->left != nullptr) {
				q.push(nullptr);
			}

		}
	}
	std::cout << std::endl;

	for (int i = 0; i < nodes.size(); ++i) {
		delete nodes[i];
	}
}

void destroyTree(TreeNode* root) {

}

int main() {
    //std::string S ="1-2--3--4-5--6--7";
	std::string S = "1-2--3---4-5--6---7";
	Solution ac;
	TreeNode* out = ac.recoverFromPreorder(S);
	doLayerWiseTraversalAnddestroyTheTree(out);
	return 0;
}
