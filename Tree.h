#pragma once
#include <iostream>
class Tree
{
public:
	struct TreeNode {
		char val;
		TreeNode* left;
		TreeNode* right;
		TreeNode() : val(0), left(nullptr), right(nullptr) {}
		TreeNode(char x) : val(x), left(nullptr), right(nullptr) {}
		TreeNode(char x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
	};
private:
	TreeNode* root;
	void clear(TreeNode*& node);
	void treeTransform(TreeNode* r);
public:
	Tree();
	~Tree();
	void clear();
	void print(const std::string& prefix, const TreeNode* node, bool isLeft);
	void print();
	void parseToTree(std::string s);
	void treeTransform();
	TreeNode* copyInOrder(TreeNode* root);
};

