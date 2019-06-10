

class Solution {
public:
    vector<TreeNode*> generateTrees(int n) {
        if (n == 0)
            return new vector<TreeNode*>;
        //if (n == 0) return new vector<TreeNode*>;
        return generateTrees(1, n);


    }
    vector<TreeNode*> generateTrees(int start, int end) {
        vector<TreeNode*> res;
        if (start > end) {
            res.push_back(NULL);
            return res;
        }
        if (start == end) {
            res.push_back(new TreeNode(start));
            return res;
        }
        for (int i = start; i <= end; i++) {
            vector<TreeNode*> left = generateTrees(start, i - 1);
            vector<TreeNode*> right = generateTrees(i + 1, end);
            
            for(auto l : left) {
                for (auto r : right) {
                    TreeNode* root = new TreeNode(i);
                    root->left = l;
                    root->right = r;
                    res.push_back(root);
                }
            }
        }
        return res;
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
    vector<TreeNode*> generateTrees(int n) {
        vector<vector<TreeNode*>> vec(n + 1);
            if (n == 0) return vec[0];
            vec[0] = NULL;
            for (int i = 1; i <= n; i++) {

                for(int j = 1; j <= i; j ++) {
                    
                    for(auto l : vec[j - 1]) {
                        for(auto r : vec[i - j]) {
                            TreeNode * root = new TreeNode(j);
                            r = clone(r, j + 1);
                            root->left = l;
                            root->right = r;
                            vec[i].push_back(root);

                        }
                    }
                }
            }
        return vec[n];
    }
    TreeNode* clone(TreeNode* r, int offset) {
        if(r == NULL) return NULL;
        TreeNode * root = new TreeNode(r.val + offset);
        if (r->left) {
            clone(r->left, offset);
        }
        if (r->right) {
            clone(r->right, offset);
        }
        return root;

    }
};