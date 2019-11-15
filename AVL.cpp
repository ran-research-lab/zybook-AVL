#include "AVL.h"


void AVL::updateHeight(AVLNode *n) {
  int lHeight = (n->left)  ? n->left->height  : -1;
  int rHeight = (n->right) ? n->right->height : -1;
  n->height = max(lHeight, rHeight) + 1;
}


bool AVL::setChild(AVLNode *parent, char whichChild, AVLNode *child) {
  if (child && parent)
  if (whichChild != 'l' && whichChild != 'r')
    return false;

  if (whichChild == 'l') parent->left  = child;
  else                   parent->right = child;
  
  if (child) child->parent = parent;

  updateHeight(parent);
  return true;
}

bool AVL::replaceChild(AVLNode* parent, AVLNode* currentChild, AVLNode* newChild) {
  if (parent->left == currentChild)       
    return setChild(parent, 'l', newChild);
  else if (parent->right == currentChild) 
    return setChild(parent, 'r', newChild);
  return false;
}


int AVL::getBalance(AVLNode *n) {
  
  int leftHeight = -1, rightHeight = -1;
  if (n->left) leftHeight = n->left->height;
  if (n->right) rightHeight = n->right->height;  
  return leftHeight - rightHeight;
}

void AVL::rotateRight(AVLNode *n) {
  AVLNode *leftRightChild = n->left->right;
  if (n->parent)
    replaceChild(n->parent, n, n->left);
  else { // node is root
      root = n->left;
      root->parent = NULL;
   }
   setChild(n->left, 'r', n);
   setChild(n, 'l', leftRightChild);
}

void AVL::rotateLeft(AVLNode *n) {
  AVLNode *rightLeftChild = n->right->left;
  if (n->parent)
    replaceChild(n->parent, n, n->right);
  else { // node is root
      root = n->right;
      root->parent = NULL;
   }
   setChild(n->right, 'l', n);
   setChild(n, 'r', rightLeftChild);
}

void AVL::treeRebalance(AVLNode *n) {
   updateHeight(n);        
   if (getBalance(n) == -2) {
      if (getBalance(n->right) == 1) {
         // Double rotation case.
         rotateRight(n->right);
      }
      rotateLeft(n);
   }
   else if (getBalance(n) == 2) {
      if (getBalance(n->left) == -1) {
         // Double rotation case.
         rotateLeft(n->left);
      }
      rotateRight(n);
   }        
}


void AVL::insert(int k) {
  AVLNode* n = new AVLNode(k);
  if (!root) {
      root = n;
      return;
  }

  AVLNode *cur = root;
  while (cur) {
      if (n->key < cur->key) {
         if (!cur->left) {
            cur->left = n;
            n->parent = cur;
            cur = NULL;
         }
         else
            cur = cur->left;
      }
      else {
         if (!cur->right) {
            cur->right = n;
            n->parent = cur;
            cur = NULL;
         }
         else
            cur = cur->right;
      }
   }

   n = n->parent;
   while (n) {
      treeRebalance(n);
      n = n->parent;
   }
}

AVLNode* AVL::search(int k) const {
  AVLNode* cur = root;   
  while (cur) {
    if (k == cur->key)     {return cur;}
       // Found
    else if (k < cur->key) { cur = cur->left; }
    else                   { cur = cur->right; }
  }
  return NULL;
}

bool AVL::remove(int k) {
  return remove(search(k));
}

bool AVL::remove(AVLNode *n) {
   if (!n) return false;
        
   // Parent needed for rebalancing
   AVLNode *parent = n->parent;
        
   // Case 1: Internal node with 2 children
   if (n->left  && n->right) {
      // Find successor
      AVLNode* succNode = n->right;
      while (succNode->left) succNode = succNode->left;
            

      int successorData = succNode->key;

      // Copy the value from the node
      // node = Copy succNode???
            
      // Recursively remove successor
      remove(succNode);
      
      n->key = successorData;

      // Nothing left to do since the recursive call will have rebalanced
      return true;
   }

   // Case 2: Root node (with 1 or 0 children)
   else if (n == root) {
      if (n->left) root = n->left;
      else         root = n->right;

      if (root) root->parent = NULL;

      return true;
   }

   // Case 3: Internal with left child only
   else if (n->left)
      replaceChild(parent, n, n->left);
        
   // Case 4: Internal with right child only OR leaf
   else
      replaceChild(parent, n, n->right);
        
   // node is gone. Anything that was below node that has persisted is already correctly
   // balanced, but ancestors of node may need rebalancing.
   n = parent;
   while (n) {
      treeRebalance(n);            
      n = n->parent;
   }
   return true;
}



void AVL::recDisplay(ostream &out) const {
  recDisplay(out, root, 0);
}

void AVL::recDisplay(ostream &out, AVLNode *cur, int dist) const{
	if (cur) { 
    if (cur->right) recDisplay(out, cur->right, dist + 1);
    for (int i = 0; i < dist; i++) cout << "       ";
      out << cur->key << "[" << cur->height << "]" << endl;
    if (cur->left) recDisplay(out, cur->left, dist + 1);
  }
}