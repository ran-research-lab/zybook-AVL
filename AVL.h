#include "BST.h"

class AVLNode : public BTNode {
public:
  int height;  
  int key;
  AVLNode* parent; 
  AVLNode* left;
  AVLNode* right;
  AVLNode(int k = 0, AVLNode* p = NULL, AVLNode* l = NULL, AVLNode* r = NULL): 
    key(k), left(l), right(r), parent(p) {};
};
class AVL : public BST {
private:
  AVLNode *root;
public:
  AVL() : root(NULL) {}
  void updateHeight(AVLNode *n);
  bool setChild(AVLNode *parent, char whichChild, AVLNode *child);
  bool replaceChild(AVLNode* parent, AVLNode* currentChild, AVLNode* newChild);
  int  getBalance(AVLNode *n);
  void rotateRight(AVLNode *n);
  void rotateLeft(AVLNode *n);
  void treeRebalance(AVLNode *n);
  void insert(int k);
  bool remove(int k);

  AVLNode *search(int k) const;
  
  bool remove(AVLNode *n);
  void recDisplay(ostream &out) const;
  void recDisplay(ostream &out, AVLNode *cur, int dist) const;

};