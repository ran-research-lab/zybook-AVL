#include <iostream>
#include "AVL.h"

using namespace std;

int main() {
  AVL B;
  string op;
  int val;

  while (cin >> op && op != "q") {
    if (op == "i") {
      cin >> val;
      B.insert(val);
    }
    else if (op == "r") {
      cin >> val;
      B.remove(val); 
    }
    else if (op == "s") {
      cin >> val;
      BTNode *tmp = B.search(val);
      if (tmp) { cout << "Found:" << tmp->key << endl; }
      else { cout << "Could not find:" << val << endl;}      
    }
    else if (op == "d") {
      B.recDisplay(cout); 
    }


  }
  cout << "done." << endl;


}
