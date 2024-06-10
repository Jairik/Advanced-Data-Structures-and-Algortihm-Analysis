/* ---------------------------- RBTree Header File ---------------------------- 
   This provided code will inhertied to implement Maps and Multimaps.
   Adapted to work with maps (each node has a key and value)
   ---------------------------------------------------------------------------- */

#ifndef RBTREE_H_
#define RBTREE_H_

#include <iostream>
#include <vector>
#include <string>
using namespace std;

enum color_t {
		RED, BLACK
		// Red = 0, Black = 1
	};

template<class T, class V>
class RBTreeNode {
public:

	T key;
	vector<V> value; //Values will be stored in a vector
	color_t color;
	RBTreeNode *left;
	RBTreeNode *right;
	RBTreeNode *parent;

	RBTreeNode() {
		key = NULL;
		value = NULL;
		left = nullptr;
		right = nullptr;
		parent = nullptr;
		color = RED;
	}

	RBTreeNode(T nKey, V val, color_t col, RBTreeNode *l, RBTreeNode *r,
			RBTreeNode *p) {
		key = nKey;
		value.push_back(val);
		left = l;
		right = r;
		parent = p;
		color = col;
	}
};

template<class T, class V>
class RBTree {
protected:
	RBTreeNode<T, V> *root;
	RBTreeNode<T, V> *NIL;
	void IndentBlock(int num);
	void PrintTree(RBTreeNode<T, V>*, int, int);

	void LeftRotation(RBTreeNode<T, V>*);
	void RightRotation(RBTreeNode<T, V>*);
	void insertFix(RBTreeNode<T, V>*);

	void transplant(RBTreeNode<T, V>*, RBTreeNode<T, V>*);
	void deleteFix(RBTreeNode<T, V>*);
	RBTreeNode<T, V>* getMinNode(RBTreeNode<T, V>*);

	void destroySubTree(RBTreeNode<T, V> *);

	color_t getRed() { return RED; } //Helper function that returns enumerated type RED

public:
	RBTree();
	virtual ~RBTree();

	virtual void insert(T, V);
	void remove(T);

	bool findNode(const T &item);
	RBTreeNode<T, V>* findNodeHelper(const T&);

	void PrintTree(int Indent = 4, int Level = 0);
};

template <class T, class V>
RBTree<T, V>::RBTree() {
	NIL = new RBTreeNode<T, V>(T(), V(), BLACK, nullptr, nullptr, nullptr);
	root = NIL;
}

template <class T, class V>
RBTree<T, V>::~RBTree() {
	destroySubTree(root);
	delete NIL;
}

/*
 * Recursively frees the memory of the subtree pointed to by nodePtr.
 */
template <class T, class V>
void RBTree<T, V>::destroySubTree(RBTreeNode<T, V> *nodePtr) {
	if (nodePtr != NIL) {
		if (nodePtr->left != NIL)
			destroySubTree(nodePtr->left);
		if (nodePtr->right != NIL)
			destroySubTree(nodePtr->right);
		delete nodePtr;
	}
}

/*
 * Inserts a new node into the RB-Tree as with a standard BST but then calls the
 * insertFix function to adjust the tree back to an RB tree.
 * Note: Overriden in both functions
 */
template <class T, class V>
void RBTree<T, V>::insert(T ckey, V val) {
	RBTreeNode<T, V> *newnode = new RBTreeNode<T,V>(ckey, val, RED, NIL, NIL, NIL);
	RBTreeNode<T, V> *y = NIL;
	RBTreeNode<T, V> *x = root;

	while (x != NIL) {
		y = x;
		if (ckey < x->key)
			x = x->left;
		else 
			x = x->right;
	}
	newnode->parent = y;
	if (y == NIL)
		root = newnode;
	else if (newnode->key < y->key)
		y->left = newnode;
	else
		y->right = newnode;

	//  Adjust the RB tree to retain the properties.
	insertFix(newnode);
}

/*
 * Adjusts the tree back to an RB tree after insertion of a new node.
 */
template <class T, class V>
void RBTree<T, V>::insertFix(RBTreeNode<T, V> *z) {
	RBTreeNode<T, V> *y = NIL;

	while (z->parent->color == RED) {
		if (z->parent == z->parent->parent->left) {
			y = z->parent->parent->right;
			if (y->color == RED) {
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			} else {
				if (z == z->parent->right) {
					z = z->parent;
					LeftRotation(z);
				}
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				RightRotation(z->parent->parent);
			}
		} else {
			y = z->parent->parent->left;
			if (y->color == RED) {
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			} else {
				if (z == z->parent->left) {
					z = z->parent;
					RightRotation(z);
				}
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				LeftRotation(z->parent->parent);
			}
		}
	}
	root->color = BLACK;
}

/*
 * This is a helper function to the node deletion process.
 */
template <class T, class V>
void RBTree<T, V>::transplant(RBTreeNode<T, V> *u, RBTreeNode<T, V> *v) {
	if (u->parent == NIL)
		root = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;
	v->parent = u->parent;
}

/*
 * Finds the smallest node in the subtree pointed to by x.  As usual
 * we traverse down the left branch as far as possible.  The node y
 * tracks x's parent so that when x == NIL, y is the minimum valued
 * node.
 */
template <class T, class V>
RBTreeNode<T, V>* RBTree<T, V>::getMinNode(RBTreeNode<T, V> *x) {
	if (x == NIL)
		return NIL;

	RBTreeNode<T, V> *y = NIL;
	while (x != NIL) {
		y = x;
		x = x->left;
	}
	return y;
}

/*
 * Finds and deletes the node whose value is val.  Calls the deleteFix function
 * to readjust the tree back to RB format.
 */
template <class T, class V>
void RBTree<T, V>::remove(T key) {
	RBTreeNode<T, V> *z = findNodeHelper(key);
	if (z == NIL)
		return;

	RBTreeNode<T, V> *y = z;
	RBTreeNode<T, V> *x = NIL;
	color_t yorigcol = y->color;

	if (z->left == NIL) {
		x = z->right;
		transplant(z, z->right);
	} else if (z->right == NIL) {
		x = z->left;
		transplant(z, z->left);
	} else {
		y = getMinNode(z->right);
		yorigcol = y->color;
		x = y->right;
		if (y->parent == z)
			x->parent = y;
		else {
			transplant(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		transplant(z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}
	delete z;
	if (yorigcol == BLACK)
		deleteFix(x);
}

/*
 * Readjusts the RB tree to fix any violated properties after the deletion of a
 * node.
 */
template <class T, class V>
void RBTree<T, V>::deleteFix(RBTreeNode<T, V> *x) {
	RBTreeNode<T, V> *w = NIL;

	while (x != root && x->color == BLACK) {
		if (x == x->parent->left) {
			w = x->parent->right;
			if (w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				LeftRotation(x->parent);
				w = x->parent->right;
			}
			if (w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				x = x->parent;
			} else {
				if (w->right->color == BLACK) {
					w->left->color = BLACK;
					w->color = RED;
					RightRotation(w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->right->color = BLACK;
				LeftRotation(x->parent);
				x = root;
			}
		} else {
			w = x->parent->left;
			if (w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				RightRotation(x->parent);
				w = x->parent->left;
			}
			if (w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				x = x->parent;
			} else {
				if (w->left->color == BLACK) {
					w->right->color = BLACK;
					w->color = RED;
					LeftRotation(w);
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->left->color = BLACK;
				RightRotation(x->parent);
				x = root;
			}
		}
	}
	x->color = BLACK;
}

/*
 * This returns true if the item is in the RB-tree and false otherwise.
 * It simply calls the node based recursive version and checks the result
 * against the NIL object.
 */
template <class T, class V>
bool RBTree<T, V>::findNode(const T &item) {
	return findNodeHelper(item) != NIL;
}

/*
 Does a right rotation at the input node.
 The function also updates the height values for the nodes.

 Parameters
 x --- pointer to the node to rotate right around.
 */

template <class T, class V>
void RBTree<T, V>::RightRotation(RBTreeNode<T, V> *x) {
	RBTreeNode<T, V> *y = x->left;
	x->left = y->right;

	if (y->right != NIL)
		y->right->parent = x;

	y->parent = x->parent;

	if (x->parent == NIL)
		root = y;
	else if (x == x->parent->right)
		x->parent->right = y;
	else
		x->parent->left = y;

	y->right = x;
	x->parent = y;
}

/*
 Does a left rotation at the input node.
 The function also updates the height values for the nodes.

 Parameters
 nodePtr --- pointer to the node to rotate right around.
 */

template <class T, class V>
void RBTree<T, V>::LeftRotation(RBTreeNode<T, V> *x) {
	RBTreeNode<T, V> *y = x->right;
	x->right = y->left;

	if (y->left != NIL)
		y->left->parent = x;

	y->parent = x->parent;

	if (x->parent == NIL)
		root = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;

	y->left = x;
	x->parent = y;
}

/*
 * Recursive find function that finds the first node containing the key.
 * Parameter: The key to search for
 */
template <class T, class V>
RBTreeNode<T, V>* RBTree<T, V>::findNodeHelper(const T &item) {
	RBTreeNode<T, V> *nodePtr = root;

	while (nodePtr != NIL) {
		if (nodePtr->key == item)
			return nodePtr;
		else if (item < nodePtr->key)
			nodePtr = nodePtr->left;
		else
			nodePtr = nodePtr->right;
	}
	return NIL;
}

//****************************************************************
// Simple helper function to do the indentations for the tree
// printing algorithm.
//****************************************************************
template <class T, class V>
void RBTree<T, V>::IndentBlock(int num) {
	for (int i = 0; i < num; i++)
		cout << " ";
}

//****************************************************************
// This function recursively prints the tree contents to the
// console using a reverse inorder traversal with indenting.
// This includes the height and balance factor of each node.
//****************************************************************

template <class T, class V>
void RBTree<T, V>::PrintTree(RBTreeNode<T, V> *t, int Indent, int Level) {
	if (t != NIL) {
		PrintTree(t->right, Indent, Level + 1);

		string RBstr;
		if (t->color == RED)
			RBstr = "R";
		else
			RBstr = "B";

		IndentBlock(Indent * Level);
		cout << t->value << " (" << RBstr << ")" << endl;

		PrintTree(t->left, Indent, Level + 1);
	}
}

//****************************************************************
// This function initiates the recursive printing function to
// print the contents of the tree in tree form sideways with the
// root at the far left. This includes the height and balance
// factor of each node.
//****************************************************************

template <class T, class V>
void RBTree<T, V>::PrintTree(int Indent, int Level) {
	if (root)
		PrintTree(root, Indent, Level);
}

#endif /* RBTREE_H_ */
