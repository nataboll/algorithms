#include <iostream>
#include <set>
#include <utility>

//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {

    int max = 0;

    std::pair<int, int> search(TreeNode *root) {
        if (!root->left && !root->right)
            return std::make_pair(0, root->val);
        else {
            std::pair<int, int> ans_l, ans_r;
            if (root->left) {
                ans_l = search(root->left);
                if (ans_l.second == root->val) {
                    ans_l.first++;
                    max = std::max(max, ans_l.first);
                }
                else {
                    max = std::max(max, ans_l.first);
                    ans_l = std::make_pair(0, root->val);
                }
            }
            if (root->right) {
                ans_r = search(root->right);
                if (ans_r.second == root->val) {
                    ans_r.first++;
                    max = std::max(ans_r.first, max);
                }
                else {
                    ans_r = std::make_pair(0, root->val);
                    max = std::max(ans_r.first, max);
                }
            }
            if (root->val == ans_l.second && root->val == ans_r.second) {
                ans_l.first = ans_l.first + ans_r.first;
                max = std::max(ans_l.first, max);
            }
            return std::make_pair(std::max(ans_r.first, ans_l.first), root->val);
        }
    }

public:
    int longestUnivaluePath(TreeNode* root) {
        search(root);
        return max;
    }
};

int main() {
    TreeNode root(1);
    TreeNode r(1);
    TreeNode l(1);
    root.right = &r;
    root.left = &l;
//    TreeNode r1(4), l1(4), r2(5);
//    root.right->right = &r2;
//    root.left->left = &l1;
//    root.left->right = &r1;
    Solution sol;
    std::cout << sol.longestUnivaluePath(&root) << std::endl;
    return 0;
}
