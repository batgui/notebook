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
    int rangeSumBST(TreeNode* root, int L, int R) {
        if (root == NULL) {
            return 0;

        }
        else {
        	return (root->val >= L && root->val <= R ? root->val : 0) + rangeSumBST(root->left, L, R) + rangeSumBST(root->right, L, R);
        }

    }
};

class Solution {
public:
    int rangeSumBST(TreeNode* root, int L, int R) {
        if (root == NULL) {
            return 0;
        }
        if (root->val < L) {
        	return rangeSumBST(root->right, L, R);
        }
        if (root->val > R) {
        	return rangeSumBST(root->left, L, R);
        }
        return root->val + rangeSumBST(root->left, L, R) + rangeSumBST(root->right, L, R);


    }
};


class Solution {
public:
    int rangeSumBST(TreeNode* root, int L, int R) {
        if (root == NULL) {
            return 0;
        }
        auto sum = 0;
        if (root->val >= L) {
        	sum += rangeSumBST(root->left, L, R);
        }
        if (root->val <= R) {
        	sum += rangeSumBST(root->right, L, R);
        }
        if (root->val >= L && root->val <= R) { sum += root->val; } // count root in.
        return sum;

		

    }
};


class NumArray {
public:
    NumArray(vector<int>& nums) {
    	int n = nums.size();
        vector<int> d(n,0);

        for(int  i = 1; i < nums.size(); i++ ) {
        	d[i] = d[i - 1] +  nums[i - 1];

        }
        c = d;
    }
    
    int sumRange(int i, int j) {

    	if (i == 0) {
    		return c[j];
    	}
        return c[j] - c[i - 1];
    }
private:
	vector<int> c;
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(i,j);
 */