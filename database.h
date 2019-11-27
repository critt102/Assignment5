#include <iostream>
#include <fstream>
#include <limits>
#include <cstring>
#include "BST.h"
using namespace std;

class Database{
public:
  ifstream in_file_s;
  ifstream in_file_f;
  ofstream out_file_s;
  ofstream out_file_f;
  //snapshots masterStudent
  ifstream in_1_s;
  ofstream out_1_s;
  ifstream in_2_s;
  ofstream out_2_s;
  ifstream in_3_s;
  ofstream out_3_s;
  ifstream in_4_s;
  ofstream out_4_s;
  ifstream in_5_s;
  ofstream out_5_s;
  //snapshots masterFaculty
  ifstream in_1_f;
  ofstream out_1_f;
  ifstream in_2_f;
  ofstream out_2_f;
  ifstream in_3_f;
  ofstream out_3_f;
  ifstream in_4_f;
  ofstream out_4_f;
  ifstream in_5_f;
  ofstream out_5_f;

  int pull;
  int push;

  BST<Student>* masterStudent;
  BST<Faculty>* masterFaculty;
  string line;
  string menu;
  int choice;

  void snapshot(){
    //original tree?
    if(push==1){
      out_1_s.open("one_s", ios::out);
      out_1_f.open("one_f", ios::out);
      masterStudent->serializeTree(out_1_s);
      masterFaculty->serializeTree(out_1_f);
      push=2;
      pull=1;
      cout<<"Snapshot written to 1"<<endl;
      out_1_s.close();
      out_1_f.close();
    }
    else if(push==2){
      out_2_s.open("two_s", ios::out);
      out_2_f.open("two_f", ios::out);
      masterStudent->serializeTree(out_2_s);
      masterFaculty->serializeTree(out_2_f);
      push=3;
      pull=2;
      cout<<"Snapshot written to 2"<<endl;
      out_2_s.close();
      out_2_f.close();
    }
    else if(push==3){
      out_3_s.open("three_s", ios::out);
      out_3_f.open("three_f", ios::out);
      masterStudent->serializeTree(out_3_s);
      masterFaculty->serializeTree(out_2_f);
      push=4;
      pull=3;
      cout<<"Snapshot written to 3"<<endl;
      out_3_s.close();
      out_3_f.close();
    }
    else if(push==4){
      out_4_s.open("four_s", ios::out);
      out_4_f.open("four_f", ios::out);
      masterStudent->serializeTree(out_4_s);
      masterFaculty->serializeTree(out_2_f);
      push=5;
      pull=4;
      cout<<"Snapshot written to 4"<<endl;
      out_4_s.close();
      out_4_f.close();
    }
    else if(push==5){
      out_5_s.open("five_s", ios::out);
      out_5_f.open("five_f", ios::out);
      masterStudent->serializeTree(out_5_s);
      masterFaculty->serializeTree(out_2_f);
      push=1;
      pull=5;
      cout<<"Snapshot written to 5"<<endl;
      out_5_s.close();
      out_5_f.close();
    }
    else{
      cout<<"Snapshot gone wrong"<<endl;
      exit(0);
    }
  }

  void rollback(){
    if(pull==1){
      in_1_s.open("one_s", ios::in);
      in_1_f.open("one_f", ios::in);
      read(in_1_s, in_1_f);
      cout<<"Rollback complete 1"<<endl;
      push=1;
      if(!(in_5_s.peek()==ifstream::traits_type::eof())){
        if(!(in_5_f.peek()==ifstream::traits_type::eof())){
          pull==5;
        }
      }
      else{
        pull==0;
      }
      in_1_s.close();
      in_1_f.close();
    }
    else if(pull==2){
      in_2_s.open("two_s", ios::in);
      in_2_f.open("two_f", ios::in);
      read(in_2_s, in_2_f);
      push=2;
      cout<<"Rollback complete 2"<<endl;
      in_2_s.close();
      in_2_f.close();
      pull=1;
    }
    else if(pull==3){
      in_3_s.open("three_s", ios::in);
      in_3_f.open("three_f", ios::in);
      read(in_3_s, in_3_f);
      push=3;
      cout<<"Rollback complete 3"<<endl;
      in_3_s.close();
      in_3_f.close();
      pull=2;
    }
    else if(pull==4){
      in_4_s.open("four_s", ios::in);
      in_4_f.open("four_f", ios::in);
      read(in_4_s, in_4_f);
      push=4;
      cout<<"Rollback complete 4"<<endl;
      in_4_s.close();
      in_4_f.close();
      pull=3;
    }
    else if(pull==5){
      in_5_s.open("five_s", ios::in);
      in_5_f.open("five_f", ios::in);
      read(in_5_s, in_5_f);
      push=5;
      cout<<"Rollback complete 5"<<endl;
      in_5_s.close();
      in_5_f.close();
      pull=4;
    }
    else if(pull==0){
      cout<<"No actions to undo"<<endl;
    }
    else{
      cout<<"Rollback gone wrong"<<endl;
      exit(0);
    }
  }

  void clean(){
    if(masterStudent->isEmpty()==false)
      masterStudent->serializeTree(out_file_s);
    if(masterFaculty->isEmpty()==false)
      masterFaculty->serializeTree(out_file_f);

    masterStudent=NULL;
    masterFaculty=NULL;
    out_file_s.close();
    out_file_f.close();
    //clear 1
    out_1_s.open("one_s", ios::out);
    out_1_f.open("one_f", ios::out);
    out_1_s.close();
    out_1_f.close();
    //clear 2
    out_2_s.open("two_s", ios::out);
    out_2_f.open("two_f", ios::out);
    out_2_s.close();
    out_2_f.close();
    //clear 3
    out_3_s.open("three_s", ios::out);
    out_3_f.open("three_f", ios::out);
    out_3_s.close();
    out_3_f.close();
    //clear 4
    out_4_s.open("four_s", ios::out);
    out_4_f.open("four_f", ios::out);
    out_4_s.close();
    out_4_f.close();
    //clear 5
    out_5_s.open("five_s", ios::out);
    out_5_f.open("five_f", ios::out);
    out_5_s.close();
    out_5_f.close();
  }

  void pressEnter(){
    cout<<"Press Enter to continue.";
    cin.get();
    cin.ignore();
  }

  void read(ifstream& s, ifstream& f){
    //inputFile.peek() == std::ifstream::traits_type::eof()
    if(!(s.peek()==ifstream::traits_type::eof())){
      //read in students from file
      int student_id;
      string name;
      string level;
      string major;
      double gpa;
      int advisor;
      string space;
      getline(s, space);
      while(!s.eof()){
        //student id
        getline(s, line);
        student_id=stoi(line.c_str());
        //name
        getline(s, name);
        //level
        getline(s, level);
        //major
        getline(s, major);
        //gpa
        getline(s, line);
        gpa=stod(line.c_str());
        //advisor
        getline(s, line);
        advisor=stoi(line.c_str());
        // //space
        // getline(s, space);
        Student* s=new Student(student_id, name, level, major, gpa, advisor);
        masterStudent=new BST<Student>();
        TreeNode<Student>* s_match=masterStudent->search(*s);
        if(s_match==NULL){
          masterStudent->insert(*s);
        }
        else{
          cout<<"Student with given id already exists in the database."<<endl;
        }
      }
      s.close();
    }
    else{
      masterStudent=new BST<Student>();
    }
    if(!(f.peek()==ifstream::traits_type::eof())){
      //read in faculty from file
      int faculty_id;
      string name;
      string level;
      string depart;
      string space;
      string advisees;
      getline(f, space);

      while(!f.eof()){
        DLinkedList<int>* ids=new DLinkedList<int>();
        //faculty id
        getline(f, line);
        faculty_id=stoi(line.c_str());
        //name
        getline(f, name);
        //level
        getline(f, level);
        //department
        getline(f, depart);
        //space/ids
        //getline(f, space);
        getline(f, advisees);
        //cout<<"5"<<advisees<<endl;
        string a = "";
        for (auto x : advisees){
          if (x == ' '){
            if(a!="" || a!=" "){
              ids->insertFront(stoi(a));
            }
              //ids->insertFront(stoi(a));
            a = "";
          }
          else{
            a += x;
          }
        }
        Faculty* f=new Faculty(faculty_id, name, level, depart, ids);
        masterFaculty=new BST<Faculty>();
        //look for existing student id
        TreeNode<Faculty>* f_match=masterFaculty->search(*f);
        if(f_match==NULL){
          masterFaculty->insert(*f);
        }
        else{
          cout<<"Faculty member with given id already exists in the database."<<endl;
        }
        delete f;
      }
      f.close();
    }
    else{
      masterFaculty=new BST<Faculty>();
    }
  }

  // "1. Print all students and their information (sorted by ascending id #)\n"
  // "2. Print all faculty and their information (sorted by ascending id #)\n"
  // "3. Find and display student information given the students id\n"
  // "4. Find and display faculty information given the faculty id\n"
  // "5. Given a student’s id, print the name and info of their faculty advisor\n"
  // "6. Given a faculty id, print ALL the names and info of his/her advisees.\n"
  // "7. Add a new student\n"
  // "8. Delete a student given the id\n"
  // "9. Add a new faculty member\n"
  // "10. Delete a faculty member given the id.\n"
  // "11. Change a student’s advisor given the student id and the new faculty id.\n"
  // "12. Remove an advisee from a faculty member given the ids\n"
  // "13. Rollback\n"
  // "14. Clear Database of all entries.\n"
  // "15. Exit\n"
  // "Please Enter the number of the action you want to perform.\n";
  void prompt(){
    while(true){
      cout<<menu;
      cin>>choice;
      if(cin.fail()){
        cin.ignore();
        cout<<"Entry is invalid."<<endl;
        clean();
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
          cout<<"Entry is invalid."<<endl;
          clean();
          exit(0);
        }
        Student* s = new Student(id_in);
        TreeNode<Student>* s_out=masterStudent->search(*s);
        if(s_out!=NULL){
          cout<<s_out->key<<endl;
        }
        else{
          cout<<"Student not found."<<endl;
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
          cout<<"Entry is invalid."<<endl;
          clean();
          exit(0);
        }
        Faculty* f = new Faculty(id_in);
        TreeNode<Faculty>* f_out=masterFaculty->search(*f);
        if(f_out!=NULL){
          cout<<f_out->key<<endl;
        }
        else{
          cout<<"Faculty member not found."<<endl;
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
          cout<<"Entry is invalid."<<endl;
          clean();
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
          }
          delete f;
        }
        else{
          cout<<"Student not found."<<endl;
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
          cout<<"Entry is invalid."<<endl;
          clean();
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
            }
            delete s;
          }
        }
        else{
          cout<<"Faculty member not found."<<endl;
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
        cin.ignore(numeric_limits<int>::max(),'\n');
        if(cin.fail()){
          cout<<"Entry is invalid."<<endl;
          clean();
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
          cout<<"Entry is invalid."<<endl;
          clean();
          exit(0);
        }
        cout<<"Enter student's advisor's id number: ";
        cin>>advisor;
        if(cin.fail()){
          cout<<"Entry is invalid."<<endl;
          clean();
          exit(0);
        }
        cout<<endl;

        Student* s=new Student(student_id, name, level, major, gpa, advisor);
        Faculty *s_advisor=new Faculty(advisor);
        TreeNode<Faculty>* f_advisor=masterFaculty->search(*s_advisor);
        //check if faculty advisor exists
        if(f_advisor!=NULL){
          TreeNode<Student>* s_match=masterStudent->search(*s);
          if(s_match==NULL){
            snapshot();
            masterStudent->insert(*s);
            cout<<"Student entry created."<<endl;
            masterFaculty->search(*s_advisor)->key.ids->insertBack(s->student_id);
            cout<<"Student added to Faculty Advisor's list."<<endl;
          }
          else{
            cout<<"Student with given id already exists in the database."<<endl;
          }
        }
        else{
          cout<<"Student cannot be created because given faculty advisor does not exist."<<endl;
        }
        delete s;
        delete s_advisor;

        pressEnter();
      }

      //Delete a student given the id
      else if(choice==8){
        int id_in;
        cout<<"Enter the student id number: ";
        cin>>id_in;
        if(cin.fail()){
          cout<<"Entry is invalid."<<endl;
          clean();
          exit(0);
        }
        Student* s = new Student(id_in);
        TreeNode<Student>* s_found=masterStudent->search(*s);
        if(s_found!=NULL){
          int advisor_id=s_found->key.advisor;
          Faculty* s_advisor=new Faculty(advisor_id);
          TreeNode<Faculty>* f_out=masterFaculty->search(*s_advisor);
          if(f_out!=NULL){
            DLinkedList<int>* f_out_advisees=f_out->key.ids;
            if(f_out_advisees->isEmpty()==false){
              snapshot();

              ListNode<int>* s_delete=masterFaculty->search(*s_advisor)->key.ids->remove(s->student_id);
              bool deleted=masterStudent->deleteNode(*s);
              if(s_delete!=NULL && deleted==true){
                cout<<"Student removed from Advisor's list."<<endl;
                cout<<"Student deleted."<<endl;
              }
              else{
                cout<<"Student not found in faculty advisee list."<<endl;
              }
            }
            else{
              cout<<"Faculty advisee list not found"<<endl;
            }
          }
          else{
            cout<<"No students found in advisee list"<<endl;
          }
          delete s;
          delete s_advisor;
          pressEnter();
        }
        else{
          cout<<"Student not found."<<endl;
        }
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
          cout<<"Entry is invalid."<<endl;
          clean();
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
        //look for match
        TreeNode<Faculty>* f_match=masterFaculty->search(*f);
        if(f_match==NULL){
          snapshot();
          masterFaculty->insert(*f);
          cout<<"Faculty member created."<<endl;
        }
        else{
          cout<<"Faculty member with given id already exists in the database."<<endl;
        }

        delete f;
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
            cout<<"Entry is invalid."<<endl;
            clean();
            exit(0);
          }
          Faculty* f = new Faculty(id_in);
          //search for faculty member in tree
          TreeNode<Faculty>* f_test=masterFaculty->search(*f);
          //if faculty member is the only one in the tree
          if(masterFaculty->isRoot(f_test)==true && f_test!=NULL && f_test->right==NULL && f_test->left==NULL){
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
          }
            //go through with the deletion
          if(run_program==1){
            //find and delete the faculty member
            //bool deleted=masterFaculty->deleteNode(*f);
            if(f_test!=NULL){
              cout<<"F is found"<<endl;
            //if found
            //if(deleted==true){
              //cout<<"Faculty member deleted."<<endl;
              //time to reassign advisors/advisees
              //get advisee list
              DLinkedList<int>* f_advisees=f_test->key.ids;
              if(f_advisees->isEmpty()==true){
                snapshot();

                bool deleted=masterFaculty->deleteNode(*f);
                if(deleted==true){
                  cout<<"Faculty member deleted."<<endl;
                }
              }
              //go through all ids in list
              string inp;
              if(f_advisees->isEmpty()==false){
                cout<<"Do you want to reassign a faculty advisor for the deleted faculy member's advisees? y or n? "
                  <<"(if n, students advisees will automatically be assigned to an existing faculty member)"<<endl;
                cin>>inp;
              }
              while(f_advisees->isEmpty()==false){
                  cout<<"List is not empty."<<endl;
                  int current=f_advisees->removeFront();
                  Student* s=new Student(current);
                  //find the student in the student tree
                  TreeNode<Student>* s_out=masterStudent->search(*s);
                  //if student exists
                  if(s_out!=NULL){
                    cout<<"student found"<<endl;
                    //user wants to choose new faculty advisor
                    if(inp=="Y" || inp=="y"){
                      int newadvisor;
                      cout<<"Enter the id number of the desired faculty advisor: ";
                      cin>>newadvisor;
                      if(cin.fail()){
                        cout<<"Entry is invalid."<<endl;
                        clean();
                        exit(0);
                      }
                      Faculty* new_f=new Faculty(newadvisor);
                      TreeNode<Faculty>* new_advisor=masterFaculty->search(*new_f);
                      //if faculty member exists
                      if(new_advisor!=NULL){
                        snapshot();

                        //assign new advisor to the student
                        masterStudent->search(*s)->key.advisor=newadvisor;
                        //add student to new advisors advisee list
                        masterFaculty->search(*new_f)->key.ids->insertBack(s_out->key.student_id);
                        //delete faculty member
                        bool deleted=masterFaculty->deleteNode(*f);
                        if(deleted==true){
                          cout<<"Faculty member deleted."<<endl;
                        }
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
                        snapshot();

                        //assign new advisor to the student
                        s_out->key.advisor=new_advisor->key.faculty_id;
                        //add student to new advisors advisee list
                        masterFaculty->getMin()->key.ids->insertBack(s_out->key.student_id);
                        //delete faculty member
                        bool deleted=masterFaculty->deleteNode(*f);
                        if(deleted==true){
                          cout<<"Faculty member deleted."<<endl;
                        }
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
                    clean();
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
        else{
          cout<<"Faculty database is empty."<<endl;
        }
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
          cout<<"Entry is invalid."<<endl;
          clean();
          exit(0);
        }
        Student* s=new Student(s_id_in);
        //search for student in masterStudent
        TreeNode<Student>* s_curr=masterStudent->search(*s);
        if(s_curr==NULL){
          cout<<"Student not found."<<endl;
        }
        else{
          cout<<"Enter the faculty id number: ";
          cin>>f_id_in;
          if(cin.fail()){
            cout<<"Entry is invalid."<<endl;
            clean();
            exit(0);
          }

          Faculty* f = new Faculty(f_id_in);
          //search for faculty member in masterFaculty
          TreeNode<Faculty>* f_new=masterFaculty->search(*f);
          if(f_new==NULL){
            cout<<"Faculty member not found."<<endl;
          }
          //both student and faculty were found
          if(s_curr!=NULL && f_new!=NULL){
            snapshot();

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
            cout<<"Student's advisor has been changed."<<endl;
            //add student to faculy's advisee list
            masterFaculty->search(*f)->key.ids->insertBack(s_curr->key.student_id);

          }

          // else{
          //   cout<<"Faculty advisor or student advisee not found."<<endl;
          // }
          delete f;
        }
        delete s;
        pressEnter();
      }

      //Remove an advisee from a faculty member given the ids
      else if(choice==12){
        int s_id;
        int f_id;
        cout<<"Enter the student id number: ";
        cin>>s_id;
        if(cin.fail()){
          cout<<"Entry is invalid."<<endl;
          clean();
          exit(0);
        }
        Student* s = new Student(s_id);
        //find student in tree
        TreeNode<Student>* s_out=masterStudent->search(*s);
        if(s_out==NULL){
          cout<<"Student not found."<<endl;
        }
        else{
          cout<<"Enter the faculty id number: ";
          cin>>f_id;
          if(cin.fail()){
            cout<<"Entry is invalid."<<endl;
            clean();
            exit(0);
          }
          Faculty* f=new Faculty(f_id);
          //find faculty in tree
          TreeNode<Faculty>* f_out=masterFaculty->search(*f);
          //if both are found
          if(f_out==NULL){
            cout<<"Faculty member not found."<<endl;
          }
          if(f_out!=NULL && s_out!=NULL){
            //get advisee listnode
            DLinkedList<int>* f_out_advisees=f_out->key.ids;
            //if advisee list isn't empty
            if(f_out_advisees->isEmpty()==false){
              snapshot();

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
                    cout<<"Entry is invalid."<<endl;
                    clean();
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
                  int minormax;
                  TreeNode<Faculty>* new_advisor;
                  //automatically assign a new one to the students
                  if(masterFaculty->getMin()->key.faculty_id!=f_id){
                    new_advisor=masterFaculty->getMin();
                    minormax=0;
                  }
                  else if(masterFaculty->getMax()->key.faculty_id!=f_id){
                    new_advisor=masterFaculty->getMax();
                    minormax=1;
                  }
                  else{
                    cout<<"F is the min and the max yikes"<<endl;
                    clean();
                    exit(0);
                  }
                  //tree isn't empty, there are advisors available
                  if(new_advisor!=NULL){
                    //assign new advisor to the student
                    masterStudent->search(*s)->key.advisor=new_advisor->key.faculty_id;
                    //add student to new advisors advisee list
                    if(minormax==0)
                      masterFaculty->getMin()->key.ids->insertBack(s_id);
                    else if(minormax==1)
                      masterFaculty->getMax()->key.ids->insertBack(s_id);
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
            }
          }
          // else{
          //   cout<<"Faculty advisor or student advisee not found"<<endl;
          // }
          delete f;
        }
        delete s;
        pressEnter();
      }

      //Rollback
      else if(choice==13){
        rollback();
        pressEnter();
      }

      //Clear
      else if(choice==14){
        masterStudent=new BST<Student>();
        masterFaculty=new BST<Faculty>();
        cout<<"Databases have been cleared."<<endl;
        pressEnter();
      }
      //Exit
      else if(choice==15){
        clean();
        exit(0);
      }
      //did not enter a valid number
      else{
        cout<<"Entry invald. Please try again."<<endl;
        pressEnter();
      }
    }
  }

  Database(){
    in_file_s.open("studentTable", ios::in);
    in_file_f.open("facultyTable", ios::in);
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
    "14. Clear Database of all entries.\n"
    "15. Exit\n"
    "Please Enter the number of the action you want to perform.\n";

    read(in_file_s, in_file_f);

    out_file_s.open("studentTable", ios::out);
    out_file_f.open("facultyTable", ios::out);

    pull=0;
    push=1;

    prompt();
  }

  ~Database(){}

};
