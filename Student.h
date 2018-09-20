#include <iostream>

using namespace std;

class Student
{
private:
  // int id;
  // string name;
  // string level;
  // string major;
  // double gpa;
  // int advisor;

public:
  int id;
  string name;
  string level;
  string major;
  double gpa;
  int advisor;

  Student();
  Student(int id, string name, string level, string major, double gpa, int advisor);
  ~Student();
  int getId();
  string getName();
  int getAdvisor();
  void setAdvisor(int newAdvisor);
  void setLevel(string level);
  void setMajor(string major);

  /*
  This overloads the assignment operator for Student objects. It allows us
  to set temporary Student objects equal to their counterparts.
  */
  Student operator = (const Student &obj)
  {
    id = obj.id;
    name = obj.name;
    level = obj.level;
    major = obj.major;
    gpa = obj.gpa;
    advisor = obj.advisor;
    return *this;
  }
};
