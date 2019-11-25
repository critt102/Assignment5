#include <iostream>
using namespace std;

template <class T>
class GenStack
{
  public:
    int size;
    int top;
    T *myArray;

    GenStack(){
      myArray=new T[10];
      size=10;
      top =-1;
    }

    GenStack(int maxSize){
      myArray=new T[maxSize];
      size=maxSize;
      top=-1;
    }

    ~GenStack(){
      delete myArray;
    }

    void push(T d){
      //need to check error/boundry check
      //this is your job
      myArray[++top]=d;
    }
    T pop(){
      //error checking, make sure it's not isEmpty
      //return and remove
      return myArray[top--];
    }
    T peek(){
      //check if empty
      return myArray[top];
    }
    bool isFull(){
      return (top==size-1);
    }
    bool isEmpty(){
      return (top==-1);
    }
};
