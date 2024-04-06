#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
#include <cmath>

using namespace std;

template<class T> class BinaryTree {
private:
	class TreeNode {
	public:
		T value;
		TreeNode *left;
		TreeNode *right;

		TreeNode() {
			left = nullptr;
			right = nullptr;
		}
	};

	TreeNode *root;

	// Private member functions
	void insert(TreeNode*&, TreeNode*&);
	void destroySubTree(TreeNode*);
	void deleteNode(T, TreeNode*&);
	void makeDeletion(TreeNode*&);
	void displayInOrder(TreeNode*) const;
	void displayPreOrder(TreeNode*) const;
	void displayPostOrder(TreeNode*) const;
	void IndentBlock(int);
	void PrintTree(TreeNode*, int, int);

	void LeftRotation(TreeNode *&nodePtr);
	void RightRotation(TreeNode *&nodePtr);
	void CreateBackboneRec(TreeNode *&nodePtr);
	void CreateBackbone();
	int CountNodes(TreeNode *nodePtr);
	void CreateBalanceRec(TreeNode *&nodePtr, int count, int stop);
	void CreateBalance(int num);
	int height(TreeNode *nodePtr);

public:
	// Constructor
	BinaryTree() {
		root = nullptr;
	}

	// Destructor
	~BinaryTree() {
		destroySubTree(root);
	}

	void clear() {
		destroySubTree(root);
		root = nullptr;
	}

	// Binary tree operations
	void insertNode(T);
	bool searchNode(T);
	void remove(T);
	T* search(T &item);

	void balance();
	int CountNodes();
	int CountNodesLL();
	int height();

	void displayInOrder() const {
		displayInOrder(root);
	}

	void displayPreOrder() const {
		displayPreOrder(root);
	}

	void displayPostOrder() const {
		displayPostOrder(root);
	}

	void PrintTree(int Indent = 4, int Level = 0);
};

/*
 * Finds the height of the tree starting at the root.
 */
template<class T> int BinaryTree<T>::height() {
	return height(root);
}

/*
 * Finds the height of the tree starting at the pointer nodePtr.
 */
template<class T> int BinaryTree<T>::height(TreeNode *nodePtr) {
	if (!nodePtr)
		return 0;

	return max(height(nodePtr->left), height(nodePtr->right)) + 1;
}

/*
 * Counts the number of nodes in a binary tree starting at the root.
 */
template<class T> int BinaryTree<T>::CountNodes() {
	return CountNodes(root);
}

/*
 * Recursively counts the number of nodes in a binary tree starting at the pointer nodePtr.
 */
template<class T> int BinaryTree<T>::CountNodes(TreeNode *nodePtr) {
	if (!nodePtr)
		return 0;

	return CountNodes(nodePtr->left) + CountNodes(nodePtr->right) + 1;
}

/*
 * Counts the number of nodes in a binary tree starting at the root.
 * Assumes that the tree is a degenerate linked list with only right
 * children, that is, a backbone.
 */
template<class T> int BinaryTree<T>::CountNodesLL() {
	TreeNode *ptr = root;
	if (!root)
		return 0;

	int count = 0;
	while (ptr) {
		count++;
		ptr = ptr->right;
	}

	return count;
}

/*
 * Does a right rotation about nodePtr.
 */
template<class T> void BinaryTree<T>::RightRotation(TreeNode *&nodePtr) {
	TreeNode *L = nodePtr->left;
	TreeNode *temp = L->right;
	L->right = nodePtr;
	nodePtr->left = temp;
	nodePtr = L;
}

/*
 * Does a left rotation about nodePtr.
 */
template<class T> void BinaryTree<T>::LeftRotation(TreeNode *&nodePtr) {
	TreeNode *R = nodePtr->right;
	TreeNode *temp = R->left;
	R->left = nodePtr;
	nodePtr->right = temp;
	nodePtr = R;
}

/*
 * Recursively reforms the tree into a "backbone".  That is, a linked list to
 * the right child where the values will be ordered.
 */
template<class T> void BinaryTree<T>::CreateBackboneRec(TreeNode *&parent) {
	while (parent->left) {
		RightRotation(parent);
	}

	if (parent->right)
		CreateBackboneRec(parent->right);
}

/*
 * Iterative version that reforms the tree into a "backbone".  That is, a
 * linked list to the right child where the values will be ordered.
 */
template<class T> void BinaryTree<T>::CreateBackbone() {
	if (!root)
		return;

	while (root->left) {
		RightRotation(root);
	}

	TreeNode *ptr = root;
	while (ptr->right) {
		while (ptr->right->left) {
			RightRotation(ptr->right);
		}
		ptr = ptr->right;
	}
}

/*
 * Recursive version of an iterative that rotates left at each right child, stop
 * number of times, assuming count is initially called at 1.
 */
template<class T> void BinaryTree<T>::CreateBalanceRec(TreeNode *&nodePtr,
		int count, int stop) {
	if (count > stop)
		return;

	LeftRotation(nodePtr);
	CreateBalanceRec(nodePtr->right, count + 1, stop);
}

/*
 * Iterative version of a single pass in tree balancing using DSW.
 */
template<class T> void BinaryTree<T>::CreateBalance(int num) {
	if (num == 0)
		return;

	LeftRotation(root);
	TreeNode *ptr = root;
	for (int i = 0; i < num - 1; i++) {
		LeftRotation(ptr->right);
		ptr = ptr->right;
	}
}

/*
 * DSW (Colin Day, Quentin F. Stout, and Bette L. Warren) tree balancing algorithm
 * the first creates a backbone of the tree, then using left rotations forms a
 * perfectly balanced tree.
 */
template<class T> void BinaryTree<T>::balance() {
	if (!root)
		return;

	CreateBackbone();
	int n = CountNodesLL();

	// The addition of 0.5 is a standard rounding procedure when truncating to
	// an integer.  In the case of 1.9999999 when the true result is 2.
	int m = static_cast<int>(pow(2, floor(log2(n + 1))) - 1 + 0.5);

	CreateBalance(n - m);
	while (m > 1) {
		m = m / 2;
		CreateBalance(m);
	}
}

//*************************************************************
// insert accepts a TreeNode pointer and a pointer to a node. *
// The function inserts the node into the tree pointed to by  *
// the TreeNode pointer. This function is called recursively. *
//*************************************************************
template<class T>
void BinaryTree<T>::insert(TreeNode *&nodePtr, TreeNode *&newNode) {
	if (nodePtr == nullptr)
		nodePtr = newNode; // Insert the node.
	else if (newNode->value < nodePtr->value)
		insert(nodePtr->left, newNode); // Search the left branch
	else
		insert(nodePtr->right, newNode); // Search the right branch
}

//**********************************************************
// insertNode creates a new node to hold num as its value, *
// and passes it to the insert function.                   *
//**********************************************************
template<class T> void BinaryTree<T>::insertNode(T item) {
	TreeNode *newNode = nullptr; // Pointer to a new node.

// Create a new node and store num in it.
	newNode = new TreeNode;
	newNode->value = item;
	newNode->left = newNode->right = nullptr;

// Insert the node.
	insert(root, newNode);
}

//***************************************************
// destroySubTree is called by the destructor. It   *
// deletes all nodes in the tree.                   *
//***************************************************
template<class T> void BinaryTree<T>::destroySubTree(TreeNode *nodePtr) {
	if (nodePtr) {
		if (nodePtr->left)
			destroySubTree(nodePtr->left);
		if (nodePtr->right)
			destroySubTree(nodePtr->right);
		delete nodePtr;
	}
}

//***************************************************
// searchNode determines if a value is present in   *
// the tree. If so, the function returns true.      *
// Otherwise, it returns false.                     *
//***************************************************
template<class T> bool BinaryTree<T>::searchNode(T item) {
	TreeNode *nodePtr = root;

	while (nodePtr) {
		if (nodePtr->value == item)
			return true;
		else if (item < nodePtr->value)
			nodePtr = nodePtr->left;
		else
			nodePtr = nodePtr->right;
	}
	return false;
}

/*
 * search determines if an item is in the tree.  If so
 * a pointer to the item is returned and if not nullptr
 * is returned.  Note that if we returned T then the data
 * type T would possibly need a copy constructor.
 */
template<class T> T* BinaryTree<T>::search(T &item) {
	TreeNode *nodePtr = root;

	while (nodePtr) {
		if (nodePtr->value == item)
			return &nodePtr->value;
		else if (item < nodePtr->value)
			nodePtr = nodePtr->left;
		else
			nodePtr = nodePtr->right;
	}
	return nullptr;
}

//**********************************************
// remove calls deleteNode to delete the       *
// node whose value member is the same as num. *
//**********************************************
template<class T> void BinaryTree<T>::remove(T item) {
	deleteNode(item, root);
}

//********************************************
// deleteNode deletes the node whose value   *
// member is the same as num.                *
//********************************************
template<class T> void BinaryTree<T>::deleteNode(T item, TreeNode *&nodePtr) {
	if (!nodePtr)
		return;

	if (item < nodePtr->value)
		deleteNode(item, nodePtr->left);
	else if (item > nodePtr->value)
		deleteNode(item, nodePtr->right);
	else
		makeDeletion(nodePtr);
}

//***********************************************************
// makeDeletion takes a reference to a pointer to the node  *
// that is to be deleted. The node is removed and the       *
// branches of the tree below the node are reattached.      *
//***********************************************************
template<class T> void BinaryTree<T>::makeDeletion(TreeNode *&nodePtr) {
// Define a temporary pointer to use in reattaching
// the left subtree.
	TreeNode *tempNodePtr = nullptr;

	if (nodePtr == nullptr)
		cout << "Cannot delete empty node.\n";
	else if (nodePtr->right == nullptr) {
		tempNodePtr = nodePtr;
		nodePtr = nodePtr->left; // Reattach the left child
		delete tempNodePtr;
	} else if (nodePtr->left == nullptr) {
		tempNodePtr = nodePtr;
		nodePtr = nodePtr->right; // Reattach the right child
		delete tempNodePtr;
	}
// If the node has two children.
	else {
		// Move one node the right.
		tempNodePtr = nodePtr->right;
		// Go to the end left node.
		while (tempNodePtr->left)
			tempNodePtr = tempNodePtr->left;
		// Reattach the left subtree.
		tempNodePtr->left = nodePtr->left;
		tempNodePtr = nodePtr;
		// Reattach the right subtree.
		nodePtr = nodePtr->right;
		delete tempNodePtr;
	}
}

//****************************************************************
// The displayInOrder member function displays the values        *
// in the subtree pointed to by nodePtr, via inorder traversal.  *
//****************************************************************
template<class T> void BinaryTree<T>::displayInOrder(TreeNode *nodePtr) const {
	if (nodePtr) {
		displayInOrder(nodePtr->left);
		cout << nodePtr->value << endl;
		displayInOrder(nodePtr->right);
	}
}

//****************************************************************
// The displayPreOrder member function displays the values       *
// in the subtree pointed to by nodePtr, via preorder traversal. *
//****************************************************************
template<class T>
void BinaryTree<T>::displayPreOrder(TreeNode *nodePtr) const {
	if (nodePtr) {
		cout << nodePtr->value << endl;
		displayPreOrder(nodePtr->left);
		displayPreOrder(nodePtr->right);
	}
}

//****************************************************************
// The displayPostOrder member function displays the values      *
// in the subtree pointed to by nodePtr, via postorder traversal.*
//****************************************************************
template<class T>
void BinaryTree<T>::displayPostOrder(TreeNode *nodePtr) const {
	if (nodePtr) {
		displayPostOrder(nodePtr->left);
		displayPostOrder(nodePtr->right);
		cout << nodePtr->value << endl;
	}
}

//****************************************************************
// Simple helper function to do the indentations for the tree
// printing algorithm.
//****************************************************************

template<class T> void BinaryTree<T>::IndentBlock(int num) {
	for (int i = 0; i < num; i++)
		cout << " ";
}

//****************************************************************
// This function recursively prints the tree contents to the
// console using a reverse inorder traversal with indenting.
//****************************************************************

template<class T>
void BinaryTree<T>::PrintTree(TreeNode *t, int Indent, int Level) {
	if (t != NULL) {
		PrintTree(t->right, Indent, Level + 1);
		IndentBlock(Indent * Level);
		cout << t->value << "\n";
		PrintTree(t->left, Indent, Level + 1);
	}
}

//****************************************************************
// This function initiates the recursive printing function to
// print the contents of the tree in tree form sideways with the
// root at the far left.
//****************************************************************

template<class T> void BinaryTree<T>::PrintTree(int Indent, int Level) {
	if (root != NULL)
		PrintTree(root, Indent, Level);
}

#endif
