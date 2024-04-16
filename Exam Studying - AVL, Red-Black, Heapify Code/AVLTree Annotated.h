#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <vector>

using namespace std;

/*
--------------------------------------------------------------------------------------
Annotated Code for AVL Trees. Comments are added on functions that will be tested
--------------------------------------------------------------------------------------
*/



//Performs a right rotation around a given node
template <class T> void AVLTree<T>::RightRotation(TreeNode *&nodePtr) {
  //Store left and left->right pointers
  TreeNode *L = nodePtr->left; 
  TreeNode *temp = L->right;
  //"Roll" the nodes around, moving the left ptr to the root
  L->right = nodePtr;
  //Move left to nodePtr's original left->right
  nodePtr->left = temp;
  //Get the height of nodePtr and L
  nodePtr->height =
      max(getHeight(nodePtr->left), getHeight(nodePtr->right)) + 1;
  L->height = max(getHeight(L->left), getHeight(L->right)) + 1;
  //Set the root as L
  nodePtr = L;
}


//Performs a left rotation around a given node
template <class T> void AVLTree<T>::LeftRotation(TreeNode *&nodePtr) {
  //Store nodePtr->right subtree as R
  TreeNode *R = nodePtr->right;
  //Store R->left subtree as temp
  TreeNode *temp = R->left;
  //Move nodePtr to R->left
  R->left = nodePtr;
  //Reassign the right child of nodePtr to temp
  nodePtr->right = temp;
  //Updating the heights of nodePtr and R
  nodePtr->height =
      max(getHeight(nodePtr->left), getHeight(nodePtr->right)) + 1;
  R->height = max(getHeight(R->left), getHeight(R->right)) + 1;
  //Set the root as R
  nodePtr = R;
}


//Returns the stored height of a given node
template <class T> int AVLTree<T>::getHeight(TreeNode *nodePtr) {
  if (!nodePtr)
    return 0;

  return nodePtr->height;
}


//Given a node, finds the largest height difference
template <class T> int AVLTree<T>::getBalanceFactor(TreeNode *nodePtr) {
  if (!nodePtr)
    return 0;

  return getHeight(nodePtr->left) - getHeight(nodePtr->right); //Left Subtree - Right Subtree
}


/*Given a node, will apply one of the four cases:
    1) BF > 1 (Left Heavy) & BF of left subtree >= 0
        -> Right Rotation
    2) BF > 1 (Left Heav) & BF of left subtree < 0
        -> Left Rotation on left subtree
        -> Right Rotation
    3) BF < -1 & BF of right subtree <= 0 
        -> Left Rotation
    4) BF < -1 & BF of right subtree > 0
        -> Right Rotation on right subtree
        -> Left Rotation
*/
template <class T> void AVLTree<T>::Balance(TreeNode *&nodePtr) {
  if (!nodePtr)
    return;

  int balanceFactor = getBalanceFactor(nodePtr);

  // If right heavy, case 1 & 2
  if (balanceFactor > 1) {
    if (getBalanceFactor(nodePtr->left) >= 0)
      RightRotation(nodePtr);
    else {
      LeftRotation(nodePtr->left);
      RightRotation(nodePtr);
    }
  }

  // If Left Heavy, case 3 & 4
  if (balanceFactor < -1) {
    if (getBalanceFactor(nodePtr->right) <= 0) {
      LeftRotation(nodePtr);
    } else {
      RightRotation(nodePtr->right);
      LeftRotation(nodePtr);
    }
  }
}


//Inserts a node. If it already exists, increases count.
//Parameters: nodePtr is the "temp" and newNode is the node to insert
template <class T>
void AVLTree<T>::insert(TreeNode *&nodePtr, TreeNode *&newNode) {
  //Base case. End of the tree and proper location has been reached.
  if (nodePtr == nullptr) {
    nodePtr = newNode; // Insert the node.
  }
  //Recursively move to the left child
  else if (newNode->value < nodePtr->value) {
    insert(nodePtr->left, newNode); // Search the left branch
  }
  //Recursively move to the right child
  else if (newNode->value > nodePtr->value) {
    insert(nodePtr->right, newNode); // Search the right branch
  }
  //nodePtr == newNode. Then increment the count and delete unused newNode
  else {
    nodePtr->count++;
    delete newNode;
  }

  //Update the height of each node in the branches called.
  nodePtr->height = 1 + max(getHeight(nodePtr->left), getHeight(nodePtr->right));

  //Rebalance the tree
  Balance(nodePtr);
}

//Helper function for insertNode. Creates node and calls function
template <class T> void AVLTree<T>::insertNode(T item) {
  TreeNode *newNode = nullptr; // Pointer to a new node.

  newNode = new TreeNode;
  newNode->value = item;
  insert(root, newNode);
}

//Just returns if a node is present in the tree, easy stuff 
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

//Helper function to delete a node
template <class T> void AVLTree<T>::remove(T item) { deleteNode(item, root); }

//Deletes a given node, if it is present
//Comments added by professor are sufficient. If I get tested on this i'm cooked
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


/* -------------------------------------------------------------------------
------------------END OF TESTABLE MATERIAL----------------------------------
----------------------------------------------------------------------------*/
//The rest of this code is unmodified


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
  void insert(TreeNode *&, TreeNode *&); //Annotated
  void destroySubTree(TreeNode *); 
  void deleteNode(T, TreeNode *&); //Annotated
  void displayInOrder(TreeNode *) const;
  void displayPreOrder(TreeNode *) const;
  void displayPostOrder(TreeNode *) const;
  void IndentBlock(int);
  void PrintTree(TreeNode *, int, int);

  void LeftRotation(TreeNode *&); //Annotated
  void RightRotation(TreeNode *&); //Annotated
  int getBalanceFactor(TreeNode *); //Annotated
  int getHeight(TreeNode *); //Annotated
  void Balance(TreeNode *&); //Annotated

  // Testing Functions
  bool isBalanced(TreeNode *);
  bool isBST(TreeNode *);
  void PrintTreeHB(TreeNode *, int, int);

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
};

#endif
