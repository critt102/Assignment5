#include <iostream>
#include "database.h"
using namespace std;

int main(int argc, char**argv){
  BST<Student> bb;
  Student* one=new Student(500, "Ally", "Junior", "English", 3.8, 12345);
  Student* two=new Student(2010, "Katie", "Freshman", "Film", 2.7, 12345);
  Student* three=new Student(60012, "Katie", "Freshman", "Film", 4.0, 98765);
  bb.insert(*one);
  bb.insert(*two);
  bb.insert(*three);
  //bb.printTree();

  //cout<<bb.getMax()->key<<endl;
  // bool sear=bb.search(29);
  // if(sear==true)
  //   cout<<"TRUE"<<endl;
  // else
  //   cout<<"FALSE"<<endl;

  // Database directory;
  // directory.print();

  // bb.deleteNode(*one);
  // bb.printTree();

  return 0;
}
