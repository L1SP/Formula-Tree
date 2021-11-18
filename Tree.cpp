#include "Tree.h"
#include "Stack.h"
#include "Queue.h"
Tree::Tree() {
	root = nullptr;
}
Tree::~Tree() {
	clear();
}

void Tree::clear(TreeNode*& node) {
	if (node) {
		clear(node->left);
		clear(node->right);
		delete node;
		node = nullptr;
	}
}
void Tree::clear() {
	clear(root);
}
void Tree::print(const std::string& prefix, const TreeNode* node, bool isLeft) {
	if (node) {
		std::cout << prefix;
		std::cout << (isLeft ? u8"├── " : u8"└── ");
		std::cout << node->val << std::endl;
		print(prefix + (isLeft ? u8"│   " : u8"    "), node->left, true);
		print(prefix + (isLeft ? u8"│   " : u8"    "), node->right, false);
	}
}
void Tree::print() {
	print("", root, false);
}
void Tree::parseToTree(std::string postfix) {
	TreeStack* st = new TreeStack;
	TreeNode* temp_tree1;
	TreeNode* temp_tree2;
	for (unsigned int i = 0; i < postfix.length(); ++i) {
		if (!(postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*'))
		{
			root = new TreeNode(postfix[i]);
			st->push(root);
		}
		else
		{
			root = new TreeNode(postfix[i]);
			temp_tree1 = st->pop();
			temp_tree2 = st->pop();
			root->right = temp_tree1;
			root->left = temp_tree2;
			st->push(root);
		}
	}
	delete st;
}
Tree::TreeNode* Tree::copyInOrder(Tree::TreeNode* root) {
	if (root == nullptr)
		return nullptr;
	else {
		TreeNode* tmp = new TreeNode;
		tmp->val = root->val;
		tmp->right = copyInOrder(root->right);
		tmp->left = copyInOrder(root->left);
		return tmp;
	}
}
void Tree::treeTransform() {
	treeTransform(root);
}
void Tree::treeTransform(TreeNode* r) {
	TreeNode* copyTree1;
	TreeNode* copyTree2;
	if (!r)
		return;
	if (r->left && (r->left->val == '-' || r->left->val == '+')) {
		char sign = r->left->val;
		copyTree1 = copyInOrder(r->right);
		delete r->right->left;
		delete r->right->right;
		copyTree2 = copyInOrder(r->left->right);
		delete r->left->right;
		r->left->val = '*';
		r->val = sign;
		r->right->val = '*';
		r->right->right = copyTree1;
		r->right->left = copyTree2;
		r->left->right = copyInOrder(copyTree1);
		treeTransform(r);
		treeTransform(r->left);
		treeTransform(r->right);
	}
	else if (r->right && (r->right->val == '-' || r->right->val == '+')) {
		char sign = r->right->val;
		copyTree1 = copyInOrder(r->left);
		delete r->left->left;
		delete r->left->right;
		copyTree2 = copyInOrder(r->right->left);
		delete r->right->left;
		r->left->val = '*';
		r->val = sign;
		r->right->val = '*';
		r->left->left = copyTree1;
		r->left->right = copyTree2;
		r->right->left = copyInOrder(copyTree1);
		treeTransform(r);
		treeTransform(r->left);
		treeTransform(r->right);
	}
	else {
		treeTransform(r->left);
		treeTransform(r->right);
	}
	

}