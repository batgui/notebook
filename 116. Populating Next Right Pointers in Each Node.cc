/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() {}

    Node(int _val, Node* _left, Node* _right, Node* _next) {
        val = _val;
        left = _left;
        right = _right;
        next = _next;
    }
};
*/
class Solution {
public:
    Node* connect(Node* root) {
        if (root == NULL) return root;
        Node* pre = root;
        Node* cur;
        while (pre -> left) {
            cur = pre;
            while (cur) {
            cur -> left -> next = cur -> right;
            if (cur -> next)
                cur -> right -> next = cur -> next -> left;
            cur = cur -> next;
            }
            pre = pre -> left;
        }

        return root;
    }
};


class Solution {
public:
    Node* connect(Node* root) {
        if (root == NULL) return root;

        if (root -> left) {
            root -> left -> next = root -> right;
            if (root -> next) {
                root -> right -> next = root -> next -> left;
            }
        }
        connect(root -> left);
        connect(root -> right);
        return root;

    }
};