#include <iostream>
using namespace std;  

#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

class AVL
{
 public:
  /***** Function Members *****/
  AVL();
  bool empty() const;
  bool search(const int & item) const; 
  void insert(const int & item);
  void deletenode(const int & item);
  void preOrder()const;
  void inOrder()const;
  void nodecount()const;
  
  
 private:

  /***** Node class *****/
  class BinNode 
  {
    
    public:
      
    int data;
    BinNode * left;
    BinNode * right;
    BinNode * parentofnode;
    int height;
    // BinNode constructors
    // Default -- data part is default int value; both links are null.
    BinNode()
    : left(0), right(0),height(-1),parentofnode(0)
    {}

    // Explicit Value -- data part contains item; both links are null.
    BinNode(int item)
    : data(item), left(0), right(0),height(-1),parentofnode(0)
    {}
 
  };// end of class BinNode declaration
  
  /***** Data Members *****/
  BinNode * myRoot; 
  void preOrderRecursion(BinNode* node)const;
  void inOrderRecursion(BinNode* node)const;
  void rightRotate(BinNode* node, BinNode* myRoot)const;
  void leftRotate(BinNode* node, BinNode* myRoot)const;
  void leftRotatethenRightRotate(BinNode* node)const;
  void rightRotatethenLeftRotate(BinNode* node)const;
  void recalculateheight(BinNode* node)const;
  void checkInconsistency(BinNode* node,int heavycase)const;
  int nodecountRecursion(BinNode* node,int totalnodes)const;
  int heavyside(BinNode* addednode)const;
}; // end of class declaration

#endif
