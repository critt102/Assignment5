#include <iostream>
#include <fstream>
#include "BST.h"
#include "genstack.h"
using namespace std;

class Database{
public:
  ifstream in_file_s;
  ifstream in_file_f;
  ofstream out_file;
  BST<Student>* masterStudent;
  BST<Faculty>* masterFaculty;
  string line;
  string menu;
  string student_file;
  string faculty_file;
  int choice;
  GenStack* Rollback;

  void prompt(){
    cout<<menu<<endl;
    cin>>choice;

    //Print all students and their information (sorted by ascending id #)
    if(choice==1){
      masterStudent->printTree();
    }

    //Print all faculty and their information (sorted by ascending id #)
    else if(choice==2){
      masterFaculty->printTree();
    }

    //Find and display student information given the students id
    else if(choice==3){
      int id_in;
      cout<<"Enter the student id number: ";
      cin>>id_in;
      //check for if entry is not a number
      Student* s = new Student(id_in);
      TreeNode<Student>* s_out=masterStudent->search(*s);
      if(s_out!=NULL){
        cout<<s_out->key<<endl;
      }
      else{
        cout<<"Student not found."<<endl;
        exit(0);
      }
      delete s;
    }

    //Find and display faculty information given the faculty id
    else if(choice==4){
      int id_in;
      cout<<"Enter the faculty id number: ";
      cin>>id_in;
      //check if entry is an integer
      Faculty* f = new Faculty(id_in);
      TreeNode<Faculty>* f_out=masterFaculty->search(*f);
      if(f_out!=NULL){
        cout<<f_out->key<<endl;
      }
      else{
        cout<<"Faculty member not found."<<endl;
        exit(0);
      }
      delete f;
    }

    //Find and display faculty information given the faculty id
    else if(choice==5){
      int id_in;
      cout<<"Enter the student id number: ";
      cin>>id_in;
      //check if input is an integer
      Student* s = new Student(id_in);
      TreeNode<Student>* s_out=masterStudent->search(*s);
      if(s_out!=NULL){
        int s_advisor=s_out->key.advisor;
        Faculty* f= new Faculty(s_advisor);
        TreeNode<Faculty>* f_out=masterFaculty->search(*f);
        if(f_out!=NULL){
          cout<<f_out->key<<endl;
        }
        else{
          cout<<"Faculty advisor not found."<<endl;
          exit(0);
        }
        delete f;
      }
      else{
        cout<<"Student not found."<<endl;
        exit(0);
      }
      delete s;
    }

    //Given a faculty id, print ALL the names and info of his/her advisees.
    else if(choice==6){
      int id_in;
      cout<<"Enter the faculty id number: ";
      cin>>id_in;
      //check that input is an integer
      Faculty* f = new Faculty(id_in);
      TreeNode<Faculty>* f_out=masterFaculty->search(*f);
      if(f_out!=NULL){
        DLinkedList<int>* f_advisees=f_out->key.ids;
        while(f_advisees->isEmpty()!=true){
          int id_num=f_advisees->removeFront();
          Student* s = new Student(id_num);
          TreeNode<Student>* s_out=masterStudent->search(*s);
          if(s_out!=NULL){
            cout<<s_out->key<<endl;
          }
          else{
            cout<<"Student advisee information not found."<<endl;
            exit(0);
          }
          delete s;
        }
      }
      else{
        cout<<"Faculty member not found."<<endl;
        exit(0);
      }
      delete f;
    }

    //Add a new student
    else if(choice==7){

    }

    //Delete a student given the id
    else if(choice==8){
      int id_in;
      cout<<"Enter the student id number: ";
      cin>>id_in;
      //check for if entry is not a number
      Student* s = new Student(id_in);
      bool deleted=masterStudent->deleteNode(*s);
      if(deleted==true){
        cout<<"Student deleted."<<endl;
      }
      else{
        cout<<"Student not found."<<endl;
        exit(0);
      }
      int advisor_id=s->advisor;
      Faculty* s_advisor=new Faculty(advisor_id);
      TreeNode<Faculty>* f_out=masterFaculty->search(*s_advisor);
      if(f_out!=NULL){
        DLinkedList<int>* f_out_advisees=f_out->key.ids;
        if(f_out_advisees->isEmpty()==false){
          ListNode<int>* s_delete=f_out_advisees->remove(s->student_id);
          if(s_delete!=NULL){
            cout<<"Student removed from Advisor's list."<<endl;
          }
          else{
            cout<<"Student not found in faculty advisee list."<<endl;
            exit(0);
          }
        }
        else{
          cout<<"Faculty advisee list not found"<<endl;
          exit(0);
        }
      }
      else{
        cout<<"No students found in advisee list"<<endl;
        exit(0);
      }
      delete s;
      delete s_advisor;
    }

    //Add a new faculty member
    else if(choice==9){

    }

    //Delete a faculty member given the id.
    else if(choice==10){
      int id_in;
      cout<<"Enter the faculty id number: ";
      cin>>id_in;
      //check if entry is an integer
      Faculty* f = new Faculty(id_in);
      bool deleted=masterFaculty->deleteNode(*f);
      if(deleted==true){
        cout<<"Faculty member deleted."<<endl;
      }
      else{
        cout<<"Faculty member not found."<<endl;
        exit(0);
      }

      /**
       *go through list of Advisees, find them in masterStudent
       *reassign them a new advisor, find that advisor in masterFaculty
       *add student id to advisee list
       */
       delete f;
    }

    //Change a student’s advisor given the student id and the new faculty id.
    else if(choice==11){

    }

    //Remove an advisee from a faculty member given the ids
    else if(choice==12){
      int s_id;
      int f_id;
      cout<<"Enter the student id number: ";
      cin>>s_id;
      cout<<"Enter the faculty id number: ";
      cin>>f_id;
      //check for if entry is not a number
      Student* s = new Student(s_id);
      Faculty* f=new Faculty(f_id);
      TreeNode<Faculty>* f_out=masterFaculty->search(*f);
      if(f_out!=NULL){
        DLinkedList<int>* f_out_advisees=f_out->key.ids;
        if(f_out_advisees->isEmpty()==false){
          ListNode<int>* s_delete=f_out_advisees->remove(s_id);
          if(s_delete!=NULL){
            cout<<"Student removed from advisee list."<<endl;
          }
          else{
            cout<<"Student not found in faculty advisee list."<<endl;
            exit(0);
          }
        }
        else{
          cout<<"No students found in advisee list"<<endl;
          exit(0);
        }
      }
      else{
        cout<<"Faculty advisor not found"<<endl;
        exit(0);
      }

      //assign student new advisor

      delete s;
      delete f;
    }

    //Rollback
    else if(choice==13){

    }

    //Exit
    else if(choice==14){
      exit(0);
    }
    //did not enter a valid number
    else{
      cout<<"Entry invald. Please try again.";
      exit(0);
    }
  }

  Database(){
    masterStudent=new BST<Student>();
    masterFaculty=new BST<Faculty>();
    line="";
    menu=
    "1. Print all students and their information (sorted by ascending id #)\n"
    "2. Print all faculty and their information (sorted by ascending id #)\n"
    "3. Find and display student information given the students id\n"
    "4. Find and display faculty information given the faculty id\n"
    "5. Given a student’s id, print the name and info of their faculty advisor\n"
    "6. Given a faculty id, print ALL the names and info of his/her advisees.\n"
    "7. Add a new student\n"
    "8. Delete a student given the id\n"
    "9. Add a new faculty member\n"
    "10. Delete a faculty member given the id.\n"
    "11. Change a student’s advisor given the student id and the new faculty id.\n"
    "12. Remove an advisee from a faculty member given the ids\n"
    "13. Rollback\n"
    "14. Exit\n";
    Rollback= new GenStack(5);
    prompt();
  }

  Database(string m_student_file, string m_faculty_file){
    student_file=m_student_file;
    faculty_file=m_faculty_file;
    in_file_s.open(student_file, ios::in);
    in_file_f.open(faculty_file, ios::in);
    masterStudent=new BST<Student>();
    masterFaculty=new BST<Faculty>();
    line="";
    menu=
    "1. Print all students and their information (sorted by ascending id #)\n"
    "2. Print all faculty and their information (sorted by ascending id #)\n"
    "3. Find and display student information given the students id\n"
    "4. Find and display faculty information given the faculty id\n"
    "5. Given a student’s id, print the name and info of their faculty advisor\n"
    "6. Given a faculty id, print ALL the names and info of his/her advisees.\n"
    "7. Add a new student\n"
    "8. Delete a student given the id\n"
    "9. Add a new faculty member\n"
    "10. Delete a faculty member given the id.\n"
    "11. Change a student’s advisor given the student id and the new faculty id.\n"
    "12. Remove an advisee from a faculty member given the ids\n"
    "13. Rollback\n"
    "14. Exit\n";
    Rollback= new GenStack(5);
  }

  ~Database(){}

  void print(){
    cout<<menu<<endl;
  }

};
