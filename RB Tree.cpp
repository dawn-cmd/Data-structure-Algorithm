#include "bits/stdc++.h"
using namespace std;
class RBTree {
private:
    struct Node {
        int val;
        vector<string> data;
        bool is_red;
        Node *left, *right, *parent;
    };
    Node *root;
    Node *leftRotate(Node *cur) {
        //Store cur's right's left node in tmp
        Node *tmp = cur->right->left;
        //Set cur->right->left to cur
        cur->right->left = cur;
        //Set cur->parent as cur->right
        cur->right->parent = cur->parent;
        //Set cur->parent to cur->right
        cur->parent = cur->right;
        //Set cur->right to the previously stored tmp
        //node
        cur->right = tmp;
        //Set cur->parent->left to cur
        cur->parent->left = cur;
        //Set tmp's parent to cur
        tmp->parent = cur;
        //Determine root node when cur is being rotated.
        if (root == cur) {
            root = cur->parent;
        } else {
            //Check if Parent of the current node has cur as its left or right child
            if (cur->parent->parent->left == cur) {
                cur->parent->parent->left = cur->parent;
            } else {
                cur->parent->parent->right = cur->parent;
            }
        }
        //Return the new parent node
        return cur->parent;
    }
    Node *rightRotate(Node *cur) {
        // Store the subsidiary node before changing its pointer
        Node *tmp = cur->left->right;
        // Make the connection between the right child of left child and the current node
        cur->left->right = cur;
        // Update the parent pointer of the right child of left child
        cur->left->parent = cur->parent;
        // Move the parent pointer of the current node to its left child
        cur->parent = cur->left;
        // Replace the right child of the current node with the auxiliary node
        cur->left = tmp;
        // Connect the auxiliary node with the current node
        cur->parent->right = cur;
        // Move parent pointer from auxiliary node to cur
        tmp->parent = cur;
        // Check if the current node is root or not
        if (root == cur) {
            // If it's, update the root pointer to its parent
            root = cur->parent;
        }
        // Check if the grand parent of the current node has a left or right child
        else if (cur->parent->parent->left == cur) {
            // If it has a left child, that must be the parent of the current node
            cur->parent->parent->left = cur->parent;
        } else {
            // If it has a right child, that must be the parent of the current node
            cur->parent->parent->right = cur->parent;
        }
        return cur->parent;// Return new node after zig operation
    }
    // Function to insert a node and balance the tree
    void insertBalance(Node *cur) {
        // Set root node to be black
        if (cur == root) {
            cur->is_red = 0;
            return;
        }
        // Return if parent of current node is black
        if (!cur->parent->is_red) {
            return;
        }
        // If parent is the root, set it to black and terminate
        if (cur->parent == root) {
            root->is_red = 0;
            return;
        }
        // Initialise parent and uncle nodes
        Node *parent = cur->parent;
        Node *uncle = parent == parent->parent->left ? parent->parent->right : parent->parent->left;
        // If uncle is red, recolor both parent and uncle and call function again for parent's parent
        if (uncle != nullptr && uncle->is_red) {
            parent->is_red = 0;
            uncle->is_red = 0;
            parent->parent->is_red = 1;
            insertBalance(parent->parent);
            return;
        }
        // Perform zigzig or zagzag transformations
        if (parent->parent->left == parent && parent->right == cur) {
            cur = leftRotate(parent);
        } else if (parent->parent->right == parent && parent->left == cur) {
            cur = rightRotate(parent);
        } else {
            cur = parent;
        }
        // Perform either zig or zag transformation
        if (cur == cur->parent->left) {
            cur = rightRotate(cur->parent);
        } else {
            cur = leftRotate(cur->parent);
        }
        // Set colors of newly inserted node and its children
        cur->is_red = 0;
        if (cur->left != nullptr) {
            cur->left->is_red = 1;
        }
        if (cur->right != nullptr) {
            cur->right->is_red = 1;
        }
    }
    void removeBalance(Node *cur) {
        Node *bro = cur == cur->parent->left ? cur->parent->right : cur->parent->left;
        
    }
public:
    RBTree() {
        root = nullptr;
    }
    vector<string> search(int val) {
        Node *cur = root;
        while (cur != nullptr) {
            if (cur->val == val) {
                return move(cur->data);
            }
            cur = cur->val < val ? cur->left : cur->right;
        }
        vector<string> tmp;
        return move(tmp);
    }
    void insert(int val, const string &data) {
        if (root == nullptr) {
            root = new Node{val};
            root->is_red = 0;
            root->data.emplace_back(data);
            return;
        }
        Node *cur = root;
        Node *pre = nullptr;
        while (cur != nullptr) {
            pre = cur;
            if (val == cur->val) {
                cur->data.emplace_back(data);
                return;
            }
            if (val < cur->val) {
                cur = cur->left;
                continue;
            }
            if (val > cur->val) {
                cur = cur->right;
                continue;
            }
        }
        cur = new Node{val};
        cur->data.emplace_back(data);
        cur->is_red = 1;
        cur->parent = pre;
    }
    void remove(int val) {
        Node *cur = root;
        while (cur != nullptr) {
            if (cur->val == val) {
                break;
            }
            cur = cur->val < val ? cur->left : cur->right;
        }
        if (cur == nullptr) {
            return;
        }
        if (cur == root && cur->left == nullptr && cur->right == nullptr) {
            root = nullptr;
            return;
        }
        if (cur->left != nullptr && cur->right != nullptr) {
            Node *suc = cur->right;
            while (suc->left != nullptr) {
                suc = suc->left;
            }
            swap(suc->data, cur->data);
            swap(suc->val, cur->val);
            cur = suc;
        }
        if (cur->left == nullptr && cur->right == nullptr) {
            
        }
    }
};
int main() {
    return 0;
}
