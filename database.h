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
  GenStack<BST<Student>>* rollback_s;
  GenStack<BST<Faculty>>* rollback_f;

  void pressEnter(){
    cout<<"Press Enter to continue.";
    cin.get();
    cin.ignore();
  }

  void prompt(){
    while(true){
      cout<<menu;
      cin>>choice;
      if(cin.fail()){
        cout<<"Number entered is invalid."<<endl;
        exit(0);
      }

      //Print all students and their information (sorted by ascending id #)
      if(choice==1){
        masterStudent->printTree();
        pressEnter();
      }

      //Print all faculty and their information (sorted by ascending id #)
      else if(choice==2){
        masterFaculty->printTree();
        pressEnter();
      }

      //Find and display student information given the students id
      else if(choice==3){
        int id_in;
        cout<<"Enter the student id number: ";
        cin>>id_in;
        if(cin.fail()){
          cout<<"Number entered is invalid."<<endl;
          exit(0);
        }
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
        pressEnter();
      }

      //Find and display faculty information given the faculty id
      else if(choice==4){
        int id_in;
        cout<<"Enter the faculty id number: ";
        cin>>id_in;
        if(cin.fail()){
          cout<<"Number entered is invalid."<<endl;
          exit(0);
        }
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
        pressEnter();
      }

      //Given a student’s id, print the name and info of their faculty advisor
      else if(choice==5){
        int id_in;
        cout<<"Enter the student id number: ";
        cin>>id_in;
        if(cin.fail()){
          cout<<"Number entered is invalid."<<endl;
          exit(0);
        }
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
        pressEnter();
      }

      //Given a faculty id, print ALL the names and info of his/her advisees.
      else if(choice==6){
        int id_in;
        cout<<"Enter the faculty id number: ";
        cin>>id_in;
        if(cin.fail()){
          cout<<"Number entered is invalid."<<endl;
          exit(0);
        }
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
        pressEnter();
      }

      //Add a new student
      else if(choice==7){
        int student_id;
        string name;
        string level;
        string major;
        double gpa;
        int advisor;

        cout<<"Enter student's id number: ";
        cin>>student_id;
        if(cin.fail()){
          cout<<"Number entered is invalid."<<endl;
          exit(0);
        }
        cout<<"Enter student's name: ";
        cin>>name;
        cout<<"Enter student's level (Freshman, Sophomore, etc): ";
        cin>>level;
        cout<<"Enter student's major: ";
        cin>>major;
        cout<<"Enter student's gpa: ";
        cin>>gpa;
        if(cin.fail()){
          cout<<"Number entered is invalid."<<endl;
          exit(0);
        }
        cout<<"Enter student's advisor's id number: ";
        cin>>advisor;
        if(cin.fail()){
          cout<<"Number entered is invalid."<<endl;
          exit(0);
        }
        cout<<endl;

        Student* s=new Student(student_id, name, level, major, gpa, advisor);
        Faculty *s_advisor=new Faculty(advisor);
        TreeNode<Faculty>* f_advisor=masterFaculty->search(*s_advisor);
        //check if faculty advisor exists
        if(f_advisor!=NULL){
          masterStudent->insert(*s);
          cout<<"Student entry created."<<endl;
        }
        else{
          cout<<"Student cannot be created because given faculty advisor does not exist."<<endl;
        }
        delete s;
        delete s_advisor;

        rollback_s->push(*masterStudent);
        rollback_f->push(*masterFaculty);
        pressEnter();
      }

      //Delete a student given the id
      else if(choice==8){
        int id_in;
        cout<<"Enter the student id number: ";
        cin>>id_in;
        if(cin.fail()){
          cout<<"Number entered is invalid."<<endl;
          exit(0);
        }
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
            ListNode<int>* s_delete=masterFaculty->search(*s_advisor)->key.ids->remove(s->student_id);
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

        rollback_s->push(*masterStudent);
        rollback_f->push(*masterFaculty);
        pressEnter();
      }

      //Add a new faculty member
      else if(choice==9){
        int faculty_id;
        string name;
        string level;
        string depart;

        cout<<"Enter faculty's id number: ";
        cin>>faculty_id;
        if(cin.fail()){
          cout<<"Number entered is invalid."<<endl;
          exit(0);
        }
        cout<<"Enter faculty's name: ";
        cin>>name;
        cout<<"Enter faculty's level (Professor, Assistant prof, etc): ";
        cin>>level;
        cout<<"Enter the faculty's department: ";
        cin>>depart;
        cout<<endl;

        Faculty* f=new Faculty(faculty_id, name, level, depart);
        masterFaculty->insert(*f);
        delete f;
        cout<<"Faculty member created."<<endl;

        rollback_s->push(*masterStudent);
        rollback_f->push(*masterFaculty);
        pressEnter();
      }

      //Delete a faculty member given the id.
      else if(choice==10){
        int run_program=1;
        //if faculty tree isn't empty
        if(masterFaculty->isEmpty()==false){
          int id_in;
          //ask for faculty member to delete
          cout<<"Enter the faculty id number: ";
          cin>>id_in;
          if(cin.fail()){
            cout<<"Number entered is invalid."<<endl;
            exit(0);
          }
          Faculty* f = new Faculty(id_in);
          //search for faculty member in tree
          TreeNode<Faculty>* f_test=masterFaculty->search(*f);
          //if faculty member is the only one in the tree
          if(masterFaculty->isRoot(f_test)==true && f_test!=NULL){
            string del_con;
            //ask if they want to continue
            cout<<"There is only one faculty member left in the tree, are you sure you want to delete? y or n?"<<endl;
            cin>>del_con;
            //if they want to continue
            if(del_con=="y" || del_con=="Y"){
              run_program=1;
            }
            else{
              cout<<"Action aborted."<<endl;
              run_program=0;
            }

            //go through with the deletion
            if(run_program==1){
              //find and delete the faculty member
              bool deleted=masterFaculty->deleteNode(*f);
              //if found
              if(deleted==true){
                cout<<"Faculty member deleted."<<endl;
                //time to reassign advisors/advisees
                //get advisee list
                DLinkedList<int>* f_advisees=f->ids;
                //go through all ids in list
                while(f_advisees->isEmpty()==false){
                    int current=f_advisees->removeFront();
                    Student* s=new Student(current);
                    //find the student in the student tree
                    TreeNode<Student>* s_out=masterStudent->search(*s);
                    //if student exists
                    if(s_out!=NULL){
                      string inp;
                      cout<<"Do you want to reassign a faculty advisor for the deleted faculy member's advisees? y or n? "
                        <<"(if n, students advisees will automatically be assigned to an existing faculty member)"<<endl;
                      cin>>inp;
                      //user wants to choose new faculty advisor
                      if(inp=="Y" || inp=="y"){
                        int newadvisor;
                        cout<<"Enter the id number of the desired faculty advisor: ";
                        cin>>newadvisor;
                        if(cin.fail()){
                          cout<<"Number entered is invalid."<<endl;
                          exit(0);
                        }
                        Faculty* new_f=new Faculty(newadvisor);
                        TreeNode<Faculty>* new_advisor=masterFaculty->search(*new_f);
                        //if faculty member exists
                        if(new_advisor!=NULL){
                          //assign new advisor to the student
                          masterStudent->search(*s)->key.advisor=newadvisor;
                          //add student to new advisors advisee list
                          masterFaculty->search(*new_f)->key.ids->insertBack(s_out->key.student_id);
                        }
                        else{
                          cout<<"Faculty member not found"<<endl;
                        }
                        delete new_f;
                      }
                      //user does not want to assign specific faculty advisor
                      else if(inp=="N" || inp=="n"){
                        //automatically assign a new one to the students
                        TreeNode<Faculty>* new_advisor=masterFaculty->getMin();
                        //tree isn't empty, there are advisors available
                        if(new_advisor!=NULL){
                          //assign new advisor to the student
                          s_out->key.advisor=new_advisor->key.faculty_id;
                          //add student to new advisors advisee list
                          masterFaculty->getMin()->key.ids->insertBack(s_out->key.student_id);
                        }
                        else{
                          cout<<"Faculty Tree is Empty"<<endl;
                        }
                      }
                      else{
                        cout<<"Invalid input."<<endl;
                      }
                    }
                    //student is not found in masterStudent
                    else{
                      cout<<"There is a student on an advisee list that is not in the student database."<<endl;
                      exit(0);
                    }
                  delete s;
                }
                 delete f;
              }
              else{
                cout<<"Faculty member not found."<<endl;
              }
            }
          }
        }
        else{
          cout<<"Faculty database is empty."<<endl;
        }

        rollback_s->push(*masterStudent);
        rollback_f->push(*masterFaculty);
        pressEnter();
      }

      //Change a student’s advisor given the student id and the new faculty id.
      else if(choice==11){
        int f_id_in;
        int s_id_in;
        //ask for faculty member to delete
        cout<<"Enter the student id number: ";
        cin>>s_id_in;
        if(cin.fail()){
          cout<<"Number entered is invalid."<<endl;
          exit(0);
        }
        Student* s=new Student(s_id_in);
        //search for student in masterStudent
        TreeNode<Student>* s_curr=masterStudent->search(*s);
        if(s_curr==NULL){
          cout<<"Student not found."<<endl;
          exit(0);
        }
        cout<<"Enter the faculty id number: ";
        cin>>f_id_in;
        if(cin.fail()){
          cout<<"Number entered is invalid."<<endl;
          exit(0);
        }

        Faculty* f = new Faculty(f_id_in);
        //search for faculty member in masterFaculty
        TreeNode<Faculty>* f_new=masterFaculty->search(*f);
        if(f_new==NULL){
          cout<<"Faculty member not found."<<endl;
          exit(0);
        }
        //both student and facult were found
        if(s_curr!=NULL && f_new!=NULL){

          //remove student from current advisor's list
          int f_curr_id=s_curr->key.advisor;
          Faculty* f_curr=new Faculty(f_curr_id);
          TreeNode<Faculty>* f_node=masterFaculty->search(*f_curr);
          //if faculty member is found in tree
          if(f_node!=NULL){
            //attempt to remove student from list
            ListNode<int>* s_found=masterFaculty->search(*f_curr)->key.ids->remove(s_id_in);
            //if student is found on advisee list
            if(s_found!=NULL){
              cout<<"Student has been removed from previous Faculty advisor's advisee list."<<endl;
            }
            else{
              cout<<"Student was not found on current advisor's advisee list."<<endl;
            }
          }
          else{
            cout<<"Previous Faculty advisor was not found in Faculty Tree."<<endl;
          }

          //change student's advisor
          masterStudent->search(*s)->key.advisor=f_new->key.faculty_id;
          //add student to faculy's advisee list
          masterFaculty->search(*f)->key.ids->insertBack(s_curr->key.student_id);
        }

        else{
          cout<<"Faculty advisor or student advisee not found."<<endl;
          exit(0);
        }
        delete f;
        delete s;

        rollback_s->push(*masterStudent);
        rollback_f->push(*masterFaculty);
        pressEnter();
      }

      //Remove an advisee from a faculty member given the ids
      else if(choice==12){
        int s_id;
        int f_id;
        cout<<"Enter the student id number: ";
        cin>>s_id;
        if(cin.fail()){
          cout<<"Number entered is invalid."<<endl;
          exit(0);
        }
        Student* s = new Student(s_id);
        //find student in tree
        TreeNode<Student>* s_out=masterStudent->search(*s);
        if(s_out==NULL){
          cout<<"Student not found."<<endl;
          exit(0);
        }
        cout<<"Enter the faculty id number: ";
        cin>>f_id;
        if(cin.fail()){
          cout<<"Number entered is invalid."<<endl;
          exit(0);
        }
        Faculty* f=new Faculty(f_id);
        //find faculty in tree
        TreeNode<Faculty>* f_out=masterFaculty->search(*f);
        //if both are found
        if(f_out==NULL){
          cout<<"Faculty member not found."<<endl;
          exit(0);
        }
        if(f_out!=NULL && s_out!=NULL){
          //get advisee listnode
          DLinkedList<int>* f_out_advisees=f_out->key.ids;
          //if advisee list isn't empty
          if(f_out_advisees->isEmpty()==false){
            //attempt to remove student from advisee list
            ListNode<int>* s_delete=masterFaculty->search(*f)->key.ids->remove(s_id);
            //if student is found
            if(s_delete!=NULL){
              cout<<"Student removed from advisee list."<<endl;

              //assign new faculty advisor
              string inp;
              cout<<"Do you want to reassign a faculty advisor to the recently removed student? y or n? "
                <<"(if n, the student will automatically be assigned to an existing faculty member)"<<endl;
              cin>>inp;
              //user wants to choose new faculty advisor
              if(inp=="Y" || inp=="y"){
                int newadvisor;
                cout<<"Enter the id number of the desired faculty advisor: ";
                cin>>newadvisor;
                if(cin.fail()){
                  cout<<"Number entered is invalid."<<endl;
                  exit(0);
                }
                Faculty* new_f=new Faculty(newadvisor);
                TreeNode<Faculty>* new_advisor=masterFaculty->search(*new_f);
                //if faculty member exists
                if(new_advisor!=NULL){
                  //assign new advisor to the student
                  masterStudent->search(*s)->key.advisor=newadvisor;
                  //add student to new advisors advisee list
                  masterFaculty->search(*new_f)->key.ids->insertBack(s_id);
                }
                else{
                  cout<<"Faculty member not found"<<endl;
                }
                delete new_f;
              }
              //user does not want to assign specific faculty advisor
              else if(inp=="N" || inp=="n"){
                //automatically assign a new one to the students
                TreeNode<Faculty>* new_advisor=masterFaculty->getMin();
                //tree isn't empty, there are advisors available
                if(new_advisor!=NULL){
                  //assign new advisor to the student
                  masterStudent->search(*s)->key.advisor=new_advisor->key.faculty_id;
                  //add student to new advisors advisee list
                  masterFaculty->getMin()->key.ids->insertBack(s_id);
                }
                else{
                  cout<<"Faculty Tree is Empty"<<endl;
                }
              }
              else{
                cout<<"Invalid input."<<endl;
              }
            }

            else{
              cout<<"Student not found in faculty advisee list."<<endl;
            }
          }
          else{
            cout<<"No students found in advisee list"<<endl;
            exit(0);
          }
        }

        else{
          cout<<"Faculty advisor or student advisee not found"<<endl;
          exit(0);
        }

        delete s;
        delete f;

        rollback_s->push(*masterStudent);
        rollback_f->push(*masterFaculty);
        pressEnter();
      }

      //Rollback
      else if(choice==13){
        if(rollback_s->isEmpty()==false){
          BST<Student> prev_s=rollback_s->pop();
          masterStudent=&prev_s;
          if(rollback_f->isEmpty()==false){
            BST<Faculty> prev_f=rollback_f->pop();
            masterFaculty=&prev_f;
            cout<<"Last action has been undone."<<endl;
          }
          else{
            cout<<"No previous actions to undo."<<endl;
          }
        }
        else{
          cout<<"No previous actions to undo."<<endl;
        }
        pressEnter();
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
    "14. Exit\n"
    "Please Enter the number of the action you want to perform.\n";
    rollback_s= new GenStack<BST<Student>>(5);
    rollback_f=new GenStack<BST<Faculty>>(5);
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
    "14. Exit\n"
    "Please Enter the number of the action you want to perform.\n";
    rollback_s= new GenStack<BST<Student>>(5);
    rollback_f=new GenStack<BST<Faculty>>(5);
    prompt();
  }

  ~Database(){}

  void print(){
    cout<<menu<<endl;
  }

};
