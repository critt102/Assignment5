/** BST.h
 *Header file for Binary Search Trees
 *@author Mary Kate Crittenden
 *2278514
 *critt102@mail.chapman.edu
 *CPSC 350-01
 *Assignment 5
 */
#include <iostream>
#include <fstream>
#include "faculty.h"
#include "student.h"
#include "BST_node.h"
using namespace std;

/**
 * BST creates and defines the parts of a Binary Search Tree (BST)
 * supporting the usual operations
 */
template <class T>
class BST{
  private:
    //TreeNode representing the root of the BST
    TreeNode<T> *root;
  public:
    //default constructor
    BST(){
      root=NULL; //empty Tree
    }
    /**
     * Recursive destructor method to delete nodes of BST
     * @param node, represents the node to start destructing at
     */
    void recDestruct(TreeNode<T>* node){
      if (node!=NULL){
        recDestruct(node->left);
        recDestruct(node->right);
        delete node;
      }
    }
    //destructor
    ~BST(){
      recDestruct(root);
    }
    /**
     * Checks to see if the BST is empty
     * @return bool, true if root of tree is NULL, false otherwise
     */
    bool isEmpty(){
      if(root==NULL){
        return true;
      }
      else{
        return false;
      }
    }
    /**
     * Checks to see if the given node is the root of the tree
     * @param  node, node to compare to root
     * @return bool, true if node given is the root of the tree, false otherwise
     */
    bool isRoot(TreeNode<T>* node){
      if(node==root){
        return true;
      }
      else{
        return false;
      }
    }
    /**
     * Recursive print method, prints values of all nodes in tree to console,
     * in ascending order.
     * @param node, the node to start printing at
     */
    void recPrint(TreeNode<T>* node){
      if(node!=NULL){
        recPrint(node->left);
        cout<<node->key<<endl;
        recPrint(node->right);
      }
      else if(root==NULL){
        cout<<"The tree is empty."<<endl;
      }
    }
    /**
     * Calls recPrint, to print entire BST
     */
    void printTree(){
      recPrint(root);
    }

    /**
     * Recursive serialize method, to write a BST to a file
     * @param node, node to start serializing at
     * @param out_file, the stream of the file to write to
     */
    void recSerialize(TreeNode<T>* node, ofstream& out_file){
      if(node!=NULL){
        recSerialize(node->left, out_file);
        out_file<<node->key;
        recSerialize(node->right, out_file);
      }
    }
    /**
     * Calls recSerialize, to write entire BST to a file
     * @param out_file, the stream of the file to write to
     */
    void serializeTree(ofstream& out_file){
      recSerialize(root, out_file);
    }
    /**
     * Finds and returns the Node with the greatest value in the tree
     * @return TreeNode with greatest value
     */
    TreeNode<T>* getMax(){
      TreeNode<T> *current=root;
      if(root==NULL)//empty TreeNode
        return NULL;
      while(current->right !=NULL){
        current=current->right;
      }
      return (current);
    }
    /**
     * Finds and returns the Node with the smallest value in the tree
     * @return TreeNode with smallest value
     */
    TreeNode<T>* getMin(){
      TreeNode<T> *current=root;
      if(root==NULL)//empty TreeNode
        return NULL;
      while(current->left !=NULL){
        current=current->left;
      }
      return(current);
    }
    /**
     * Creates a node for given value, then inserts it into the BST
     * @param value, the value to be inserted
     */
    void insert(T value){
      TreeNode<T> *node=new TreeNode<T>(value);
      if(root==NULL){
        //empty Tree
        root=node;
      }
      else{
        //tree is not empty, we need to find insertion location
        TreeNode<T> *current=root;
        TreeNode<T> *parent=NULL;
        while (current !=NULL){
          parent=current;
          if(value<current->key){
            //go left
            current=current->left;
            if (current==NULL){
              //we found our insertion point
              parent->left=node;
              break;
            }
          }
          else if(value==current->key){
            //if value already exists in tree, don't insert
            cout<<"Value already exists in the tree."<<endl;
            break;
          }
          else{
            //go right
            current=current->right;
            if (current==NULL){
              //we found our insertion point
              parent->right=node;
              break;
            }
          }
        }
      }
    }
    /**
     * Traverses the tree to see if it contains the given value
     * @param  value, value to find in the tree
     * @return Treenode that contains the matching value, or NULL if the value is not found
     */
    TreeNode<T>* search(T value){
      if(root==NULL){ //empty tree
        return NULL;
      }
      else{
        //tree is not empty, look for value
        TreeNode<T> *current=root;
        while(current->key !=value){
          if(value<current->key){
            current=current->left;
          }
          else{
            current=current->right;
          }
          if(current==NULL){
            //value not found
            return NULL;
          }
        }
        return current;
      }
    }
    /**
     * gets the successor to a node, to be used in delete
     * @param  d, node to find successor to
     * @return Tree node that is the successor to d
     */
    TreeNode<T>* getSuccessor(TreeNode<T> *d)
    {
      TreeNode<T> *sp=d; //sp is successor's parent/node to be deleted
      TreeNode<T> *successor=d;
      TreeNode<T> *current=d->right; //start one right

      while(current !=NULL){
        //one right all the way left
        sp=successor;
        successor=current;
        current=current->left;
      }

      if (successor!=d->right){
        //successor is descendant of the right child
        sp->left=successor->right;
        successor->right=d->right;
      }
      return successor;
    }
    /**
     * Deletes given node from the BST
     * @param  value, value of node to delete
     * @return bool, true if node is found and deleted, false otherwise
     */
    bool deleteNode(T value){
      if(root==NULL){
        return false;
      }
      TreeNode<T> *current=root;
      TreeNode<T> *parent=root;
      bool isLeft=true;

      //look for the node
      while(current->key !=value){
        parent=current;
        if(value<current->key){
          isLeft=true;
          current=current->left;
        }
        else{
          isLeft=false;
          current=current->right;
        }
        if(current==NULL){
          //did not find the value
          return false;
        }
      }
      //found node that needs to be deleted
      //no children, leaf node
      if(current->left==NULL && current->right==NULL){
        if(current==root){
          root=NULL;
        }
        else if(isLeft){
          parent->left=NULL;
        }
        else{
          parent->right=NULL;
        }
      }

      //node has one child, need to determine if child is left or right
      else if(current->right==NULL){
        //has no right child
        if(current==root){
          root=current->left;
        }
        else if(isLeft){
          parent->left=current->left;
        }
        else{
          parent->right=current->left;
        }
      }

      else if(current->left==NULL){
        //has no left child
        if(current==root){
          root=current->right;
        }
        else if(isLeft){
          parent->left=current->right;
        }
        else{
          parent->right=current->right;
        }
      }
      //node has two children
      else{
        //find successor
        TreeNode<T> *successor =getSuccessor(current);
        if(current==root){
          root=successor;
        }
        else if(isLeft){
          parent->left=successor;
        }
        else{
          parent->right=successor;
        }
        successor->left=current->left;
      }
      return true;
    }
};
