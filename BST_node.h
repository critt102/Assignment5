/** BST_node.h
 *Header file for Binary Search Tree Nodes
 *@author Mary Kate Crittenden
 *2278514
 *critt102@mail.chapman.edu
 *CPSC 350-01
 *Assignment 5
 */
#include <iostream>
using namespace std;

/**
 * TreeNode creates and defines Nodes to be used in a Binary Search Tree (BST)
 */
template <class T>
class TreeNode{
  public:
    //template to hold key/value of node
    T key;
    //pointer to left node
    TreeNode *left;
    //pointer to right node
    TreeNode *right;
    //default constructor
    TreeNode(){
      key=0;
      left=NULL;
      right=NULL;
    }
    //overloaded constructor
    TreeNode(T k){
      key=k;
      left=NULL;
      right=NULL;
    }
    //destructor
    virtual ~TreeNode(){}
};
