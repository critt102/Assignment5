#include <iostream>
#include "faculty.h"
#include "student.h"
#include "BST_node.h"
using namespace std;

template <class T>
class BST{
  private:
    TreeNode<T> *root;
  public:
    BST(){
      root=NULL; //empty Tree
    }

    ~BST(){
      //research
    }

    bool isEmpty(){
      if(root==NULL){
        return true;
      }
      else{
        return false;
      }
    }

    bool isRoot(TreeNode<T>* node){
      if(node==root){
        return true;
      }
      else{
        return false;
      }
    }

    void recPrint(TreeNode<T>* node){
      if(node!=NULL){
        recPrint(node->left);
        cout<<node->key<<endl;
        recPrint(node->right);
      }
      else{
        cout<<"The tree is empty."<<endl;
      }
    }

    void printTree(){
      recPrint(root);
    }

    TreeNode<T>* getMax(){
      TreeNode<T> *current=root;
      if(root==NULL)//empty TreeNode
        return NULL;
      while(current->right !=NULL){
        current=current->right;
      }
      return (current);
    }

    TreeNode<T>* getMin(){
      TreeNode<T> *current=root;
      if(root==NULL)//empty TreeNode
        return NULL;
      while(current->left !=NULL){
        current=current->left;
      }
      return(current);
    }

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
            current=current->left;
            //going left
            if (current==NULL){
              //we found our insertion point
              parent->left=node;
              break;
            }
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

    TreeNode<T>* search(T value){
      if(root==NULL){ //empty tree
        return NULL;
      }
      else{
        //tree is not empty, lets attempt to look for it
        TreeNode<T> *current=root;
        while(current->key !=value){
          if(value<current->key){
            current=current->left;
          }
          else{
            current=current->right;
          }
          if(current==NULL){ //we did not find the value
            return NULL;
          }
        }
        return current;
      }
    }

    TreeNode<T>* getSuccessor(TreeNode<T> *d)//d is the node to be deleted
    {
      TreeNode<T> *sp=d; //sp is successor's parent/node to be deleted
      TreeNode<T> *successor=d;
      TreeNode<T> *current=d->right; //start one right

      while(current !=NULL){ //one right all the way left
        sp=successor;
        successor=current;
        current=current->left;
      }

      if (successor!=d->right){
        //if successor is descentdant of the right child
        sp->left=successor->right;
        successor->right=d->right;
      }
      return successor;
    }

    bool deleteNode(T value){
      if(root==NULL){
        return false;
      }
      TreeNode<T> *current=root;
      TreeNode<T> *parent=root;
      bool isLeft=true;

      //now lets look for the node
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
        if(current==NULL){ //we did not find the value
          return false;
        }
      }
      //if we make it here, then we found the node that needs to be deleted
      //now lets check our different cases

      //no children, leaf node
      if(current->left==NULL && current->right==NULL){ //leaf
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
      else if(current->right==NULL){ //has no right child
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

      else if(current->left==NULL){ //has no left child
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

      else{ //node has two children
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
