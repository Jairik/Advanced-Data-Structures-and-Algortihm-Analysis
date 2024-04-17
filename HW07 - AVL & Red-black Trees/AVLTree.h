#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <vector>

using namespace std;

/*
AVL Tree class that supports multiple values with a count parameter.
This allows us to assume that the values stored in each node are unique.
That assumption simplifies much of the code to balance the tree, especially
on the removing of a node.
*/

template <class T> class AVLTree {
private:
  struct TreeNode {
    T value;
    unsigned int count = 1;  // Number of occurrences of the value.
    unsigned int height = 1; //  Height of the subtree below the node.
    TreeNode *left = nullptr;
    TreeNode *right = nullptr;
  };

  TreeNode *root = nullptr;

  // Private member functions
  void insert(TreeNode *&, TreeNode *&);
  void destroySubTree(TreeNode *);
  void deleteNode(T, TreeNode *&);
  void displayInOrder(TreeNode *) const;
  void displayPreOrder(TreeNode *) const;
  void displayPostOrder(TreeNode *) const;
  void IndentBlock(int);
  void PrintTree(TreeNode *, int, int);

  void LeftRotation(TreeNode *&);
  void RightRotation(TreeNode *&);
  int getBalanceFactor(TreeNode *);
  int getHeight(TreeNode *);
  void Balance(TreeNode *&);

  // Testing Functions
  bool isBalanced(TreeNode *);
  bool isBST(TreeNode *);
  void PrintTreeHB(TreeNode *, int, int);

  /*Description: Helper function that recursively adds the depth of all nodes
  Parameters: TreeNode *nodePtr - The current node in the iteration
  int currentDepth - The current depth at the given node
  Return: int: IPL (current Internal Path Length)
  Notes: Implemented here for ease */
  int calculateIPL(TreeNode *nodePtr, int currentDepth) {
    //Check for null case
    if (nodePtr == nullptr) {
      return 0;
    }

    //Recursively returns the sum (depth) of all path lengths
    return currentDepth + calculateIPL(nodePtr->left, currentDepth+1) + calculateIPL(nodePtr->right, currentDepth+1);
  }

public:
  AVLTree() { root = nullptr; }
  ~AVLTree() { destroySubTree(root); }

  void insertNode(T);
  bool searchNode(T);
  void remove(T);
  void displayInOrder() const { displayInOrder(root); }
  void displayPreOrder() const { displayPreOrder(root); }
  void displayPostOrder() const { displayPostOrder(root); }
  void PrintTree(int Indent = 4, int Level = 0);
  bool isEmpty() { return root == nullptr; }

  void kill() {
    destroySubTree(root);
    root = nullptr;
  }

  // Testing Functions
  bool isBalanced();
  bool isBST();
  void PrintTreeHB(int Indent = 4, int Level = 0);

  /*Description: Public function that calls the calculateIPL helper function
  Parameters: N/A
  Return: int: IPL (current Internal Path Length)
  Notes: Implemented here for ease */
  int getIPL() {
    return calculateIPL(root, 0);
  }

};

/*
Does a right rotation at the input node.  The function also updates the height
values for the nodes that are affected.

Parameters
nodePtr --- pointer to the node to rotate right around.
*/

template <class T> void AVLTree<T>::RightRotation(TreeNode *&nodePtr) {
  TreeNode *L = nodePtr->left;
  TreeNode *temp = L->right;
  L->right = nodePtr;
  nodePtr->left = temp;
  nodePtr->height =
      max(getHeight(nodePtr->left), getHeight(nodePtr->right)) + 1;
  L->height = max(getHeight(L->left), getHeight(L->right)) + 1;
  nodePtr = L;
}

/*
Does a left rotation at the input node.  The function also updates the height
values for the nodes that are affected.

Parameters
nodePtr --- pointer to the node to rotate right around.
*/

template <class T> void AVLTree<T>::LeftRotation(TreeNode *&nodePtr) {
  TreeNode *R = nodePtr->right;
  TreeNode *temp = R->left;
  R->left = nodePtr;
  nodePtr->right = temp;
  nodePtr->height =
      max(getHeight(nodePtr->left), getHeight(nodePtr->right)) + 1;
  R->height = max(getHeight(R->left), getHeight(R->right)) + 1;
  nodePtr = R;
}

/*
Returns the height of the subtree pointed to by nodePtr.

Parameters
nodePtr --- pointer to the node.
*/
template <class T> int AVLTree<T>::getHeight(TreeNode *nodePtr) {
  if (!nodePtr)
    return 0;

  return nodePtr->height;
}

/*
Returns the balance factor of the node pointed to by nodePtr.

Parameters
nodePtr --- pointer to the node.
*/
template <class T> int AVLTree<T>::getBalanceFactor(TreeNode *nodePtr) {
  if (!nodePtr)
    return 0;

  return getHeight(nodePtr->left) - getHeight(nodePtr->right);
}

/*
Does one balance of the subtree at the given node.

Parameters
nodePtr --- pointer to the node.
*/

template <class T> void AVLTree<T>::Balance(TreeNode *&nodePtr) {
  if (!nodePtr)
    return;

  int balanceFactor = getBalanceFactor(nodePtr);

  // Left heavy.
  if (balanceFactor > 1) {
    if (getBalanceFactor(nodePtr->left) >= 0)
      RightRotation(nodePtr);
    else {
      LeftRotation(nodePtr->left);
      RightRotation(nodePtr);
    }
  }

  // Right heavy.
  if (balanceFactor < -1) {
    if (getBalanceFactor(nodePtr->right) <= 0) {
      LeftRotation(nodePtr);
    } else {
      RightRotation(nodePtr->right);
      LeftRotation(nodePtr);
    }
  }
}

/*
Inserts newNode into the AVL tree if the value is not already in the
tree.  If the value is in the tree the count on the node is increased
and the new node is released from memory.
*/
template <class T>
void AVLTree<T>::insert(TreeNode *&nodePtr, TreeNode *&newNode) {
  if (nodePtr == nullptr)
    nodePtr = newNode; // Insert the node.
  else if (newNode->value < nodePtr->value)
    insert(nodePtr->left, newNode); // Search the left branch
  else if (newNode->value > nodePtr->value)
    insert(nodePtr->right, newNode); // Search the right branch
  else {
    // If the value is a duplicate increase the count.
    // In this case the newNode is not needed, delete it.
    nodePtr->count++;
    delete newNode;
  }

  // Update the height of each node in the branches called.
  nodePtr->height =
      1 + max(getHeight(nodePtr->left), getHeight(nodePtr->right));

  Balance(nodePtr);
}

//***********************************************************
// insertNode creates a new node to hold item as its value, *
// and passes it to the insert function.                    *
//***********************************************************
template <class T> void AVLTree<T>::insertNode(T item) {
  TreeNode *newNode = nullptr; // Pointer to a new node.

  newNode = new TreeNode;
  newNode->value = item;
  insert(root, newNode);
}

//***************************************************
// destroySubTree is called by the destructor. It   *
// deletes all nodes in the tree.                   *
//***************************************************
template <class T> void AVLTree<T>::destroySubTree(TreeNode *nodePtr) {
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
template <class T> bool AVLTree<T>::searchNode(T item) {
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

//***********************************************
// remove calls deleteNode to delete the        *
// node whose value member is the same as item. *
//***********************************************
template <class T> void AVLTree<T>::remove(T item) { deleteNode(item, root); }

//*********************************************
// deleteNode deletes the node whose value    *
// member is the same as item.                *
//*********************************************
template <class T> void AVLTree<T>::deleteNode(T item, TreeNode *&nodePtr) {
  if (!nodePtr)
    return;

  if (item == nodePtr->value) {
    // If the item is found, reduce the count.
    nodePtr->count--;

    // If the count is 0 then remove the node from the tree.
    // Uses a standard delete by copy with a small difference,
    // does a recursive call on the left branch with the copied
    // node value to delete it.  This is done to put the entire
    // path to the copied node on the stack so that on the derecursing
    // of the function every node on the path is checked for balance
    // and rebalanced if needed.
    if (nodePtr->count == 0) {
      if (!nodePtr->left || !nodePtr->right) {
        TreeNode *tempNodePtr = nullptr;
        if (!nodePtr->left)
          tempNodePtr = nodePtr->right;
        else
          tempNodePtr = nodePtr->left;

        if (!tempNodePtr) {
          tempNodePtr = nodePtr;
          nodePtr = nullptr;
        } else
          *nodePtr = *tempNodePtr;
        delete tempNodePtr;
      } else {
        TreeNode *tmp = nodePtr;
        tmp = nodePtr->left;
        while (tmp->right)
          tmp = tmp->right;

        nodePtr->value = tmp->value;
        nodePtr->count = tmp->count;
        tmp->count = 1; // Trick to delete tmp node on next recursive call.
        T nextval = tmp->value;

        // Recurse on the left branch with the copied value to
        // put all path nodes on the stack.
        deleteNode(nextval, nodePtr->left);
      }
    }
  } else if (item < nodePtr->value)
    deleteNode(item, nodePtr->left);
  else
    deleteNode(item, nodePtr->right);

  if (!nodePtr)
    return;

  // Update the height of each node in the branches called.
  nodePtr->height =
      1 + max(getHeight(nodePtr->left), getHeight(nodePtr->right));

  // Rebalance at the node if needed.
  int balanceFactor = getBalanceFactor(nodePtr);
  if (balanceFactor > 1 || balanceFactor < -1)
    Balance(nodePtr);
}

//****************************************************************
// The displayInOrder member function displays the values        *
// in the subtree pointed to by nodePtr, via inorder traversal.  *
//****************************************************************
template <class T> void AVLTree<T>::displayInOrder(TreeNode *nodePtr) const {
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
template <class T> void AVLTree<T>::displayPreOrder(TreeNode *nodePtr) const {
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
template <class T> void AVLTree<T>::displayPostOrder(TreeNode *nodePtr) const {
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

template <class T> void AVLTree<T>::IndentBlock(int num) {
  for (int i = 0; i < num; i++)
    cout << " ";
}

//****************************************************************
// This function recursively prints the tree contents to the
// console using a reverse inorder traversal with indenting.
//****************************************************************

template <class T>
void AVLTree<T>::PrintTree(TreeNode *t, int Indent, int Level) {
  if (t) {
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

template <class T> void AVLTree<T>::PrintTree(int Indent, int Level) {
  if (root)
    PrintTree(root, Indent, Level);
}

//****************************************************************
// This function recursively prints the tree contents to the
// console using a reverse inorder traversal with indenting.
// This includes the height and balance factor of each node.
//****************************************************************

template <class T>
void AVLTree<T>::PrintTreeHB(TreeNode *t, int Indent, int Level) {
  if (t) {
    int bal = getBalanceFactor(t);
    PrintTreeHB(t->right, Indent, Level + 1);
    IndentBlock(Indent * Level);
    cout << t->value << " (" << t->count << ")/" << t->height << "/" << bal
         << "\n";
    PrintTreeHB(t->left, Indent, Level + 1);
  }
}

//****************************************************************
// This function initiates the recursive printing function to
// print the contents of the tree in tree form sideways with the
// root at the far left. This includes the height and balance
// factor of each node.
//****************************************************************

template <class T> void AVLTree<T>::PrintTreeHB(int Indent, int Level) {
  if (root)
    PrintTreeHB(root, Indent, Level);
}

//****************************************************************
// This function is a recursive function to test if the AVL
// Tree is balanced.
//****************************************************************

template <class T> bool AVLTree<T>::isBalanced(TreeNode *t) {
  if (!t)
    return true;

  if (getBalanceFactor(t) > 1 || getBalanceFactor(t) < -1)
    return false;
  else
    return isBalanced(t->left) && isBalanced(t->right);
}

//****************************************************************
// This function initiates a recursive function to test if the AVL
// Tree is balanced.
//****************************************************************

template <class T> bool AVLTree<T>::isBalanced() {
  if (root)
    return isBalanced(root);

  return true;
}

/*
This function is a recursive function to test if the AVL tree
is a BST.
*/
template <class T> bool AVLTree<T>::isBST(TreeNode *t) {
  if (!t)
    return true;

  bool bstleft = isBST(t->left);
  bool bstright = isBST(t->right);
  bool bstnode = true;
  if (t->left && (t->left->value > t->value))
    bstnode = false;
  if (t->right && (t->right->value < t->value))
    bstnode = false;

  return bstleft && bstright && bstnode;
}

/*
This function initiates a recursive function to test if the AVL tree
is a BST.
*/
template <class T> bool AVLTree<T>::isBST() {
  if (root)
    return isBST(root);

  return true;
}

#endif
