#include <iostream>
#include "ListNode copy.h"

using namespace std;

class Faculty
{
public:

  int id;
  string name;
  string level;
  string department;
  DoublyLinkedList<int> advisees;

  ~Faculty();
  Faculty();
  Faculty(int id, string name, string level, string department, DoublyLinkedList<int> studentAdvisees);
  int getId();
  void getAdvisees();
  void setLevel(string level);

  /*
  This overloads the assignment operator for faculty objects so that we can set temporary values equal
  to Faculty objects.
  */
  Faculty operator = (const Faculty &obj)
  {
    id = obj.id;
    name = obj.name;
    level = obj.level;
    department = obj.department;
    advisees = obj.advisees;
    return *this;
  }
};
