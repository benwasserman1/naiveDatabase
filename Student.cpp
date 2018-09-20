/*
Ben Wasserman
2280906
wasse114@mail.chapman.edu
CPSC 350 Section 3
Assignment #5: Student and Faculty Database

Purpose of source file: This source file defines what a Student object contains,
and has some methods that allow us to manipulate student objects. That is hugely important
for the core of this program, which manipulates half Student objects.
*/

#include <iostream>
#include "Student.h"

using namespace std;

/*
This is the default constructor. It sets the attributes equal to either 0
or "none".
*/
Student::Student()
{
  id = 0;
  name = "none";
  level = "none";
  major = "none";
  gpa = 0;
  advisor = 0;
}

/*
This is the overloaded constructor. It takes in 5 parameters and defines the student with them.
Those parameters are an integer for the ID, a string for the name, a string for the level, a string for the
major, a double for the GPA, and an integer for the advisor.
*/
Student::Student(int studentId, string studentName, string studentLevel, string studentMajor, double studentGpa, int studentAdvisor)
{
  id = studentId;
  name = studentName;
  level = studentLevel;
  major = studentMajor;
  gpa = studentGpa;
  advisor = studentAdvisor;
}

/*
This is the destructor for the Student class. The objects are all handled in other
classes so there is nothing here.
*/
Student::~Student()
{
}

/*
This is an accessor method to get the ID of a student. It takes in
no parameters and returns an integer.
*/
int Student::getId()
{
  return id;
}

/*
This is an accessor method to get the name of a student. It takes in
no parameters and returns a string.
*/
string Student::getName()
{
  return name;
}

/*
This is an accessor method to get the advisor of a student. It takes in
no parameters and returns an integer.
*/
int Student::getAdvisor()
{
  return advisor;
}

/*
This is a mutator method to change the major of a student. It takes in
the new major as a string parameter. It doesn't return a value, just sets
the new major attribute.
*/
void Student::setMajor(string newMajor)
{
  major = newMajor;
}

/*
This is a mutator method to change the level of a student. It takes in
the new level as a string parameter. It doesn't return a value, just sets
the new levl attribute.
*/
void Student::setLevel(string newLevel)
{
  level = newLevel;
}

/*
This is a mutator method to change the advisor of a student. It takes in
the new advisor as an integer parameter. It doesn't return a value, just sets
the new advisor attribute.
*/
void Student::setAdvisor(int newAdvisor)
{
  advisor = newAdvisor;
}
