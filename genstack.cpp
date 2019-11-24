#include "genstack.h"
#include <iostream>
using namespace std;

GenStack::GenStack(){
  myArray=new char[128];
  size=128;
  top =-1;
}

GenStack::GenStack(int maxSize){
  myArray=new char[maxSize];
  size=maxSize;
  top=-1;
}

GenStack::~GenStack(){
  //lets build some character
  //your job to research this
  delete myArray; //maybe this
}

void GenStack::push(char d){
  //need to check error/boundry check
  //this is your job
  myArray[++top]=d;
}
char GenStack::pop(){
  //error checking, make sure it's not isEmpty
  //return and remove
  return myArray[top--];
}
char GenStack::peek(){
  //check if empty
  return myArray[top];
}
bool GenStack::isFull(){
  return (top==size-1);
}
bool GenStack::isEmpty(){
  return (top==-1);
}
