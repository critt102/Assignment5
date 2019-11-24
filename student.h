#include <iostream>
using namespace std;

class Student{
public:
  int student_id;
  string name;
  string level;
  string major;
  double gpa;
  int advisor;

  Student(){
    student_id=0;
    name="";
    level="";
    major="";
    gpa=0.00;
    advisor=0;
  }
  Student(int m_id){
    student_id=m_id;
    name="";
    level="";
    major="";
    gpa=0.00;
    advisor=0;
  }
  Student(int m_id, string m_name, string m_level, string m_major, double m_gpa, int m_advisor){
    student_id=m_id;
    name=m_name;
    level=m_level;
    major=m_major;
    gpa=m_gpa;
    advisor=m_advisor;
  }
  ~Student(){}

  bool operator<(Student student_b){
    return(this->student_id < student_b.student_id);
  }

  bool operator>(Student student_b){
    return(this->student_id > student_b.student_id);
  }

  bool operator==(Student student_b){
    return(this->student_id==student_b.student_id);
  }

  bool operator!=(Student student_b){
    return(this->student_id!=student_b.student_id);
  }



  //overload equality, less than, greater than operations
};
ostream& operator<<(ostream& os, const Student student_b) {
		os << "Student ID: " << student_b.student_id << endl;
		os << "Student Name: " << student_b.name << endl;
		os << "Student Year: " << student_b.level << endl;
		os << "Student Major: " << student_b.major << endl;
		os << "Student GPA: " << student_b.gpa << endl;
		os << "Student Advisor's ID: " << student_b.advisor << endl;
    return os;
}
