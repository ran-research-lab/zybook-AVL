#include <iostream>
using namespace std;
class BTNode {
  public:
    int key;
    BTNode *left, *right;
    BTNode(int k = 0, BTNode *l = NULL, BTNode *r = NULL) : key(k), left(l), right(r) {}
};
class BST {
  protected:
    BTNode *root;

  public:
    BST(): root(NULL) {}
    void insert(int k);
    void insertRec(int k);
    void insertRec(int k, BTNode *r);
    
    void remove(int k);
    void remove(int k, BTNode *r);
    void recDisplay(ostream &out) const;
    void recDisplay(ostream &out, BTNode *cur, int dist) const;
    void printInOrder() const;
    void printInOrder(BTNode *r) const;
    BTNode *search(int k) const;
    BTNode *searchRec(int k) const;
    BTNode *searchRec(int k, BTNode *r) const;
  

    int getHeight() const;
    int getHeight(BTNode *r) const;
    int sum() const;
    int sum(BTNode *r) const;
    int leafQty() const;
    int leafQty(BTNode *n) const;
    int parentsOfTwo() const;
    int parentsOfTwo(BTNode *n) const;

    void InOrder() const;
    void InOrder(BTNode *n) const;
};