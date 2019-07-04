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
        Node* head = NULL;
        Node* pre = NULL;
        Node* cur = root;
        while (cur != NULL) {
            while (cur != NULL) {
                if (cur -> left != NULL) {
                    if (head == NULL) {
                        head = cur -> left;
                    } else {
                        pre -> next = cur -> left;
                    }
                    pre = cur -> left; 
                }

                if (cur -> right != NULL) {
                    if (head == NULL) {
                        head = cur -> right;
                    } else {
                        pre -> next = cur -> right;
                    }
                    pre = cur -> right;
                }
                cur = cur -> next;

            }
            cur = head;
            pre = NULL;
            head = NULL;
        }
        return root;
    }
};
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
        
        
        Node* cur = root;

        while (cur != NULL) {
            Node* dummy = new Node(0, NULL, NULL, NULL);
            Node* temp = dummy;

            while (cur != NULL) {
                //cout << cur -> val << endl;
                if (cur -> left != NULL) {
                    temp -> next = cur -> left;
                    temp = temp -> next;

                }
                if (cur -> right != NULL) {
                    temp -> next = cur -> right;
                    temp = temp -> next;
                }
                cur = cur -> next;
            }
            cur = dummy -> next;
            

        }
        return root;
    }
};