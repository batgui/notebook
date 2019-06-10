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
    int rob(TreeNode* root) {
     	if (root == NULL) return 0;
     	if (umap.find(root) != umap.end()) return umap[root];
     	int value = 0;
     	if (root->left) {
     		value += rob(root->left->left) + rob(root->left->right);
     	}
     	if (root->right) {
     		value += rob(root->right->left) + rob(root->right->right);
     	}
     	auto res = max(root->val + value, rob(root->left) + rob(root->right));
     	umap[root] = res;
	    return res;
	    }
private:
	unordered_map<TreeNode*, int> umap;
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
    int rob(TreeNode* root) {
  		vector<int> vec = rob2(root);
  		return max(vec[0], vec[1]);

    }
    vector<int> rob2(TreeNode* root) {
    	
    	vector<int> vec(2, 0);
    	if (root == NULL) return vec;
    	auto left = rob2(root->left);
    	auto right = rob2(root->right);
    	vec[0] = max(left[0], left[1]) + max(right[0], right[1]);
    	vec[1] = root->val + left[0] + right[0];
    	return vec;
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
    int rob(TreeNode* root) {
        return max(robInclude(root), robExclude(root));
    }
    int robInclude(TreeNode* root) {
    	if (root == NULL) return 0;
    	return robExclude(root->left) + robExclude(root->right) + root->val;
    }
    int robExclude(TreeNode* root) {
    	if (root == NULL) return 0;
    	return rob(root->left) + rob(root->right);
    }
};


