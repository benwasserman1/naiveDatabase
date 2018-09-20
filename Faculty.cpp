/*
Ben Wasserman
2280906
wasse114@mail.chapman.edu
CPSC 350 Section 3
Assignment #5: Student and Faculty Database

Purpose of source file: This source file defines what a Faculty object contains,
and has some methods that allow us to manipulate faculty objects. That is hugely important
for the core of this program, which manipulates half Faculty objects.
*/

#include <iostream>
#include "Faculty.h"

using namespace std;

/*
This is the default constructor. It sets the attributes equal to either 0
or "none".
*/
Faculty::Faculty()
{
  id = 0;
  name = "none";
  level = "none";
  department = "none";
  advisees.insertFront(0);
}

/*
This is the overloaded constructor. It takes in 5 parameters and defines the faculty member with them.
Those parameters are an integer for the ID, a string for the name, a string for the level, a string for the
department, and a DoublyLinkedList for the advisees.
*/
Faculty::Faculty(int facultyId, string facultyName, string facultyLevel, string facultyDepartment, DoublyLinkedList<int> studentAdvisees)
{
  id = facultyId;
  name = facultyName;
  level = facultyLevel;
  department = facultyDepartment;
  advisees = studentAdvisees;
}

/*
This is the destructor for the Faculty class. The objects are all handled in other
classes so there is nothing here.
*/
Faculty::~Faculty()
{
}

/*
This is an accessor method to get the ID of a faculty member. It takes in
no parameters and returns an integer.
*/
int Faculty::getId()
{
  return id;
}

/*
This is an accessor method to get the advisees of a faculty member. It takes
in no parameters and returns no values. It merely calls a function from
our DoublyLinkedList implementation to print the advisees.
*/
void Faculty::getAdvisees()
{
  //Loop through and use remove to get each advisee
  cout << advisees.printList();
}

/*
This is a mutator method to change the level of a faculty member. It takes in
the new level as a string parameter. It doesn't return a value, just sets
the new levl attribute.
*/
void Faculty::setLevel(string newLevel)
{
  level = newLevel;
}
