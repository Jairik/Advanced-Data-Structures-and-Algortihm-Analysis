// Specification file for the IntBinaryTree class
#ifndef INTBINARYTREE_H
#define INTBINARYTREE_H

class IntBinaryTree {
private:
	struct TreeNode {
		int value;
		TreeNode *left;
		TreeNode *right;
	};

	TreeNode *root;

	int maxInt; //Holds the maximum value in the tree

	// Private member functions
	void IndentBlock(int);
	void PrintTree(TreeNode*, int, int);
	TreeNode *makeCompleteBinaryTree(int, int, int *, int&, int);
	void getRootedArray(IntBinaryTree::TreeNode *, int *, int &);
	void updateTree(IntBinaryTree::TreeNode *);
	
public:
	// Constructor
	IntBinaryTree() {
		root = nullptr;
	}

	void PrintTree(int Indent = 4, int Level = 0);
	void createCompleteBT(int *, int);
	void sortTree(int);
    void orderTree(IntBinaryTree::TreeNode *, int &, int);
    int getRoots(int size);
    void findRoots(IntBinaryTree::TreeNode *node, int);
};
#endif
