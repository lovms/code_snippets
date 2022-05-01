/*
 * 这是树形dp的入门题。
 * 由于直接相邻的父母-孩子节点不能同时被偷盗，否则会触发报警，因此，每一个节点就会有两种状态：被偷或者不被偷。
 * 最终在root节点比较，root节点被偷或者不被偷两种状态下，获得的金额较大者为最优解。
 *  
 * 由于每个节点只需要用到孩子节点的偷盗累计值，所以，我直接用两个变量分别保存，层层返回了。
 * 也可以像力扣上的题解一样，用unordered_map来保存下中间值。
 */

#include <iostream>
#include <vector>
using std::vector;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    int rob(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }

        int dp0 = 0;
        int dp1 = 0;
        downTrip(root, dp0, dp1);
        return std::max(dp0, dp1);

    }

    void downTrip(TreeNode* node, int& dp0, int&dp1) {
        if (node == nullptr) {
            return;
        }
        int ldp0 = 0;
        int ldp1 =0;
        int rdp0 = 0;
        int rdp1 = 0;
        dp1 += node->val;
        std::cout << "val: " << node->val << std::endl;
        if (node->left != nullptr) {
            downTrip(node->left, ldp0, ldp1);
            dp1 += ldp0;                        // 这里需要注意，dp1意味者该节点被盗，那么孩子节点就要一定不能盗
            dp0 += std::max(ldp1, ldp0);        // 但dp0意味者不偷该节点，那么孩子节点其实有两种选择，需要比较大小；而不是说孩子节点一定要偷！！！
        }
        if (node->right != nullptr) {
            downTrip(node->right, rdp0, rdp1);
            dp1 += rdp0;
            dp0 += std::max(rdp0, rdp1);
        }
    } 
};

// values like [3,2,3,-1(null),3,-1(null),1]
void buildTree(vector<TreeNode*>& ttree, vector<int>& values) {
    if (ttree.size() != values.size()) {
        return;
    }

    for (int i = values.size()-1; i >= 0; --i) {
        if (values[i] == -1) continue;
        ttree[i] = new TreeNode(values[i]);
        if (2*i+1 < ttree.size() &&
            values[2*i+1] != -1) {
            ttree[i]->left = ttree[2*i+1];
        }
        if (2*i+2 < ttree.size() &&
            values[2*i+2] != -1) {
            ttree[i]->right = ttree[2*i+2];
        }
    }
}

void destroyTree(vector<TreeNode*>& ttree) {
    for (auto& it : ttree) {
        delete it;
    }
}

int main() {
    //vector<int> values = {3,2,3,-1,3,-1,1}; // 7
    //vector<int> values = {3,4,5,1,3,-1,1}; // 9
    vector<int> values = {4,1,-1,2,-1,3}; // 7 ,这个case似乎有点问题，最后3这个节点挂在空节点上？？？ 我这里跑结果是6，但提交上去是可以ac的
    vector<TreeNode*> ttree(values.size(), nullptr);
    buildTree(ttree, values);
    TreeNode* root = ttree[0];
    for (auto it : ttree) {
        if (it != nullptr) {
            std::cout << "val: " << it->val
                << "-left: " << (it->left == nullptr ? -1 : it->left->val)
                << "-right: " << (it->right == nullptr ? -1 : it->right->val)
                << ";" << std::endl;
        }
    }

    Solution sol;
    std::cout << sol.rob(root) << std::endl;
    destroyTree(ttree);
    return 0;
}
