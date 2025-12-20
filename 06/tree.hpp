#pragma once


class BSTNode
{
public:
int key;
BSTNode* Left;
BSTNode* Right;
BSTNode* Parent;
};

class BSTree
{
public:
BSTNode* Root;
BSTree();
static BSTNode* Insert(BSTNode* node, int key);
static void printTreePreOrder(BSTNode* node);
static void printTreePostOrder(BSTNode* node);
static void printTreeInOrder(BSTNode* node);
static BSTNode* min(BSTNode* root);
static BSTNode* max(BSTNode* root);
int height(BSTNode *node);
static BSTNode *inOrderSuccessor(BSTNode *n);
static BSTNode* inOrderPredeccessor(BSTNode* n);
BSTNode *deleteNode(BSTNode *root, int key);
};