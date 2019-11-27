#include <iostream>
#include <typeinfo>
#include "dlinkedlist.h"
using namespace std;

class Faculty{
public:
  int faculty_id;
  string name;
  string level;
  string depart;
  DLinkedList<int>* ids;

  Faculty(){
    faculty_id=0;
    name="";
    level="";
    depart="";
    ids=new DLinkedList<int>();
  }

  Faculty(int m_id){
    faculty_id=m_id;
    name="";
    level="";
    depart="";
    ids=new DLinkedList<int>();
  }

  Faculty(int m_id, string m_name, string m_level, string m_depart){
    faculty_id=m_id;
    name=m_name;
    level=m_level;
    depart=m_depart;
    ids=new DLinkedList<int>();
  }

  Faculty(int m_id, string m_name, string m_level, string m_depart, DLinkedList<int>* m_ids){
    faculty_id=m_id;
    name=m_name;
    level=m_level;
    depart=m_depart;
    ids=m_ids;
  }

  ~Faculty(){}

  bool operator<(Faculty faculty_b){
    return(this->faculty_id < faculty_b.faculty_id);
  }

  bool operator>(Faculty faculty_b){
    return(this->faculty_id > faculty_b.faculty_id);
  }

  bool operator==(Faculty faculty_b){
    return(this->faculty_id == faculty_b.faculty_id);
  }

  bool operator!=(Faculty faculty_b){
    return(this->faculty_id != faculty_b.faculty_id);
  }

  //overload equality, less than, greater than operations
};


ostream& operator<<(ostream& os, const Faculty faculty_b) {
  if (typeid(os) == typeid(ofstream)){
    os<<endl;
    os << faculty_b.faculty_id << endl;
    os << faculty_b.name << endl;
    os << faculty_b.level << endl;
    os << faculty_b.depart << endl;
    if(faculty_b.ids != NULL){
      ListNode<int>* temp = faculty_b.ids->front;
      while (temp != NULL) {
        os << temp->data << " ";
        temp = temp->next;
      }
    }
  }
  else{
    os << "Faculty ID: " << faculty_b.faculty_id << endl;
    os << "Faculty Name: " << faculty_b.name << endl;
    os << "Faculty Year: " << faculty_b.level << endl;
    os << "Faculty Department: " << faculty_b.depart << endl;
    os << "Faculty Advisees: ";
    if(faculty_b.ids != NULL){
      ListNode<int>* temp = faculty_b.ids->front;
      while (temp != NULL) {
        os << temp->data << " ";
        temp = temp->next;
      }
    }
    os<<endl;
  }
  return os;
}
