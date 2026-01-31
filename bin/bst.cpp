#include <iostream>



struct BSTNode {
    int data;
    BSTNode* left;
    BSTNode* right;
    BSTNode(int val) : data(val), left(nullptr), right(nullptr) {}
    BSTNode() : data(0), left(nullptr), right(nullptr) {}
    BSTNode(const BSTNode& other) : data(other.data), left(nullptr), right(nullptr) {
        if (other.left) {
            left = new BSTNode(*other.left);
        }
        if (other.right) {
            right = new BSTNode(*other.right);
        }
    }
};


class BST {
private:
    BSTNode* root;

public:
    BST() : root(nullptr) {}
    void insert(int val) {
        if (!root) {
            root = new BSTNode(val);
            return;
        }

        BSTNode* current = root;
        while (true) {
            if (val < current->data) {
                if (!current->left) {
                    current->left = new BSTNode(val);
                    return;
                }
                current = current->left;
            } else {
                if (!current->right) {
                    current->right = new BSTNode(val);
                    return;
                }
                current = current->right;
            }
        }


    }

    void inorderTraversal(BSTNode* node) {
        if (node) {
            inorderTraversal(node->left);
            std::cout << node->data << " ";
            inorderTraversal(node->right);
        }
        
    }
};