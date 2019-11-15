#include <iostream>
#include "BST.h"

using namespace std;

BTNode* BST::search(int k) const {
  BTNode* cur = root;   
  while (cur) {
    if (k == cur->key)     {return cur;}
       // Found
    else if (k < cur->key) { cur = cur->left; }
    else                   { cur = cur->right; }
  }
  return NULL;
}

void BST::insert(int k) {
  BTNode *cur;
  BTNode *n = new BTNode(k);
  
  if (!root) { 
    // This tree is empty, the new node is the root!
    root = n; 
  }
  else {
    // Lets search the tree for a place to insert....
    cur = root;
    while (cur) {
      if (k < cur->key){
        // The value to insert is less than current node
        if (cur->left == NULL) {
          // If we have reached a node who lacks a left child
          // then our new node will be the left child
          cur->left = n;
          cur = NULL;
        }
        else {
          // keep looking for a place to insert, on the left subtree 
          cur = cur->left; 
        }
      }
      else {
        // The value to insert is greater or equal than current node
        if (cur->right == NULL){
          // If we have reached a node who lacks a right child
          // then our new node will be the right child
          cur->right = n;
          cur = NULL;
        }
        else { 
          // keep looking for a place to insert, on the right subtree
          cur = cur->right; 
        }  
      }
    }     
  }
}

void BST::recDisplay(ostream &out) const {
  recDisplay(out, root, 0);
}

void BST::recDisplay(ostream &out, BTNode *cur, int dist) const{
  cout << "diplaying.." << endl;
	if (cur) { 
    if (cur->right) recDisplay(out, cur->right, dist + 1);
    for (int i = 0; i < dist; i++) cout << "    ";
      out << cur->key << endl;
    if (cur->left) recDisplay(out, cur->left, dist + 1);
  }
}

void BST::remove(int k) {
  remove(k, root);
}

void BST::remove(int k, BTNode *r) {
   BTNode *parent = NULL;
   BTNode *cur = r;
   while (cur) { // Search for node
      if (cur->key == k) { // Node found 
         if (cur->left == NULL && cur->right == NULL) {        // Remove leaf
            cout << "cur is a leaf: " << cur->key << endl;
            if (!parent) { // Node is root
              root = NULL;
            }
            else if (parent->left == cur) 
              parent->left = NULL;
            else
              parent->right = NULL;
            delete cur;
         }
         else if (cur->left && cur->right == NULL) {    // Remove node with only left child
            if (!parent) // Node is root
              root = cur->left;
            else if (parent->left == cur) 
               parent->left = cur->left;
            else
               parent->right = cur->left;
            delete cur;
         }
         else if (cur->left == NULL && cur->right) {    // Remove node with only right child
            if (!parent) // Node is root
              root = cur->right;
            else if (parent->left == cur) 
               parent->left = cur->right;
            else
               parent->right = cur->right;
            delete cur;
         }
         else {                                  // Remove node with two children
            // Find successor (leftmost child of right subtree)
            BTNode *suc = cur->right;
            
            while (suc->left )
               suc = suc->left;
            int successorData = suc->key;
            remove(suc->key, cur);     // Remove successor
            cur->key = successorData;
         }
         return; // Node found and removed
      }
      else if (cur->key < k) { // Search right
         parent = cur;
         cur = cur->right;
      }
      else {                     // Search left
         parent = cur;
         cur = cur->left;
      }
   }
   return; // Node not found 
}

void BST::printInOrder() const {
  printInOrder(root);   
}

void BST::printInOrder(BTNode *r) const {
  if (!r) return;                     

  printInOrder(r->left);   
  cout << r->key << endl;                     
  printInOrder(r->right);  
}

int  BST::getHeight() const {
  return getHeight(root);
}

int  BST::getHeight(BTNode *r) const {
  if (!r) return -1;

  int leftHeight = getHeight(r->left);
  int rightHeight = getHeight(r->right);
  return 1 + max(leftHeight, rightHeight);
}

int BST::sum() const { return sum(root);}

int BST::sum(BTNode *n) const {
    if (!n) return 0;
    else return n->key + sum(n->left) + sum(n->right);
}

int BST::leafQty() const { return leafQty(root);}

int BST::leafQty(BTNode *n) const {
    if (!n) return 0;
    if (n->left == NULL && n->right == NULL) return 1;
    else return leafQty(n->left) + leafQty(n->right); 
}
int BST::parentsOfTwo() const {
  return parentsOfTwo(root);
}
int BST::parentsOfTwo(BTNode *n) const {
    if (!n || (!n->left && !n->right)) return 0;
    int resultLeft = parentsOfTwo(n->left);
    int resultRight = parentsOfTwo(n->right);
    if (n->left && n->right) return 1 + resultLeft + resultRight;
    else return resultLeft + resultRight;
}


void BST::InOrder() const { InOrder(root); }
void BST::InOrder(BTNode *n) const {
  if (n) {
    InOrder(n->left);
    cout << n->key << endl;
    InOrder(n->right);
  }
}


BTNode* BST::searchRec(int k) const { return searchRec(k,root); }

BTNode* BST::searchRec(int k, BTNode *r) const {
  if (r) {
    if (k == r->key) return r;
    else if (k < r->key) 
      return searchRec(k, r->left);
    else
      return searchRec(k, r->right);
  }
  return NULL;
}

void BST::insertRec(int k) {
  if (!root) root = new BTNode(k);
  else insertRec(k, root);
}
void BST::insertRec(int k, BTNode *r) {
  if (k < r->key) {
    if (r->left == NULL) r->left = new BTNode(k);
    else insertRec(k, r->left);
  }
  else { // k is greater than r->key
    if (r->right == NULL) r->right = new BTNode(k);
  else insertRec(k, r->right);
  }
}