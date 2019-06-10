/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool hasPathSum(TreeNode* root, int sum) {
    	if (root == NULL) return false;
    	if (root->left == NULL && root->right == NULL && sum - root->val == 0) return true;
    	return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);
    }

};



/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool hasPathSum(TreeNode* root, int sum) {
        stack<TreeNode *> s;
        int total = 0;
        TreeNode *pre = NULL, *cur = root;
        while (cur || !s.empty()) {
        	while (cur) {
        		s.push(cur);
        		total += cur->val;
        		cur = cur->left;

        	}
        	cur = s.top();
        	if (cur->left == NULL && cur->right == NULL && sum == total);
        		return true;
        	if (cur->right && pre != cur->right) {
        		cur = cur->right;
        		else {
        			pre = cur;
        			s.pop();
        			total -= cur->val;
        			cur = NULL;
        		}

        	}
        } 
        return false;
    }
};