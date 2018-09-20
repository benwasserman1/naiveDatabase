/*
Ben Wasserman
2280906
wasse114@mail.chapman.edu
CPSC 350 Section 3
Assignment #5: Student and Faculty Database

Purpose of source file: This is the heart of the program. Within Menu,
we check to see if there are any files in the directory that we can use
to read into masterStudent or masterFaculty. Then we go into the main menu
which calls a variety of functions from there that manipulate or print the
database.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include "Student.h"
#include "Faculty.h"
#include "TreeNode.h"
#include "Menu.h"
//#include "GenStack.h"

using namespace std;

/*
A few global variables are declared up here, outside the constructor.
These are used throughout the program. First we have our pointers to the TreeNodes
of type Faculty and Student. These are used to the print to the data, as they are
necessary parameters.
*/
TreeNode<Faculty> *ftree;
TreeNode<Student> *stree;



/*
This overloads the << operator when a Student object is passed in. It allows us
to print the entire student table in an easy and clean way.
*/
std::ostream &operator<<(std::ostream &os, const Student& obj)
{
  os << "ID: " << obj.id << endl << "Name: " << obj.name << endl << "Level: " << obj.level << endl << "Major: " << obj.major << endl << "GPA: " << obj.gpa << endl << "Advisor's ID: " << obj.advisor << endl;
  return os;
}

/*
This overloads the << operator when a DoublyLinkedList of integers is passed in.
It allows us to print the doubly linked list, but more importantly it formats the printing
of it so that the DoublyLinkedList portion can be easily printed in the next overloaded part.
*/
std::ostream &operator<<(std::ostream &os, const DoublyLinkedList<int>& obj)
{
  os << obj.printList();
  return os;
}

/*
This overloads the << operator when a Faculty object is passed in. It allows us to print the entire
Faculty table in an easy and clean way.
*/
std::ostream &operator<<(std::ostream &os, const Faculty& obj)
{
  os << "ID: " << obj.id << endl << "Name: " << obj.name << endl << "Level: " << obj.level << endl << "Department: " << obj.department << endl << "Advisees: " << obj.advisees << endl;
  return os;
}

/*
This was going to be used to overload the >> operator, but is no longer necessary. It can be ignored.
*/
std::istream &operator>>(std::istream &is, const Student& obj)
{
  is >> obj;
  return is;
}

/*
This is the default Menu constructor. It is also the only Menu contructor since
there aren't attributes that need to be passed in as parameters. It initializes masterStudent,
the BST that contains the student table and masterFaculty, the BST that contains the faculty table.
It also initializes the stacks that we use for the rollback command which we will see later.
*/
Menu::Menu()
{
  BST<Student> masterStudent;
  BST<Faculty> masterFaculty;
  GenStack <Faculty> facultyStack(5);
  GenStack <Student> studentStack(5);
  GenStack <int> checkStack(5);
}

/*
This is the Menu destructor. It doesn't delete anything because all the objects are cleaned up in other classes.
*/
Menu::~Menu()
{
}

/*
The function checkFile takes in no parameters and returns no value. It checks
to see if studentTable.txt or facultyTable.txt exist in the current directory, and if
they do, it reads in their contents and inputs them into masterStudent and masterFaculty.
Since the format of my database includes some labels, it does a little bit of string manipulation
and then parsing to get the actual values that it needs to input into each table.
*/
void Menu::checkFile()
{
  string line;
  int studentId;
  string studentName;
  string studentLevel;
  string studentMajor;
  double studentGpa;
  string tempAdvisor;
  int studentAdvisor;

  int facultyId;
  string facultyName;
  string facultyLevel;
  string facultyDepartment;
  string facultyAdvisee;


  string facultyTable = "facultyTable.txt";
  string studentTable = "studentTable.txt";

  ifstream inFile(facultyTable);
  ifstream inFile1(studentTable);

  //Check faculty file
  if (inFile.fail())
  {
    cout << "The faculty file is not in the directory" << endl;
  }
  else
  {
    int i = 0;
    while (getline(inFile, line))
    {
      if (i%6 == 1)
      {
        facultyId = atoi(line.substr(4).c_str());
      }
      else if (i%6 == 2)
      {
        facultyName = line.substr(6);
      }
      else if (i%6 == 3)
      {
        facultyLevel = line.substr(7);
      }
      else if (i%6 == 4)
      {
        facultyDepartment = line.substr(12);
      }
      //This part grabs each advisee and inserts them into a doubly linked list
      else if (i%6 == 5)
      {
        int k = 0;
        DoublyLinkedList<int> advisees;
        facultyAdvisee = line.substr(10);
        for (int j = 0; j < facultyAdvisee.size()/5; ++j){
          studentAdvisor = atoi(facultyAdvisee.substr(0+k, 4).c_str());
          advisees.insertFront(studentAdvisor);
          k+=6;
        }
        createFaculty(facultyId, facultyName, facultyLevel, facultyDepartment, advisees); //Creating a Faculty object
      }
      ++i;
    }
  }

  //Check student file
  if (inFile1.fail())
  {
    cout << "The student file is not in the directory" << endl;
  }
  else
  {
    int i = 0;
    while (getline(inFile1, line))
    {
      if (i%7 == 1){
        studentId = atoi(line.substr(4).c_str());
      }
      else if (i%7 == 2)
      {
        studentName = line.substr(6);
      }
      else if (i%7 == 3)
      {
        studentLevel = line.substr(7);
      }
      else if (i%7 == 4)
      {
        studentMajor = line.substr(7);
      }
      else if (i%7 ==5)
      {
        studentGpa = atof(line.substr(5).c_str());
      }
      else if (i%7 == 6)
      {
        if (line.substr(16).size() < 4)
        {
          studentAdvisor = atoi(line.substr(14).c_str());
        }
        else{
          studentAdvisor = atoi(line.substr(16).c_str());
        }
        createStudent(studentId, studentName, studentLevel, studentMajor, studentGpa, studentAdvisor); //Create student object
      }
      ++i;
    }
  }
}

/*
This function doesn't return anything but it takes all the same parameters as the overloaded Student
constructor and then it inserts the student into the table based on the ID. This is a function more for readability
than anything else.
*/
void Menu::createStudent(int id, string name, string level, string major, double gpa, int advisor)
{
  Student s(id, name, level, major, gpa, advisor);
  masterStudent.insert(s.getId(), s);
}

/*
This function doesn't return anything but it takes all the same parameters as the overloaded Faculty constructor and
then it inserts the faculty member into the table based on the ID. This is a function more for readability than anything else.
*/
void Menu::createFaculty(int id, string name, string level, string department, DoublyLinkedList<int> advisees)
{
  Faculty f(id, name, level, department, advisees);
  masterFaculty.insert(f.getId(), f);
}

/*
This is the main menu. As you can see it lays out all the options that the database
provides for manipulation, and it is constantly looped to unless the 'Exit' option is performed.
The function doesn't return anything and doesn't take in any parameters.
*/
void Menu::mainMenu()
{
  string input;
  while (true)
  {
    cout << endl << "MAIN MENU. Enter the number that corresponds to the query you would like to perform" << endl;
    cout << "1. Print all students and their information" << endl;
    cout << "2. Print all faculty and their information" << endl;
    cout << "3. Display a specific student's information" << endl;
    cout << "4. Display a specific faculty's information" << endl;
    cout << "5. Print the name and information of a student's faculty advisor" << endl;
    cout << "6. Print all the students a faculty member advises" << endl;
    cout << "7. Add a new student" << endl;
    cout << "8. Delete a student" << endl;
    cout << "9. Add a faculty member" << endl;
    cout << "10. Delete a faculty member" << endl;
    cout << "11. Change a student's advisor" << endl;
    cout << "12. Remove an advisee from a faculty member" << endl;
    cout << "13. Rollback" << endl;
    cout << "14. Exit" << endl;
    cout << "15. Change major of student" << endl;
    cout << "16. Change level of student" << endl;
    cout << "17. Change level of faculty member" << endl;
    cin >> input;
    if (controller(input) == false)
    {
      break;
    }
  }
}

/*
This function doesn't return anything and doesn't take any parameters. It assigns
a temporary Student object to the Student with the user input ID, changes the major
for that temporary object, deletes the old node, and inserts a new one with the proper major.
*/
void Menu::changeMajor()
{
  int id;
  string major;
  Student temp;
  cout << "Enter the student's ID" << endl;

  cin >> id;

  if (masterStudent.contains(id) == 0)
  {
    cout << "This student doesn't exist" << endl;
  }
  else{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout << "Enter the new major" << endl;
    getline(cin, major);
    temp = masterStudent.printSingle(id);
    temp.setMajor(major);
    deleteTempStudent(id);
    masterStudent.insert(temp.getId(), temp);
    //masterStudent.printSingle(id).setMajor(major);
  }
}

/*
This function doesn't return anything and doesn't take any parameters. It assigns
a temporary Student object to the Student with the user input ID, changes the level
for that temporary object, deletes the old node, and inserts a new one with the proper level.
*/
void Menu::changeStudentLevel()
{
  int id;
  string level;
  Student temp;
  cout << "Enter the student's ID" << endl;
  cin >> id;

  if (masterStudent.contains(id) == 0)
  {
    cout << "This student doesn't exist" << endl;
  }
  else{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout << "Enter the new level" << endl;
    getline(cin, level);
    temp = masterStudent.printSingle(id);
    temp.setLevel(level);
    deleteTempStudent(id);
    masterStudent.insert(temp.getId(), temp);
  }
}

/*
This function doesn't return anything and doesn't take any parameters. It assigns
a temporary Faculty object to the faculty member with the user input ID, changes the level
for that temporary object, deletes the old node, and inserts a new one with the proper level.
*/
void Menu::changeFacultyLevel()
{
  int id;
  string level;
  Faculty temp;
  cout << "Enter the faculty member's ID" << endl;
  cin >> id;

  if (masterFaculty.contains(id) == 0)
  {
    cout << "The faculty member doesn't exist" << endl;
  }
  else{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout << "Enter the new level" << endl;
    getline(cin, level);
    temp = masterFaculty.printSingle(id);
    temp.setLevel(level);
    deleteTempFaculty(id);
    masterFaculty.insert(temp.getId(), temp);
  }
}

/*
The function controller returns a boolean and takes a string as input. The input string
corresponds to what the user entered as their input from the main menu. The function returns
a boolean because false must be returned if the user selects exit. This breaks the loop in the main
menu. This function also calls a variety of other functions, depending on the input from the main menu.
*/
bool Menu::controller(string input)
{
  int studentId;
  int facultyId;

  if (input == "1")
  {
    printStudents();
  }
  else if (input == "2")
  {
    printFaculty();
  }
  else if (input == "3")
  {
    cout << "Enter the student's ID" << endl;
    cin >> studentId;
    printStudents(studentId);
  }

  else if (input == "4")
  {
    cout << "Enter the faculty member's ID" << endl;
    cin >> facultyId;
    printFaculty(facultyId);
  }
  else if (input == "5")
  {
    printAdvisor();
  }
  else if (input == "6")
  {
    cout << "Enter the faculty member's ID" << endl;
    cin >> facultyId;
    printAdvisees(facultyId);
  }
  else if (input == "7")
  {
    int id = generateID();
    addStudent(id);
  }
  else if (input == "8")
  {
    cout << "Enter the ID of the student that you would like to delete" << endl;
    cin >> studentId;
    checkStack.push(8);
    studentStack.push(masterStudent.printSingle(studentId));
    deleteStudent(studentId);
  }
  else if (input == "9")
  {
    int id = generateID();
    addFaculty(id);
  }
  else if (input == "10")
  {
    cout << "Enter the ID of the faculty member that you would like to delete" << endl;
    cin >> facultyId;
    checkStack.push(10);
    facultyStack.push(masterFaculty.printSingle(facultyId));
    deleteFaculty(facultyId);
  }
  else if (input == "11")
  {
    cout << "Enter the ID of the student" << endl;
    cin >> studentId;
    cout << "Enter the ID of the new faculty advisor" << endl;
    cin >> facultyId;
    changeAdvisor(studentId, facultyId);
  }
  else if (input == "12")
  {
    cout << "Enter the faculty member's ID" << endl;
    cin >> facultyId;
    cout << "Enter the ID of the student you would like to remove" << endl;
    cin >> studentId;
    checkStack.push(12);
    facultyStack.push(masterFaculty.printSingle(facultyId));
    removeAdvisee(facultyId, studentId);
  }
  else if (input == "13")
  {
    rollBack();
  }
  else if (input == "14")
  {
    writeToFiles();
    return false;
  }
  else if (input == "15")
  {
    changeMajor();
  }
  else if (input == "16")
  {
    changeStudentLevel();
  }
  else if (input == "17")
  {
    changeFacultyLevel();
  }
  else
  {
    cout << "IMPROPER INPUT. Enter a new menu command" << endl;
    return true;
  }
  return true;
}

/*
The function printStudents takes in no parameters and returns no value. It merely
prints a simple labeling statement and then prints the entire studentTable by calling
printTree.
*/
void Menu::printStudents()
{
  cout << endl << "Here are all the students:" << endl << endl;
  cout << masterStudent.printTree(stree);
}

/*
The function printFaculty takes in no parameters and returns no value. It merely
prints a simple labeling statement and then prints the entire FacyTable by calling
printTree.
*/
void Menu::printFaculty()
{
  cout << endl << "Here are all the faculty:" << endl << endl;
  cout << masterFaculty.printTree(ftree);
}

/*
The function printStudents takes in an integer, id, and returns no value. It overloads the
previous printStudents function. It checks to see if the id entered by the user matches
one of the ID's in thte table, and if it does, that student's info is printed using the
function printSingle from TreeNode.h.
*/
void Menu::printStudents(int id)
{
  string menu;
  if (masterStudent.contains(id) == 0)
  {
    cout << "Couldn't find the student. Try a different ID or enter 0 to return to the main menu" << endl;
    cin >> menu;
    if (menu == "0")
    {
      mainMenu();
    }
    else{
      controller("3");
    }
  }
  else
  {
    cout << endl << masterStudent.printSingle(id) << endl;
  }
}

/*
The function printFaculty takes in an integer, id, and returns no value. It overloads the
previous printFaculty function. It checks to see if the id entered by the user matches
one of the ID's in the table, and if it does, that faculty member's info is printed using the
function printSingle from TreeNode.h.
*/
void Menu::printFaculty(int id)
{
  string menu;
  cout << endl;
  if (masterFaculty.contains(id) == 0)
  {
    cout << "Couldn't find the faculty member. Try a different ID or enter 0 to return to the main menu" << endl;
    cin >> menu;
    if (menu == "0")
    {
      mainMenu();
    }
    else{
      controller("4");
    }
  }
  else
  {
    cout << masterFaculty.printSingle(id) << endl;
  }
}

/*
The function addStudent take in an id that was generated in the controller method.
It doesn't return anything. The function takes in all the user input for the attributes
of the student, creates a student object, and inserts that student into masterStudent. However,
it also must then add the student ID to whatever advisor the user input. Finally, since this
function alters the database, it must push an instance of what it did to the stack that allows
us to undo commands.
*/
void Menu::addStudent(int id)
{
  string name;
  string level;
  string major;
  double gpa;
  int advisor;

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  cout << "Enter name" << endl;
  getline(cin, name);

  cout << "Enter level" << endl;
  getline(cin, level);

  cout << "Enter major" << endl;
  getline(cin, major);

  cout << "Enter gpa" << endl;
  cin >> gpa;

  while (true)
  {
    cout << "Enter advisor" << endl;
    cin >> advisor;
    if (advisor == 0)
    {
      break;
    }
    else if (masterFaculty.contains(advisor) != 0)
    {
      break;
    }
    cout << "The faculty member doesn't exist. Enter a new one or press 0 to exit" << endl;
  }
  Student s(id, name, level, major, gpa, advisor);
  masterStudent.insert(s.getId(), s);
  checkStack.push(7);
  studentStack.push(masterStudent.printSingle(id));
  addAdvisee(id, advisor); //This is adding an advisee to a faculty member
}

/*
The function addFaculty take in an id that was generated in the controller method.
It doesn't return anything. The function takes in all the user input for the attributes
of the faculty member, creates a faculty object, and inserts that into masterFaculty. However,
it also must then add the faculty ID to whatever advisees the user input. Finally, since this
function alters the database, it must push an instance of what it did to the stack that allows
us to undo commands.
*/
void Menu::addFaculty(int id)
{
  string name;
  string level;
  string department;
  int tempID;
  DoublyLinkedList<int> advisees;

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  cout << "Enter name" << endl;
  getline(cin, name);

  cout << "Enter level" << endl;
  getline(cin, level);

  cout << "Enter department" << endl;
  getline(cin, department);

  cout << "Enter each student advisee's ID number and press 0 to exit once they've been input" << endl;
  while (true)
  {
    cout << "Enter the id or press 0 to exit" << endl;
    cin >> tempID;

    if (tempID == 0)
    {
      break;
    }
    else if (masterStudent.contains(tempID) == 0)
    {
      cout << "This student doesn't exist. Enter another ID. Or press 0 if they don't have any advisees" << endl;
    }
    else
    {
      advisees.insertFront(tempID);
    }
  }
  Faculty f(id, name, level, department, advisees);
  masterFaculty.insert(f.getId(), f);
  checkStack.push(9);
  facultyStack.push(masterFaculty.printSingle(id));
  //What if the student has a different advisor - should change the advisor!!!
}

/*
This function takes in no parameters and doesn't return anything. It first checks
to see if the stack is empty, and then checks to see what's at the top of the stack.
Depending on what's popped from the stack, certain reversal functions are prompted to undo
the last command.
*/
void Menu::rollBack()
{
  if (checkStack.isEmpty())
  {
    cout << "You can't undo any more operations" << endl;
  }
  else if (checkStack.peek() == 7)
  {
    checkStack.pop();
    Student temp = studentStack.pop();
    //masterStudent.deleteNode(temp.getId());
    deleteStudent(temp.getId());
  }
  else if (checkStack.peek() == 9)
  {
    checkStack.pop();
    Faculty temp = facultyStack.pop();
    //masterFaculty.deleteNode(temp.getId());
    deleteFaculty(temp.getId());
  }
  else if (checkStack.peek() == 10)
  {
    checkStack.pop();
    Faculty temp = facultyStack.pop();
    masterFaculty.insert(temp.getId(), temp);
  }
  else if (checkStack.peek() == 8)
  {
    checkStack.pop();
    Student temp = studentStack.pop();
    masterStudent.insert(temp.getId(), temp);
  }
  else if (checkStack.peek() == 12)
  {
    checkStack.pop();
    Faculty temp = facultyStack.pop();
    deleteTempFaculty(temp.getId());
    masterFaculty.insert(temp.getId(), temp);
  }
  else{
    cout << "ERROR" << endl;
  }
}

/*
This function takes in an integer, id, and doesn't return a value. It starts by
checking if the student exists, and then it deletes the student from the database, and calls
a function that removes the advisee from faculty member that student corresponded with.
*/
void Menu::deleteStudent(int id)
{
  Student temp;
  int advisor;
  if (masterStudent.contains(id) == 0)
  {
    cout << "This student doesn't exist" << endl;
  }
  else
  {
    temp = masterStudent.printSingle(id);
    advisor = temp.getAdvisor();
    masterStudent.deleteNode(id);
    removeTempAdvisee(advisor, id); //Check that this all works
  }
}

/*
This function takes in an integer, id, as a parameter and doesn't return anything. It
is very similar to the previous function except it deosn't call the function that removes
the advisee. This is because we would have circular logic in certain cases if it did.
*/
void Menu::deleteTempStudent(int id)
{
  Student temp;
  int advisor;
  if (masterStudent.contains(id) == 0)
  {
    cout << "This student doesn't exist" << endl;
  }
  else
  {
    temp = masterStudent.printSingle(id);
    advisor = temp.getAdvisor();
    masterStudent.deleteNode(id);
  }
}

/*
This function takes in an integer, id, as a parameter. It doesn't return anything.
The function checks to see if the faculty member exists and deletes that node from
the database if it does. From there, it prompts the user to enter new advisor's for
all the advisees that the we're also deleted when the faculty member was deleted.
*/
void Menu::deleteFaculty(int id)
{
  Faculty temp;
  DoublyLinkedList<int> advisees;
  if (masterFaculty.contains(id) == 0)
  {
    cout << "This faculty member doesn't exist" << endl;
  }
  else
  {
    temp = masterFaculty.printSingle(id);
    masterFaculty.deleteNode(id);
    int newAdvisor;
    int student;
    for (int i =0; i < temp.advisees.getSize(); ++i)
    {
      student = temp.advisees.removeFront();
      cout << "New advisor ID for student " << student << endl;
      cin >> newAdvisor;
      changeAdvisor(student, newAdvisor);
    }
  }
}

/*
This function takes in an integer, id, as a parameter. It doesn't return anything.
The function checks to see if the faculty member exists and deletes that node from
the database if it does. It is very similar to the last except it doesn't mess with
advisees in order to avoid circular logic in specific cases.
*/
void Menu::deleteTempFaculty(int id)
{
  Faculty temp;
  DoublyLinkedList<int> advisees;
  if (masterFaculty.contains(id) == 0)
  {
    cout << "This faculty member doesn't exist" << endl;
  }
  else
  {
    temp = masterFaculty.printSingle(id);
    masterFaculty.deleteNode(id);
  }
}

/*
This function takes no parameters and doesn't return a value. It takes
a student ID as input from the user and then uses this value to get the advisor's ID, which
the function uses to print all the information about the advisor.
*/
void Menu::printAdvisor()
{
  int id;
  int advisor;
  cout << "Enter the ID of the student" << endl;
  cin >> id;
  if (masterStudent.contains(id) == 0)
  {
    cout << "This student doesn't exist" << endl;
  }
  else
  {
    Student temp;
    temp = masterStudent.printSingle(id);
    advisor = temp.getAdvisor();
    cout << endl << "That student's advisor: " << endl << endl;
    cout << masterFaculty.printSingle(advisor) << endl;
  }
}

/*
This function takes in an integer, id, as a parameter and doesn't return anything.
It checks to see that the integer does truly correspond to a faculty member's ID first.
From there, it gets all the advisees from the faculty members and uses the function
printSingle to print the information of the corresponding students from masterStudent.
*/
void Menu::printAdvisees(int id)
{
  DoublyLinkedList<int> advisees;
  if (masterFaculty.contains(id) == 0)
  {
    cout << "This faculty member doesn't exist" << endl;
  }
  else
  {
    Faculty temp;
    int listObject;
    temp = masterFaculty.printSingle(id);
    for (int i = 0; i < temp.advisees.getSize(); i++)
    {
      listObject = temp.advisees.removeFront();
      cout << endl;
      cout << masterStudent.printSingle(listObject);
    }
  }
}

/*
The function changeAdvisor takes two integers as parameters, the student ID and the faculty ID.
It doesn't return anything. First it checks to see that both ID's are valid. From there, the function
sets a new value for the advisor and removes the advisee from the previous advisor. Lastly, the function
calls a addAdvisee which allows for a new advisee to be added.
*/
void Menu::changeAdvisor(int studentId, int facultyId)
{
  if (masterStudent.contains(studentId) == 0)
  {
    cout << "This student doesn't exist" << endl;
  }
  else if (masterFaculty.contains(facultyId) == 0)
  {
    cout << "This faculty member doesn't exist" << endl;
  }
  else{ //might not need to do all this temp bullshit
    Student temp;
    temp = masterStudent.printSingle(studentId);
    temp.setAdvisor(facultyId);
    removeTempAdvisee(facultyId, studentId);
    deleteTempStudent(studentId);
    masterStudent.insert(temp.getId(), temp);
    addAdvisee(studentId, facultyId);
  }
}

/*
This function takes in two integer parameters. One is the ID that of the advisee
that we want to get rid of, and the other is the ID of the advisor. The function
removes the advisee from the DoublyLinkedList.
*/
void Menu::removeTempAdvisee(int id, int idDelete)
{
  int newAdvisor;
  DoublyLinkedList<int> advisees;
  if (masterFaculty.contains(id) == 0)
  {
    cout << "This faculty member doesn't exist" << endl;
  }
  else
  {
    Faculty temp;
    temp = masterFaculty.printSingle(id);
    temp.advisees.remove(idDelete);
    deleteTempFaculty(id);
    masterFaculty.insert(temp.getId(), temp);
  }
}

/*
This function takes in two integer parameters. One is the ID that of the advisee
that we want to get rid of, and the other is the ID of the advisor. The function
removes the advisee from the DoublyLinkedList. Lastly, this function allows a new
advisor to be appointed to the deleted advisee.
*/
void Menu::removeAdvisee(int id, int idDelete)
{
  int newAdvisor;
  DoublyLinkedList<int> advisees;
  if (masterFaculty.contains(id) == 0)
  {
    cout << "This faculty member doesn't exist" << endl;
  }
  else
  {
    Faculty temp;
    temp = masterFaculty.printSingle(id);
    //masterFaculty.printSingle(id).advisees.remove(idDelete);
    temp.advisees.remove(idDelete);
    deleteTempFaculty(id);
    masterFaculty.insert(temp.getId(), temp);
    cout << "The student with the ID " << idDelete << " no longer has an advisor. Enter a new advisor's ID for that student" << endl;
    cin >> newAdvisor;
    changeAdvisor(idDelete, newAdvisor);
  }
}

/*
This function takes in two integer parameters, studentId and facultyId. It doesn't
return anything. The function merely adds an advisee to the doubly linked list, which
is an object of each Faculty member. It is a helper method for a lot of other functions.
*/
void Menu::addAdvisee(int studentId, int facultyId)
{
  DoublyLinkedList<int> advisees;
  if (masterFaculty.contains(facultyId) == 0)
  {
    cout << "This faculty member doesn't exist" << endl;
  }
  else
  {
    Faculty temp;
    temp = masterFaculty.printSingle(facultyId);
    temp.advisees.insertFront(studentId);
    deleteTempFaculty(facultyId);
    masterFaculty.insert(temp.getId(), temp);
  }
}

/*
The function generateID doesn't take any parameters but it returns an integer.
it uses the rand function to generate a random number between 1000 and 6000. It double checks
to make sure these ID's aren't already in the database, and then returns the ID.
*/
int Menu::generateID()
{
  int id;
  srand(time(NULL));
  id = rand() % 5000 + 1000;
  if (masterFaculty.contains(id) == 1)
  {
    generateID();
  }
  else if  (masterStudent.contains(id) == 1)
  {
    generateID();
  }
  return id;
}

/*
This function is called when the program is exited. It doesn't take any input as parameters
and it doesn't return anything. It merely calls two functions that were designed to write the databases
to their respective studentTable and facultyTable files.
*/
void Menu::writeToFiles()
{
  //Write out the faculty DB
  masterFaculty.filePrintFacTree(ftree);

  //Write out the student DB
  masterStudent.filePrintStudTree(stree);
}
