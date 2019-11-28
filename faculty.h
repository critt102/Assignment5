/** faculty.h
 *Header file for Faculty class
 *@author Mary Kate Crittenden
 *2278514
 *critt102@mail.chapman.edu
 *CPSC 350-01
 *Assignment 5
 */
#include <iostream>
#include <fstream>
#include <typeinfo>
#include "dlinkedlist.h"
using namespace std;

/**
 * Faculty class creates and defines a faculty member, to be used in database,
 * overloading operations >, <, ==, !=, and ostream operator <<
 */
class Faculty{
public:
  //faculty's id number
  int faculty_id;
  //faculty's name
  string name;
  //faculty's level (Professor, Asst Prof, etc)
  string level;
  //faculty's department
  string depart;
  //Linked list of student id, representing faculty's advisees
  DLinkedList<int>* ids;
  //default constructor
  Faculty(){
    faculty_id=0;
    name="";
    level="";
    depart="";
    ids=new DLinkedList<int>();
  }
  //overloaded constructor, faculty id only
  Faculty(int m_id){
    faculty_id=m_id;
    name="";
    level="";
    depart="";
    ids=new DLinkedList<int>();
  }
  //overloaded constructor, minus advisee ids
  Faculty(int m_id, string m_name, string m_level, string m_depart){
    faculty_id=m_id;
    name=m_name;
    level=m_level;
    depart=m_depart;
    ids=new DLinkedList<int>();
  }
  //overloaded constructor
  Faculty(int m_id, string m_name, string m_level, string m_depart, DLinkedList<int>* m_ids){
    faculty_id=m_id;
    name=m_name;
    level=m_level;
    depart=m_depart;
    ids=m_ids;
  }
  //destructor
  ~Faculty(){
    ids=NULL;
  }
  /**
   * overloads the < operator for the faculty class
   * @param faculty_b, faculty to compare to this faculty
   * @return bool, true if give faculty id is greater than this faculty id, false otherwise
   */
  bool operator<(Faculty faculty_b){
    return(this->faculty_id < faculty_b.faculty_id);
  }
  /**
   * overloads the > operator for the faculty class
   * @param faculty_b, faculty to compare to this faculty
   * @return bool, true if give faculty id is less than this faculty id, false otherwise
   */
  bool operator>(Faculty faculty_b){
    return(this->faculty_id > faculty_b.faculty_id);
  }
  /**
   * overloads the == operator for the faculty class
   * @param faculty_b, faculty to compare to this faculty
   * @return bool, true if give faculty id is equal to this faculty id, false otherwise
   */
  bool operator==(Faculty faculty_b){
    return(this->faculty_id == faculty_b.faculty_id);
  }
  /**
   * overloads the != operator for the faculty class
   * @param faculty_b, faculty to compare to this faculty
   * @return bool, true if give faculty id is not equal to this faculty id, false otherwise
   */
  bool operator!=(Faculty faculty_b){
    return(this->faculty_id != faculty_b.faculty_id);
  }
};
/**
 * overloads the ostream operator << for the faculty class
 * @param os, the stream with location to write to; faculty_b, the faculty to print
 */
ostream& operator<<(ostream& os, const Faculty faculty_b) {
  //if writing to a file
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
  //to write to console
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
