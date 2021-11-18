#pragma once
#include "Tree.h"
class Stack
{
    struct Node {
        char data;
        Node* next;
    };
    Node* top;
public:
    Stack();
    ~Stack();
    void print();
    void clear();
    bool isEmpty();
    Node* getTop();
    char peek();
    void push(char value);
    char pop();
};
class TreeStack
{
    struct Node {
        Tree::TreeNode* data;
        Node* next;
    };
    Node* top;
public:
    TreeStack();
    ~TreeStack();
    void clear();
    bool isEmpty();
    Node* getTop();
    Tree::TreeNode* peek();
    void push(Tree::TreeNode* value);
    Tree::TreeNode* pop();
};

