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
    bool isSubtree(TreeNode* s, TreeNode* t) {
 		if(s == NULL) return false;
 		if (isSameTree(s, t)) return true;
 		return isSubtree(s->left, t) || isSubtree(s->right, t);

 		}

 	bool isSameTree(TreeNode* s, TreeNode* t) {
 		if (s == NULL && t == NULL) return true;
 		if (s == NULL || t == NULL) return false;
 		if (s->val == t->val)
 			return isSameTree(s->left, t->left) && isSameTree(s->right, t->right);
 		return false;
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
    bool isSubtree(TreeNode* s, TreeNode* t) {
        string ss = serialize(s);
        string tt = serialize(t);
        if (ss.find(tt) != string::npos) {
        	return true;
        }
        return false;

    }

    string serialize( TreeNode* s) {
    	if ( s == NULL )
    		return ",#";
    	return "," + to_string(s->val) + serialize(s->left) + serialize(s->right);
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
    bool isSubtree(TreeNode* s, TreeNode* t) {
        string ss = serialize(s);
        string tt = serialize(t);
        if (ss.find(tt) != string::npos) {
        	return true;
        }
        return false;

    }

    string serialize( TreeNode* s) {
    	stack<TreeNode* > nodeStack;
    	string ss;
    	nodeStack.push(s);
    	while(!nodeStack.empty()) {
    		auto node = nodeStack.top();
    		nodeStack.pop();
    		if (node == NULL)
    			ss += ",#";
    		else ss += "," + to_string(node->val);
    		if (node->right) 
            nodeStack.push(node->right); 
        if (node->left) 
            nodeStack.push(node->left); 
   
    	}
    	return ss;
    }
};
