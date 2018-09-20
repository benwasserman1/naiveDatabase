#include <iostream>
#include "GenStack.h"


using namespace std;

class Menu
{
private:
  GenStack<Faculty> facultyStack;
  GenStack<Student> studentStack;
  GenStack<int> checkStack;
  // GenStack <BST <Faculty> > facultyStack;
  // GenStack <BST <Student> > studentStack;
  // GenStack <int> checkStack;
public:

  BST<Student>masterStudent;
  BST<Faculty>masterFaculty;

  Menu();
  ~Menu();
  void checkFile();
  void createStudent(int id, string name, string level, string major, double gpa, int advisor);
  void createFaculty(int id, string name, string level, string department, DoublyLinkedList<int> advisees);
  void mainMenu();
  bool controller(string input);
  void printStudents();
  void printFaculty();
  void printStudents(int id);
  void printFaculty(int id);
  void addStudent(int id);
  void addFaculty(int id);
  void rollBack();
  void deleteStudent(int id);
  void deleteFaculty(int id);
  void printAdvisor();
  void printAdvisees(int id);
  void changeAdvisor(int studentId, int facultyId);
  void removeAdvisee(int id, int idDelete);
  int generateID();
  void writeToFiles();
  void addAdvisee(int studentId, int facultyId);
  void deleteTempFaculty(int id);
  void removeTempAdvisee(int id, int idDelete);
  void deleteTempStudent(int id);
  void changeMajor();
  void changeStudentLevel();
  void changeFacultyLevel();
};
