/** student.h
 *Header file for Student class
 *@author Mary Kate Crittenden
 *2278514
 *critt102@mail.chapman.edu
 *CPSC 350-01
 *Assignment 5
 */
#include <iostream>
#include <fstream>
#include <typeinfo>
using namespace std;

/**
 * Student class creates and defines a student, to be used in database,
 * overloading operations >, <, ==, !=, and ostream operator <<
 */
class Student{
public:
  //student's id number
  int student_id;
  //student's name
  string name;
  //student's level (freshman, sophomore, etc)
  string level;
  //student's major
  string major;
  //students gpa
  double gpa;
  //id number of student's faculty advisor
  int advisor;

  //default constructor
  Student(){
    student_id=0;
    name="";
    level="";
    major="";
    gpa=0.00;
    advisor=0;
  }
  //overloaded constructor, just student id
  Student(int m_id){
    student_id=m_id;
    name="";
    level="";
    major="";
    gpa=0.00;
    advisor=0;
  }
  //overloaded constructor
  Student(int m_id, string m_name, string m_level, string m_major, double m_gpa, int m_advisor){
    student_id=m_id;
    name=m_name;
    level=m_level;
    major=m_major;
    gpa=m_gpa;
    advisor=m_advisor;
  }
  //destructor
  ~Student(){}
  /**
   * overloads the < operator for the student class
   * @param student_b Student to compare to this student
   * @return bool, true if give student id is greater than this student id, false otherwise
   */
  bool operator<(Student student_b){
    return(this->student_id < student_b.student_id);
  }
  /**
   * overloads the > operator for the student class
   * @param student_b Student to compare to this student
   * @return bool, true if give student id is less than this student id, false otherwise
   */
  bool operator>(Student student_b){
    return(this->student_id > student_b.student_id);
  }
  /**
   * overloads the == operator for the student class
   * @param student_b Student to compare to this student
   * @return bool, true if give student id is equal to this student id, false otherwise
   */
  bool operator==(Student student_b){
    return(this->student_id==student_b.student_id);
  }
  /**
   * overloads the != operator for the student class
   * @param student_b Student to compare to this student
   * @return bool, true if give student id is not equal to this student id, false otherwise
   */
  bool operator!=(Student student_b){
    return(this->student_id!=student_b.student_id);
  }
};
/**
 * overloads the ostream operator << for the student class
 * @param os, the stream with location to write to; student_b, the student to print
 */
ostream& operator<<(ostream& os, const Student student_b) {
  //if writing to a file
  if (typeid(os) == typeid(ofstream)){
    os<<endl;
    os << student_b.student_id << endl;
		os << student_b.name << endl;
		os << student_b.level << endl;
		os << student_b.major << endl;
		os << student_b.gpa << endl;
		os << student_b.advisor;
  }
  //to write to console
  else{
    os << "Student ID: " << student_b.student_id << endl;
		os << "Student Name: " << student_b.name << endl;
		os << "Student Year: " << student_b.level << endl;
		os << "Student Major: " << student_b.major << endl;
		os << "Student GPA: " << student_b.gpa << endl;
		os << "Student Advisor's ID: " << student_b.advisor << endl;
  }
  return os;
}
