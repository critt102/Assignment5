#include <iostream>
using namespace std;

template <class T>
class TreeNode{
  public:
    T key;
    TreeNode *left;
    TreeNode *right;

    TreeNode(){
      key=0;
      left=NULL;
      right=NULL;
    }
    //k=key, which in this example is also the value(data)
    TreeNode(T k){
      key=k;
      left=NULL;
      right=NULL;
    }
    //when creating a template class, destructor must be virtual
    ~TreeNode(){
      //you can research this
    }
};
